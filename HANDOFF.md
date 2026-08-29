# DG128 GCC Motion Project — Programmer Handoff

## Purpose and current status

This project proves that GNU GCC can build working C89 firmware for an
MC9S12DG128 and that the important control code can also run unchanged in a PC
simulation.  It has been tested on the physical DG128 using NoICE and a P&E BDM
interface.  The bench hardware completed two extend/retract cycles using a PP4
GPIO proximity input and an L6203 motor driver, returning to position zero with
no fault.  The PC version completed the equivalent test.

The simulated-CAN coating application has completed the short/long stroke
pattern on the physical DG128 with zero motion fault and zero dropped records.
The new both-edge/asymmetry-compensation revision passes strict C89 host linkage
and all PC scenarios, but still requires its first HC12 build/map review and
controlled bench run.

Current tuning is:

```c
POSITION_KP_X100          250
SPEED_KP_GAIN               5
SPEED_KI_STEP_GAIN          2
INTEGRAL_LIMIT_X100      1500  /* PI integral contribution limited to +/-15% */
MAX_SPEED_X100            600  /* Same physical speed as former 3.00 rising/s */
REVERSAL_PAUSE_MS         100
MOTION_TELEMETRY_PERIOD_MS 250
OUTWARD_TARGET_COUNTS      98
TEST_CYCLES                 2
MAX_DUTY_PERCENT           95
MIN_DUTY_PERCENT           10
```

Speed diagnostics use doubled both-edge units. The controller divides speed
error by two before applying `SPEED_KP_GAIN` and `SPEED_KI_STEP_GAIN`, so the
listed 5/2 values retain the original physical loop response.

## Architecture

The design separates portable application/control logic from platform code.
Root-level batch and shell files are launchers, so the familiar build commands
do not change when source files move between platform folders.

Shared by PC and embedded builds:

- `common/include/motion_sequence.h`, `common/src/motion_sequence.c` — state machine,
  position P loop, speed PI loop, timeouts, cycle handling and signed duty.
- `common/include/motion_csv.h`, `common/src/motion_csv.c` — identical compact CSV telemetry
  format using C89-compatible integer formatting.
- `common/include/coating_cycle.h`, `common/src/coating_cycle.c` — menu settings and coating
  scheduler that emits two-byte point-move commands; compiled by PC and DG128.
- `common/include/coating_csv.h`, `common/src/coating_csv.c` — C89 event telemetry shared by
  the embedded simulated-CAN test.

DG128 platform:

- `embedded/src/dg128_smoke.c` — PLL, 1 ms timer ISR, PP4 prox qualification, prox-period
  speed calculation, PWM/L6203 control, motion service and telemetry scheduling.
- `embedded/src/noice_vuart.c` — nonblocking BDM Virtual UART queue.
- `embedded/src/dg128_startup.S`, `embedded/src/dg128_vectors.S` — startup and vectors.
- `embedded/include/` — DG128 registers and embedded-only interfaces.
- `embedded/linker/dg128_fixed.x` — DG128 fixed-memory layout.

PC platform:

- `pc/src/motion_sequence_pc.c` — 1 ms simulated clock, motor inertia model,
  simulated prox pulses, console report and `motion_pc.csv` output.
- `pc/src/can_coating_pc.c` — simulated CAN process image, unknown-position home,
  point moves, coating scheduler, moving/fault status and `can_coating_pc.csv`.

The essential interface is:

```c
MotionSequence_Step(&sequence, now_ms, position, measured_speed_x100);
```

The embedded platform obtains the arguments from hardware.  The PC platform
obtains them from the simulator.  Both consume `sequence.duty_command`.

For production-style single moves, use:

```c
MotionMove_Start(&sequence, now_ms, position,
                 target_counts, speed_limit_x100);
MotionMove_Step(&sequence, now_ms, position, measured_speed_x100);
```

