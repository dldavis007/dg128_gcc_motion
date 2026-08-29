# MC9S12DG128 GCC motion-control trial

This is an intentionally staged trial project.

## Current verified build

This project uses proximity feedback only.  The bench DG128 polls PP4 every
1 ms and counts qualified rising edges. Direction is inferred from the signed
motor command. The portable state machine and cascaded position-P/speed-PI
controller in `motion_sequence.c` are compiled without modification into both
the embedded firmware and the PC simulation.

The original embedded two-cycle path has been physically tested. The new
embedded simulated-CAN coating path is implemented and passes C89 host syntax,
linkage and PC behavioral tests, but still requires an actual HC12 build/map
check and its first controlled bench run.

Build on Windows with MinGW GCC:

```bat
build_motion_pc.bat
```

Build on Linux:

```sh
./build_motion_pc.sh
```

## Project layout

The source tree is divided by build ownership. Root-level build and NoICE
launcher scripts remain in place so existing commands continue to work.

| Folder | Used by | Contents |
| --- | --- | --- |
| `common/include`, `common/src` | PC and embedded | Portable motion controller, coating scheduler and CSV formatting |
| `embedded/include`, `embedded/src` | DG128 only | Hardware registers, startup, interrupts, PWM/prox services and Virtual UART |
| `embedded/linker` | DG128 only | Fixed-memory linker scripts |
| `pc/src` | PC only | Motor/prox model and simulated-CAN test programs |
| `tools` | Build/debug tooling | NoICE mapping/watch generator and plotting tools |
| `build` | Generated | Objects, executables, ELF/S19/map and NoICE session files |

Current speed-loop test tuning is `SPEED_KP_GAIN=10`,
`SPEED_KI_STEP_GAIN=10`, and `INTEGRAL_LIMIT_X100=2500`. The integral limit
allows a correction of up to 25 PWM percentage points in either direction;
the feed-forward value is a starting command, not a cap.

## CAN point-move and coating-cycle simulation

The project also contains a portable two-byte command model matching the older
actuator-controller interface:

```text
byte 0: absolute position in 0.1-inch units
byte 1: requested speed in percent
```

`MotionMove_Start()` and `MotionMove_Step()` execute one absolute move using the
same position-P/speed-PI controller as the original two-cycle bench test. The
simulated CAN receiver asserts `moving=1` when it accepts a command and clears
it only after feedback reaches or passes the target. Identical position and
speed bytes are treated as a repeated command and do not retrigger motion.

Build and run the coating simulation on Windows:

```bat
build_can_coating_pc.bat
```

or on Linux:

```sh
./build_can_coating_pc.sh
```

The default cycle homes from an unknown simulated position, positions at the
lower endpoint of a centered 4.0-inch stroke, performs four short passes, then
performs four 10.0-inch passes. One stroke count is one directional pass; the
first coating stroke extends. Direction alternates after every pass, including
the short-to-long transition, so the first long pass overlaps the last short
pass rather than continuing in the same direction. The first two passes in
each group use the fast speed and the remaining passes use the slow speed.

Boundary tests are available with:

```bat
build_can_coating_pc.bat short-zero
build_can_coating_pc.bat long-zero
build_can_coating_pc.bat both-zero
build_can_coating_pc.bat short-length-zero
build_can_coating_pc.bat long-length-zero
```

The program reports homing, each simulated CAN receive, operation, stroke
number, direction, position, speed, target counts and every `moving` clear. It
also writes `can_coating_pc.csv`. A 100 ms supervisory gap makes the cleared
moving status observable before the next command is sent.

### Suggested menu settings

The implemented `COATING_SETTINGS` values are suitable menu candidates:

| Setting | Units/purpose |
| --- | --- |
| Actuator length | 0.1 inch; validates every target and defines homing travel |
| Short stroke count | Directional passes; zero skips short strokes |
| Short stroke length | 0.1 inch; centered; zero also skips short strokes |
| Long stroke count | Directional passes; zero skips long strokes |
| Long stroke length | 0.1 inch; centered; zero also skips long strokes |
| Positioning speed | Percent used to reach the first lower endpoint |
| Homing speed | Percent used during retraction to the home reference |
| Fast stroke count | Number of early passes in each group using fast speed |
| Short fast/slow speeds | Percent for early/later short passes |
| Long fast/slow speeds | Percent for early/later long passes |
| Feedback counts/inch | Fixed-point calibration, presently 4.85 counts/inch |
| Maximum motor speed | Prox counts/second x100 used to scale speed percent |

