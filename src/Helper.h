#ifndef HELPER_H
#define HELPER_H

#include "raylib.h"

#include <fstream>
#include <string>
#include <vector>

Vector2 operator+ (const Vector2 &a, const Vector2 &b);

Vector2 operator- (const Vector2 &a, const Vector2 &b);

Vector2 operator* (const Vector2 &a, float x);

Vector2 operator/ (const Vector2 &a, float x);

void scaleTexture(Texture2D &source, Vector2 newSize);

template <typename T>
std::vector<T> readListFromFile(std::string filePath);

#endif // HELPER_H

template <typename T>
std::vector<T> readListFromFile(std::string filePath) {
    std::ifstream fin;
    fin.open(filePath);
    std::vector<T> ret;
    T input;
    while (fin >> input) {
        ret.push_back(input);
    }
    fin.close();
    return ret;
}