The CAN model receives position in 0.1-inch units and speed in percent. The
platform converts these into target prox counts and a counts/second x100 speed
limit. CANopen processing belongs in the DG128 platform layer; the portable
controller does not know about PDOs or object dictionaries.

## Hardware mapping used by the bench test

- MC9S12DG128, 8 MHz crystal, 24 MHz bus.
- PP0/PWM0 -> L6203 IN1.
- PP1/PWM1 -> L6203 IN2.
- PA1 -> filtered L6203 ENABLE command.
- PP3 -> ENABLE feedback input.
- PP4 -> prox input, polled as GPIO every 1 ms.
- Prox produces nine tooth cycles and 18 qualified edges per revolution.
- Position counts both edges. Speed learns separate extend/retract high-time
  fractions from full cycles and normalizes every high and low interval.
- Direction is inferred from the commanded motor direction because this is a
  single-channel prox.  The final product is expected to use PA6 or PB6 GPIO.
- No encoder capture ISR, vector, globals or PC encoder simulation remain in
  this project. Feedback is deliberately proximity-only.

## Toolchains and builds

### PC motion test

Requirements: ordinary PC GCC on PATH.

```bat
build_motion_pc.bat
```

This compiles `motion_sequence.c`, `motion_csv.c` and
`motion_sequence_pc.c`, runs two cycles, prints a human-readable report and
creates `motion_pc.csv` at 250 ms resolution.

The shell equivalent is:

```sh
./build_motion_pc.sh
```

### PC CAN/coating test

```bat
build_can_coating_pc.bat
```

This builds the portable point-to-point move API, coating scheduler and PC CAN
process-image simulation. The two simulated receive bytes are absolute position
in tenths of an inch and speed in percent. The receive layer raises `moving`
until the requested target is reached or passed, then clears it. A 100 ms gap
represents the supervising unit observing that clear before issuing the next
command.

Default menu settings are 10.0-inch actuator travel, four centered 4.0-inch
short passes and four centered 10.0-inch long passes. A stroke count is one
directional pass and the first coating pass extends. Direction alternates after
every pass and is explicitly checked at the short-to-long transition. The first
two passes in each group run fast and the remaining two run slow.

Run `build_can_coating_pc.bat short-zero`, `long-zero`, or `both-zero` to test
the valid zero-count cases. The `short-length-zero` and `long-length-zero`
modes verify that a zero length also skips that group. Output includes the current operation, stroke
number/total, direction, speed, target position/counts, moving transitions and
fault. Detailed output is written to `can_coating_pc.csv`.

Menu candidates implemented in `COATING_SETTINGS` are actuator length, short
and long counts/lengths, positioning and homing speeds, fast-pass count, fast
and slow speed for each stroke group, feedback counts/inch and calibrated
maximum motor speed. Production menus should also consider direction and home
polarity, timeouts, target tolerance, PWM limits, CAN node ID and—if an encoder
variant is restored—encoder PPR plus mechanical travel per revolution.

This application is not wired into the real DG128 CANopen object dictionary.
The embedded test instead uses RAM-backed process-image variables described
below. Future MCO integration should replace that simulated transport inside
`dg128_smoke.c`, not move protocol handling into the portable controller.

### Embedded simulated-CAN coating test

The embedded build compiles `coating_cycle.c` and `coating_csv.c`. The original
two-cycle test remains armed by `MotionTestArm=0C3H`. The coating test uses:

```text
CoatingTestArm = 0D4H
```

The `Coat*` NoICE globals are editable menu settings and are copied/validated
only when the test is armed. `SimCanPositionTenths`, `SimCanSpeedPercent` and
`SimCanCommandPending` model received process-image data. `SimCanMoving` and
`SimCanFault` model the returned status. The portable scheduler waits for the
moving response to clear before sending the next command.

Embedded homing is deliberately non-driving. During `CoatOperation=1`, moving
is one for `CoatSimHomeDelayMs`, after which the current sprocket location is
declared count zero. This is safe for the present sprocket-only bench but is not
a production homing implementation. Never run it on a mechanically connected
actuator unless that actuator has first been placed at its retracted reference.
A real unit requires a home switch or a separately validated homing method.

