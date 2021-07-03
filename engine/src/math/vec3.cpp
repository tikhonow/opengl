#include <cmath>
#include "vec3.hpp"
#include "utils.hpp"

using Vec3 = cglm::Vec3;

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float value) : x(value), y(value), z(value) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)  {}

Vec3::Vec3(const Vec3 &src) {
  x = src.x;
  y = src.y;
  z = src.z;
}

Vec3::Vec3(Vec3 &&src) noexcept {
  x = src.x;
  y = src.y;
  z = src.z;
}

bool Vec3::operator==(const Vec3 &src) const {
  return (
     cglm::IsFloatEqual(x, src.x) &&
     cglm::IsFloatEqual(y, src.y) &&
     cglm::IsFloatEqual(z, src.z));
}

bool Vec3::operator!=(const Vec3 &src) const {
  return !(
     cglm::IsFloatEqual(x, src.x) &&
     cglm::IsFloatEqual(y, src.y) &&
     cglm::IsFloatEqual(z, src.z));
}

Vec3 Vec3::operator+(const Vec3 &src) const {
  return {x + src.x, y + src.y, z + src.z};
}

Vec3 Vec3::operator-(const Vec3 &src) const {
  return {x - src.x, y - src.y, z - src.z};
}

Vec3 Vec3::operator*(float val) const {
  return {x * val, y * val, z * val};
}

Vec3 Vec3::operator/(float val) const {
  return {x / val, y / val, z / val};
}

Vec3 &Vec3::operator+=(const Vec3 &src) {
  x += src.x;
  y += src.y;
  z += src.z;
  return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &src) {
  x -= src.x;
  y -= src.y;
  z -= src.z;
  return *this;
}

Vec3 &Vec3::operator*=(float v) {
  x *= v;
  y *= v;
  z *= v;
  return *this;
}

Vec3 &Vec3::operator/=(float v) {
  x /= v;
  y /= v;
  z /= v;
  return *this;
}

float Vec3::length() const {
  return sqrtf(x * x + y * y + z * z);
}

float Vec3::operator*(const Vec3 &src) const {
  return (
    x * src.x +
    y * src.y +
    z * src.z);
}

Vec3 Vec3::normalize() const {
  float inv_length = 1.0f / sqrtf(x*x + y*y + z*z);
  return (*this * inv_length);
}

Vec3 &Vec3::operator=(const Vec3 &) = default;


