#define CATCH_CONFIG_MAIN

#define EPSILON 1e-5

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <glm/geometric.hpp>
#include <glm/ext.hpp>
#include <glm/ext/vector_float2.hpp>
#include "catch.hpp"
#include "../src/math/vec2.hpp"
#include "../src/math/vec3.hpp"
#include "../src/math/vec4.hpp"

using Vec2 = cglm::Vec2;
using Vec3 = cglm::Vec3;
using Vec4 = cglm::Vec4;

bool floatCmp(float a, float b) {
  return std::fabs(a - b) < EPSILON;
}

TEST_CASE("Vec2 initialization") {
  {
    glm::vec2 glm_vec{};
    Vec2 custom_vec;

    REQUIRE(glm_vec.x == custom_vec.x);
    REQUIRE(glm_vec.y == custom_vec.y);
  }

  {
    glm::vec2 glm_vec(1.1f);
    Vec2 custom_vec(1.1f);

    REQUIRE(glm_vec.x == custom_vec.x);
    REQUIRE(glm_vec.y == custom_vec.y);
  }

  {
    glm::vec2 glm_vec(3.14f, 1.77f);
    Vec2 custom_vec(3.14f, 1.77f);

    REQUIRE(glm_vec.x == custom_vec.x);
    REQUIRE(glm_vec.y == custom_vec.y);
  }
}

TEST_CASE("Vec2 copy and move constructors") {
  {
    Vec2 dst_vec(1.1f, 3.14f);
    Vec2 src_vec(dst_vec);

    REQUIRE(src_vec.x == dst_vec.x);
    REQUIRE(src_vec.y == dst_vec.y);
  }

  {
    Vec2 dst_vec(0.01f);
    Vec2 src_vec(dst_vec);

    REQUIRE(src_vec.x == dst_vec.x);
    REQUIRE(src_vec.y == dst_vec.y);
  }

  {
    Vec2 vec(std::move(Vec2(1.14f, 3.28f)));

    REQUIRE(floatCmp(vec.x, 1.14f));
    REQUIRE(floatCmp(vec.y, 3.28f));
  }
}

TEST_CASE("Vec2 comparison") {
  {
    Vec2 vec_0(1.14f, 3.14f);
    Vec2 vec_1(1.14f, 3.14f);

    REQUIRE(vec_0 == vec_1);
  }

  {
    REQUIRE(Vec2(1.1f) == Vec2(1.1f));
    REQUIRE(Vec2() == Vec2());
    REQUIRE(Vec2(0.0f) == Vec2(0.0f));
    REQUIRE(Vec2(1.21f, 14.4f) == Vec2(1.21f, 14.4f));
  }

  {
    Vec2 vec_0(1.14f, 3.14f);
    Vec2 vec_1(1.14f, 3.13f);

    REQUIRE(vec_0 != vec_1);
  }

  {
    REQUIRE(Vec2(33333.3f) != Vec2(1.1f));
    REQUIRE(Vec2() != Vec2(1.1f));
    REQUIRE(Vec2(11.21f, 14.4f) != Vec2(33.1f, 50.2f));
  }
}

TEST_CASE("Vec2 length method") {
  {
    Vec2 custom_vec(1.23f, 32.1f);
    REQUIRE(floatCmp(32.12355677f, custom_vec.length()));

    Vec2 custom_vec1(11.3f);
    REQUIRE(floatCmp(15.980613f, custom_vec1.length()));
  }
  {
    REQUIRE(Vec2(0.0f).length() == 0.0f);
    REQUIRE(floatCmp(Vec2(1.0f).length(), sqrtf(2.0f)));
    REQUIRE(floatCmp(Vec2(3.0f, 4.0f).length(), 5.0f));
    REQUIRE(floatCmp(Vec2(3.0f, 0.0f).length(), 3.0f));
  }
}

TEST_CASE("Vec2 addition and subtraction") {
  {
    glm::vec2 glm_vec1(1.3f, 17.4f);
    glm::vec2 glm_vec2(17.5f, 9.4f);

    Vec2 custom_vec1(1.3f, 17.4f);
    Vec2 custom_vec2(17.5f, 9.4f);

    glm::vec2 glm_result_vec = glm_vec1 + glm_vec2;
    Vec2 custom_result_vec = custom_vec1 + custom_vec2;

    REQUIRE(glm_result_vec.x == custom_result_vec.x);
    REQUIRE(glm_result_vec.y == custom_result_vec.y);
  }

  {
    glm::vec2 glm_vec1(31231.1f, 38129.2f);
    glm::vec2 glm_vec2(0.4320f, 50.2f);

    Vec2 custom_vec1(31231.1f, 38129.2f);
    Vec2 custom_vec2(0.4320f, 50.2f);

    glm::vec2 glm_result_vec = glm_vec1 - glm_vec2;
    Vec2 custom_result_vec = custom_vec1 - custom_vec2;

    REQUIRE(glm_result_vec.x == custom_result_vec.x);
    REQUIRE(glm_result_vec.y == custom_result_vec.y);
  }
}

