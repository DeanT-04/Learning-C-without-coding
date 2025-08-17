#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Header guard prevents multiple inclusions

// Function-like macros
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

// Mathematical constants
#define PI 3.14159265359
#define E 2.71828182846

// Conversion macros
#define CELSIUS_TO_FAHRENHEIT(c) (((c) * 9.0 / 5.0) + 32.0)
#define FAHRENHEIT_TO_CELSIUS(f) (((f) - 32.0) * 5.0 / 9.0)

// Bit manipulation macros
#define SET_BIT(num, pos) ((num) |= (1 << (pos)))
#define CLEAR_BIT(num, pos) ((num) &= ~(1 << (pos)))
#define TOGGLE_BIT(num, pos) ((num) ^= (1 << (pos)))
#define CHECK_BIT(num, pos) (((num) >> (pos)) & 1)

// Array size macro
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif // MATH_UTILS_H