Production additions worth considering are direction polarity, home-input
polarity, move timeout, target tolerance, minimum/maximum PWM, CAN node ID and
an encoder PPR/drive-travel pair when encoder feedback is used. This project is
currently proximity-only, so it stores the directly useful counts-per-inch
calibration instead of an unused encoder PPR setting.

The scheduler and process-image simulation are portable C89 code. They are not
connected to the DG128 CANopen object dictionary. The embedded smoke test now
uses the same interface with RAM-backed simulated CAN bytes; later platform
integration should replace only that transport boundary.

### Embedded simulated-CAN coating test

The DG128 build now compiles `coating_cycle.c` and `coating_csv.c`. It retains
the original `MotionTestArm = 0C3H` test and adds a separate arm:

```text
CoatingTestArm = 0D4H
```

Before arming, edit the `Coat*` menu globals in NoICE if desired. The defaults
match the PC output: 10.0-inch travel, four 4.0-inch short passes, four
10.0-inch long passes and fast/slow speed changes after the first two passes.

For bench safety, embedded homing is simulated and never energizes the motor.
`SimCanMoving` remains one for `CoatSimHomeDelayMs` (default 1000 ms), then the
firmware assigns the current location as `MotionPositionCount=0`. This is
appropriate for the sprocket-only bench. Do not use this simulated-zero mode on
a connected full actuator unless it has first been physically placed at its
retracted reference. Production firmware must replace it with a real home
switch or a separately validated homing procedure.

After simulated home, the scheduler fills `SimCanPositionTenths` and
`SimCanSpeedPercent`, sets `SimCanCommandPending`, and the receiver converts the
two bytes into `MotionMove_Start()`. Real PP4 feedback, speed PI control and the
existing guarded PWM service perform the move. `SimCanMoving` clears at each
target and the scheduler waits 100 ms before issuing the next command.

Useful status values are:

| Variable | Meaning |
| --- | --- |
| `CoatOperation` | 1 home, 2 position start, 3 short, 4 long, 5 complete, 6 fault |
| `CoatStrokeNumber/Total` | Current directional pass and group total |
| `CoatDirectionExtend` | 1 extend, 0 retract |
| `CoatTargetTenths` | Target position in 0.1-inch units |
| `CoatSpeedPercent` | Requested move speed |
| `SimCanMoving` | Simulated response, one until target completion |
| `SimCanFault` | 0 none; 1/2 move timeout, 3 duplicate, 4 test conflict, 5 abort |

Set `CoatingTestArm=0` to abort. The legacy and coating automatic tests are
mutually exclusive. Coating events are also emitted through Virtual UART as
CSV containing operation, stroke, direction, target, speed, moving and
controller data.

To run the embedded test:

1. Build and load with `build_and_debug_noice.bat` using the UART target profile
   if CSV is wanted. Use 500 ms watch refresh or disable timed refresh while the
   58-watch session loads.
2. With the motor stopped, place the bench mechanism at the physical location
   that may safely be treated as retracted zero. Confirm `MotorOutputsEnabled=0`.
3. Review/edit the `Coat*` settings. Ensure actuator and stroke lengths cannot
   command motion beyond the mechanically safe bench travel.
4. Set `CoatingTestArm=0D4H` and click Run. Do not single-step or halt while PWM
   may be active.
5. On success verify `CoatOperation=5`, `CoatAutomaticActive=0`,
   `SimCanMoving=0`, `SimCanFault=0`, `MotionFault=0` and
   `MotorOutputsEnabled=0`.

Removing the arm requests a controlled firmware stop, but if NoICE cannot
communicate while running, remove motor power rather than relying on a debugger
write. The current fixed-memory linker must also be checked after rebuilding;
the added application and formatter increase flash use.

The older combined encoder/proximity simulator was removed. The retained PC
programs test the legacy bench cycle and the new CAN/coating application while
sharing one proximity-feedback controller.

## Embedded fixed-memory smoke test

Run `build_embedded.bat` from a normal Command Prompt. It produces:

- `build/dg128_smoke.elf` for NoICE source-level debugging
- `build/dg128_smoke_stabs.elf` as an alternate NoICE source-debug format
- `build/dg128_smoke.s19` for later programming
- `build/dg128_smoke.map` for memory verification