After home, point moves use real PP4 edges, compensated speed PI and the
guarded L6203 output. Each move invalidates old timing and requires one fresh
complete rising-to-rising cycle before using speed feedback. The legacy and coating tests
are mutually exclusive. Setting `CoatingTestArm=0` aborts the coating test.

Coating operation values are 0 idle, 1 simulated home, 2 positioning, 3 short
stroke, 4 long stroke, 5 complete and 6 fault. Simulated-CAN fault values are
1/2 movement timeout, 3 duplicate command, 4 conflicting test and 5 operator
abort. Event CSV is sent through Virtual UART; the flat `Coat*`, `SimCan*` and
existing `Motion*` globals are the reliable NoICE view.

### DG128 embedded build

Installed cross-toolchain:

```text
C:\Toolchains\GNU68HC12\bin\m6811-elf-gcc.exe
GCC 3.3.6-m68hc1x-20060122
```

Important flags:

```text
-m68hc12 -mshort -fshort-double -mlong-calls -std=c89 -O0
```

The ordinary command below is the NoICE debug build:

```bat
build_embedded.bat
```

It adds `-DNOICE_DEBUG_GLOBALS=1`. `common\include\debug_visibility.h` consequently
expands `FILE_LOCAL` to nothing, making normally file-static functions and
variables global in the ELF symbol table so NoICE 9.8 can select and watch
them. This changes linkage/symbol visibility, not controller behavior.

To verify normal production linkage, use:

```bat
build_embedded.bat release
```

In that build `FILE_LOCAL` expands to the C `static` keyword. File-local names
will generally not be available as ordinary NoICE watches.

Run:

```bat
build_embedded.bat
```

Important outputs:

- `build\dg128_smoke.elf` — DWARF ELF.
- `build\dg128_smoke_stabs.elf` — STABS ELF used by NoICE.
- `build\dg128_smoke.s19` — programmer input after validation.
- `build\dg128_smoke.map` — linker map.
- `build\dg128_smoke.noi` — generated source/function/line mappings.
- `build\dg128_smoke_debug.noi` — automated NoICE startup session.
- `build\dg128_smoke_reconnect.noi` — no-load reconnect session.
- `build\dg128_smoke_debug_watches.noi` — standalone copy of the same complete
  watch list, used to restore watches without reloading the ELF.

The mapping generator emits both `DEFS` and `STATICFUNCTION` for file-static C
functions. NoICE 9.8 needs the separate scoped symbol when its source selector
evaluates a name such as `dg128_smoke.c#motion_sequence_service`.

The current linker is a DG128 fixed/nonpaged proof-of-concept.  Production
DG128/DG256 paged-function placement and Cyclone banked S-record generation are
future build/linker work, not yet implemented here.

## Automated NoICE debug launch

Run:

```bat
build_and_debug_noice.bat
```

It rebuilds, starts NoICE12, loads the STABS ELF, installs generated source and
function mappings, selects source mode and adds the complete 67-variable proximity,
timing, manual-motor, motion-controller and Virtual UART diagnostic set. The
authoritative list is `ESSENTIAL_WATCHES` in `tools\stabs_to_noice.py`.

Before starting or playing a session containing the complete watch list, set
NoICE **Refresh watches every** to 250 ms or disable timed refresh. A shorter
interval can cause NoICE to refresh target
memory while it is still adding watches and become unresponsive. If loading is
still unreliable, disable timed refresh, play the file, wait for all watches to
appear, and then restore the desired interval. Disable timed refresh during
sensitive source stepping or Virtual UART capture if BDM becomes unstable.

`build\dg128_smoke_debug_watches.noi` is generated from the same
`ESSENTIAL_WATCHES` list and can restore all watches without reloading the ELF.

