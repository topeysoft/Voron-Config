#include "Utils.h"

void printDouble(Stream *serial, double val, unsigned int precision)
{
    // prints val with number of decimal places determine by precision
    // NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
    // example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)
    serial->print(int(val)); // prints the int part
    serial->print(".");      // print the decimal point
    unsigned int frac;
    if (val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val) - val) * precision;
    serial->print(frac, DEC);
}

double mapDouble(double val, double in_min, double in_max, double out_min, double out_max)
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float toRadians(float degrees)
{
    return degrees * M_PI / 180;
}
float toDegrees(float radians)
{
    return radians * 180 / M_PI;
}
int normalizeAngle(int angle)
{
    return angle % 360;
}
double normalizeAngle(double angle)
{
    angle = fmod(angle, 360);
    if (angle < 0)
        angle += 360;
    return angle;
}

size_t base64Decode(unsigned char *encodedString, unsigned char *decodedString)
{
    return decode_base64(encodedString, strlen((char *)encodedString), decodedString);
}

size_t base64Encode(unsigned char *str, unsigned char *encodedString)
{
    return encode_base64(str, strlen((char *)str), encodedString);
}

const char *decodeJwtBody(const char *jwt)
{
    String tokenString = jwt;
    // Split the token string by '.'
    int index = tokenString.indexOf('.');
    if (index < 0)
    {
        return "";
    }
    String tokenHeader = tokenString.substring(0, index);
    String tokenPayload = tokenString.substring(index + 1, tokenString.indexOf('.'));

    unsigned char tokenDataString[200]; // 14 bytes for output + 1 for null terminator

    // decode_base64() does not place a null terminator, because the output is not always a string
    unsigned int string_length = base64Decode((unsigned char *)tokenPayload.c_str(), tokenDataString);
    tokenDataString[string_length] = '\0';
    return (const char *)tokenDataString;
}