TEST_CASE("Vec2 assignment addition and subtraction") {
  {
    glm::vec2 glm_vec(31231.1f, 38129.2f);
    Vec2 custom_vec(31231.1f, 38129.2f);

    glm_vec += glm::vec2(94.8f, 4891.3f);
    custom_vec += Vec2(94.8f, 4891.3f);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
  }

  {
    glm::vec2 glm_vec(13.1f, 38.2f);
    Vec2 custom_vec(13.1f, 38.2f);

    glm_vec -= glm::vec2(2.8f, 48.3f);
    custom_vec -= Vec2(2.8f, 48.3f);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
  }
}

TEST_CASE("Vec2 assignment multiplication and division") {
  {
    glm::vec2 glm_vec(31231.1f, 38129.2f);
    Vec2 custom_vec(31231.1f, 38129.2f);

    glm_vec *= 3.3f;
    custom_vec *= 3.3f;

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
  }

  {
    glm::vec2 glm_vec(9417.122f);
    Vec2 custom_vec(9417.122f);

    glm_vec /= 23.4f;
    custom_vec /= 23.4f;

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
  }
}

TEST_CASE("Vec2 scalar multiplication") {
  Vec2 custom_vec1(11.1f, 32.2f);
  Vec2 custom_vec2(9.20f, 510.2f);

  float custom_cross_result = custom_vec1 * custom_vec2;
  REQUIRE(floatCmp(custom_cross_result, 16530.56f));
}

TEST_CASE("Vec2 multiplication and div on number") {
  {
    glm::vec2 glm_vec(12.4f, 32.1f);
    Vec2 custom_vec(12.4f, 32.1f);

    glm_vec = glm::operator*(glm_vec, {3});
    custom_vec = custom_vec * 3;

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
  }

  {
    glm::vec2 glm_vec(12.4f, 32.1f);
    Vec2 custom_vec(12.4f, 32.1f);

    glm_vec = glm::operator/(glm_vec, {2});
    custom_vec = custom_vec / 2;

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
  }
}

TEST_CASE("Vec2 normalization") {
  {
    glm::vec2 glm_vec(12.4f, 32.1f);
    Vec2 custom_vec(12.4f, 32.1f);

    glm_vec = glm::normalize(glm_vec);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.normalize().x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.normalize().y));
  }

  {
    glm::vec2 glm_vec(134.443f);
    Vec2 custom_vec(134.443f);

    glm_vec = glm::normalize(glm_vec);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.normalize().x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.normalize().y));
  }

  {
    glm::vec2 glm_vec(0.0f, 0.01f);
    Vec2 custom_vec(0.0f, 0.01f);

    glm_vec = glm::normalize(glm_vec);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.normalize().x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.normalize().y));
  }
}

/* Vec3 TEST_CASE block */

TEST_CASE("Vec3 init") {
  {
    Vec3 vec;
    REQUIRE(vec.x == 0);
    REQUIRE(vec.y == 0);
    REQUIRE(vec.z == 0);
  }

  {
    Vec3 vec(3.14f);
    REQUIRE(vec.x == 3.14f);
    REQUIRE(vec.y == 3.14f);
    REQUIRE(vec.z == 3.14f);
  }

  {
    Vec3 vec(3.14f, 1.77f, 0.42f);
    REQUIRE(vec.x == 3.14f);
    REQUIRE(vec.y == 1.77f);
    REQUIRE(vec.z == 0.42f);
  }

  {
    Vec3 vec(3.14f, 1.77f);
    REQUIRE(3.14f == vec.x);
    REQUIRE(1.77f == vec.y);
    REQUIRE(0.00f == vec.z);
  }
}