The batch file first checks `C:\Toolchains\GNU68HC12\bin`, then PATH. GCC
3.3.6 uses the older `-W` warning option rather than the later `-Wextra` name.
It compiles embedded C from inside `embedded\src` and portable C from inside
`common\src`. This gives NoICE unambiguous source records after the folder
split and avoids mismatches between command-line paths and debugger records.

The normal ELF contains DWARF information. The alternate `_stabs.elf` contains
STABS source and line records for diagnosing NoICE compatibility. Both use the
same source, compiler ABI, memory layout, and unoptimized machine-code settings.

By default, `build_embedded.bat` defines `NOICE_DEBUG_GLOBALS=1`. The
`FILE_LOCAL` macro then makes normally static file functions and variables
global so NoICE can display them. Run `build_embedded.bat release` to restore
normal C `static` linkage for a production-style build.

This first image intentionally uses only fixed flash at `0x4000-0x7fff`.
The reset vector remains at `0xfffe`, within the vector table beginning at
`0xff80`. The supplied GCC `crt1.o` loads SP=`0x4000`; our `.install1` code
then writes `INITRM=0x21` before `crt1` performs its first subroutine call.
The startup module also supplies a local non-returning `exit` trap, avoiding a
stray undefined `NAME` symbol in this toolchain's `libgcc.a(__exit.o)`.

Watched variables for the first NoICE session:

- `StartupPassed` becomes `0x5a`
- `MainLoopCount` increases continuously
- `Tick1msCount` increases every 1 ms
- `Tick10msCount` increases every 10 ms
- `ProxInputRaw` and `ProxInputStable` show the PP4 GPIO state
- `ProxEdgeCount` increases on each qualified rising edge at PP4
- `ProxPeriodMs` contains milliseconds between rising edges
- `MotorOutputsEnabled` remains zero and does not control hardware yet

The hardware vectors enter small fixed-memory assembly wrappers. Each wrapper
calls its fixed C handler with `JSR` and completes with `RTI`, keeping the C
handler visible and step-able without relying on a compiler-specific ISR keyword.

Do not program the S19 until the build output and map show `.text` in
`0x4000-0x7fff`, Virtual UART at `0x2000-0x2001`, `.data/.bss` in
`0x2002-0x3fff`, and `.vectors` at `0xff80`.

The smoke build uses `embedded/linker/dg128_fixed.x` directly. It does not request the
banked linker emulation; paged placement will be added only after this fixed
startup and debugger test succeeds.

## Embedded bring-up policy

The first embedded image must not start the motor automatically after reset.
The planned DG128 sequence is:

1. Load the GCC ELF/DWARF file in NoICE.
2. Verify reset, source stepping, globals, and normal variables beginning at
   RAM address 0x2002.
3. Verify the 1 ms GPIO polling tick and derived 10 ms tick.
4. Drive the sprocket externally and verify PP4 rising-edge measurements.
5. Enable low-duty manual motor output from a watched command variable.
6. Enable the automatic position/speed controller only after the above tests.

## Toolchain requirements

The embedded compiler must be the GNU 68HC11/68HC12 cross toolchain, not the
normal Windows GCC.  Required target features are:

- `-m68hc12`
- ELF output with DWARF (`-g`)
- `__attribute__((interrupt))`
- `__attribute__((far))` / `-mlong-calls`
- GNU linker HC12 trampoline support

The linker/startup portion should not be flashed until its generated map,
vectors, CALL/RTC sequences, and S-record address ranges have been inspected.

## Motor interface recorded from the supplied schematic

- PP0: L6203 IN1
- PP1: L6203 IN2
- PA1: drives the filtered L6203 ENABLE command through R1/C4
- PP3: GPIO input monitoring ENABLE through D4

The exact PWM strategy and safe inactive polarity must be confirmed from the
currently working firmware before the embedded motor-output layer is enabled.
## NoICE source-level debugging

NoICE 9.8 can load the symbols from this GCC 3.3.6 ELF, but it may not import
the associated source/function/line hierarchy.  `build_embedded.bat` therefore
also creates `build\dg128_smoke.noi` from the STABS records.
The generator also emits a file-scoped `DEFS` symbol for each C `static`
function. This allows NoICE's **Select Source File or Function** window to
resolve selections such as `dg128_smoke.c#motion_sequence_service`.

After a successful build:

1. In NoICE, load `build\dg128_smoke_stabs.elf`.
2. Use **File > Play Command File** (or the `PLAY` command) to play
   `build\dg128_smoke.noi`.
3. Use mixed/source mode and step normally.  The `.noi` file ends with
   `MODE 2` and `SOURCE PC`, so the current C source should appear immediately.

