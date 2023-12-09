## Voron TAP

You must run `PROBE_CALIBRATE` to calibrate the probe before you can use it.

```
PROBE_CALIBRATE
```

Add the following to your slicer's start script

```c
PRINT_START EXTRUDER=[extruder0_temperature] BED=[bed0_temperature] CHAMBER=[bed1_temperature]
```

## Calibrate Heater PID

### Calibrate Extruder PID

```
PID_CALIBRATE HEATER=extruder TARGET=200
```

### Calibrate Bed PID

```
PID_CALIBRATE HEATER=heater_bed TARGET=60
```

## Calibrate Input Shaper

### Calibrate all axes

```
SHAPER_CALIBRATE
```

OR

### Calibrate X Axis

```
TEST_RESONANCES AXIS=X
```

### Calibrate Y Axis

```
TEST_RESONANCES AXIS=Y
```
