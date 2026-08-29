"""Overlay DG128/NoICE and PC motion telemetry CSV files."""

import csv
import sys

import matplotlib.pyplot as plt


REQUIRED_HEADER = "ms,state,cycle,position,target,speed_cmd_x100,speed_fb_x100,duty,fault,dropped"


def load_csv(path):
    with open(path, "r", newline="") as source:
        lines = source.readlines()

    start = None
    for index, line in enumerate(lines):
        if line.strip() == REQUIRED_HEADER:
            start = index
            break
    if start is None:
        raise ValueError("CSV header not found in %s" % path)

    rows = []
    reader = csv.DictReader(lines[start:])
    for row in reader:
        if row.get("ms", "").strip() in ("", "ms"):
            continue
        try:
            rows.append({name: int(row[name]) for name in reader.fieldnames})
        except (KeyError, TypeError, ValueError):
            continue
    if not rows:
        raise ValueError("No telemetry records found in %s" % path)

    first_ms = rows[0]["ms"]
    for row in rows:
        row["seconds"] = (row["ms"] - first_ms) / 1000.0
    return rows


def values(rows, name, scale=1.0):
    return [row[name] / scale for row in rows]


def plot_set(axes, rows, label, color, linestyle):
    time = values(rows, "seconds")
    axes[0].plot(time, values(rows, "position"), linestyle, color=color,
                 label=label + " position")
    axes[0].plot(time, values(rows, "target"), ":", color=color,
                 label=label + " target")
    axes[1].plot(time, values(rows, "speed_cmd_x100", 100.0), linestyle,
                 color=color,
                 label=label + " command")
    axes[1].plot(time, values(rows, "speed_fb_x100", 100.0), "--",
                 color=color,
                 label=label + " feedback")
    axes[2].plot(time, values(rows, "duty"), linestyle, color=color,
                 label=label + " duty")


def main():
    embedded_path = sys.argv[1] if len(sys.argv) > 1 else "motion_embedded.csv"
    pc_path = sys.argv[2] if len(sys.argv) > 2 else "motion_pc.csv"
    output_path = sys.argv[3] if len(sys.argv) > 3 else "motion_comparison.png"

    embedded = load_csv(embedded_path)
    pc = load_csv(pc_path)
    figure, axes = plt.subplots(3, 1, figsize=(12, 9), sharex=True)
    plot_set(axes, embedded, "Embedded", "tab:blue", "-")
    plot_set(axes, pc, "PC", "tab:orange", "-.")
    axes[0].set_ylabel("Prox counts")
    axes[1].set_ylabel("Counts/second")
    axes[2].set_ylabel("Duty (%)")
    axes[2].set_xlabel("Seconds from first record")
    for axis in axes:
        axis.grid(True, alpha=0.3)
        axis.legend(loc="best")
    figure.suptitle("DG128 Hardware versus PC Motion Control")
    figure.tight_layout()
    figure.savefig(output_path, dpi=150)

    dropped = max(values(embedded, "dropped"))
    print("Saved %s" % output_path)
    print("Embedded records: %d; PC records: %d; dropped: %d" %
          (len(embedded), len(pc), dropped))
    if dropped != 0:
        print("Increase MOTION_TELEMETRY_PERIOD_MS before the next test.")


if __name__ == "__main__":
    main()
