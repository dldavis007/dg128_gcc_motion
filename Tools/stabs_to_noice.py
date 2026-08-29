"""Convert GCC/ELF STABS source records into a NoICE command file.

This is intentionally small and compatible with the Python 3 installation used
by the Windows build scripts.  The ELF remains the source for executable bytes,
symbols and types; this file supplies the source/function/line associations that
NoICE 9.8 does not reliably import from this old GCC toolchain.
"""

import os
import re
import subprocess
import sys


STAB_RE = re.compile(
    r"^\s*\d+\s+(SO|FUN|SLINE)\s+\d+\s+(\d+)\s+([0-9A-Fa-f]+)\s+\d+\s*(.*)$"
)
NM_RE = re.compile(r"^\s*([0-9A-Fa-f]+)\s+[A-Za-z]\s+(\S+)\s*$")

ESSENTIAL_WATCHES = [
    ("NoICE_VuartDroppedRecords", "%U16"),
    ("ProxInputRaw", "%U08"),
    ("ProxInputStable", "%U08"),
    ("ProxEdgeCount", "%U32"),
    ("ProxLastEdgeMs", "%U32"),
    ("ProxLastRiseMs", "%U32"),
    ("ProxPeriodMs", "%U32"),
    ("ProxLastIntervalMs", "%U32"),
    ("ProxHighTimeMs", "%U32"),
    ("ProxLowTimeMs", "%U32"),
    ("ProxPeriodValid", "%U08"),
    ("ProxLastIntervalWasHigh", "%U08"),
    ("ProxHighFractionExtendX1000", "%U16"),
    ("ProxHighFractionRetractX1000", "%U16"),
    ("ProxHighFractionExtendValid", "%U08"),
    ("ProxHighFractionRetractValid", "%U08"),
    ("ProxStopped", "%U08"),
    ("Tick1msCount", "%U32"),
    ("Tick10msCount", "%U32"),
    ("StartupPassed", "%X08"),
    ("MotorTestDutyPercent", "%S08"),
    ("MotorTestArm", "%X08"),
    ("MotorTestStatus", "%U08"),
    ("MotorTestTimeoutMs", "%U32"),
    ("MotorTestElapsedMs", "%U32"),
    ("MotorOutputsEnabled", "%U08"),
    ("MotorEnableFeedback", "%U08"),
    ("MotionTestArm", "%X08"),
    ("MotionState", "%U08"),
    ("MotionCycle", "%U08"),
    ("MotionFault", "%U08"),
    ("MotionPositionCount", "%S32"),
    ("MotionTargetCount", "%S32"),
    ("MotionCommandDuty", "%S08"),
    ("MotionPositionErrorCounts", "%S16"),
    ("MotionSpeedCommandX100", "%S16"),
    ("MotionMeasuredSpeedX100", "%S16"),
    ("MotionSpeedErrorX100", "%S16"),
    ("MotionSpeedIntegralX100", "%S16"),
    ("CoatingTestArm", "%X08"),
    ("CoatAutomaticActive", "%U08"),
    ("CoatOperation", "%U08"),
    ("CoatStrokeNumber", "%U08"),
    ("CoatStrokeTotal", "%U08"),
    ("CoatDirectionExtend", "%U08"),
    ("CoatTargetTenths", "%U08"),
    ("CoatSpeedPercent", "%U08"),
    ("SimCanPositionTenths", "%U08"),
    ("SimCanSpeedPercent", "%U08"),
    ("SimCanCommandPending", "%U08"),
    ("SimCanMoving", "%U08"),
    ("SimCanFault", "%U08"),
    ("CoatActuatorLengthTenths", "%U08"),
    ("CoatShortStrokeCount", "%U08"),
    ("CoatShortLengthTenths", "%U08"),
    ("CoatLongStrokeCount", "%U08"),
    ("CoatLongLengthTenths", "%U08"),
    ("CoatPositioningSpeedPercent", "%U08"),
    ("CoatHomingSpeedPercent", "%U08"),
    ("CoatFastStrokeCount", "%U08"),
    ("CoatShortFastSpeedPercent", "%U08"),
    ("CoatShortSlowSpeedPercent", "%U08"),
    ("CoatLongFastSpeedPercent", "%U08"),
    ("CoatLongSlowSpeedPercent", "%U08"),
    ("CoatFeedbackCountsPerInchX100", "%U16"),
    ("CoatMotorMaxSpeedCountsX100", "%U16"),
    ("CoatSimHomeDelayMs", "%U32"),
]