TEST_CASE("Vec3 copy and move constructor") {
  {
    Vec3 src(3.14f, 1.77f, 0.42f);
    Vec3 dst(src);

    REQUIRE(src.x == dst.x);
    REQUIRE(src.y == dst.y);
    REQUIRE(src.z == dst.z);
  }

  {
    Vec3 src(3.14f, 1.77f, 0.42f);
    Vec3 dst(std::move(src));

    REQUIRE(3.14f == dst.x);
    REQUIRE(1.77f == dst.y);
    REQUIRE(0.42f == dst.z);
  }
}

TEST_CASE("Vec3 comparison") {
  {
    REQUIRE(Vec3() == Vec3());
    REQUIRE(Vec3(2.3f) == Vec3(2.3f));
    REQUIRE(Vec3(2.3f, 4.1f) == Vec3(2.3f, 4.1f));
    REQUIRE(Vec3(3.14f, 1.77f, 0.42f) == Vec3(3.14f, 1.77f, 0.42f));
  }

  {
    REQUIRE(Vec3() != Vec3(1.1f));
    REQUIRE(Vec3(2.34f) != Vec3(2.3f));
    REQUIRE(Vec3(2.312f, 4.1f) != Vec3(2.3f, 4.131f));
    REQUIRE(Vec3(3.14f, 1.77000f, 0.42f) != Vec3(3.14f, 1.77f, 0.4212f));
  }
}

TEST_CASE("Vec3 sum and subtraction") {
  {
    glm::vec3 glm_vec0(3.14f, 1.77000f, 0.42f);
    glm::vec3 glm_vec1(33.4f, 4.4f, 31.2f);

    Vec3 custom_vec0(3.14f, 1.77000f, 0.42f);
    Vec3 custom_vec1(33.4f, 4.4f, 31.2f);

    glm::vec3 glm_result_vec = glm_vec0 + glm_vec1;
    Vec3 custom_vec_result = custom_vec0 + custom_vec1;

    REQUIRE(glm_result_vec.x == custom_vec_result.x);
    REQUIRE(glm_result_vec.y == custom_vec_result.y);
    REQUIRE(glm_result_vec.z == custom_vec_result.z);
  }

  {
    glm::vec3 glm_vec0(43.14f, 1.20f, 11.42f);
    glm::vec3 glm_vec1(3223.4f, 4442.24f, 213.24f);

    Vec3 custom_vec0(43.14f, 1.20f, 11.42f);
    Vec3 custom_vec1(3223.4f, 4442.24f, 213.24f);

    glm::vec3 glm_result_vec = glm_vec0 - glm_vec1;
    Vec3 custom_vec_result = custom_vec0 - custom_vec1;

    REQUIRE(glm_result_vec.x == custom_vec_result.x);
    REQUIRE(glm_result_vec.y == custom_vec_result.y);
    REQUIRE(glm_result_vec.z == custom_vec_result.z);
  }
}

TEST_CASE("Vec3 multiplication and division on a numbers") {
  {
    glm::vec3 glm_vec(0.3f, 21.4f, 11.12f);
    Vec3 custom_vec(0.3f, 21.4f, 11.12f);

    glm_vec = glm::operator*(glm_vec, {14.2});
    custom_vec = custom_vec * 14.2;

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
    REQUIRE(floatCmp(glm_vec.z, custom_vec.z));
  }

  {
    glm::vec3 glm_vec(0.3f, 21.4f, 11.12f);
    Vec3 custom_vec(0.3f, 21.4f, 11.12f);

    glm_vec = glm::operator/(glm_vec, {14.2});
    custom_vec = custom_vec / 14.2;

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
    REQUIRE(floatCmp(glm_vec.z, custom_vec.z));
  }
}

