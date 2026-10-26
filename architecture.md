# JalMitra Architecture (Starter)

## System overview
JalMitra is planned as a tethered underwater debris-collection robot controlled from the pond bank. This repository implements only a basic ESP32 remote-drive firmware scaffold.

```text
Operator / Serial Console
          |
          v
       ESP32
       |   |
       v   v
 Motor Driver Channels ----> Waterproof Thrusters
       |
       +---- (future) depth sensor / battery monitor

Future surface unit:
Solar panel -> charge controller -> protected battery -> tether -> robot power
```

## Main modules
1. **Control:** ESP32 accepts `F`, `B`, `L`, `R`, and `S` commands over serial.
2. **Motion:** two output channels control left and right thrusters through suitable external drivers.
3. **Fail-safe:** firmware stops outputs after 1.5 seconds without a valid command.
4. **Collection subsystem (planned):** guarded intake, clog-resistant path, removable debris basket.
5. **Power subsystem (planned):** appropriately rated battery, fuse, battery protection and solar charge controller on a surface buoy.
6. **Sensing (planned):** depth sensor first; camera and autonomy only after basic operation is validated.

## Key constraints and risks
- Underwater enclosures and cable penetrations need pressure/leak testing.
- Thrusters can entangle weeds and must be guarded/placed away from the intake.
- Suction can clog and disturb bottom sediment; begin with loose debris and weeds.
- A mesh screen does not make water safe or remove dissolved contaminants.
- Composting is appropriate only for tested, uncontaminated organic material.
- Battery, charger, cable and motor ratings must be calculated for the actual hardware.

## Validation plan
1. Compile firmware and test serial commands with motors disconnected.
2. Verify driver signals using LEDs or a logic analyzer.
3. Test motor direction at low power in a dry, guarded setup.
4. Conduct leak and tether tests separately from powered motor tests.
5. Test in a controlled tank with recoverable, clean test debris.
6. Record runtime, collected mass, clog events and battery voltage.
7. Conduct any real pond trial only with permission, supervision and an emergency recovery plan.
