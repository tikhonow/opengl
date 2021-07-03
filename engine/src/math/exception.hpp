#ifndef COMPUTER_GRAPHICS_COURSE_SRC_MATH_EXCEPTION_HPP_
#define COMPUTER_GRAPHICS_COURSE_SRC_MATH_EXCEPTION_HPP_

#include <exception>

namespace cglm {

class OutOfRangeException : public std::exception{
 public:
  const char * what() const noexcept override;
};

class NoInverseMatrixException : public std::exception {
 public:
  const char * what() const noexcept override;
};

}  // namespace cglm

#endif //COMPUTER_GRAPHICS_COURSE_SRC_MATH_EXCEPTION_HPP_
