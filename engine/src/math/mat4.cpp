#include "mat4.hpp"
#include "exception.hpp"
#include "utils.hpp"
#include <math.h>
#include <stdint.h>

using vec_type = cglm::Vec4;
using Mat4 = cglm::Mat4;

Mat4::Mat4() {
  rows_[0] = {1, 0, 0, 0};
  rows_[1] = {0, 1, 0, 0};
  rows_[2] = {0, 0, 1, 0};
  rows_[3] = {0, 0, 0, 1};
}

Mat4::Mat4(float v) {
  rows_[0] = {v, 0, 0, 0};
  rows_[1] = {0, v, 0, 0};
  rows_[2] = {0, 0, v, 0};
  rows_[3] = {0, 0, 0, v};
}

Mat4::Mat4(const vec_type &diag_vec) {
  rows_[0] = {diag_vec.x, 0, 0, 0};
  rows_[1] = {0, diag_vec.y, 0, 0};
  rows_[2] = {0, 0, diag_vec.z, 0};
  rows_[3] = {0, 0, 0, diag_vec.w};
}

Mat4::Mat4(float v0, float v1, float v2, float v3) {
  rows_[0] = {v0, 0, 0, 0};
  rows_[1] = {0, v1, 0, 0};
  rows_[2] = {0, 0, v2, 0};
  rows_[3] = {0, 0, 0, v3};
}

Mat4::Mat4(const vec_type &r0, const vec_type &r1, const vec_type &r2, const vec_type &r3) {
  rows_[0] = r0;
  rows_[1] = r1;
  rows_[2] = r2;
  rows_[3] = r3;
}

vec_type Mat4::get_row(uint32_t r) const {
  if (r < 0u || r > 3u)
    throw cglm::OutOfRangeException();
  else
    return rows_[r];
}

vec_type Mat4::get_col(uint32_t c) const {
  if (c < 0u || c > 3u)
    throw cglm::OutOfRangeException();
  else if (c == 0)
    return {rows_[0].x, rows_[1].x, rows_[2].x, rows_[3].x};
  else if (c == 1)
    return {rows_[0].y, rows_[1].y, rows_[2].y, rows_[3].y};
  else if (c == 2)
    return {rows_[0].z, rows_[1].z, rows_[2].z, rows_[3].z};
  else
    return {rows_[0].w, rows_[1].w, rows_[2].w, rows_[3].w};
}

vec_type Mat4::get_diag() const noexcept {
  return {rows_[0].x, rows_[1].y, rows_[2].z, rows_[3].w};
}

vec_type Mat4::operator[](unsigned int r) const {
  if (r < 0u || r > 3u)
    throw cglm::OutOfRangeException();
  else
    return rows_[r];
}

Mat4 cglm::Mat4::operator+(const Mat4 &src) const {
  return {{rows_[0] + src[0]},
          {rows_[1] + src[1]},
          {rows_[2] + src[2]},
          {rows_[3] + src[3]}};
}

Mat4 cglm::Mat4::operator-(const Mat4 &src) const {
  return {{rows_[0] - src[0]},
          {rows_[1] - src[1]},
          {rows_[2] - src[2]},
          {rows_[3] - src[3]}};
}

Mat4 cglm::Mat4::operator*(const Mat4 &src) const {
  vec_type row0(rows_[0] * src.get_col(0),
                rows_[0] * src.get_col(1),
                rows_[0] * src.get_col(2),
                rows_[0] * src.get_col(3));
  vec_type row1(rows_[1] * src.get_col(0),
                rows_[1] * src.get_col(1),
                rows_[1] * src.get_col(2),
                rows_[1] * src.get_col(3));
  vec_type row2(rows_[2] * src.get_col(0),
                rows_[2] * src.get_col(1),
                rows_[2] * src.get_col(2),
                rows_[2] * src.get_col(3));
  vec_type row3(rows_[3] * src.get_col(0),
                rows_[3] * src.get_col(1),
                rows_[3] * src.get_col(2),
                rows_[3] * src.get_col(3));

  return {row0, row1, row2, row3};
}

Mat4 cglm::Mat4::operator*(float v) const {
  return {{rows_[0] * v},
          {rows_[1] * v},
          {rows_[2] * v},
          {rows_[3] * v}};
}

Mat4 cglm::Mat4::operator/(float v) const {
  return {{rows_[0] / v},
          {rows_[1] / v},
          {rows_[2] / v},
          {rows_[3] / v}};
}

