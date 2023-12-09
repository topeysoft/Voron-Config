#ifndef ELYIR_UTILS_H
#define ELYIR_UTILS_H
#include <base64.h>
#include <Arduino.h>

void printDouble(Stream *serial, double val, unsigned int precision);

double mapDouble(double val, double in_min, double in_max, double out_min, double out_max);
float toRadians(float degrees);
float toDegrees(float radians);
double normalizeAngle(double angle);
int normalizeAngle(int angle);
size_t base64Decode(unsigned char *encodedString, unsigned char *decodedString);
size_t base64Decode(unsigned char *str, unsigned char *encodedString);
const char *decodeJwtBody(const char *jwt);
#endif // ELYIR_UTILS_H