For a one-step build and debug launch, run:

```text
build_and_debug_noice.bat
```

This rebuilds the project, starts NoICE12, and opens the generated
`build\dg128_smoke_debug.noi` session.  That session loads the STABS ELF,
installs the source mappings directly (without a nested `PLAY`), selects source
mode, and adds the complete 58-variable diagnostic/menu watch list. The earlier
30-item list loaded reliably at 250 ms. Because the coating additions expanded
the list, use **Refresh watches every = 500 ms** or disable timed refresh while
loading. NoICE may otherwise refresh target memory while it is still processing
watch commands and become unresponsive.

If the list still fails to load, turn timed watch refresh off, start or play the
session, wait until all watches appear, and then restore the desired interval.
For sensitive stepping or Virtual UART capture, leaving timed refresh disabled
may provide better BDM stability. NoICE still refreshes watches after a step,
breakpoint, register change, or a manual `WATCH` command.

The build also creates `build\dg128_smoke_debug_watches.noi`. It contains the
same 58 watches and can restore the Watch window without reloading the ELF.
The generator derives both files from `ESSENTIAL_WATCHES` in
`tools\stabs_to_noice.py`, so the lists cannot drift apart.

To restart a failed or unresponsive NoICE session without compiling, run:

```text
restart_noice.bat
```

This closes any existing NoICE12 process and reopens the previously generated
debug session. It reloads the existing STABS ELF, symbols, source mappings and
complete watch list. To reconnect without loading target memory, run either
`restart_noice.bat noload` or `restart_noice_no_load.bat`. The no-load session
restores explicit source mappings and essential global watches, but not all ELF
type/local-variable information. Use it only when the MCU contains the exact
firmware represented by the current `build` directory.

Load the ELF before playing the `.noi` file after every rebuild.  The `.noi`
file does not clear symbols or line information because the ELF remains the
authoritative source for symbols and data types.

## Proximity input used by this test

The current bench unit connects the proximity signal to PP4.  This firmware
intentionally treats PP4 as an ordinary GPIO input; it does not enable the
KWP4 interrupt.  TC7 runs every 1 ms, qualifies a state change for two samples,
and counts rising edges.  This matches the intended final approach for a prox
input on PA6 or PB6.

Useful NoICE variables are `ProxInputRaw`, `ProxInputStable`, `ProxEdgeCount`,
`ProxLastRiseMs`, `ProxPeriodMs`, `ProxPeriodValid`, and `ProxStopped`.
`ProxStopped` becomes one after 2000 ms without another rising edge.  Motor
outputs remain forced low until the guarded motor test is explicitly armed.

## Guarded motor-output test

PWM0 drives PP0/L6203 IN1, PWM1 drives PP1/L6203 IN2, PA1 commands ENABLE,
and PP3 reads back the ENABLE node.  The PWM setup matches the supplied ImageCraft initialization:
100-count active-high PWM using the scaled clock (approximately 20 kHz at a
24 MHz bus).  Reset never starts the motor.

To perform one short test while stopped in NoICE:

1. Set `MotorTestDutyPercent` to a conservative signed value such as `10`.
   Positive and negative values select opposite directions.
2. Leave `MotorTestTimeoutMs` at its default `5000` ms for the first test.
3. Set `MotorTestArm` to hexadecimal `A5`.
4. Run the processor and allow the timeout to stop the motor before halting.

Status values are: 0 stopped/not armed, 1 running, 2 timed out, and 3 rejected
direction change.  A direction change requires stopping and setting the arm
value again.  Duty is limited to 100 percent and timeout to 60 seconds.
`MotorEnableFeedback` shows the PP3 readback state.

Do not halt the CPU with the motor running: BDM freezes firmware timeout
processing while peripheral output state may persist.  For the initial test,
wait longer than the selected timeout before halting.  Remove motor power for
an immediate emergency stop.

## Two-cycle extend/retract test

`motion_sequence.c` is shared by the DG128 firmware and the PC test.  It uses
the verified nine rising-edge pulses per sprocket revolution and treats the
single-channel prox direction as the commanded motor direction.

The staged test assumes the mechanism starts retracted at position zero.  It
extends to 49 counts (about 10.1 inches with the recorded sprocket geometry),
pauses 100 ms, returns to zero, and repeats for two cycles.  Maximum duty is
95 percent, minimum approach duty is 10 percent, and each movement has a
45-second timeout.

