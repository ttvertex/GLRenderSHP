///////////////////////////////////////////////////////////////////////////////
// Vectors.h
// =========
// 2D/3D/4D vectors
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2007-02-14
// UPDATED: 2013-01-20
//
// Copyright (C) 2007-2013 Song Ho Ahn
///////////////////////////////////////////////////////////////////////////////


#ifndef VECTORS_H_DEF
#define VECTORS_H_DEF

#include <cmath>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// 2D vector
///////////////////////////////////////////////////////////////////////////////
struct vec2
{
    float x;
    float y;

    // ctors
    vec2() : x(0), y(0) {};
    vec2(float x, float y) : x(x), y(y) {};

    // utils functions
    void        set(float x, float y);
    float       length() const;                         //
    float       distance(const vec2& vec) const;     // distance between two vectors
    vec2&    normalize();                            //
    float       dot(const vec2& vec) const;          // dot product
    bool        equal(const vec2& vec, float e) const; // compare with epsilon

    // operators
    vec2     operator-() const;                      // unary operator (negate)
    vec2     operator+(const vec2& rhs) const;    // add rhs
    vec2     operator-(const vec2& rhs) const;    // subtract rhs
    vec2&    operator+=(const vec2& rhs);         // add rhs and update this object
    vec2&    operator-=(const vec2& rhs);         // subtract rhs and update this object
    vec2     operator*(const float scale) const;     // scale
    vec2     operator*(const vec2& rhs) const;    // multiply each element
    vec2&    operator*=(const float scale);          // scale and update this object
    vec2&    operator*=(const vec2& rhs);         // multiply each element and update this object
    vec2     operator/(const float scale) const;     // inverse scale
    vec2&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const vec2& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const vec2& rhs) const;   // exact compare, no epsilon
    bool        operator<(const vec2& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend vec2 operator*(const float a, const vec2 vec);
    friend std::ostream& operator<<(std::ostream& os, const vec2& vec);
};



///////////////////////////////////////////////////////////////////////////////
// 3D vector
///////////////////////////////////////////////////////////////////////////////
struct vec3
{
    float x;
    float y;
    float z;

    // ctors
    vec3() : x(0), y(0), z(0) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};

    // utils functions
    void        set(float x, float y, float z);
    float       length() const;                         //
    float       distance(const vec3& vec) const;     // distance between two vectors
    vec3&    normalize();                            //
    float       dot(const vec3& vec) const;          // dot product
    vec3     cross(const vec3& vec) const;        // cross product
    bool        equal(const vec3& vec, float e) const; // compare with epsilon

    // operators
    vec3     operator-() const;                      // unary operator (negate)
    vec3     operator+(const vec3& rhs) const;    // add rhs
    vec3     operator-(const vec3& rhs) const;    // subtract rhs
    vec3&    operator+=(const vec3& rhs);         // add rhs and update this object
    vec3&    operator-=(const vec3& rhs);         // subtract rhs and update this object
    vec3     operator*(const float scale) const;     // scale
    vec3     operator*(const vec3& rhs) const;    // multiplay each element
    vec3&    operator*=(const float scale);          // scale and update this object
    vec3&    operator*=(const vec3& rhs);         // product each element and update this object
    vec3     operator/(const float scale) const;     // inverse scale
    vec3&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const vec3& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const vec3& rhs) const;   // exact compare, no epsilon
    bool        operator<(const vec3& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend vec3 operator*(const float a, const vec3 vec);
    friend std::ostream& operator<<(std::ostream& os, const vec3& vec);
};



///////////////////////////////////////////////////////////////////////////////
// 4D vector
///////////////////////////////////////////////////////////////////////////////
struct vec4
{
    float x;
    float y;
    float z;
    float w;

    // ctors
    vec4() : x(0), y(0), z(0), w(0) {};
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

    // utils functions
    void        set(float x, float y, float z, float w);
    float       length() const;                         //
    float       distance(const vec4& vec) const;     // distance between two vectors
    vec4&    normalize();                            //
    float       dot(const vec4& vec) const;          // dot product
    bool        equal(const vec4& vec, float e) const; // compare with epsilon

