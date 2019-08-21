#ifndef H_VEC
#define H_VEC

// ---- vec2 ---- //

struct vec2{

    vec2();
    vec2(const float f);
    vec2(const float ix, const float iy);

    inline vec2& operator+=(const vec2& vec);
    inline vec2& operator+=(const float f);
    inline vec2& operator-=(const float f);
    inline vec2& operator-=(const vec2& vec);
    inline vec2& operator*=(const vec2& vec);
    inline vec2& operator*=(const float f);
    inline vec2& operator/=(const vec2& vec);
    inline vec2& operator/=(const float f);

    inline vec2 operator+() const;
    inline vec2 operator-() const;

    union{
        float data[2];
        struct{
            float x;
            float y;
        };
    };
};

inline vec2 operator+(const vec2& lhs, const vec2& rhs);
inline vec2 operator-(const vec2& lhs, const vec2& rhs);
inline vec2 operator*(const vec2& lhs, const vec2& rhs);
inline vec2 operator/(const vec2& lhs, const vec2& rhs);

inline vec2 operator+(const vec2& lhs, const float rhs);
inline vec2 operator-(const vec2& lhs, const float rhs);
inline vec2 operator*(const vec2& lhs, const float rhs);
inline vec2 operator/(const vec2& lhs, const float rhs);

inline vec2 operator+(const float lhs, const vec2& rhs);
inline vec2 operator-(const float lhs, const vec2& rhs);
inline vec2 operator*(const float lhs, const vec2& rhs);
inline vec2 operator/(const float lhs, const vec2& rhs);

inline float dot(const vec2& vA, const vec2& vB);
inline float length(const vec2& vec);
inline float sqlength(const vec2& vec);
inline vec2 normalize(const vec2& vec);

// ---- vec3 ---- //

struct vec3{

    vec3();
    vec3(const float f);
    vec3(const float ix, const float iy, const float iz);

    inline vec3& operator+=(const vec3& vec);
    inline vec3& operator+=(const float f);
    inline vec3& operator-=(const vec3& vec);
    inline vec3& operator-=(const float f);
    inline vec3& operator*=(const vec3& vec);
    inline vec3& operator*=(const float f);
    inline vec3& operator/=(const vec3& vec);
    inline vec3& operator/=(const float f);

    inline vec3 operator+() const;
    inline vec3 operator-() const;

    union{
        float data[3];
        struct{
            float x;
            float y;
            float z;
        };
        struct{
            float r;
            float g;
            float b;
        };
    };
};

inline vec3 operator+(const vec3& lhs, const vec3& rhs);
inline vec3 operator-(const vec3& lhs, const vec3& rhs);
inline vec3 operator*(const vec3& lhs, const vec3& rhs);
inline vec3 operator/(const vec3& lhs, const vec3& rhs);

inline vec3 operator+(const vec3& lhs, const float rhs);
inline vec3 operator-(const vec3& lhs, const float rhs);
inline vec3 operator*(const vec3& lhs, const float rhs);
inline vec3 operator/(const vec3& lhs, const float rhs);

inline vec3 operator+(const float lhs, const vec3& rhs);
inline vec3 operator-(const float lhs, const vec3& rhs);
inline vec3 operator*(const float lhs, const vec3& rhs);
inline vec3 operator/(const float lhs, const vec3& rhs);

inline float dot(const vec3& vA, const vec3& vB);
inline vec3 cross(const vec3& vA, const vec3& vB);
inline float length(const vec3& vec);
inline float sqlength(const vec3& vec);
inline vec3 normalize(const vec3& vec);

#include "vec.inl"

#endif
