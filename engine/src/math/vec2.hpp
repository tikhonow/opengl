#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC2_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC2_HPP_

namespace cglm {

class Vec2 {
 public:
  Vec2();
  explicit Vec2(float value);
  Vec2(float x, float y);

  Vec2(const Vec2&);
  Vec2(Vec2 &&) noexcept;

  ~Vec2() = default;

  bool operator==(const Vec2 &) const;
  bool operator!=(const Vec2 &) const;

  Vec2 operator+(const Vec2 &) const;
  Vec2 operator-(const Vec2 &) const;

  Vec2 operator*(float) const;  // multiplication with number
  Vec2 operator/(float) const;

  Vec2& operator=(const Vec2 &) = default;
  Vec2& operator+=(const Vec2 &);
  Vec2& operator-=(const Vec2 &);

  Vec2& operator*=(float);
  Vec2& operator/=(float);

  float length() const;
  float operator*(const Vec2 &) const;  // scalar multiplication

  Vec2 normalize() const;

  float x, y;
};

}  // cglm

#endif  //COMPUTER_GRAPHICS_COURSE_SRC_MATH_VEC2_HPP_