TEST_CASE("Vec3 assignment operations") {
  {
    Vec3 vec0(0, 0.3f, 21.2f);
    Vec3 vec1(1.1f, 3, 22.2f);

    vec0 = vec1;
    REQUIRE(vec0 == vec1);
    REQUIRE(vec0.x == 1.1f);
    REQUIRE(vec0.y == 3.0f);
    REQUIRE(vec0.z == 22.2f);
  }

  {
    Vec3 custom_vec0(0, 0.3f, 21.2f);
    Vec3 custom_vec1(1.1f, 3, 22.2f);

    glm::vec3 glm_vec0(0, 0.3f, 21.2f);
    glm::vec3 glm_vec1(1.1f, 3, 22.2f);

    custom_vec0 += custom_vec1;
    glm_vec0 += glm_vec1;

    REQUIRE(floatCmp(glm_vec0.x, custom_vec0.x));
    REQUIRE(floatCmp(glm_vec0.y, custom_vec0.y));
    REQUIRE(floatCmp(glm_vec0.z, custom_vec0.z));
  }

  {
    Vec3 custom_vec0(12.1f, 0.3f, 21.2f);
    Vec3 custom_vec1(1.1f, 3.4f, 44.2f);

    glm::vec3 glm_vec0(12.1f, 0.3f, 21.2f);
    glm::vec3 glm_vec1(1.1f, 3.4f, 44.2f);

    custom_vec0 -= custom_vec1;
    glm_vec0 -= glm_vec1;

    REQUIRE(floatCmp(glm_vec0.x, custom_vec0.x));
    REQUIRE(floatCmp(glm_vec0.y, custom_vec0.y));
    REQUIRE(floatCmp(glm_vec0.z, custom_vec0.z));
  }

  {
    Vec3 custom_vec0(12.1f, 0.3f, 21.2f);
    Vec3 custom_vec1(1.1f, 3.4f, 44.2f);

    glm::vec3 glm_vec0(12.1f, 0.3f, 21.2f);
    glm::vec3 glm_vec1(1.1f, 3.4f, 44.2f);

    custom_vec0 -= custom_vec1;
    glm_vec0 -= glm_vec1;

    REQUIRE(floatCmp(glm_vec0.x, custom_vec0.x));
    REQUIRE(floatCmp(glm_vec0.y, custom_vec0.y));
    REQUIRE(floatCmp(glm_vec0.z, custom_vec0.z));
  }

  {
    Vec3 custom_vec(12.1f, 0.3f, 21.2f);

    glm::vec3 glm_vec(12.1f, 0.3f, 21.2f);

    custom_vec *= 3.14f;
    glm_vec = glm::operator*(glm_vec, 3.14f);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
    REQUIRE(floatCmp(glm_vec.z, custom_vec.z));
  }

  {
    Vec3 custom_vec(12.1f, 1.3f, 21.2f);
    glm::vec3 glm_vec(12.1f, 1.3f, 21.2f);

    custom_vec /= 2.14f;
    glm_vec = glm::operator/(glm_vec, 2.14f);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.y));
    REQUIRE(floatCmp(glm_vec.z, custom_vec.z));
  }
}

TEST_CASE("Vec3 scalar multiplication, normalization and length") {
  {
    Vec3 custom_vec0(12.1f, 0.3f, 21.2f);
    Vec3 custom_vec1(1.1f, 3.4f, 44.2f);

    float custom_vec_result = custom_vec0 * custom_vec1;

    REQUIRE(custom_vec_result == 951.37006f);
  }

  {
    Vec3 custom_vec0(12.12f, 134.14f, 20.2f);
    Vec3 custom_vec1(12, 1.14f, 0.2f);

    REQUIRE(floatCmp(custom_vec0.length(), 136.19278f));
    REQUIRE(floatCmp(custom_vec1.length(), 12.05569f));
  }

  {
    glm::vec3 glm_vec(12.124f, 2.1f, 192.2f);
    Vec3 custom_vec(12.124f, 2.1f, 192.2f);

    glm_vec = glm::normalize(glm_vec);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.normalize().x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.normalize().y));
  }

  {
    glm::vec3 glm_vec(120, 23.11f, 13123.2f);
    Vec3 custom_vec(120, 23.11f, 13123.2f);

    glm_vec = glm::normalize(glm_vec);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.normalize().x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.normalize().y));
  }
}

/* Vec4 tests block */

TEST_CASE("Vec4 constructors") {
  {
    Vec4 vec;
    REQUIRE(vec.x == 0);
    REQUIRE(vec.y == 0);
    REQUIRE(vec.z == 0);
    REQUIRE(vec.w == 0);
  }

  {
    Vec4 vec(12.8f);
    REQUIRE(vec.x == 12.8f);
    REQUIRE(vec.y == 12.8f);
    REQUIRE(vec.z == 12.8f);
    REQUIRE(vec.w == 12.8f);
  }

  {
    Vec4 vec(1.111f, 22.22f, 333.3f, 4444);
    REQUIRE(vec.x == 1.111f);
    REQUIRE(vec.y == 22.22f);
    REQUIRE(vec.z == 333.3f);
    REQUIRE(vec.w == 4444);
  }

  {
    Vec4 vec(9.99f, 2.22f);
    REQUIRE(vec.x == 9.99f);
    REQUIRE(vec.y == 2.22f);
    REQUIRE(vec.z == 0);
    REQUIRE(vec.w == 0);
  }
}

