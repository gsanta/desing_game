#pragma once

#include <iostream>

namespace spright
{
namespace maths
{

    struct Vec4
    {
        Vec4();

        Vec4(const float &x, const float &y, const float &z, const float &w);

        Vec4(float n);

        Vec4 &add(const Vec4 &other);

        Vec4 &subtract(const Vec4 &other);

        Vec4 &multiply(const Vec4 &other);

        Vec4 &divide(const Vec4 &other);

        friend Vec4 operator+(Vec4 left, const Vec4 &right);

        friend Vec4 operator-(Vec4 left, const Vec4 &right);

        friend Vec4 operator*(Vec4 left, const Vec4 &right);

        friend Vec4 operator/(Vec4 left, const Vec4 &right);

        friend std::ostream &operator<<(std::ostream &stream, const Vec4 vec);

        bool operator==(const Vec4 &other);

        bool operator!=(const Vec4 &other);

        Vec4 &operator+=(const Vec4 &other);

        Vec4 &operator-=(const Vec4 &other);

        Vec4 &operator*=(const Vec4 &other);

        Vec4 &operator/=(const Vec4 &other);

        float operator[](int index) const;

        float x, y, z, w;
    };
} // namespace maths
} // namespace spright
