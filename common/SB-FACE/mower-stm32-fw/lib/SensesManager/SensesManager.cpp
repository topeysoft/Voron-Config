

#include "SensesManager.h"
// #include <Adafruit_Sensor.h>
// #include <Adafruit_HMC5883_U.h>

SensesManagerClass sensesManager;

// QMC5883LCompass compass;
;
#include <HMC5883L.h>

HMC5883L compass;

int previousDegree;
int compass_read_count = 0;
int x = 0, y = 0, z = 0;
bool senses_ready_notified = false;

void SensesManagerClass::setup()
{
    _pose.position.lat = 0;
    _pose.position.lon = 0;
    _pose.position.alt = 0;
    _pose.orientation.roll = 0;
    _pose.orientation.pitch = 0;
    _pose.orientation.yaw = 0;
    _voltage = 0;
    _lowestVoltage = 11.60;
    _highestVoltage = 12.8;
    _last_read = 0;
    _voltageMessageAcknowledged = false;
    while (!compass.begin())
    {
        delay(500);
    }
    // Set measurement range
    compass.setRange(HMC5883L_RANGE_1_3GA);

    // Set measurement mode
    compass.setMeasurementMode(HMC5883L_CONTINOUS);

    // Set data rate
    compass.setDataRate(HMC5883L_DATARATE_30HZ);

    // Set number of samples averaged
    compass.setSamples(HMC5883L_SAMPLES_8);

    // Set calibration offset. See HMC5883L_calibration.ino
    compass.setOffset(0, 0);
}

void SensesManagerClass::work()
{
    // compass_read_count++;
    // compass.read();
    // // Return XYZ readings
    // x += abs(compass.getX());
    // y += abs(compass.getY());
    // z += abs(compass.getZ());
    // if (compass_read_count >= 25)
    // {
    //     x /= compass_read_count;
    //     y /= compass_read_count;
    //     z /= compass_read_count;
    //     _orientation.pitch = abs(x % 360);
    //     _orientation.roll = abs(y % 360);
    //     _orientation.yaw = abs(z % 360);
    //     compass_read_count = 0;
    //     x = 0;
    //     y = 0;
    //     z = 0;
    // }
    if (millis() - _last_read >= _readInterval)
    {
        _last_read = millis();
        Vector norm = compass.readNormalize();

        // Calculate heading

        // compass.read();
        // x = (compass.getX());
        // y = (compass.getY());
        // z = (compass.getZ());
        x = norm.XAxis;
        y = norm.YAxis;
        z = norm.ZAxis;
        // float heading = atan2(event.magnetic.y, event.magnetic.x);
        float heading = atan2(y, x);

        // Set declination angle on your location and fix heading
        // You can find your declination on: http://magnetic-declination.com/
        // (+) Positive or (-) for negative
        // For Holts Summit, MO USA, declination angle is +1°6'E (positive)
        // Formula: (deg + (min / 60.0)) / (180 / M_PI);
        float declinationAngle = (1 + (6 / 60.0)) / (180 / M_PI);
        heading += declinationAngle;

        // Correct for heading < 0deg and heading > 360deg
        if (heading < 0)
        {
            heading += 2 * PI;
        }

        if (heading > 2 * PI)
        {
            heading -= 2 * PI;
        }

        // Convert to degrees
        float headingDegrees = heading * 180 / M_PI;

        // Fix HMC5883L issue with angles
        float fixedHeadingDegrees;

        if (headingDegrees >= 1 && headingDegrees < 240)
        {
            fixedHeadingDegrees = map(headingDegrees, 0, 239, 0, 179);
        }
        else if (headingDegrees >= 240)
        {
            fixedHeadingDegrees = map(headingDegrees, 240, 360, 180, 360);
        }

        // Smooth angles rotation for +/- 3deg
        int smoothHeadingDegrees = round(fixedHeadingDegrees);

        if (smoothHeadingDegrees < (previousDegree + 3) && smoothHeadingDegrees > (previousDegree - 3))
        {
            smoothHeadingDegrees = previousDegree;
        }

        previousDegree = smoothHeadingDegrees;
        // int one80_degrees = map(smoothHeadingDegrees, 0, 360, -180, 180);
        _pose.orientation.pitch = x;                  // abs(x % 360);
        _pose.orientation.roll = y;                   // abs(y % 360);
        _pose.orientation.yaw = smoothHeadingDegrees; // headingDegrees;
        ;                                             // abs(z % 360);

        // _pose.orientation.yaw = atan2(y, x) * 180 / PI;
        // ; // abs(z % 360);

        double chargerVal = analogRead(_chargerPin);
        double chargerVoltRead = chargerVal * (3.3 / 1023.0);
        double chargerVolt = mapDouble(chargerVoltRead, 0.00, 3.3, 0.001, _highestChargerVoltage);
        if (chargerVolt > _noChargerVoltage && !isChargerConnected())
        {
            if (_chargerStatusCallback)
            {
                _chargerStatusCallback(true, chargerVolt);
            }
        }
        else if (chargerVolt <= _noChargerVoltage && isChargerConnected())
        {
            if (_chargerStatusCallback)
            {
                _chargerStatusCallback(false, chargerVolt);
            }
        }
        _chargerVoltage = chargerVolt;

        // Read voltage
        double val = analogRead(_voltagePin);
        // double volt = val * 3.3 / 4096.0;
        double volt = val * 3.3 / 1023.0;
        _voltage = mapDouble(volt, 0.00, 2.8, _lowestVoltage, _highestVoltage);
        // _voltage = mapDouble(volt, 0.00, 3.3, _lowestVoltage, _highestVoltage);
        _voltagePercent = round(mapDouble(_voltage, _lowestVoltage, _highestVoltage, 0, 100));
        if (_voltagePercent < 10)
        {
            if (!_voltageMessageAcknowledged)
            {
                if (_lowVoltageCallback)
                {
                    _lowVoltageCallback(_voltage, _voltagePercent);
                }
            }
        }
        else if (_voltagePercent > 90)
        {
            if (!_voltageMessageAcknowledged)
            {
                if (_fullVoltageCallback)
                {
                    _fullVoltageCallback(_voltage, _voltagePercent);
                }
            }
        }
        else
        {
            _voltageMessageAcknowledged = false;
        }
        if (!senses_ready_notified)
        {
            if (_readyCallback)
            {
                _readyCallback();
            }
            senses_ready_notified = true;
        }
    }
}