TEST_CASE("Vec4 copy ctr and move ctr") {
  {
    Vec4 test_vec(1.111f, 22.22f, 333.3f, 4444);
    Vec4 vec(test_vec);

    REQUIRE(vec.x == 1.111f);
    REQUIRE(vec.y == 22.22f);
    REQUIRE(vec.z == 333.3f);
    REQUIRE(vec.w == 4444);
  }

  {
    Vec4 test_vec(1.111f, 22.22f, 333.3f, 4444);
    Vec4 vec(std::move(test_vec));

    REQUIRE(vec.x == 1.111f);
    REQUIRE(vec.y == 22.22f);
    REQUIRE(vec.z == 333.3f);
    REQUIRE(vec.w == 4444);
  }
}

TEST_CASE("Vec4 comparison") {
  {
    REQUIRE(Vec4() == Vec4());
    REQUIRE(Vec4(12.3f) == Vec4(12.3f));
    REQUIRE(Vec4(12.111f, 53.32f, 49.2f, 23.4f) == Vec4(12.111f, 53.32f, 49.2f, 23.4f));
    REQUIRE(Vec4(12.111f, 53.32f, 49.4f) == Vec4(12.111f, 53.32f, 49.4f));
  }
  {
    REQUIRE(Vec4(0.001) != Vec4(0.1f));
    REQUIRE(Vec4(12) != Vec4(12.3f));
    REQUIRE(Vec4(12.111f, 53.32f, 49.2f, 23.20f) != Vec4(12.111f, 53.32f, 49.2f, 23.4f));
    REQUIRE(Vec4(12.111f, 53.32f) != Vec4(12.111f, 53.32f, 49.4f));
  }
}

TEST_CASE("Vec4 sum and subtraction") {
  {
    Vec4 custom_vec0(12.4f, 44.4f, 29.4f, 0.23f);
    Vec4 custom_vec1(20.5f, 77.7f, 2.4f, 11.3f);

    glm::vec4 glm_vec0(12.4f, 44.4f, 29.4f, 0.23f);
    glm::vec4 glm_vec1(20.5f, 77.7f, 2.4f, 11.3f);

    Vec4 custom_vec_result = custom_vec0 + custom_vec1;
    glm::vec4 glm_vec_result = glm_vec0 + glm_vec1;

    REQUIRE(floatCmp(custom_vec_result.x, glm_vec_result.x));
    REQUIRE(floatCmp(custom_vec_result.y, glm_vec_result.y));
    REQUIRE(floatCmp(custom_vec_result.z, glm_vec_result.z));
    REQUIRE(floatCmp(custom_vec_result.w, glm_vec_result.w));
  }

  {
    Vec4 custom_vec0(12.4f, 44.4f, 29.4f, 0.23f);
    Vec4 custom_vec1(20.5f, 77.7f, 2.4f, 11.3f);

    glm::vec4 glm_vec0(12.4f, 44.4f, 29.4f, 0.23f);
    glm::vec4 glm_vec1(20.5f, 77.7f, 2.4f, 11.3f);

    Vec4 custom_vec_result = custom_vec0 - custom_vec1;
    glm::vec4 glm_vec_result = glm_vec0 - glm_vec1;

    REQUIRE(floatCmp(custom_vec_result.x, glm_vec_result.x));
    REQUIRE(floatCmp(custom_vec_result.y, glm_vec_result.y));
    REQUIRE(floatCmp(custom_vec_result.z, glm_vec_result.z));
    REQUIRE(floatCmp(custom_vec_result.w, glm_vec_result.w));
  }
}

TEST_CASE("Vec4 multiplication and div on a number") {
  {
    Vec4 custom_vec(12.4f, 44.4f, 29.4f, 0.23f);
    glm::vec4 glm_vec(12.4f, 44.4f, 29.4f, 0.23f);

    Vec4 custom_vec_result = custom_vec * 13.44f;
    glm::vec4 glm_vec_result = glm_vec * 13.44f;

    REQUIRE(floatCmp(custom_vec_result.x, glm_vec_result.x));
    REQUIRE(floatCmp(custom_vec_result.y, glm_vec_result.y));
    REQUIRE(floatCmp(custom_vec_result.z, glm_vec_result.z));
    REQUIRE(floatCmp(custom_vec_result.w, glm_vec_result.w));
  }

  {
    Vec4 custom_vec(12.4f, 44.4f, 29.4f, 0.23f);
    glm::vec4 glm_vec(12.4f, 44.4f, 29.4f, 0.23f);

    Vec4 custom_vec_result = custom_vec / 13.44f;
    glm::vec4 glm_vec_result = glm_vec / 13.44f;

    REQUIRE(floatCmp(custom_vec_result.x, glm_vec_result.x));
    REQUIRE(floatCmp(custom_vec_result.y, glm_vec_result.y));
    REQUIRE(floatCmp(custom_vec_result.z, glm_vec_result.z));
    REQUIRE(floatCmp(custom_vec_result.w, glm_vec_result.w));
  }
}