If NoICE itself becomes unresponsive, run `restart_noice.bat`. It does not
compile; it terminates the existing NoICE12 process and opens the already-built
automated session, including its ELF load, source mappings and complete watches.
Use `restart_noice_no_load.bat` (or `restart_noice.bat noload`) when target
memory must not be loaded. That mode restores explicit source mappings and the
essential global watches only. It must be used with the exact firmware from the
current `build` directory; it cannot restore every ELF local/type definition.

To start the two-cycle hardware test, set this NoICE watch to hexadecimal C3
and run:

```text
MotionTestArm = 0C3H
```

States are 1 extend, 2 extended pause, 3 retract, 4 retracted pause, 5 complete
and 6 fault.

## Embedded printf-like output

NoICE BDM Virtual UART is used instead of the physical SCI and instead of
compiler semihosting.  The linker permanently reserves:

```text
0x2000 Virtual UART TX
0x2001 Virtual UART RX
0x2002 start of ordinary program RAM
```

### Recommended two-profile NoICE workflow

Testing showed that NoICE 9.8 is substantially less stable while single
stepping when its BDM Virtual UART is enabled. It may lose BDM communications
or require a frequency retry. Keep two otherwise identical target entries:

- **DG128 Step/Debug** — omit `virtualUART_address`; use for breakpoints,
  watches, source selection and stepping.
- **DG128 UART Capture** — include `virtualUART_address=0x2000`; use to run the
  motion sequence continuously and collect CSV from the Output window.

Close/restart NoICE when switching profiles. Avoid stepping and unnecessary
watch/memory refreshes during UART capture. Conversely, use the non-UART entry
when investigating code flow. This separation has proven more reliable than
trying to step and stream telemetry in the same session.

### NoICE symbol and structure limitations

NoICE does not reliably expose this old GCC toolchain's file-static variables
as watches, which is why the debug visibility mode exists. NoICE also does not
reliably decode `MOTION_SEQUENCE` as a structure; it may display the object as
an address/pointer instead of expandable members. Use the intentionally flat
scalar mirrors `MotionState`, `MotionCycle`, `MotionFault`,
`MotionPositionCount`, `MotionTargetCount`, `MotionCommandDuty`,
`MotionPositionErrorCounts`, `MotionSpeedCommandX100`,
`MotionMeasuredSpeedX100`, `MotionSpeedErrorX100`, and
`MotionSpeedIntegralX100`. These are the authoritative debugger-facing view of
the structure's current values.

In the active DG128 entry (preferably a copied/renamed entry) in:

```text
C:\Program Files (x86)\NoICE\config\noice12_targets.ini
```

add:

```ini
virtualUART_address=0x2000
```

Restart NoICE and select that target configuration.  The firmware sends CSV to
NoICE's Output window:

```text
ms,state,cycle,position,target,speed_cmd_x100,speed_fb_x100,duty,fault,dropped
```

This is printf-like diagnostic output, but it intentionally does not link the
large standard `printf` library.  `motion_csv.c` performs small deterministic
integer formatting, and `noice_vuart.c` queues characters without blocking the
motor controller.  If NoICE is disconnected, a Cyclone-programmed unit still
runs normally.  `NoICE_VuartDroppedRecords` reports terminal bandwidth loss.

Copy the Output-window CSV into `motion_embedded.csv`.  Compare it with
`motion_pc.csv` using:

```bat
python -m pip install matplotlib
plot_motion_comparison.bat
```

This creates `motion_comparison.png` with position/target, command/feedback
speed, and duty overlays.

## Important next improvements

1. Build the expanded embedded image with the actual HC12 cross-toolchain and
   confirm text/RAM fit, vectors, unresolved symbols and S-record layout before
   loading it on the bench.
2. Run the embedded coating test and verify operation, stroke, moving, fault,
   final motor disable and Virtual UART dropped counts.
