#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC4_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC4_HPP_

namespace cglm {

class Vec4 {
 public:
  Vec4();
  explicit Vec4(float value);
  Vec4(float x, float y, float z = 0.0f, float w = 0.0f);

  Vec4(const Vec4 &);
  Vec4(Vec4 &&) noexcept;

  ~Vec4() = default;

  bool operator==(const Vec4 &) const;
  bool operator!=(const Vec4 &) const;

  Vec4 operator+(const Vec4 &) const;
  Vec4 operator-(const Vec4 &) const;

  Vec4 operator*(float) const;  // multiplication with number
  Vec4 operator/(float) const;

  Vec4 &operator=(const Vec4 &);
  Vec4 &operator+=(const Vec4 &);
  Vec4 &operator-=(const Vec4 &);

  Vec4 &operator*=(float);
  Vec4 &operator/=(float);

  float length() const;
  float operator*(const Vec4 &) const;  // scalar multiplication

  Vec4 normalize() const;

  float x, y, z, w;
};

}  // cglm

#endif //COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC4_HPP_
