#include "mat3.hpp"
#include "exception.hpp"
#include "vec2.hpp"
#include "utils.hpp"

using vec_type = cglm::Mat3::vec_type;

cglm::Mat3::Mat3() {
  rows_[0] = {1, 0, 0};
  rows_[1] = {0, 1, 0};
  rows_[2] = {0, 0, 1};
}

cglm::Mat3::Mat3(float v) {
  rows_[0].x = v;
  rows_[1].y = v;
  rows_[2].z = v;
}

cglm::Mat3::Mat3(const vec_type &diag_vec) {
  rows_[0].x = diag_vec.x;
  rows_[1].y = diag_vec.y;
  rows_[2].z = diag_vec.z;
}

cglm::Mat3::Mat3(float v0, float v1, float v2) {
  rows_[0].x = v0;
  rows_[1].y = v1;
  rows_[2].z = v2;
}

cglm::Mat3::Mat3(const vec_type &r0, const vec_type &r1, const vec_type &r2) {
  rows_[0] = r0;
  rows_[1] = r1;
  rows_[2] = r2;
}

vec_type cglm::Mat3::get_row(uint32_t r) const {
  if (r < 0u || r > 2u)
    throw cglm::OutOfRangeException();
  else
    return rows_[r];
}

vec_type cglm::Mat3::get_col(uint32_t c) const {
  if (c < 0u || c > 2u)
    throw cglm::OutOfRangeException();
  else if (c == 0)
    return {rows_[0].x, rows_[1].x, rows_[2].x};
  else if (c == 1)
    return {rows_[0].y, rows_[1].y, rows_[2].y};
  else
    return {rows_[0].z, rows_[1].z, rows_[2].z};
}

vec_type cglm::Mat3::get_diag() const noexcept {
  return {rows_[0].x, rows_[1].y, rows_[2].z};
}

vec_type cglm::Mat3::operator[](unsigned int r) const {
  if (r < 0u || r > 2u)
    throw cglm::OutOfRangeException();
  else
    return rows_[r];
}

cglm::Mat3 cglm::Mat3::operator+(const cglm::Mat3 &src) const {
  return {rows_[0] + src.get_row(0),
          rows_[1] + src.get_row(1),
          rows_[2] + src.get_row(2)};
}

cglm::Mat3 cglm::Mat3::operator-(const cglm::Mat3 &src) const {
  return {rows_[0] - src.get_row(0),
          rows_[1] - src.get_row(1),
          rows_[2] - src.get_row(2)};
}

cglm::Mat3 cglm::Mat3::operator*(const cglm::Mat3 &src) const {
  vec_type row0(rows_[0] * src.get_col(0),
                rows_[0] * src.get_col(1),
                rows_[0] * src.get_col(2));
  vec_type row1(rows_[1] * src.get_col(0),
                rows_[1] * src.get_col(1),
                rows_[1] * src.get_col(2));
  vec_type row2(rows_[2] * src.get_col(0),
                rows_[2] * src.get_col(1),
                rows_[2] * src.get_col(2));

  return {row0, row1, row2};
}

cglm::Mat3 cglm::Mat3::operator*(float v) const {
  return {{rows_[0] * v},
          {rows_[1] * v},
          {rows_[2] * v}};
}

cglm::Mat3 cglm::Mat3::operator/(float v) const {
  return {{rows_[0] / v},
          {rows_[1] / v},
          {rows_[2] / v}};
}

cglm::Mat3 cglm::Mat3::operator+(float v) const {
  vec_type r0(rows_[0].x + v, rows_[0].y + v, rows_[0].z + v);
  vec_type r1(rows_[1].x + v, rows_[1].y + v, rows_[1].z + v);
  vec_type r2(rows_[2].x + v, rows_[2].y + v, rows_[2].z + v);

  return {r0, r1, r2};
}

cglm::Mat3 cglm::Mat3::operator-(float v) const {
  vec_type r0(rows_[0].x - v, rows_[0].y - v, rows_[0].z - v);
  vec_type r1(rows_[1].x - v, rows_[1].y - v, rows_[1].z - v);
  vec_type r2(rows_[2].x - v, rows_[2].y - v, rows_[2].z - v);

  return {r0, r1, r2};
}

cglm::Vec3 cglm::Mat3::operator*(const vec_type &src) const {
  return {rows_[0] * src,
          rows_[1] * src,
          rows_[2] * src};
}

cglm::Mat3 cglm::Mat3::GetInverse() const {
  float det =
      (rows_[0].x * (rows_[1].y * rows_[2].z - rows_[1].z * rows_[2].y) -
          rows_[0].y * (rows_[1].x * rows_[2].z - rows_[2].x * rows_[1].z) +
          rows_[0].z * (rows_[1].x * rows_[2].y - rows_[1].y * rows_[2].x));

  if (cglm::IsFloatEqual(det, 0.0f))
    throw cglm::NoInverseMatrixException();

  float inv_det = 1 / det;

  vec_type row0(rows_[1].y * rows_[2].z - rows_[2].y * rows_[1].z,
                rows_[0].z * rows_[2].y - rows_[0].y * rows_[2].z,
                rows_[0].y * rows_[1].z - rows_[0].z * rows_[1].y);

  vec_type row1(rows_[1].z * rows_[2].x - rows_[1].x * rows_[2].z,
                rows_[0].x * rows_[2].z - rows_[0].z * rows_[2].x,
                rows_[1].x * rows_[0].z - rows_[0].x * rows_[1].z);

  vec_type row2(rows_[1].x * rows_[2].y - rows_[2].x * rows_[1].y,
                rows_[2].x * rows_[0].y - rows_[0].x * rows_[2].y,
                rows_[0].x * rows_[1].y - rows_[1].x * rows_[0].y);

  return Mat3(row0, row1, row2) * inv_det;
}

cglm::Mat3 cglm::Mat3::GetTransposed() const noexcept {
  return {get_col(0),
          get_col(1),
          get_col(2)};
}

bool cglm::Mat3::operator==(const Mat3 &src) const noexcept {
  return (
      rows_[0] == src[0] &&
          rows_[1] == src[1] &&
          rows_[2] == src[2]);
}

bool cglm::Mat3::operator!=(const cglm::Mat3 &src) const noexcept {
  return !(
      rows_[0] == src[0] &&
          rows_[1] == src[1] &&
          rows_[2] == src[2]);
}
