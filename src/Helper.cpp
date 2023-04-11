#include "Helper.h"

Vector2 operator+ (const Vector2 &a, const Vector2 &b) {
    return {a.x + b.x, a.y + b.y};
}

Vector2 operator- (const Vector2 &a, const Vector2 &b) {
    return {a.x - b.x, a.y - b.y};
}

Vector2 operator* (const Vector2 &a, float x) {
    return {a.x * x, a.y * x};
}

Vector2 operator/ (const Vector2 &a, float x) {
    return {a.x / x, a.y / x};
}
