# Config File Structure

## printer.cfg

This file contains the configuration specific to the printer. It constins the following sections:

- kinematics,
- print volume capacity, (x, y, z)
- print speed,
- acceleration,

## machine.cfg

This file contains the configuration specific to the printer mcu pin mapping. It contains the following sections:

- pin mapping for the stepper motors,
- pin mapping for the endstops,
- pin mapping for the heaters,
- pin mapping for the fans,
- pin mapping for the thermistors,
- pin mapping for the bed heater,
- pin mapping for the bed thermistor,
- pin mapping for the lcd screen (if any),
- pin mapping for the sd card reader (if any),
- pin mapping for the buzzer (if any),
- pin mapping for the led lights (if any),

## filament.cfg

This file contains the configuration for filament management. It contains the following sections:

- load gcode,
- unload gcode,
- filament sensor gcode,