The duty command now comes from a fixed-point cascaded controller shared by
both builds.  The position P loop converts remaining prox counts into a signed
speed command, limited to 3.00 counts/second.  The speed PI loop compares that
command with speed calculated from the rising-edge period and produces signed
PWM duty.  Feed-forward supplies most of the nominal duty, while the PI terms
correct motor/load variation.  The integral is reset during stops and reversal
pauses and is limited to prevent windup.  The prox stopped timeout is 3 seconds
so the verified 10-percent operating point remains valid.

To start on hardware, set `MotionTestArm` to hexadecimal `C3` and run.  Useful
watches are `MotionState`, `MotionCycle`, `MotionFault`,
`MotionPositionCount`, `MotionTargetCount`, and `MotionCommandDuty`.  Controller
diagnostics use x100 scaling: `MotionSpeedCommandX100`,
`MotionMeasuredSpeedX100`, `MotionSpeedErrorX100`, and
`MotionSpeedIntegralX100`.  For example, 275 means 2.75 prox counts/second.
State 5 means complete and state 6 means fault.  Clearing `MotionTestArm`
aborts an active test.

Run the same sequence on the computer with:

```text
build_motion_pc.bat
```

The PC model prints every state transition and must finish at state 5, cycle 2,
position zero, with fault zero.

## NoICE BDM Virtual UART and CSV telemetry

The DG128 build reserves RAM addresses `0x2000` and `0x2001` for NoICE's BDM
Virtual UART.  Normal `.data` and `.bss` now begin at `0x2002`.  The logger is
nonblocking: it queues complete records and never waits for NoICE, so a Cyclone-
programmed unit continues to operate when no debugger is attached.

Use two NoICE target configurations. The stepping/debugging configuration
should omit `virtualUART_address`; it has been noticeably more stable for
breakpoints, source stepping and watch evaluation. A second capture
configuration should contain `virtualUART_address=0x2000` and should be used
for uninterrupted runs that collect CSV output. Close and restart NoICE when
switching. Trying to single-step while Virtual UART polling is active has
repeatedly caused lost BDM communications on this setup.

NoICE 9.8 may show the internal `MotionSequence` structure as an address or
pointer rather than expandable fields. Use the flat `MotionState`,
`MotionCycle`, `MotionFault`, `MotionPositionCount`, `MotionTargetCount`,
`MotionCommandDuty`, and `Motion*X100` diagnostic globals instead.

Before using the terminal output, close NoICE and make a backup copy of:

```text
C:\Program Files (x86)\NoICE\config\noice12_targets.ini
```

Open the file with administrator permission.  Copy the processor section that
you currently use successfully for the DG128, give the copied section a unique
name such as `MC9S12DG128 Flash with Virtual UART`, and add this line within the
copied section:

```ini
virtualUART_address=0x2000
```

Do not copy DG256 example addresses from the NoICE manual.  This project's
startup maps DG128 RAM at `0x2000-0x3FFF`, and the address in the INI file must
exactly match the firmware.  Restart NoICE, open **Options > Target
Communications**, and select the newly named processor configuration while
continuing to use the same P&E BDM interface and settings that already work.

Open NoICE's **Output** window, build/load with `build_and_debug_noice.bat`, set
`MotionTestArm` to hexadecimal `C3`, and run.  The Output window receives:

```text
ms,state,cycle,position,target,speed_cmd_x100,speed_fb_x100,duty,fault,dropped
```

followed by a record every 250 ms.  `speed_cmd_x100` and `speed_fb_x100` use
the controller's fixed-point scaling, so `300` means 3.00 prox counts/second.
The `dropped` column and the `NoICE_VuartDroppedRecords` watch indicate whether
the BDM terminal could not keep up.  If either is nonzero, increase
`MOTION_TELEMETRY_PERIOD_MS` in `common\include\motion_csv.h` from 250 to 500 ms and
rebuild.  A value of zero means the captured records are complete.

After the test stops, click in the Output window, select all of its text, copy
it, and save the CSV portion as:

```text
motion_embedded.csv
```

`build_motion_pc.bat` runs the identical controller and automatically creates
`motion_pc.csv` at the same 250 ms interval.  To overlay hardware and simulated
position, speed, and duty, install matplotlib once if necessary and run:

```text
python -m pip install matplotlib
plot_motion_comparison.bat
```

The plot is saved as `motion_comparison.png`.  The plotting script normalizes
each log to its first timestamp, so the DG128's time since reset does not need
to match the PC simulation's zero-based time.
