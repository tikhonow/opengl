#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_MAT4_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_MAT4_HPP_

#include <array>
#include "vec4.hpp"
#include "vec3.hpp"
#include <stdint.h>
#include <stdint.h>

namespace cglm {

class Mat4 {
 public:
  using vec_type = cglm::Vec4;
  using vec_array = std::array<vec_type, 4>;

  //  -- Constructors --
  Mat4();
  explicit Mat4(float v);
  explicit Mat4(vec_type const &diag_vec);
  Mat4(float, float, float, float);
  Mat4(const vec_type &r0, const vec_type &r1,
       const vec_type &r2, const vec_type &r3);

  // -- Accessors --
  vec_type get_row(uint32_t r) const;
  vec_type get_col(uint32_t c) const;
  vec_type get_diag() const noexcept;
  vec_type operator[](unsigned r) const;

  // -- Binary arithmetic operations --
  Mat4 operator+(const Mat4 &) const;
  Mat4 operator-(const Mat4 &) const;
  Mat4 operator*(const Mat4 &) const;

  // -- Scalar arithmetic operations --
  Mat4 operator*(float) const;
  Mat4 operator/(float) const;
  Mat4 operator+(float) const;
  Mat4 operator-(float) const;

  vec_type operator*(const vec_type &) const;

  // -- Matrix transformations --
  Mat4 GetTransposed() const;
  Mat4 GetInverse() const;
  Mat4 Translate(const Vec3&) const;
  Mat4 Rotate(float degrees, const Vec3& axis_vec) const;

  // -- Comparison methods --
  bool operator==(const Mat4 &) const noexcept;
  bool operator!=(const Mat4 &) const noexcept;

 private:
  vec_array rows_;
};

}

#endif //COMPUTER_GRAPHICS_COURSE_SRC_MATH_MAT4_HPP_