Mat4 cglm::Mat4::operator+(float val) const {
  vec_type row0(rows_[0].x + val, rows_[0].y + val,
                rows_[0].z + val, rows_[0].w + val);
  vec_type row1(rows_[1].x + val, rows_[1].y + val,
                rows_[1].z + val, rows_[1].w + val);
  vec_type row2(rows_[2].x + val, rows_[2].y + val,
                rows_[2].z + val, rows_[2].w + val);
  vec_type row3(rows_[3].x + val, rows_[3].y + val,
                rows_[3].z + val, rows_[3].w + val);

  return {row0, row1, row2, row3};
}

Mat4 cglm::Mat4::operator-(float val) const {
  vec_type row0(rows_[0].x - val, rows_[0].y - val,
                rows_[0].z - val, rows_[0].w - val);
  vec_type row1(rows_[1].x - val, rows_[1].y - val,
                rows_[1].z - val, rows_[1].w - val);
  vec_type row2(rows_[2].x - val, rows_[2].y - val,
                rows_[2].z - val, rows_[2].w - val);
  vec_type row3(rows_[3].x - val, rows_[3].y - val,
                rows_[3].z - val, rows_[3].w - val);

  return {row0, row1, row2, row3};
}

vec_type cglm::Mat4::operator*(const vec_type &vec) const {
  return {rows_[0] * vec,
          rows_[1] * vec,
          rows_[2] * vec,
          rows_[3] * vec};
}

Mat4 cglm::Mat4::GetTransposed() const {
  return {get_col(0),
          get_col(1),
          get_col(2),
          get_col(3)};
}