    // operators
    vec4     operator-() const;                      // unary operator (negate)
    vec4     operator+(const vec4& rhs) const;    // add rhs
    vec4     operator-(const vec4& rhs) const;    // subtract rhs
    vec4&    operator+=(const vec4& rhs);         // add rhs and update this object
    vec4&    operator-=(const vec4& rhs);         // subtract rhs and update this object
    vec4     operator*(const float scale) const;     // scale
    vec4     operator*(const vec4& rhs) const;    // multiply each element
    vec4&    operator*=(const float scale);          // scale and update this object
    vec4&    operator*=(const vec4& rhs);         // multiply each element and update this object
    vec4     operator/(const float scale) const;     // inverse scale
    vec4&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const vec4& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const vec4& rhs) const;   // exact compare, no epsilon
    bool        operator<(const vec4& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend vec4 operator*(const float a, const vec4 vec);
    friend std::ostream& operator<<(std::ostream& os, const vec4& vec);
};



// fast math routines from Doom3 SDK
inline float invSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;          // get bits for floating value
    i = 0x5f3759df - (i>>1);    // gives initial guess
    x = *(float*)&i;            // convert bits back to float
    x = x * (1.5f - xhalf*x*x); // Newton step
    return x;
}



///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector2
///////////////////////////////////////////////////////////////////////////////
inline vec2 vec2::operator-() const {
    return vec2(-x, -y);
}

inline vec2 vec2::operator+(const vec2& rhs) const {
    return vec2(x+rhs.x, y+rhs.y);
}

inline vec2 vec2::operator-(const vec2& rhs) const {
    return vec2(x-rhs.x, y-rhs.y);
}

inline vec2& vec2::operator+=(const vec2& rhs) {
    x += rhs.x; y += rhs.y; return *this;
}

inline vec2& vec2::operator-=(const vec2& rhs) {
    x -= rhs.x; y -= rhs.y; return *this;
}

inline vec2 vec2::operator*(const float a) const {
    return vec2(x*a, y*a);
}

inline vec2 vec2::operator*(const vec2& rhs) const {
    return vec2(x*rhs.x, y*rhs.y);
}

inline vec2& vec2::operator*=(const float a) {
    x *= a; y *= a; return *this;
}

inline vec2& vec2::operator*=(const vec2& rhs) {
    x *= rhs.x; y *= rhs.y; return *this;
}

inline vec2 vec2::operator/(const float a) const {
    return vec2(x/a, y/a);
}

inline vec2& vec2::operator/=(const float a) {
    x /= a; y /= a; return *this;
}

inline bool vec2::operator==(const vec2& rhs) const {
    return (x == rhs.x) && (y == rhs.y);
}

inline bool vec2::operator!=(const vec2& rhs) const {
    return (x != rhs.x) || (y != rhs.y);
}

inline bool vec2::operator<(const vec2& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    return false;
}

inline float vec2::operator[](int index) const {
    return (&x)[index];
}

inline float& vec2::operator[](int index) {
    return (&x)[index];
}

inline void vec2::set(float x, float y) {
    this->x = x; this->y = y;
}

inline float vec2::length() const {
    return sqrtf(x*x + y*y);
}

inline float vec2::distance(const vec2& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y));
}

inline vec2& vec2::normalize() {
    //@@const float EPSILON = 0.000001f;
    float xxyy = x*x + y*y;
    //@@if(xxyy < EPSILON)
    //@@    return *this;

    //float invLength = invSqrt(xxyy);
    float invLength = 1.0f / sqrtf(xxyy);
    x *= invLength;
    y *= invLength;
    return *this;
}

inline float vec2::dot(const vec2& rhs) const {
    return (x*rhs.x + y*rhs.y);
}

inline bool vec2::equal(const vec2& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
}

inline vec2 operator*(const float a, const vec2 vec) {
    return vec2(a*vec.x, a*vec.y);
}

