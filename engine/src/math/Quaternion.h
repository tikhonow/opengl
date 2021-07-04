//
// Created by tikhonow on 7/4/21.
//

#ifndef CRY_QUATERNION_H
#define CRY_QUATERNION_H
#include "vec3.hpp"
#define M_PI       3.14159265358979323846f


namespace cglm {
class Quaternion {
public:

    // Radians
    float w;
    // Vector
    Vec3 vector;

    // Constructors
    Quaternion();
    Quaternion(float _w, const Vector3D& _vector);
    Quaternion(float _w, float x, float y, float z);
    Quaternion(const Quaternion& quaternion);
    Quaternion& operator=(const Quaternion& quaternion);

    ~Quaternion();

    Quaternion operator+(const Quaternion& quaternion);
    void operator+=(const Quaternion& quaternion);

    Quaternion operator-(const Quaternion& quaternion);
    void operator-=(const Quaternion& quaternion);

    Quaternion operator*(Quaternion& quaternion);
    void operator*=(Quaternion& quaternion);
    Quaternion Multiplication(Quaternion& quaternion);

    void operator*=(const float value);
    Quaternion operator*(const float value);

    void DegreesToRadians();
    void Inverse();

};
}

#endif //CRY_QUATERNION_H