Mat4 cglm::Mat4::GetInverse() const {
  // algorithm interpreted from MESA implementation of the glu library

  float m[16] = {rows_[0].x, rows_[0].y, rows_[0].z, rows_[0].w,
                 rows_[1].x, rows_[1].y, rows_[1].z, rows_[1].w,
                 rows_[2].x, rows_[2].y, rows_[2].z, rows_[2].w,
                 rows_[3].x, rows_[3].y, rows_[3].z, rows_[3].w};

  auto x0 = m[5]  * m[10] * m[15] -
      m[5]  * m[11] * m[14] -
      m[9]  * m[6]  * m[15] +
      m[9]  * m[7]  * m[14] +
      m[13] * m[6]  * m[11] -
      m[13] * m[7]  * m[10];

  auto x1 = -m[4]  * m[10] * m[15] +
      m[4]  * m[11] * m[14] +
      m[8]  * m[6]  * m[15] -
      m[8]  * m[7]  * m[14] -
      m[12] * m[6]  * m[11] +
      m[12] * m[7]  * m[10];

  auto x2 = m[4]  * m[9] * m[15] -
      m[4]  * m[11] * m[13] -
      m[8]  * m[5] * m[15] +
      m[8]  * m[7] * m[13] +
      m[12] * m[5] * m[11] -
      m[12] * m[7] * m[9];

  auto x3 = -m[4]  * m[9] * m[14] +
      m[4]  * m[10] * m[13] +
      m[8]  * m[5] * m[14] -
      m[8]  * m[6] * m[13] -
      m[12] * m[5] * m[10] +
      m[12] * m[6] * m[9];

  auto y0 = -m[1]  * m[10] * m[15] +
      m[1]  * m[11] * m[14] +
      m[9]  * m[2] * m[15] -
      m[9]  * m[3] * m[14] -
      m[13] * m[2] * m[11] +
      m[13] * m[3] * m[10];

  auto y1 = m[0]  * m[10] * m[15] -
      m[0]  * m[11] * m[14] -
      m[8]  * m[2] * m[15] +
      m[8]  * m[3] * m[14] +
      m[12] * m[2] * m[11] -
      m[12] * m[3] * m[10];

  auto y2 = -m[0]  * m[9] * m[15] +
      m[0]  * m[11] * m[13] +
      m[8]  * m[1] * m[15] -
      m[8]  * m[3] * m[13] -
      m[12] * m[1] * m[11] +
      m[12] * m[3] * m[9];

  auto y3 = m[0]  * m[9] * m[14] -
      m[0]  * m[10] * m[13] -
      m[8]  * m[1] * m[14] +
      m[8]  * m[2] * m[13] +
      m[12] * m[1] * m[10] -
      m[12] * m[2] * m[9];

  auto z0 = m[1]  * m[6] * m[15] -
      m[1]  * m[7] * m[14] -
      m[5]  * m[2] * m[15] +
      m[5]  * m[3] * m[14] +
      m[13] * m[2] * m[7] -
      m[13] * m[3] * m[6];

  auto z1 = -m[0]  * m[6] * m[15] +
      m[0]  * m[7] * m[14] +
      m[4]  * m[2] * m[15] -
      m[4]  * m[3] * m[14] -
      m[12] * m[2] * m[7] +
      m[12] * m[3] * m[6];

  auto z2 = m[0]  * m[5] * m[15] -
      m[0]  * m[7] * m[13] -
      m[4]  * m[1] * m[15] +
      m[4]  * m[3] * m[13] +
      m[12] * m[1] * m[7] -
      m[12] * m[3] * m[5];

  auto z3 = -m[0]  * m[5] * m[14] +
      m[0]  * m[6] * m[13] +
      m[4]  * m[1] * m[14] -
      m[4]  * m[2] * m[13] -
      m[12] * m[1] * m[6] +
      m[12] * m[2] * m[5];

  auto w0 = -m[1] * m[6] * m[11] +
      m[1] * m[7] * m[10] +
      m[5] * m[2] * m[11] -
      m[5] * m[3] * m[10] -
      m[9] * m[2] * m[7] +
      m[9] * m[3] * m[6];

  auto w1 = m[0] * m[6] * m[11] -
      m[0] * m[7] * m[10] -
      m[4] * m[2] * m[11] +
      m[4] * m[3] * m[10] +
      m[8] * m[2] * m[7] -
      m[8] * m[3] * m[6];

  auto w2 = -m[0] * m[5] * m[11] +
      m[0] * m[7] * m[9] +
      m[4] * m[1] * m[11] -
      m[4] * m[3] * m[9] -
      m[8] * m[1] * m[7] +
      m[8] * m[3] * m[5];

  auto w3 = m[0] * m[5] * m[10] -
      m[0] * m[6] * m[9] -
      m[4] * m[1] * m[10] +
      m[4] * m[2] * m[9] +
      m[8] * m[1] * m[6] -
      m[8] * m[2] * m[5];

  auto det = m[0] * x0 + m[1] * x1 + m[2] * x2 + m[3] * x3;

  if (cglm::IsFloatEqual(det, 0.0f))
    throw cglm::NoInverseMatrixException();

  det = 1.0f / det;

  return {{x0 * det, y0 * det, z0 * det, w0 * det},
          {x1 * det, y1 * det, z1 * det, w1 * det},
          {x2 * det, y2 * det, z2 * det, w2 * det},
          {x3 * det, y3 * det, z3 * det, w3 * det}};
}
bool cglm::Mat4::operator==(const Mat4 &src) const noexcept {
  return (
      rows_[0] == src.get_row(0) &&
      rows_[1] == src.get_row(1) &&
      rows_[2] == src.get_row(2) &&
      rows_[3] == src.get_row(3));
}

bool cglm::Mat4::operator!=(const Mat4 &src) const noexcept {
  return !(
      rows_[0] == src.get_row(0) &&
      rows_[1] == src.get_row(1) &&
      rows_[2] == src.get_row(2) &&
      rows_[3] == src.get_row(3));
}

Mat4 cglm::Mat4::Translate(const cglm::Vec3 &src) const {
  vec_type row0(rows_[0]);
  row0.w = src.x;
  vec_type row1(rows_[1]);
  row1.w = src.y;
  vec_type row2(rows_[2]);
  row2.w = src.z;

  return {row0, row1, row2, rows_[3]};
}

Mat4 cglm::Mat4::Rotate(float degrees, const cglm::Vec3 &axis_vec) const {
  float radians = (degrees * (float)M_PI) / 180.0f;

  vec_type row0(rows_[0]);
  vec_type row1(rows_[1]);
  vec_type row2(rows_[2]);
  vec_type row3(rows_[3]);

  if (axis_vec.x != 0) {
    row1.x = cos(radians);
    row1.y = -sin(radians);
    row2.x = sin(radians);
    row2.y = cos(radians);
  }

  if (axis_vec.y != 0) {
    row0.x = cos(radians);
    row0.z = sin(radians);
    row2.x = -sin(radians);
    row2.z = cos(radians);
  }

  if (axis_vec.z != 0) {
    row0.x = cos(radians);
    row0.y = -sin(radians);
    row1.x = sin(radians);
    row1.y = cos(radians);
  }

  return {row0, row1, row2, row3};
}
