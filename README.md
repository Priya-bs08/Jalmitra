# JalMitra — Pond-Cleaning Robot (Starter Repository)

JalMitra is a student prototype concept for a tethered, remotely operated robot that collects loose pond debris and aquatic weeds. This repository contains **starter firmware and documentation** for simulation and early prototyping. It is not a certified or field-ready underwater system.

## Features in this starter
- ESP32 serial-command control (`F`, `B`, `L`, `R`, `S`)
- Two motor-channel outputs intended for a suitable motor driver
- Basic depth-sensor reading placeholder/interface
- Runtime safety timeout that stops motors if commands stop arriving
- Sample sensor data and lightweight host-side tests

## Hardware assumptions
- ESP32 development board
- Two compatible motor drivers and two suitable waterproof thrusters
- A depth sensor supported by an installed Arduino library (see code comments)
- Properly sealed enclosure, strain-relieved tether, fuse, emergency disconnect, and battery protection

**Important safety notes**
- Do not connect motors directly to ESP32 GPIO pins.
- Do not use this starter code to operate a robot in a pond without supervised engineering review and bench/tank testing.
- Test with motors disconnected first, then use a current-limited supply and a safe test tank.
- Solar charging, battery management, camera navigation, suction pump, cutter, and autonomous navigation are not implemented here.
- Do not return water as “purified”; a mesh only screens larger debris and does not remove dissolved pollutants or pathogens.

## Quick start
1. Install the Arduino IDE.
2. Install ESP32 board support using the official Espressif Arduino-ESP32 installation instructions.
3. Open `src/JalMitra.ino`.
4. Review and update the pin assignments for your actual driver board.
5. Upload to an ESP32 with the motor driver disconnected.
6. Open Serial Monitor at **115200 baud** and send one command per line:
   - `F` forward
   - `B` backward
   - `L` turn left
   - `R` turn right
   - `S` stop
7. Verify the serial responses and motor output pins before connecting any driver.

## Repository layout
```text
JalMitra/
├── src/
│   └── JalMitra.ino
├── docs/
│   └── architecture.md
├── data/
│   └── sample_sensor_data.csv
├── tests/
│   ├── test_sample_data.py
│   └── test_commands.py
├── LICENSE
└── README.md
```

## Testing
The host-side tests use Python's standard library and do not require hardware:
```bash
python -m unittest discover -s tests -v
```
These tests validate command parsing assumptions and sample-data structure only. They do **not** prove waterproofing, motor safety, or real-world collection performance.

## Roadmap
- [ ] Bench-tested motor driver integration
- [ ] Add selected depth sensor library and validate sensor readings
- [ ] Add guarded intake and removable debris basket
- [ ] Measure battery endurance and collection efficiency
- [ ] Add solar charging buoy with a correctly rated charge controller
- [ ] Add camera and autonomous sweeping only after reliable remote control
- [ ] Separate plastic from organic waste and assess safe disposal/reuse

## License
Released under the MIT License; see `LICENSE`.
