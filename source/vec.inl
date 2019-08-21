#ifndef INL_VEC
#define INL_VEC

#include <cmath>

// ---- vec2 ---- //

inline vec2& vec2::operator+=(const vec2& vec){
    x += vec.x;
    y += vec.y;
    return *this;
}
inline vec2& vec2::operator+=(const float f){
    x += f;
    y += f;
    return *this;
}
inline vec2& vec2::operator-=(const vec2& vec){
    x -= vec.x;
    y -= vec.y;
    return *this;
}
inline vec2& vec2::operator-=(const float f){
    x -= f;
    y -= f;
    return *this;
}
inline vec2& vec2::operator*=(const vec2& vec){
    x *= vec.x;
    y *= vec.y;
    return *this;
}
inline vec2& vec2::operator*=(const float f){
    x *= f;
    y *= f;
    return *this;
}
inline vec2& vec2::operator/=(const vec2& vec){
    x /= vec.x;
    y /= vec.y;
    return *this;
}
inline vec2& vec2::operator/=(const float f){
    x /= f;
    y /= f;
    return *this;
}

inline vec2 vec2::operator+() const{
    return *this;
}
inline vec2 vec2::operator-() const{
    return vec2(-x, -y);
}

inline vec2 operator+(const vec2& lhs, const vec2& rhs){
    return vec2(lhs) += rhs;
}
inline vec2 operator-(const vec2& lhs, const vec2& rhs){
    return vec2(lhs) -= rhs;
}
inline vec2 operator*(const vec2& lhs, const vec2& rhs){
    return vec2(lhs) *= rhs;
}
inline vec2 operator/(const vec2& lhs, const vec2& rhs){
    return vec2(lhs) /= rhs;
}

inline vec2 operator+(const vec2& lhs, const float rhs){
    return vec2(lhs) += rhs;
}
inline vec2 operator-(const vec2& lhs, const float rhs){
    return vec2(lhs) -= rhs;
}
inline vec2 operator*(const vec2& lhs, const float rhs){
    return vec2(lhs) *= rhs;
}
inline vec2 operator/(const vec2& lhs, const float rhs){
    return vec2(lhs) /= rhs;
}

inline vec2 operator+(const float lhs, const vec2& rhs){
    return vec2(rhs) += lhs;
}
inline vec2 operator-(const float lhs, const vec2& rhs){
    return vec2(rhs) -= lhs;
}
inline vec2 operator*(const float lhs, const vec2& rhs){
    return vec2(rhs) *= lhs;
}
inline vec2 operator/(const float lhs, const vec2& rhs){
    return vec2(rhs) /= lhs;
}

inline float dot(const vec2& vA, const vec2& vB){
    return vA.x * vB.x + vA.y * vB.y;
}
inline float length(const vec2& vec){
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
inline float sqlength(const vec2& vec){
    return vec.x * vec.x + vec.y * vec.y;
}

inline vec2 normalize(const vec2& vec){
    return vec / length(vec);
}

// ---- vec3 ---- //

inline vec3& vec3::operator+=(const vec3& vec){
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}
inline vec3& vec3::operator+=(const float f){
    x += f;
    y += f;
    z += f;
    return *this;
}
inline vec3& vec3::operator-=(const vec3& vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}
inline vec3& vec3::operator-=(const float f){
    x -= f;
    y -= f;
    z -= f;
    return *this;
}
inline vec3& vec3::operator*=(const vec3& vec){
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}
inline vec3& vec3::operator*=(const float f){
    x *= f;
    y *= f;
    z *= f;
    return *this;
}
inline vec3& vec3::operator/=(const vec3& vec){
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}
inline vec3& vec3::operator/=(const float f){
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

inline vec3 vec3::operator+() const{
    return *this;
}
inline vec3 vec3::operator-() const{
    return vec3(-x, -y, -z);
}

inline vec3 operator+(const vec3& lhs, const vec3& rhs){
    return vec3(lhs) += rhs;
}
inline vec3 operator-(const vec3& lhs, const vec3& rhs){
    return vec3(lhs) -= rhs;
}
inline vec3 operator*(const vec3& lhs, const vec3& rhs){
    return vec3(lhs) *= rhs;
}
inline vec3 operator/(const vec3& lhs, const vec3& rhs){
    return vec3(lhs) /= rhs;
}

inline vec3 operator+(const vec3& lhs, const float rhs){
    return vec3(lhs) += rhs;
}
inline vec3 operator-(const vec3& lhs, const float rhs){
    return vec3(lhs) -= rhs;
}
inline vec3 operator*(const vec3& lhs, const float rhs){
    return vec3(lhs) *= rhs;
}
inline vec3 operator/(const vec3& lhs, const float rhs){
    return vec3(lhs) /= rhs;
}

inline vec3 operator+(const float lhs, const vec3& rhs){
    return vec3(rhs) += lhs;
}
inline vec3 operator-(const float lhs, const vec3& rhs){
    return vec3(rhs) -= lhs;
}
inline vec3 operator*(const float lhs, const vec3& rhs){
    return vec3(rhs) *= lhs;
}
inline vec3 operator/(const float lhs, const vec3& rhs){
    return vec3(rhs) /= lhs;
}

inline float dot(const vec3& vA, const vec3& vB){
    return vA.x * vB.x + vA.y * vB.y + vA.z * vB.z;
}
inline vec3 cross(const vec3& vA, const vec3& vB){
    return vec3(vA.y * vB.z - vA.z * vB.y,
                vA.z * vB.x - vA.x * vB.z,
                vA.x * vB.y - vA.y * vB.x);
}
inline float length(const vec3& vec){
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
inline float sqlength(const vec3& vec){
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}
inline vec3 normalize(const vec3& vec){
    return vec / length(vec);
}

#endif
