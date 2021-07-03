#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_UTILS_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_UTILS_HPP_

#include <cmath>

namespace cglm {

inline bool IsFloatEqual(float lhs, float rhs) {
  const double kEpsilon = 1e-5f;
  return std::fabs(lhs - rhs) < kEpsilon;
}

}  // cglm

#endif //COMPUTER_GRAPHICS_COURSE_SRC_MATH_UTILS_HPP_
