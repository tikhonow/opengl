#define CATCH_CONFIG_MAIN

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/vector_int1.hpp>
#include <glm/ext/scalar_common.hpp>
#include <iostream>
#include "catch.hpp"
#include "../src/math/mat2.hpp"
#include "../src/math/vec2.hpp"
#include "../src/math/mat3.hpp"
#include "../src/math/vec3.hpp"
#include "../src/math/mat4.hpp"
#include "../src/math/vec4.hpp"

using Mat2 = cglm::Mat2;
using Vec2 = cglm::Vec2;
using Mat3 = cglm::Mat3;
using Vec3 = cglm::Vec3;
using Mat4 = cglm::Mat4;
using Vec4 = cglm::Vec4;

bool floatCmp(float a, float b) {
  return std::fabs(a - b) < 1e-3;
}

TEST_CASE("Mat2 constructors and accessors") {
  {
    Mat2 mat;

    REQUIRE(mat.get_row(0) == Vec2(1, 0));
    REQUIRE(mat.get_row(1) == Vec2(0, 1));

    REQUIRE(mat.get_col(0) == Vec2(1, 0));
    REQUIRE(mat.get_col(1) == Vec2(0, 1));

    REQUIRE(mat.get_diag() == Vec2(1, 1));
  }
  {
    Mat2 mat(3.14f);

    REQUIRE(mat.get_row(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_row(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_col(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_col(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_diag() == Vec2(3.14f, 3.14f));
  }

  {
    Mat2 mat(Vec2(3.14f, 3.14f));

    REQUIRE(mat.get_row(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_row(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_col(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_col(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_diag() == Vec2(3.14f, 3.14f));
  }

  {
    Mat2 mat(3.14f, 3.14f);

    REQUIRE(mat.get_row(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_row(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_col(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_col(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_diag() == Vec2(3.14f, 3.14f));
  }

  {
    Mat2 dst_mat(3.14f, 3.14f);
    Mat2 mat(dst_mat);

    REQUIRE(mat.get_row(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_row(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_col(0) == Vec2(3.14f, 0));
    REQUIRE(mat.get_col(1) == Vec2(0, 3.14f));

    REQUIRE(mat.get_diag() == Vec2(3.14f, 3.14f));
  }

  {
    Mat2 mat({3, 10},
             {12.3f, 11.2f});

    REQUIRE(mat.get_row(0) == Vec2(3, 10));
    REQUIRE(mat.get_row(1) == Vec2(12.3f, 11.2f));

    REQUIRE(mat.get_col(0) == Vec2(3, 12.3f));
    REQUIRE(mat.get_col(1) == Vec2(10, 11.2f));

    REQUIRE(mat.get_diag() == Vec2(3, 11.2f));
  }
}

TEST_CASE("Mat2 binary arithmetic operations") {
  {
    glm::mat2 glm_mat1({1, 2},
                       {3, 4});
    glm::mat2 glm_mat2({1, 2},
                       {3, 4});

    Mat2 mat1({1, 2},
              {3, 4});

    Mat2 mat2({1, 2},
              {3, 4});

    glm::mat2 glm_mat_result = glm_mat1 + glm_mat2;
    Mat2 mat_result = mat1 + mat2;

    REQUIRE(glm_mat_result[0].x == mat_result[0].x);
    REQUIRE(glm_mat_result[0].y == mat_result[0].y);
    REQUIRE(glm_mat_result[1].x == mat_result[1].x);
    REQUIRE(glm_mat_result[1].y == mat_result[1].y);
  }

  {
    glm::mat2 glm_mat1({1, 3.13f},
                       {11.1f, 4});
    glm::mat2 glm_mat2({1, 2},
                       {3.13f, 2.2f});

    Mat2 mat1({1, 3.13f},
              {11.1f, 4});

    Mat2 mat2({1, 2},
              {3.13f, 2.2f});

    glm::mat2 glm_mat_result = glm_mat1 - glm_mat2;
    Mat2 mat_result = mat1 - mat2;

    REQUIRE(glm_mat_result[0].x == mat_result[0].x);
    REQUIRE(glm_mat_result[0].y == mat_result[0].y);
    REQUIRE(glm_mat_result[1].x == mat_result[1].x);
    REQUIRE(glm_mat_result[1].y == mat_result[1].y);
  }
}

TEST_CASE("Mat2 multiplication") {
  {
    glm::mat2 glm_mat =
        glm::mat2({3, 12}, {1, 14}) *
            glm::mat2({123, 13.2f}, {33, 4.4f});

    Mat2 mat =
        Mat2{{3, 1}, {12, 14}} *
            Mat2{{123, 33}, {13.2f, 4.4f}};

    REQUIRE(floatCmp(glm_mat[0].x, mat[0].x));
    REQUIRE(floatCmp(glm_mat[1].x, mat[0].y));
    REQUIRE(floatCmp(glm_mat[0].y, mat[1].x));
    REQUIRE(floatCmp(glm_mat[1].y, mat[1].y));
  }
}

TEST_CASE("Mat2 multiplication on a number") {
  Mat2 mat =
      Mat2({3.14, 32.2f}, {100.1f, 1.11f}) * 10;

  REQUIRE(floatCmp(31.4f, mat[0].x));
  REQUIRE(floatCmp(322.0f, mat[0].y));
  REQUIRE(floatCmp(1001.0f, mat[1].x));
  REQUIRE(floatCmp(11.1f, mat[1].y));
}

TEST_CASE("Mat2 division on a number") {
  Mat2 mat =
      Mat2({3.14, 32.2f}, {100.1f, 1.11f}) / 10;

  REQUIRE(floatCmp(0.314f, mat[0].x));
  REQUIRE(floatCmp(3.220f, mat[0].y));
  REQUIRE(floatCmp(10.01f, mat[1].x));
  REQUIRE(floatCmp(0.111f, mat[1].y));
}

TEST_CASE("Mat2 sum and subtraction on a number") {
  {
    Mat2 mat = Mat2({10.14f, 10},
                    {14.3f, 12.2f}) + 10;

    REQUIRE(floatCmp(20.14f, mat[0].x));
    REQUIRE(floatCmp(20, mat[0].y));
    REQUIRE(floatCmp(24.3f, mat[1].x));
    REQUIRE(floatCmp(22.2f, mat[1].y));
  }

  {
    Mat2 mat = Mat2({10.14f, 10},
                    {14.3f, 12.2f}) - 5;

    REQUIRE(floatCmp(5.14f, mat[0].x));
    REQUIRE(floatCmp(5, mat[0].y));
    REQUIRE(floatCmp(9.3f, mat[1].x));
    REQUIRE(floatCmp(7.2f, mat[1].y));
  }
}

TEST_CASE("Mat2 multiplication on a Vec2") {
  Mat2 mat({9, 12.2},
           {23.3, 48});

  Vec2 vec(132, 22);

  Vec2 result = mat * vec;

  REQUIRE(floatCmp(result.x, 1456.4f));
  REQUIRE(floatCmp(result.y, 4131.5996f));
}

TEST_CASE("Mat2 inverse matrix") {
  {
    Mat2 inverted_mat = Mat2({10, 14}, {12.2, 2}).GetInverse();
    glm::mat2 glm_inverted_mat = glm::inverse(glm::mat2({10, 14}, {12.2, 2}));

    REQUIRE(floatCmp(glm_inverted_mat[0].x, inverted_mat[0].x));
    REQUIRE(floatCmp(glm_inverted_mat[0].y, inverted_mat[0].y));
    REQUIRE(floatCmp(glm_inverted_mat[1].x, inverted_mat[1].x));
    REQUIRE(floatCmp(glm_inverted_mat[1].y, inverted_mat[1].y));
  }

  {
    Mat2 inverted_mat = Mat2({22.2, 12.4}, {11.9, 43.4}).GetInverse();
    glm::mat2 glm_inverted_mat = glm::inverse(glm::mat2({22.2, 12.4}, {11.9, 43.4}));

    REQUIRE(floatCmp(glm_inverted_mat[0].x, inverted_mat[0].x));
    REQUIRE(floatCmp(glm_inverted_mat[0].y, inverted_mat[0].y));
    REQUIRE(floatCmp(glm_inverted_mat[1].x, inverted_mat[1].x));
    REQUIRE(floatCmp(glm_inverted_mat[1].y, inverted_mat[1].y));
  }
}

TEST_CASE("Mat2 transpose") {
  {
    Mat2 mat({10, 12}, {14, 22});
    glm::mat2 glm_mat({10, 12}, {14, 22});

    mat = mat.GetTransposed();
    glm_mat = glm::transpose(glm_mat);

    REQUIRE(floatCmp(glm_mat[0].x, mat[0].x));
    REQUIRE(floatCmp(glm_mat[0].y, mat[0].y));
    REQUIRE(floatCmp(glm_mat[1].x, mat[1].x));
    REQUIRE(floatCmp(glm_mat[1].y, mat[1].y));
  }

  {
    Mat2 mat({23.31, 2}, {94.1, 54});
    glm::mat2 glm_mat({23.31, 2}, {94.1, 54});

    mat = mat.GetTransposed();
    glm_mat = glm::transpose(glm_mat);

    REQUIRE(floatCmp(glm_mat[0].x, mat[0].x));
    REQUIRE(floatCmp(glm_mat[0].y, mat[0].y));
    REQUIRE(floatCmp(glm_mat[1].x, mat[1].x));
    REQUIRE(floatCmp(glm_mat[1].y, mat[1].y));
  }
}

TEST_CASE("Mat2 comparison") {
  {
    Mat2 mat0;
    Mat2 mat1(0);

    REQUIRE(mat0 != mat1);
  }

  {
    Mat2 mat0({10, 22}, {3.31, 97.2});
    Mat2 mat1({10, 22}, {3.31, 97.2});

    REQUIRE(mat0 == mat1);
  }

  {
    Mat2 mat0(10);
    Mat2 mat1(10);

    REQUIRE(mat0 == mat1);
  }

  {
    Mat2 mat0;
    Mat2 mat1(10);

    REQUIRE(mat0 != mat1);
  }
}

/// Mat3 test section

TEST_CASE("Mat3 constructors and accessors") {
  {
    Mat3 mat;

    REQUIRE(mat[0] == Vec3(1, 0, 0));
    REQUIRE(mat[1] == Vec3(0, 1, 0));
    REQUIRE(mat[2] == Vec3(0, 0, 1));

    REQUIRE(mat.get_row(0) == Vec3(1, 0, 0));
    REQUIRE(mat.get_row(1) == Vec3(0, 1, 0));
    REQUIRE(mat.get_row(2) == Vec3(0, 0, 1));

    REQUIRE(mat.get_col(0) == Vec3(1, 0, 0));
    REQUIRE(mat.get_col(1) == Vec3(0, 1, 0));
    REQUIRE(mat.get_col(2) == Vec3(0, 0, 1));

    REQUIRE(mat.get_diag() == Vec3(1, 1, 1));
  }

  {
    Mat3 mat(1.14);

    REQUIRE(mat[0] == Vec3(1.14, 0, 0));
    REQUIRE(mat[1] == Vec3(0, 1.14, 0));
    REQUIRE(mat[2] == Vec3(0, 0, 1.14));

    REQUIRE(mat.get_row(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_row(1) == Vec3(0, 1.14, 0));
    REQUIRE(mat.get_row(2) == Vec3(0, 0, 1.14));

    REQUIRE(mat.get_col(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_col(1) == Vec3(0, 1.14, 0));
    REQUIRE(mat.get_col(2) == Vec3(0, 0, 1.14));

    REQUIRE(mat.get_diag() == Vec3(1.14, 1.14, 1.14));
  }

  {
    Mat3 mat(Vec3(1.14, 12.22, 99.3));

    REQUIRE(mat[0] == Vec3(1.14, 0, 0));
    REQUIRE(mat[1] == Vec3(0, 12.22, 0));
    REQUIRE(mat[2] == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_row(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_row(1) == Vec3(0, 12.22, 0));
    REQUIRE(mat.get_row(2) == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_col(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_col(1) == Vec3(0, 12.22, 0));
    REQUIRE(mat.get_col(2) == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_diag() == Vec3(1.14, 12.22, 99.3));
  }

  {
    Mat3 mat(1.14, 12.22, 99.3);

    REQUIRE(mat[0] == Vec3(1.14, 0, 0));
    REQUIRE(mat[1] == Vec3(0, 12.22, 0));
    REQUIRE(mat[2] == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_row(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_row(1) == Vec3(0, 12.22, 0));
    REQUIRE(mat.get_row(2) == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_col(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_col(1) == Vec3(0, 12.22, 0));
    REQUIRE(mat.get_col(2) == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_diag() == Vec3(1.14, 12.22, 99.3));
  }

  {
    Mat3 mat(
        {1.14, 0, 0},
        {0, 12.22, 0},
        {0, 0, 99.3});

    REQUIRE(mat[0] == Vec3(1.14, 0, 0));
    REQUIRE(mat[1] == Vec3(0, 12.22, 0));
    REQUIRE(mat[2] == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_row(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_row(1) == Vec3(0, 12.22, 0));
    REQUIRE(mat.get_row(2) == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_col(0) == Vec3(1.14, 0, 0));
    REQUIRE(mat.get_col(1) == Vec3(0, 12.22, 0));
    REQUIRE(mat.get_col(2) == Vec3(0, 0, 99.3));

    REQUIRE(mat.get_diag() == Vec3(1.14, 12.22, 99.3));
  }
}

TEST_CASE("Mat3 addition") {
  Mat3 mat0(3);
  Mat3 mat1(0.14f);

  glm::mat3 glm_mat0(3);
  glm::mat3 glm_mat1(0.14f);

  Mat3 mat_result = mat0 + mat1;
  glm::mat3 glm_mat_result = glm_mat0 + glm_mat1;

  REQUIRE(mat_result[0].x == glm_mat_result[0].x);
  REQUIRE(mat_result[1].y == glm_mat_result[1].y);
  REQUIRE(mat_result[2].z == glm_mat_result[2].z);
}

TEST_CASE("Mat3 subtraction") {
  Mat3 mat0(3.14);
  Mat3 mat1(0.14f);

  glm::mat3 glm_mat0(3.14);
  glm::mat3 glm_mat1(0.14f);

  Mat3 mat_result = mat0 - mat1;
  glm::mat3 glm_mat_result = glm_mat0 - glm_mat1;

  REQUIRE(mat_result[0].x == glm_mat_result[0].x);
  REQUIRE(mat_result[1].y == glm_mat_result[1].y);
  REQUIRE(mat_result[2].z == glm_mat_result[2].z);
}

TEST_CASE("Mat3 multiplication") {
  Mat3 mat0({10, 4, 3},
            {18.2, 14, 29},
            {48, 44, 1});

  Mat3 mat1({12, 33, 38},
            {58, 32.5, 32},
            {13, 11, 2});

  Mat3 mat_result = mat0 * mat1;

  REQUIRE(mat_result[0].x == 391);
  REQUIRE(mat_result[0].y == 493);
  REQUIRE(mat_result[0].z == 514);
  REQUIRE(floatCmp(mat_result[1].x, 1407.4));
  REQUIRE(floatCmp(mat_result[1].y, 1374.6));
  REQUIRE(floatCmp(mat_result[1].z, 1197.6));
  REQUIRE(mat_result[2].x == 3141);
  REQUIRE(mat_result[2].y == 3025);
  REQUIRE(mat_result[2].z == 3234);
}

TEST_CASE("Mat3 multiplication on a number") {
  Mat3 mat0({10, 4, 3},
            {18.2, 14, 29},
            {48, 44, 1});

  Mat3 mat_result = mat0 * 10;

  REQUIRE(mat_result[0].x == 100);
  REQUIRE(mat_result[0].y == 40);
  REQUIRE(mat_result[0].z == 30);
  REQUIRE(mat_result[1].x == 182);
  REQUIRE(mat_result[1].y == 140);
  REQUIRE(mat_result[1].z == 290);
  REQUIRE(mat_result[2].x == 480);
  REQUIRE(mat_result[2].y == 440);
  REQUIRE(mat_result[2].z == 10);
}

TEST_CASE("Mat3 division on a number") {
  Mat3 mat0({10, 4, 3},
            {18, 14, 29},
            {48, 44, 1});

  Mat3 mat_result = mat0 / 2;

  REQUIRE(mat_result[0].x == 5);
  REQUIRE(mat_result[0].y == 2);
  REQUIRE(mat_result[0].z == 1.5);
  REQUIRE(mat_result[1].x == 9);
  REQUIRE(mat_result[1].y == 7);
  REQUIRE(mat_result[1].z == 14.5);
  REQUIRE(mat_result[2].x == 24);
  REQUIRE(mat_result[2].y == 22);
  REQUIRE(mat_result[2].z == 0.5);
}

TEST_CASE("Mat3 number addition") {
  Mat3 mat0({10, 4, 3},
            {18, 14, 29},
            {48, 44, 1});

  Mat3 mat_result = mat0 + 14;

  REQUIRE(mat_result[0].x == 24);
  REQUIRE(mat_result[0].y == 18);
  REQUIRE(mat_result[0].z == 17);
  REQUIRE(mat_result[1].x == 32);
  REQUIRE(mat_result[1].y == 28);
  REQUIRE(mat_result[1].z == 43);
  REQUIRE(mat_result[2].x == 62);
  REQUIRE(mat_result[2].y == 58);
  REQUIRE(mat_result[2].z == 15);
}

TEST_CASE("Mat3 number subtraction") {
  Mat3 mat0({10, 4, 3},
            {18, 14, 29},
            {48, 44, 1});

  Mat3 mat_result = mat0 - 20;

  REQUIRE(mat_result[0].x == -10);
  REQUIRE(mat_result[0].y == -16);
  REQUIRE(mat_result[0].z == -17);
  REQUIRE(mat_result[1].x == -2);
  REQUIRE(mat_result[1].y == -6);
  REQUIRE(mat_result[1].z == 9);
  REQUIRE(mat_result[2].x == 28);
  REQUIRE(mat_result[2].y == 24);
  REQUIRE(mat_result[2].z == -19);
}

TEST_CASE("Mat3 multiplication on a vector") {
  Mat3 mat({1, 225, 4},
           {9, 95, 23},
           {33, 14, 4});

  Vec3 vec(3, 4, 8);

  vec = mat * vec;

  glm::mat3 glm_mat({1, 9, 33},
                    {225, 95, 14},
                    {4, 23, 4});
  glm::vec3 glm_vec(3, 4, 8);

  glm_vec = glm::operator*(glm_mat, glm_vec);

  REQUIRE(vec.x == glm_vec.x);
  REQUIRE(vec.y == glm_vec.y);
  REQUIRE(vec.z == glm_vec.z);
}

TEST_CASE("Mat3 inverse") {
  Mat3 mat({1, 2, 3},
           {0, 1, 4},
           {5, 6, 0});

  mat = mat.GetInverse();

  REQUIRE(mat[0] == Vec3(-24, 18, 5));
  REQUIRE(mat[1] == Vec3(20, -15, -4));
  REQUIRE(mat[2] == Vec3(-5, 4, 1));
}

TEST_CASE("Mat3 transpose") {
  Mat3 mat({1, 2, 3},
           {0, 1, 4},
           {5, 6, 0});

  mat = mat.GetTransposed();

  REQUIRE(mat[0] == Vec3(1, 0, 5));
  REQUIRE(mat[1] == Vec3(2, 1, 6));
  REQUIRE(mat[2] == Vec3(3, 4, 0));
}

TEST_CASE("Mat3 comparison methods") {
  {
    Mat3 mat0({1, 2, 3},
              {0, 1, 4},
              {5, 6, 0});

    Mat3 mat1({1, 2, 3},
              {0, 1, 4},
              {5, 6, 0});

    REQUIRE(mat0 == mat1);
  }

  {
    Mat3 mat0;
    Mat3 mat1;

    REQUIRE(mat0 == mat1);
  }

  {
    Mat3 mat0({0, 2, 3},
              {0, 1, 4},
              {0, 6, 0});

    Mat3 mat1({1, 2, 3},
              {0, 1, 4},
              {5, 6, 0});

    REQUIRE(mat0 != mat1);
  }

  {
    Mat3 mat0(10);
    Mat3 mat1(12);

    REQUIRE(mat0 != mat1);
  }
}

/// Mat4 test section

TEST_CASE("Mat4 constructors and accessors") {
  {
    Mat4 mat;

    REQUIRE(mat[0] == Vec4(1, 0, 0, 0));
    REQUIRE(mat[1] == Vec4(0, 1, 0, 0));
    REQUIRE(mat[2] == Vec4(0, 0, 1, 0));
    REQUIRE(mat[3] == Vec4(0, 0, 0, 1));

    REQUIRE(mat.get_row(0) == Vec4(1, 0, 0, 0));
    REQUIRE(mat.get_row(1) == Vec4(0, 1, 0, 0));
    REQUIRE(mat.get_row(2) == Vec4(0, 0, 1, 0));
    REQUIRE(mat.get_row(3) == Vec4(0, 0, 0, 1));

    REQUIRE(mat.get_col(0) == Vec4(1, 0, 0, 0));
    REQUIRE(mat.get_col(1) == Vec4(0, 1, 0, 0));
    REQUIRE(mat.get_col(2) == Vec4(0, 0, 1, 0));
    REQUIRE(mat.get_col(3) == Vec4(0, 0, 0, 1));

    REQUIRE(mat.get_diag() == Vec4(1, 1, 1, 1));
  }

  {
    Mat4 mat(1.89f);

    REQUIRE(mat[0] == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat[1] == Vec4(0, 1.89f, 0, 0));
    REQUIRE(mat[2] == Vec4(0, 0, 1.89f, 0));
    REQUIRE(mat[3] == Vec4(0, 0, 0, 1.89f));

    REQUIRE(mat.get_row(0) == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat.get_row(1) == Vec4(0, 1.89f, 0, 0));
    REQUIRE(mat.get_row(2) == Vec4(0, 0, 1.89f, 0));
    REQUIRE(mat.get_row(3) == Vec4(0, 0, 0, 1.89f));

    REQUIRE(mat.get_col(0) == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat.get_col(1) == Vec4(0, 1.89f, 0, 0));
    REQUIRE(mat.get_col(2) == Vec4(0, 0, 1.89f, 0));
    REQUIRE(mat.get_col(3) == Vec4(0, 0, 0, 1.89f));

    REQUIRE(mat.get_diag() == Vec4(1.89f, 1.89f, 1.89f, 1.89f));
  }

  {
    Mat4 mat(Vec4(1.89f, 2, 3, 10));

    REQUIRE(mat[0] == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat[1] == Vec4(0, 2, 0, 0));
    REQUIRE(mat[2] == Vec4(0, 0, 3, 0));
    REQUIRE(mat[3] == Vec4(0, 0, 0, 10));

    REQUIRE(mat.get_row(0) == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat.get_row(1) == Vec4(0, 2, 0, 0));
    REQUIRE(mat.get_row(2) == Vec4(0, 0, 3, 0));
    REQUIRE(mat.get_row(3) == Vec4(0, 0, 0, 10));

    REQUIRE(mat.get_col(0) == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat.get_col(1) == Vec4(0, 2, 0, 0));
    REQUIRE(mat.get_col(2) == Vec4(0, 0, 3, 0));
    REQUIRE(mat.get_col(3) == Vec4(0, 0, 0, 10));

    REQUIRE(mat.get_diag() == Vec4(1.89f, 2, 3, 10));
  }

  {
    Mat4 mat(1.89f, 2, 3, 10);

    REQUIRE(mat[0] == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat[1] == Vec4(0, 2, 0, 0));
    REQUIRE(mat[2] == Vec4(0, 0, 3, 0));
    REQUIRE(mat[3] == Vec4(0, 0, 0, 10));

    REQUIRE(mat.get_row(0) == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat.get_row(1) == Vec4(0, 2, 0, 0));
    REQUIRE(mat.get_row(2) == Vec4(0, 0, 3, 0));
    REQUIRE(mat.get_row(3) == Vec4(0, 0, 0, 10));

    REQUIRE(mat.get_col(0) == Vec4(1.89f, 0, 0, 0));
    REQUIRE(mat.get_col(1) == Vec4(0, 2, 0, 0));
    REQUIRE(mat.get_col(2) == Vec4(0, 0, 3, 0));
    REQUIRE(mat.get_col(3) == Vec4(0, 0, 0, 10));

    REQUIRE(mat.get_diag() == Vec4(1.89f, 2, 3, 10));
  }

  Mat4 mat({1.89f, 0, 0, 0},
           {0, 2, 0, 0},
           {0, 0, 3, 0},
           {0, 0, 0, 10});

  REQUIRE(mat[0] == Vec4(1.89f, 0, 0, 0));
  REQUIRE(mat[1] == Vec4(0, 2, 0, 0));
  REQUIRE(mat[2] == Vec4(0, 0, 3, 0));
  REQUIRE(mat[3] == Vec4(0, 0, 0, 10));

  REQUIRE(mat.get_row(0) == Vec4(1.89f, 0, 0, 0));
  REQUIRE(mat.get_row(1) == Vec4(0, 2, 0, 0));
  REQUIRE(mat.get_row(2) == Vec4(0, 0, 3, 0));
  REQUIRE(mat.get_row(3) == Vec4(0, 0, 0, 10));

  REQUIRE(mat.get_col(0) == Vec4(1.89f, 0, 0, 0));
  REQUIRE(mat.get_col(1) == Vec4(0, 2, 0, 0));
  REQUIRE(mat.get_col(2) == Vec4(0, 0, 3, 0));
  REQUIRE(mat.get_col(3) == Vec4(0, 0, 0, 10));

  REQUIRE(mat.get_diag() == Vec4(1.89f, 2, 3, 10));
}

TEST_CASE("Mat4 addition") {
  Mat4 mat0(9);
  Mat4 mat1(11);

  glm::mat4 glm_mat0(9);
  glm::mat4 glm_mat1(11);

  Mat4 mat_result = mat0 + mat1;
  glm::mat4 glm_mat_result = glm_mat0 + glm_mat1;

  REQUIRE(mat_result[0].x == glm_mat_result[0].x);
  REQUIRE(mat_result[1].y == glm_mat_result[1].y);
  REQUIRE(mat_result[2].z == glm_mat_result[2].z);
  REQUIRE(mat_result[3].w == glm_mat_result[3].w);
}

TEST_CASE("Mat4 subtraction") {
  Mat4 mat0(9);
  Mat4 mat1(11);

  glm::mat4 glm_mat0(9);
  glm::mat4 glm_mat1(11);

  Mat4 mat_result = mat0 - mat1;
  glm::mat4 glm_mat_result = glm_mat0 - glm_mat1;

  REQUIRE(mat_result[0].x == glm_mat_result[0].x);
  REQUIRE(mat_result[1].y == glm_mat_result[1].y);
  REQUIRE(mat_result[2].z == glm_mat_result[2].z);
  REQUIRE(mat_result[3].w == glm_mat_result[3].w);
}

TEST_CASE("Mat4 multiplication") {
  Mat4 mat0({29, 2, 0, 1},
            {5, 18, 294, 48},
            {48, 11, 773, 63},
            {46, 0, 6, 6});

  Mat4 mat1({12, 341, 21, 2},
            {0, 213, 3, 38},
            {88, 0, 273, 0},
            {72, 6, 2, 6});

  auto mat_result = mat0 * mat1;

  REQUIRE(mat_result[0] == Vec4(420, 10321, 617, 140));
  REQUIRE(mat_result[1] == Vec4(29388, 5827, 80517, 982));
  REQUIRE(mat_result[2] == Vec4(73136, 19089, 212196, 892));
  REQUIRE(mat_result[3] == Vec4(1512, 15722, 2616, 128));
}

TEST_CASE("Mat4 multiplication on a num") {
  Mat4 mat({10, 10, 10, 10},
           {20, 20, 20, 20},
           {30, 30, 30, 30},
           {10, 10, 10, 10});

  glm::mat4 glm_mat({10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10});

  mat = mat * 3;
  glm_mat = glm::operator*(glm_mat, {3});

  REQUIRE(mat[0].x == glm_mat[0].x);
  REQUIRE(mat[0].y == glm_mat[1].x);
  REQUIRE(mat[0].z == glm_mat[2].x);
  REQUIRE(mat[0].w == glm_mat[3].x);
  REQUIRE(mat[1].x == glm_mat[0].y);
  REQUIRE(mat[1].y == glm_mat[1].y);
  REQUIRE(mat[1].z == glm_mat[2].y);
  REQUIRE(mat[1].w == glm_mat[3].y);
  REQUIRE(mat[2].x == glm_mat[0].z);
  REQUIRE(mat[2].y == glm_mat[1].z);
  REQUIRE(mat[2].z == glm_mat[2].z);
  REQUIRE(mat[2].w == glm_mat[3].z);
  REQUIRE(mat[3].x == glm_mat[0].w);
  REQUIRE(mat[3].y == glm_mat[1].w);
  REQUIRE(mat[3].z == glm_mat[2].w);
  REQUIRE(mat[3].w == glm_mat[3].w);
}

TEST_CASE("Mat4 division by num") {
  Mat4 mat({10, 10, 10, 10},
           {20, 20, 20, 20},
           {30, 30, 30, 30},
           {10, 10, 10, 10});

  glm::mat4 glm_mat({10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10});

  mat = mat / 5;
  glm_mat = glm::operator/(glm_mat, {5});

  REQUIRE(mat[0].x == glm_mat[0].x);
  REQUIRE(mat[0].y == glm_mat[1].x);
  REQUIRE(mat[0].z == glm_mat[2].x);
  REQUIRE(mat[0].w == glm_mat[3].x);
  REQUIRE(mat[1].x == glm_mat[0].y);
  REQUIRE(mat[1].y == glm_mat[1].y);
  REQUIRE(mat[1].z == glm_mat[2].y);
  REQUIRE(mat[1].w == glm_mat[3].y);
  REQUIRE(mat[2].x == glm_mat[0].z);
  REQUIRE(mat[2].y == glm_mat[1].z);
  REQUIRE(mat[2].z == glm_mat[2].z);
  REQUIRE(mat[2].w == glm_mat[3].z);
  REQUIRE(mat[3].x == glm_mat[0].w);
  REQUIRE(mat[3].y == glm_mat[1].w);
  REQUIRE(mat[3].z == glm_mat[2].w);
  REQUIRE(mat[3].w == glm_mat[3].w);
}

TEST_CASE("Mat4 adding a number") {
  Mat4 mat({10, 10, 10, 10},
           {20, 20, 20, 20},
           {30, 30, 30, 30},
           {10, 10, 10, 10});

  glm::mat4 glm_mat({10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10});

  mat = mat + 100;
  glm_mat = glm::operator+(glm_mat, {100});

  REQUIRE(mat[0].x == glm_mat[0].x);
  REQUIRE(mat[0].y == glm_mat[1].x);
  REQUIRE(mat[0].z == glm_mat[2].x);
  REQUIRE(mat[0].w == glm_mat[3].x);
  REQUIRE(mat[1].x == glm_mat[0].y);
  REQUIRE(mat[1].y == glm_mat[1].y);
  REQUIRE(mat[1].z == glm_mat[2].y);
  REQUIRE(mat[1].w == glm_mat[3].y);
  REQUIRE(mat[2].x == glm_mat[0].z);
  REQUIRE(mat[2].y == glm_mat[1].z);
  REQUIRE(mat[2].z == glm_mat[2].z);
  REQUIRE(mat[2].w == glm_mat[3].z);
  REQUIRE(mat[3].x == glm_mat[0].w);
  REQUIRE(mat[3].y == glm_mat[1].w);
  REQUIRE(mat[3].z == glm_mat[2].w);
  REQUIRE(mat[3].w == glm_mat[3].w);
}

TEST_CASE("Mat4 subtraction by number") {
  Mat4 mat({10, 10, 10, 10},
           {20, 20, 20, 20},
           {30, 30, 30, 30},
           {10, 10, 10, 10});

  glm::mat4 glm_mat({10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10});

  mat = mat - 100;
  glm_mat = glm::operator-(glm_mat, {100});

  REQUIRE(mat[0].x == glm_mat[0].x);
  REQUIRE(mat[0].y == glm_mat[1].x);
  REQUIRE(mat[0].z == glm_mat[2].x);
  REQUIRE(mat[0].w == glm_mat[3].x);
  REQUIRE(mat[1].x == glm_mat[0].y);
  REQUIRE(mat[1].y == glm_mat[1].y);
  REQUIRE(mat[1].z == glm_mat[2].y);
  REQUIRE(mat[1].w == glm_mat[3].y);
  REQUIRE(mat[2].x == glm_mat[0].z);
  REQUIRE(mat[2].y == glm_mat[1].z);
  REQUIRE(mat[2].z == glm_mat[2].z);
  REQUIRE(mat[2].w == glm_mat[3].z);
  REQUIRE(mat[3].x == glm_mat[0].w);
  REQUIRE(mat[3].y == glm_mat[1].w);
  REQUIRE(mat[3].z == glm_mat[2].w);
  REQUIRE(mat[3].w == glm_mat[3].w);
}

TEST_CASE("Mat4 vector multiplication") {
  Mat4 mat({10, 10, 10, 10},
           {20, 20, 20, 20},
           {30, 30, 30, 30},
           {10, 10, 10, 10});
  Vec4 vec(12, 31, 44, 5);

  glm::mat4 glm_mat({10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10},
                    {10, 20, 30, 10});
  glm::vec4 glm_vec(12, 31, 44, 5);

  vec = mat * vec;
  glm_vec = glm_mat * glm_vec;

  REQUIRE(vec.x == glm_vec.x);
  REQUIRE(vec.y == glm_vec.y);
  REQUIRE(vec.z == glm_vec.z);
  REQUIRE(vec.w == glm_vec.w);
}

TEST_CASE("Mat4 transposed") {
  Mat4 mat({10, 10, 10, 10},
           {20, 20, 5, 2},
           {30, 3, 30, 30},
           {1, 10, 5, 3});

  mat = mat.GetTransposed();

  REQUIRE(mat[0] == Vec4(10, 20, 30, 1));
  REQUIRE(mat[1] == Vec4(10, 20, 3, 10));
  REQUIRE(mat[2] == Vec4(10, 5, 30, 5));
  REQUIRE(mat[3] == Vec4(10, 2, 30, 3));
}

TEST_CASE("Mat4 inverse") {
  Mat4 mat({0, 3, -1, 2},
           {2, 1, 0, 0},
           {-2, -1, 0, 2},
           {-5, 7, 1, 1});

  mat = mat.GetInverse();

  REQUIRE(mat[0] == Vec4(-0.04f, 0.46f, 0.06f, -0.04f));
  REQUIRE(mat[1] == Vec4(0.08f, 0.08f, -0.12f, 0.08f));
  REQUIRE(mat[2] == Vec4(-0.76f, 1.24f, 0.64f, 0.24f));
  REQUIRE(mat[3] == Vec4(0, 0.5f, 0.5f, 0));
}

TEST_CASE("Mat4 comparison methods") {
  {
    Mat4 mat0, mat1;
    REQUIRE(mat0 == mat1);
  }
  {
    Mat4 mat0(0), mat1;
    REQUIRE(mat0 != mat1);
  }
  {
    Mat4 mat0(1), mat1(1, 1, 1, 1);
    REQUIRE(mat0 == mat1);
  }
  {
    Mat4 mat0(1), mat1(1, 1, 1, 0);
    REQUIRE(mat0 != mat1);
  }
  {
    Mat4 mat0({0, 3, -1, 2},
             {2, 1, 0, 0},
             {-2, -1, 0, 2},
             {-5, 7, 1, 1});

    Mat4 mat1({10, 10, 10, 10},
             {20, 20, 20, 20},
             {30, 30, 30, 30},
             {10, 10, 10, 10});

    REQUIRE(mat0 != mat1);
  }
  {
    Mat4 mat0({10, 10, 10, 10},
              {20, 20, 20, 20},
              {30, 30, 30, 30},
              {10, 10, 10, 10});

    Mat4 mat1({10, 10, 10, 10},
              {20, 20, 20, 20},
              {30, 30, 30, 30},
              {10, 10, 10, 10});

    REQUIRE(mat0 == mat1);
  }
}

TEST_CASE("Mat4 translation") {
  Vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  Mat4 trans(1.0f);
  trans = trans.Translate(Vec3(1.0f, 1.0f, 0.0f));
  vec = trans * vec;

  glm::vec4 glm_vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 glm_trans = glm::mat4(1.0f);
  glm_trans = glm::translate(glm_trans, glm::vec3(1.0f, 1.0f, 0.0f));
  glm_vec = glm_trans * glm_vec;

  REQUIRE(vec.x == glm_vec.x);
  REQUIRE(vec.y == glm_vec.y);
  REQUIRE(vec.z == glm_vec.z);
  REQUIRE(vec.w == glm_vec.w);
}

TEST_CASE("Mat4 rotate") {
  Mat4 mat(1.0f);
  mat = mat.Rotate(90, {0.0, 0.0, 0.1});

  glm::mat4 glm_mat = glm::mat4(1.0f);
  glm_mat = glm::rotate(glm_mat, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));

  REQUIRE(floatCmp(mat[0].x, glm_mat[0].x));
  REQUIRE(floatCmp(mat[0].y, glm_mat[1].x));
  REQUIRE(floatCmp(mat[0].z, glm_mat[2].x));
  REQUIRE(floatCmp(mat[0].w, glm_mat[3].x));
  REQUIRE(floatCmp(mat[1].x, glm_mat[0].y));
  REQUIRE(floatCmp(mat[1].y, glm_mat[1].y));
  REQUIRE(floatCmp(mat[1].z, glm_mat[2].y));
  REQUIRE(floatCmp(mat[1].w, glm_mat[3].y));
  REQUIRE(floatCmp(mat[2].x, glm_mat[0].z));
  REQUIRE(floatCmp(mat[2].y, glm_mat[1].z));
  REQUIRE(floatCmp(mat[2].z, glm_mat[2].z));
  REQUIRE(floatCmp(mat[2].w, glm_mat[3].z));
  REQUIRE(floatCmp(mat[3].x, glm_mat[0].w));
  REQUIRE(floatCmp(mat[3].y, glm_mat[1].w));
  REQUIRE(floatCmp(mat[3].z, glm_mat[2].w));
  REQUIRE(floatCmp(mat[3].w, glm_mat[3].w));
}
