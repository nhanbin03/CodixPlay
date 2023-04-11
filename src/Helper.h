#ifndef HELPER_H
#define HELPER_H

#include "raylib.h"

Vector2 operator+ (const Vector2 &a, const Vector2 &b);

Vector2 operator- (const Vector2 &a, const Vector2 &b);

Vector2 operator* (const Vector2 &a, float x);

Vector2 operator/ (const Vector2 &a, float x);

#endif // HELPER_H
