#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC3_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC3_HPP_

namespace cglm {

class Vec3 {
 public:
  Vec3();
  explicit Vec3(float value);
  Vec3(float x, float y, float z = 0.0f);

  Vec3(const Vec3&);
  Vec3(Vec3 &&) noexcept;

  ~Vec3() = default;

  bool operator==(const Vec3 &) const;
  bool operator!=(const Vec3 &) const;

  Vec3 operator+(const Vec3 &) const;
  Vec3 operator-(const Vec3 &) const;

  Vec3 operator*(float) const;  // multiplication with number
  Vec3 operator/(float) const;

  Vec3& operator=(const Vec3 &);
  Vec3& operator+=(const Vec3 &);
  Vec3& operator-=(const Vec3 &);

  Vec3& operator*=(float);
  Vec3& operator/=(float);

  float length() const;
  float operator*(const Vec3 &) const;  // scalar multiplication

  Vec3 normalize() const;

  float x, y, z;
};

}  // cglm

#endif //COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC3_HPP_
