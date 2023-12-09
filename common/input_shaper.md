Measuring the resonances¶
Checking the setup¶
Now you can test a connection.

For "non bed-slingers" (e.g. one accelerometer), in Octoprint, enter ACCELEROMETER_QUERY
For "bed-slingers" (e.g. more than one accelerometer), enter ACCELEROMETER_QUERY CHIP=<chip> where <chip> is the name of the chip as-entered, e.g. CHIP=bed (see: bed-slinger) for all installed accelerometer chips.
You should see the current measurements from the accelerometer, including the free-fall acceleration, e.g.

Recv: // adxl345 values (x, y, z): 470.719200, 941.438400, 9728.196800
If you get an error like Invalid adxl345 id (got xx vs e5), where xx is some other ID, immediately try again. There's an issue with SPI initialization. If you still get an error, it is indicative of the connection problem with ADXL345, or the faulty sensor. Double-check the power, the wiring (that it matches the schematics, no wire is broken or loose, etc.), and soldering quality.

If you are using a MPU-9250 compatible accelerometer and it shows up as mpu-unknown, use with caution! They are probably refurbished chips!

Next, try running MEASURE_AXES_NOISE in Octoprint, you should get some baseline numbers for the noise of accelerometer on the axes (should be somewhere in the range of ~1-100). Too high axes noise (e.g. 1000 and more) can be indicative of the sensor issues, problems with its power, or too noisy imbalanced fans on a 3D printer.

Measuring the resonances¶
Now you can run some real-life tests. Run the following command:

TEST_RESONANCES AXIS=X
Note that it will create vibrations on X axis. It will also disable input shaping if it was enabled previously, as it is not valid to run the resonance testing with the input shaper enabled.

Attention! Be sure to observe the printer for the first time, to make sure the vibrations do not become too violent (M112 command can be used to abort the test in case of emergency; hopefully it will not come to this though). If the vibrations do get too strong, you can attempt to specify a lower than the default value for accel_per_hz parameter in [resonance_tester] section, e.g.

[resonance_tester]
accel_chip: adxl345
accel_per_hz: 50 # default is 75
probe_points: ...
If it works for X axis, run for Y axis as well:

TEST*RESONANCES AXIS=Y
This will generate 2 CSV files (/tmp/resonances_x*_.csv and /tmp/resonances*y*_.csv). These files can be processed with the stand-alone script on a Raspberry Pi. To do that, run the following commands:

```bash
~/klipper/scripts/calibrate*shaper.py /tmp/calibration_data_x_20231119_154320.csv -o /tmp/shaper_calibrate_x.png


~/klipper/scripts/calibrate*shaper.py /tmp/calibration_data_y_20231119_154320.csv -o /tmp/shaper_calibrate_y.png
```

This script will generate the charts /tmp/shaper_calibrate_x.png and /tmp/shaper_calibrate_y.png with frequency responses. You will also get the suggested frequencies for each input shaper, as well as which input shaper is recommended for your setup. For example:

Resonances

Fitted shaper 'zv' frequency = 34.4 Hz (vibrations = 4.0%, smoothing ~= 0.132)
To avoid too much smoothing with 'zv', suggested max_accel <= 4500 mm/sec^2
Fitted shaper 'mzv' frequency = 34.6 Hz (vibrations = 0.0%, smoothing ~= 0.170)
To avoid too much smoothing with 'mzv', suggested max_accel <= 3500 mm/sec^2
Fitted shaper 'ei' frequency = 41.4 Hz (vibrations = 0.0%, smoothing ~= 0.188)
To avoid too much smoothing with 'ei', suggested max_accel <= 3200 mm/sec^2
Fitted shaper '2hump_ei' frequency = 51.8 Hz (vibrations = 0.0%, smoothing ~= 0.201)
To avoid too much smoothing with '2hump_ei', suggested max_accel <= 3000 mm/sec^2
Fitted shaper '3hump_ei' frequency = 61.8 Hz (vibrations = 0.0%, smoothing ~= 0.215)
To avoid too much smoothing with '3hump_ei', suggested max_accel <= 2800 mm/sec^2
Recommended shaper is mzv @ 34.6 Hz
The suggested configuration can be added to [input_shaper] section of printer.cfg, e.g.:

[input_shaper]
shaper_freq_x: ...
shaper_type_x: ...
shaper_freq_y: 34.6
shaper_type_y: mzv

[printer]
max_accel: 3000 # should not exceed the estimated max_accel for X and Y axes
or you can choose some other configuration yourself based on the generated charts: peaks in the power spectral density on the charts correspond to the resonance frequencies of the printer.

Note that alternatively you can run the input shaper auto-calibration from Klipper [directly](https://www.klipper3d.org/Measuring_Resonances.html#input-shaper-auto-calibration), which can be convenient, for example, for the input shaper re-calibration.

SHAPER_CALIBRATE