def noice_hex(value):
    """Return an unambiguous NoICE hexadecimal address expression."""
    return "0%XH" % value


def matching_nm_path(objdump):
    """Return the nm program beside the supplied objdump program."""
    directory, filename = os.path.split(objdump)
    lower = filename.lower()
    marker = lower.rfind("objdump")
    if marker < 0:
        return "m6811-elf-nm"
    filename = filename[:marker] + "nm" + filename[marker + len("objdump"):]
    return os.path.join(directory, filename) if directory else filename


def read_global_symbols(objdump, elf_path):
    """Read globally visible ELF symbols for a reconnect-without-load file."""
    nm = matching_nm_path(objdump)
    text = subprocess.check_output(
        [nm, "-g", elf_path],
        stderr=subprocess.STDOUT,
        universal_newlines=True,
    )
    symbols = {}
    for raw_line in text.splitlines():
        match = NM_RE.match(raw_line)
        if match:
            address, name = match.groups()
            symbols[name] = int(address, 16)
    return symbols


def main():
    if len(sys.argv) not in (5, 6):
        print("usage: stabs_to_noice.py OBJDUMP ELF SOURCE OUTPUT [SESSION_OUTPUT]")
        return 2

    objdump, elf_path, source_path, output_path = sys.argv[1:5]
    session_output_path = sys.argv[5] if len(sys.argv) == 6 else None
    elf_path = os.path.abspath(elf_path)
    source_path = os.path.abspath(source_path)
    output_path = os.path.abspath(output_path)

    try:
        text = subprocess.check_output(
            [objdump, "--stabs", elf_path],
            stderr=subprocess.STDOUT,
            universal_newlines=True,
        )
    except (OSError, subprocess.CalledProcessError) as exc:
        print("[ERROR] could not read STABS records: %s" % exc)
        return 1

    commands = [
        "; Generated from %s - do not edit" % os.path.basename(elf_path),
        "; Load the ELF first, then PLAY this file in NoICE.",
    ]
    current_start = None
    source_directory = os.path.dirname(source_path)
    function_count = 0
    line_count = 0

    for raw_line in text.splitlines():
        match = STAB_RE.match(raw_line)
        if not match:
            continue

        record, desc_text, value_text, string = match.groups()
        value = int(value_text, 16)

        if record == "SO" and string:
            if string.endswith("/") or string.endswith("\\"):
                source_directory = string
            else:
                if os.path.isabs(string):
                    active_source = string
                else:
                    active_source = os.path.join(source_directory, string)
                commands.append("FILE \"%s\"" % os.path.normpath(active_source))

        elif record == "FUN":
            if string:
                name = string.split(":", 1)[0]
                type_marker = string.split(":", 1)[1][:1] if ":" in string else "F"
                current_start = value
                if type_marker == "f":
                    # STATICFUNCTION creates source/function scope, but NoICE
                    # 9.8 does not create an expression symbol for it.  Its
                    # source-selection window later evaluates file.c#name and
                    # reports "No such symbol" unless the file-scoped symbol
                    # is declared separately.  DEFS is issued while FILE is
                    # still the active scope, before entering function scope.
                    commands.append("DEFS %s %s" % (name, noice_hex(value)))
                    commands.append("STATICFUNCTION %s %s" % (name, noice_hex(value)))
                else:
                    commands.append("FUNCTION %s %s" % (name, noice_hex(value)))
                function_count += 1
            elif current_start is not None:
                commands.append("ENDFUNCTION %s" % noice_hex(current_start + value))
                current_start = None

        elif record == "SLINE" and current_start is not None:
            line_number = int(desc_text, 10)
            commands.append("LINE %d %s" % (line_number, noice_hex(current_start + value)))
            line_count += 1

    commands.append("MODE 2")
    commands.append("SOURCE PC")

    if function_count == 0 or line_count == 0:
        print("[ERROR] no usable function/line records found in %s" % elf_path)
        return 1

    with open(output_path, "w", newline="\r\n") as output:
        output.write("\n".join(commands))
        output.write("\n")

    print(
        "Generated %s with %d functions and %d source lines."
        % (output_path, function_count, line_count)
    )

    if session_output_path:
        session_output_path = os.path.abspath(session_output_path)
        watch_output_path = os.path.splitext(session_output_path)[0] + "_watches.noi"
        if session_output_path.lower().endswith("_debug.noi"):
            reconnect_output_path = session_output_path[:-len("_debug.noi")] + "_reconnect.noi"
        else:
            reconnect_output_path = os.path.splitext(session_output_path)[0] + "_reconnect.noi"

        # The complete debugger-facing diagnostic/menu set is loaded at startup.
        # A 250 ms refresh has loaded the expanded list successfully. Disable
        # timed refresh while playing it if a particular NoICE session is unstable.
        session_commands = [
            "; Generated NoICE debug session - do not edit",
            "LOAD \"%s\"" % elf_path,
        ]
        session_commands.extend(commands[2:])
        session_commands.append("W -")
        session_commands.extend("W %s %s" % item for item in ESSENTIAL_WATCHES)
        session_commands.extend(["MODE 2", "SOURCE PC"])
        with open(session_output_path, "w", newline="\r\n") as session_output:
            session_output.write("\n".join(session_commands))
            session_output.write("\n")
        print("Generated NoICE session %s." % session_output_path)

        try:
            symbols = read_global_symbols(objdump, elf_path)
        except (OSError, subprocess.CalledProcessError) as exc:
            print("[ERROR] could not read ELF globals for reconnect file: %s" % exc)
            return 1

        reconnect_commands = [
            "; Generated NoICE reconnect session - does NOT load target memory",
            "; Use only when the target contains this exact build.",
        ]
        reconnect_commands.extend(commands[2:])
        missing = []
        for name, display_type in ESSENTIAL_WATCHES:
            address = symbols.get(name)
            if address is None:
                address = symbols.get("_" + name)
            if address is None:
                missing.append(name)
            else:
                reconnect_commands.append(
                    "DEFINE %s %s %s" % (name, noice_hex(address), display_type)
                )
        if missing:
            print("[ERROR] missing reconnect symbols: %s" % ", ".join(missing))
            return 1
        reconnect_commands.append("W -")
        reconnect_commands.extend("W %s %s" % item for item in ESSENTIAL_WATCHES)
        reconnect_commands.extend(["MODE 2", "SOURCE PC"])
        with open(reconnect_output_path, "w", newline="\r\n") as reconnect_output:
            reconnect_output.write("\n".join(reconnect_commands))
            reconnect_output.write("\n")
        print("Generated NoICE no-load reconnect session %s." % reconnect_output_path)

        # Retain the standalone watch file as a convenient way to restore the
        # same authoritative list without reloading the ELF.  Generate it from
        # ESSENTIAL_WATCHES so it cannot drift from the startup session.
        watch_commands = [
            "; Complete NoICE diagnostic watches - safe to PLAY after startup",
            "W -",
        ]
        watch_commands.extend("W %s %s" % item for item in ESSENTIAL_WATCHES)
        with open(watch_output_path, "w", newline="\r\n") as watch_output:
            watch_output.write("\n".join(watch_commands))
            watch_output.write("\n")
        print("Generated optional NoICE watches %s." % watch_output_path)

    return 0


if __name__ == "__main__":
    sys.exit(main())