inline std::ostream& operator<<(std::ostream& os, const vec2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
// END OF VECTOR2 /////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector3
///////////////////////////////////////////////////////////////////////////////
inline vec3 vec3::operator-() const {
    return vec3(-x, -y, -z);
}

inline vec3 vec3::operator+(const vec3& rhs) const {
    return vec3(x+rhs.x, y+rhs.y, z+rhs.z);
}

inline vec3 vec3::operator-(const vec3& rhs) const {
    return vec3(x-rhs.x, y-rhs.y, z-rhs.z);
}

inline vec3& vec3::operator+=(const vec3& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; return *this;
}

inline vec3& vec3::operator-=(const vec3& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;
}

inline vec3 vec3::operator*(const float a) const {
    return vec3(x*a, y*a, z*a);
}

inline vec3 vec3::operator*(const vec3& rhs) const {
    return vec3(x*rhs.x, y*rhs.y, z*rhs.z);
}

inline vec3& vec3::operator*=(const float a) {
    x *= a; y *= a; z *= a; return *this;
}

inline vec3& vec3::operator*=(const vec3& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this;
}

inline vec3 vec3::operator/(const float a) const {
    return vec3(x/a, y/a, z/a);
}

inline vec3& vec3::operator/=(const float a) {
    x /= a; y /= a; z /= a; return *this;
}

inline bool vec3::operator==(const vec3& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool vec3::operator!=(const vec3& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline bool vec3::operator<(const vec3& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    return false;
}

inline float vec3::operator[](int index) const {
    return (&x)[index];
}

inline float& vec3::operator[](int index) {
    return (&x)[index];
}

inline void vec3::set(float x, float y, float z) {
    this->x = x; this->y = y; this->z = z;
}

inline float vec3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

inline float vec3::distance(const vec3& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z));
}

inline vec3& vec3::normalize() {
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x*x + y*y + z*z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is ~zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline float vec3::dot(const vec3& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z);
}

inline vec3 vec3::cross(const vec3& rhs) const {
    return vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

inline bool vec3::equal(const vec3& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

inline vec3 operator*(const float a, const vec3 vec) {
    return vec3(a*vec.x, a*vec.y, a*vec.z);
}

inline std::ostream& operator<<(std::ostream& os, const vec3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
// END OF VECTOR3 /////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector4
///////////////////////////////////////////////////////////////////////////////
inline vec4 vec4::operator-() const {
    return vec4(-x, -y, -z, -w);
}

inline vec4 vec4::operator+(const vec4& rhs) const {
    return vec4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

inline vec4 vec4::operator-(const vec4& rhs) const {
    return vec4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

inline vec4& vec4::operator+=(const vec4& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this;
}

inline vec4& vec4::operator-=(const vec4& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this;
}

inline vec4 vec4::operator*(const float a) const {
    return vec4(x*a, y*a, z*a, w*a);
}

inline vec4 vec4::operator*(const vec4& rhs) const {
    return vec4(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
}

inline vec4& vec4::operator*=(const float a) {
    x *= a; y *= a; z *= a; w *= a; return *this;
}

inline vec4& vec4::operator*=(const vec4& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this;
}

inline vec4 vec4::operator/(const float a) const {
    return vec4(x/a, y/a, z/a, w/a);
}

inline vec4& vec4::operator/=(const float a) {
    x /= a; y /= a; z /= a; w /= a; return *this;
}

inline bool vec4::operator==(const vec4& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

inline bool vec4::operator!=(const vec4& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

inline bool vec4::operator<(const vec4& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    if(w < rhs.w) return true;
    if(w > rhs.w) return false;
    return false;
}

inline float vec4::operator[](int index) const {
    return (&x)[index];
}

inline float& vec4::operator[](int index) {
    return (&x)[index];
}

inline void vec4::set(float x, float y, float z, float w) {
    this->x = x; this->y = y; this->z = z; this->w = w;
}

inline float vec4::length() const {
    return sqrtf(x*x + y*y + z*z + w*w);
}

inline float vec4::distance(const vec4& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z) + (vec.w-w)*(vec.w-w));
}

inline vec4& vec4::normalize() {
    //NOTE: leave w-component untouched
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x*x + y*y + z*z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline float vec4::dot(const vec4& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w);
}

inline bool vec4::equal(const vec4& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon &&
           fabs(z - rhs.z) < epsilon && fabs(w - rhs.w) < epsilon;
}

inline vec4 operator*(const float a, const vec4 vec) {
    return vec4(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
}

inline std::ostream& operator<<(std::ostream& os, const vec4& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}
// END OF VECTOR4 /////////////////////////////////////////////////////////////

#endif
