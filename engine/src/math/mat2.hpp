#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_MAT2_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_MAT2_HPP_

#include <array>
#include "vec2.hpp"
#include <stdint.h>

namespace cglm {

class Mat2 {
 public:
  using vec_type = cglm::Vec2;
  using vec_array = std::array<vec_type, 2>;

  // -- Constructors --
  Mat2();
  explicit Mat2(float);
  explicit Mat2(vec_type const& diag_vec);
  Mat2(float, float);
  Mat2(const Vec2& r1, const Vec2& r2);

  Mat2(const Mat2&) = default;

  // -- Access --
  vec_type get_row(uint32_t r) const;
  vec_type get_col(uint32_t c) const;
  vec_type get_diag() const noexcept;
  vec_type operator[](unsigned r) const;
  inline float det() const noexcept;

  // -- Binary arithmetic operations --
  Mat2 operator+(const Mat2&) const;
  Mat2 operator-(const Mat2&) const;
  Mat2 operator*(const Mat2&) const;
  Mat2 operator*(float) const;
  Mat2 operator/(float) const;
  Mat2 operator+(float) const;
  Mat2 operator-(float) const;
  Vec2 operator*(const vec_type&) const;

  // -- Matrix transformations --
  Mat2 GetInverse() const;
  Mat2 GetTransposed() const noexcept;

  // -- Comparison methods --
  bool operator==(const Mat2&) const noexcept;
  bool operator!=(const Mat2&) const noexcept;

 private:
  vec_array rows_;
};

}  // namespace cglm

#endif //COMPUTER_GRAPHICS_COURSE_SRC_MATH_MAT2_HPP_