TEST_CASE("Vec4 assignment sum and subtraction") {
  {
    Vec4 vec1(10.0f, 20.0f, 300.0f, 400.0f);
    Vec4 vec2(5.0f, 15.0f, 350.0f, 450.0f);
    Vec4 vec3(2.0f, 2.0f, 200.0f, 200.0f);

    vec1 += vec2 += vec3;

    REQUIRE(vec2.x == 7.0f);
    REQUIRE(vec2.y == 17.0f);
    REQUIRE(vec2.z == 550.0f);
    REQUIRE(vec2.w == 650.0f);

    REQUIRE(vec1.x == 17.0f);
    REQUIRE(vec1.y == 37.0f);
    REQUIRE(vec1.z == 850.0f);
    REQUIRE(vec1.w == 1050.0f);
  }

  {
    Vec4 vec1(10.0f, 20.0f, 300.0f, 400.0f);
    Vec4 vec2(5.0f, 15.0f, 350.0f, 450.0f);
    Vec4 vec3(2.0f, 2.0f, 200.0f, 200.0f);

    vec1 -= vec2 -= vec3;

    REQUIRE(vec2.x == 3.0f);
    REQUIRE(vec2.y == 13.0f);
    REQUIRE(vec2.z == 150.0f);
    REQUIRE(vec2.w == 250.0f);

    REQUIRE(vec1.x == 7.0f);
    REQUIRE(vec1.y == 7.0f);
    REQUIRE(vec1.z == 150.0f);
    REQUIRE(vec1.w == 150.0f);
  }
}

TEST_CASE("Vec4 assignment multiplication and div on a num") {
  {
    Vec4 vec1(10.0f, 20.0f, 300.0f, 400.0f);
    vec1 *= 3.14f;

    REQUIRE(vec1.x == 10.0f * 3.14f);
    REQUIRE(vec1.y == 20.0f * 3.14f);
    REQUIRE(vec1.z == 300.0f * 3.14f);
    REQUIRE(vec1.w == 400.0f * 3.14f);
  }

  {
    Vec4 vec1(10.0f, 20.0f, 300.0f, 400.0f);
    vec1 /= 3.14f;

    REQUIRE(floatCmp(vec1.x, 10.0f / 3.14f));
    REQUIRE(floatCmp(vec1.y, 20.0f / 3.14f));
    REQUIRE(floatCmp(vec1.z, 300.0f / 3.14f));
    REQUIRE(floatCmp(vec1.w, 400.0f / 3.14f));
  }
}

TEST_CASE("Vec4 length, scalar multiplication and norm") {
  {
    REQUIRE(Vec4().length() == 0.0f);
    REQUIRE(floatCmp(Vec4(3.14, 42.42, 7.77, 333).length(), 335.79559f));
    REQUIRE(floatCmp(Vec4(3.3, 5.5, 4.4, 2.1).length(), 8.0566742518f));
  }

  {
    glm::vec4 glm_vec(12.4f, 32.1f, 32.2f, 10.4f);
    Vec4 custom_vec(12.4f, 32.1f, 32.2f, 10.4f);

    glm_vec = glm::normalize(glm_vec);

    REQUIRE(floatCmp(glm_vec.x, custom_vec.normalize().x));
    REQUIRE(floatCmp(glm_vec.y, custom_vec.normalize().y));
    REQUIRE(floatCmp(glm_vec.z, custom_vec.normalize().z));
    REQUIRE(floatCmp(glm_vec.w, custom_vec.normalize().w));
  }

  {
    Vec4 vec0(0.12f, 32.2f, 49.3f, 12.1f);
    Vec4 vec1(120.2f, 0.4f, 40.4f, 39.12f);

    float vec_res = vec0 * vec1;

    REQUIRE(floatCmp(vec_res, 2492.376f));
  }
}