3. Move the prox GPIO definition to the final PA6 or PB6 input.
4. Convert the fixed linker layout into production DG128/DG256 paged layouts;
   keep startup, vectors and ISRs nonpaged.
5. Generate and validate the Cyclone-compatible banked S-record separately
   from the linear/NoICE debug representation.
6. Connect the two-byte position/speed process image and moving/fault response
   to the actual DG128 CANopen object dictionary. Preserve the portable
   `MotionMove_*` and `CoatingCycle_*` interfaces.
7. Decide how menu settings are stored, range-checked and versioned in EEPROM,
   including feedback calibration and stroke/speed profiles.

## Ready-to-use continuation prompt

Copy the following prompt into a new ChatGPT conversation and attach the latest
project ZIP:

```text
I am continuing development of an MC9S12DG128/DG256 GCC firmware migration and
PC simulation project. I have attached the current project ZIP. Read README.md
and HANDOFF.md first, then inspect the actual source before proposing changes.

The established architecture keeps motion_sequence.c, motion_csv.c,
coating_cycle.c and coating_csv.c portable. The embedded DG128 build and both
PC simulations use the same motion controller. The embedded platform is
dg128_smoke.c plus startup, vectors, linker script,
NoICE Virtual UART and hardware I/O. The PC platform is motion_sequence_pc.c.
All shared and embedded C must remain compatible with C89 and the old GNU
m6811-elf-gcc 3.3.6 toolchain using -m68hc12 -mshort -fshort-double
-mlong-calls.

The tested bench mapping is PP0/PWM0 and PP1/PWM1 to an L6203, PA1 enable,
PP3 enable feedback and PP4 GPIO prox input. Direction is inferred from the
motor command. Current tuning is POSITION_KP_X100=250, SPEED_KP_GAIN=5,
SPEED_KI_STEP_GAIN=2, INTEGRAL_LIMIT_X100=1500, MAX_SPEED_X100=600,
REVERSAL_PAUSE_MS=100, 98-count travel, two cycles and 95-percent maximum duty.
The integral permits up to a +/-15 percentage-point correction. Both-edge
position and direction-specific high/low timing compensation are implemented;
this revision requires controlled hardware verification.

The build scripts generate DWARF and STABS ELFs, S19, map files and generated
NoICE source mappings. build_and_debug_noice.bat automatically launches NoICE,
loads symbols/source mappings and the complete 67-variable watch list. Set
timed watch refresh to 250 ms or disable it while loading. The BDM Virtual UART uses
RAM 0x2000/0x2001 and emits the same 250 ms CSV schema as the PC build. Normal
RAM begins at 0x2002. Do not replace the nonblocking logger with a blocking
putchar implementation.

First verify the ZIP's current build scripts, linker layout, constants and
interfaces. Preserve the shared-code architecture. Before implementing any
change, explain whether it belongs in shared control logic, the DG128 platform,
the PC simulator or build/debug tooling. Prox speed feedback is invalidated on
each motor start/reversal and requires a fresh complete rising-to-rising cycle.
Both edges count position, while learned extend/retract high fractions normalize
each high/low speed interval. After
changes, build/run the PC tests, preserve NoICE source/watch automation and
provide exact embedded test instructions.

The project also includes can_coating_pc.c and coating_cycle.c. The simulated
CAN command is two bytes: absolute position in tenths of an inch and speed in
percent. moving remains one until each target is reached, then clears before the
next command. Default coating settings perform four centered short directional
passes followed by four long passes, first pass extending, with a required
direction reversal across the short-to-long transition. Zero short or long
stroke counts and lengths are valid skipped-group settings. The DG128 now runs
this scheduler with RAM-backed simulated CAN bytes when
CoatingTestArm=0D4H. Its simulated home is non-driving and assigns the current
bench position as zero after CoatSimHomeDelayMs; it is not safe as production
homing on an unreferenced full actuator. The next application task is to test
this embedded mode and later map its transport boundary to the actual CANopen
process image without copying protocol code into the controller.
```
