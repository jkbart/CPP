#ifdef NDEBUG
  #undef NDEBUG
#endif

#include "surfaces.h"

// To jest test sprawdzający „header guard”.
#if TEST_NUM == 600
#include "surfaces.h"
#endif

// Pliki ps_plot.h i ps_plot.cc włączają plik surfaces.h i to jest test „external”.
#if TEST_NUM <= 119
#include "ps_plot.h"
#endif

#include <cassert>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>
#include <type_traits>
#include <utility>

#if TEST_NUM >= 300 && TEST_NUM <= 599
  #define AREA_CHECK(tst_f, exp_f, min_x, max_x, step_x, min_y, max_y, step_y, prec)  \
  do {                                                                                \
    for (Real y = min_y; y <= max_y; y += step_y) {                                   \
      for (Real x = min_x; x <= max_x; x += step_x) {                                 \
        Real tst_r = tst_f(Point(x, y));                                              \
        Real exp_r = exp_f(Point(x, y));                                              \
        bool r = is_eq_prec(tst_r, exp_r, prec);                                      \
        if (!r)                                                                       \
          std::cerr << "tst_f(" << x << ", " << y << ") = " << tst_r << "\n"          \
                    << "exp_f(" << x << ", " << y << ") = " << exp_r << "\n";         \
        assert(r);                                                                    \
      }                                                                               \
    }                                                                                 \
  } while(0)                                                                          \

namespace {
  using numlim_t = std::numeric_limits<Real>;

  constexpr Real BIG_VAL = 100000000000.0;
  constexpr Real DEF_PRECISION = std::pow(2, -16);

  constexpr bool is_eq_prec(Real const x, Real const y, Real const prec) {
    return std::abs(x - y) <= prec;
  }
} // koniec anonimowej przestrzeni nazw
#endif

int main() {
#if TEST_NUM == 100
  std::ofstream out("test_plot00.ps");
  create_PS_plot(out, plain(), DEFAULT_MIN, DEFAULT_MAX, DEFAULT_MIN, DEFAULT_MAX, 9.0, 15.0);
#endif

#if TEST_NUM == 101
  std::ofstream out("test_plot01.ps");
  create_PS_plot(out, steps(), -2.5, 2.5, -2.5, 2.5, 40, 40, 75);
#endif

#if TEST_NUM == 102
  std::ofstream out("test_plot02.ps");
  create_PS_plot(out, rotate(steps(0.75), 90.0), -2.5, 2.5, -2.5, 2.5, 40, 40, 75);
#endif

#if TEST_NUM == 103
  std::ofstream out("test_plot03.ps");
  create_PS_plot(out, mul(checker(), 0.5));
#endif

#if TEST_NUM == 104
  std::ofstream out("test_plot04.ps");
  create_PS_plot(out, mul(checker(), -0.125), -2.5, 2.5, -2.5, 2.5, 40, 40, 75);
#endif

#if TEST_NUM == 105
  std::ofstream out("test_plot05.ps");
  create_PS_plot(out, invert(sqr()), -2.0, 2.0, -2.0, 2.0, 40, 40, 75);
#endif

#if TEST_NUM == 106
  auto addition = [](Real const & x, Real const & y) {return x + y;};
  std::ofstream out("test_plot06.ps");
  create_PS_plot(out, evaluate(addition, mul(sqr(), 0.5), mul(invert(sqr()), 0.25)), -2.0, 2.0, -2.0, 2.0, 40, 40, 75);
#endif

#if TEST_NUM == 107
  std::ofstream out("test_plot07.ps");
  create_PS_plot(out, evaluate([](Real const & x) {return x;}, mul(sqr(), 0.5)), -2.0, 2.0, -2.0, 2.0, 40, 40, 75);
#endif

#if TEST_NUM == 108
  auto addition = [](Real const & x, Real const & y) {return x + y;};
  std::ofstream out("test_plot08.ps");
  create_PS_plot(out, evaluate(addition, mul(sqr(), 0.5), mul(invert(sqr()), -0.25)), -2.0, 2.0, -2.0, 2.0, 40, 40, 75);
#endif

#if TEST_NUM == 109
  using std::numbers::pi;
  std::ofstream out("test_plot09.ps");
  create_PS_plot(out, sin_wave(), -2 * std::numbers::pi, 2 * std::numbers::pi, -1.0, 1.0, 40, 10, 40);
#endif

#if TEST_NUM == 110
  using std::numbers::pi;
  std::ofstream out("test_plot10.ps");
  create_PS_plot(out, scale(cos_wave(), {2.0, 1.0}), -4 * std::numbers::pi, 4 * std::numbers::pi, -1.0, 1.0, 40, 5, 20);
#endif

#if TEST_NUM == 111
  std::ofstream out("test_plot11.ps");
  create_PS_plot(out, evaluate([](Real const & x, Real const & y) {return x * y;}, mul(sin_wave(), 0.75), mul(invert(sin_wave()), 0.75)), -6.0, 6.0, -6.0, 6.0, 40, 40, 30);
#endif

#if TEST_NUM == 112
  auto addition = [](Real const & x, Real const & y) {return x + y;};
  std::ofstream out("test_plot12.ps");
  create_PS_plot(out, compose(evaluate(addition, mul(sqr(), 3.0), mul(invert(sqr()), 3.0)), [](Real const & x) {return std::sqrt(x);}, [](Real const & x) {return std::cos(x);}), -6.5, 6.5, -6.5, 6.5, 50, 50, 30);
#endif

#if TEST_NUM == 113
  std::ofstream out("test_plot13.ps");
  create_PS_plot(out, evaluate([](Real const & x, Real const & y, Real const & z) {return x + y + z;}, mul(sqr(), 0.5), mul(invert(sqr()), -0.25), mul(checker(), 0.25)), -2.5, 2.5, -2.5, 2.5, 40, 40, 75);
#endif

#if TEST_NUM == 114
  std::ofstream out("test_plot14.ps");
  create_PS_plot(out, translate(mul(ellipse(1.0, 0.5), -1.5), {0.0, -1.0}), -2.0, 2.0, -2.0, 2.0, 50, 50, 100);
#endif

#if TEST_NUM == 115
  std::ofstream out("test_plot15.ps");
  create_PS_plot(out, rotate(mul(rectangle(1.5, 1.0), 0.25), -45.0), -2.0, 2.0, -2.0, 2.0, 50, 50, 100);
#endif

#if TEST_NUM == 116
  std::ofstream out("test_plot16.ps");
  create_PS_plot(out, mul(stripes(0.25), 0.25));
#endif

#if TEST_NUM == 117
  std::ofstream out("test_plot17.ps");
  create_PS_plot(out, mul(flip(stripes(0.25)), 0.25));
#endif

#if TEST_NUM == 118
  std::ofstream out("test_plot18.ps");
  create_PS_plot(out, evaluate([](Real const & x, Real const & y) {return std::max(x, y);}, mul(slope(), 0.25), mul(flip(slope()), 0.25)));
#endif

#if TEST_NUM == 119
  std::ofstream out("test_plot19.ps");
  create_PS_plot(out, mul(rings(0.5), 0.125), -2.0, 2.0, -2.0, 2.0, 50, 50, 100);
#endif

#if TEST_NUM == 120
  // Sprawdzamy asercje z przykładu użycia.
  assert(plain()(Point(0.0, 0.0)) == 0.0);
  assert(plain()(Point(1.0, -5.0)) == 0.0);
  assert(add(plain(), 1.0)(Point(0.5, 1.0)) == 1.0);
  assert(mul(add(plain(), 1.0), 0.25)(Point(-2.0, 25.0)) == 0.25);
  assert(evaluate([](Real const & x){return 2.0 + x;}, plain())(Point(2.5, -0.25)) == 2.0);
  assert(compose()(4.2) == 4.2);
  assert(compose([](auto x) {return x - 0.5;}, [](auto x) {return x * x;})(3.5) == 9);
#endif

#if TEST_NUM == 201
  static_assert(std::is_same_v<decltype(Point::x), Real const>);
  static_assert(std::is_same_v<decltype(Point::y), Real const>);
  Point p1(1.5, 2.5);
  static_assert(std::is_floating_point_v<decltype(p1.x)>);
  static_assert(std::is_floating_point_v<decltype(p1.y)>);
  assert(p1.x == 1.5);
  assert(p1.y == 2.5);
  static_assert(std::is_const_v<decltype(p1.x)>);
  static_assert(std::is_const_v<decltype(p1.y)>);
  Point const cp2(-1.5, 2.5);
  static_assert(std::is_floating_point_v<decltype(cp2.x)>);
  static_assert(std::is_floating_point_v<decltype(cp2.y)>);
  assert(cp2.x == -1.5);
  assert(cp2.y == 2.5);
  static_assert(std::is_const_v<decltype(cp2.x)>);
  static_assert(std::is_const_v<decltype(cp2.y)>);
  // constexpr Point cep3(1.5, -2.5); // NOTE: Nie ma w treści takiego wymagania.
  Point const cep3(1.5, -2.5);
  static_assert(std::is_floating_point_v<decltype(cep3.x)>);
  static_assert(std::is_floating_point_v<decltype(cep3.y)>);
  assert(cep3.x == 1.5);
  assert(cep3.y == -2.5);
  static_assert(std::is_const_v<decltype(cep3.x)>);
  static_assert(std::is_const_v<decltype(cep3.y)>);
#endif // 201

#if TEST_NUM == 202
  std::stringstream sout;
  sout << Point(1.5, -2.25);
  assert(sout.view() == "1.5 -2.25");
  std::stringstream().swap(sout);
  sout << Point(1.0, -2.0);
  assert(sout.view() == "1 -2");
  std::stringstream().swap(sout);
  sout << Point(1.0 / 0.0, -1.0 / 0.0);
  assert(sout.view() == "inf -inf");
  std::stringstream().swap(sout);
  sout << Point(0.0 / 0.0, std::nan(""));
  assert(sout.view() == "-nan nan");
#endif // 202

#if TEST_NUM == 203
  // NOTE: Obiekt typu Point jest lekki i można go przekazywać przez kopię, ale
  // dopuszczamy też przekazywanie go przez referencję.
  static_assert(std::is_same_v<Surface, std::function<Real(Point const)>> ||
                std::is_same_v<Surface, std::function<Real(Point const &)>>);
#endif // 203

// Seria testów, które nie powinny się kompilować.
#if TEST_NUM == 204
  [[maybe_unused]] Point p;
#endif // 204

#if TEST_NUM == 205
  [[maybe_unused]] Point p(1.0);
#endif

#if TEST_NUM == 206
  [[maybe_unused]] Point p(1.0, 2.0, 3.0);
#endif

#if TEST_NUM == 207
  Point p(1.5, 2.5);
  p.x = 0.0;
#endif

#if TEST_NUM == 208
  Point p(1.5, 2.5);
  p.y = 0.0;
#endif

#if TEST_NUM == 209
  Point p(1.5, 2.5);
  p = Point(-1.0, -2.0);
#endif

#if TEST_NUM == 210
  Point p(1.5, 2.5);
  Point const cp(-1.5, 2.5);
  p = cp;
#endif

#if TEST_NUM == 301
  static_assert(std::is_same_v<decltype(plain()), Surface>);
  auto expected_plain = [](Point const) -> Real {return 0.0;};
  auto tested_plain = plain();
  AREA_CHECK(tested_plain, expected_plain, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  assert(tested_plain(Point(BIG_VAL, 0.0)) == 0.0);
  assert(tested_plain(Point(0.0, BIG_VAL)) == 0.0);
  assert(tested_plain(Point(BIG_VAL, BIG_VAL)) == 0.0);
  assert(tested_plain(Point(-BIG_VAL, 0.0)) == 0.0);
  assert(tested_plain(Point(0.0, -BIG_VAL)) == 0.0);
  assert(tested_plain(Point(-BIG_VAL, -BIG_VAL)) == 0.0);
  if (numlim_t::has_infinity) {
    assert(tested_plain(Point(numlim_t::infinity(), 0.0)) == 0.0);
    assert(tested_plain(Point(0.0, numlim_t::infinity())) == 0.0);
    assert(tested_plain(Point(numlim_t::infinity(), numlim_t::infinity())) == 0.0);
    assert(tested_plain(Point(-numlim_t::infinity(), 0.0)) == 0.0);
    assert(tested_plain(Point(0.0, -numlim_t::infinity())) == 0.0);
    assert(tested_plain(Point(-numlim_t::infinity(), -numlim_t::infinity())) == 0.0);
    assert(tested_plain(Point(numlim_t::infinity(), -numlim_t::infinity())) == 0.0);
    assert(tested_plain(Point(-numlim_t::infinity(), numlim_t::infinity())) == 0.0);
  }
  if (numlim_t::has_quiet_NaN) {
    assert(tested_plain(Point(numlim_t::quiet_NaN(), 0.0)) == 0.0);
    assert(tested_plain(Point(0.0, numlim_t::quiet_NaN())) == 0.0);
    assert(tested_plain(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN())) == 0.0);
  }
#endif // 301

#if TEST_NUM == 302
  static_assert(std::is_same_v<decltype(slope()), Surface>);
  auto expected_slope = [](Point const p) {return p.x;};
  auto tested_slope = slope();
  AREA_CHECK(tested_slope, expected_slope, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  assert(tested_slope(Point(BIG_VAL, 0.0)) == BIG_VAL);
  assert(tested_slope(Point(0.0, BIG_VAL)) == 0.0);
  assert(tested_slope(Point(BIG_VAL, BIG_VAL)) == BIG_VAL);
  assert(tested_slope(Point(-BIG_VAL, 0.0)) == -BIG_VAL);
  assert(tested_slope(Point(0.0, -BIG_VAL)) == 0.0);
  assert(tested_slope(Point(-BIG_VAL, -BIG_VAL)) == -BIG_VAL);
  if (numlim_t::has_infinity) {
    assert(tested_slope(Point(numlim_t::infinity(), 0.0)) == numlim_t::infinity());
    assert(tested_slope(Point(0.0, numlim_t::infinity())) == 0.0);
    assert(tested_slope(Point(numlim_t::infinity(), numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_slope(Point(-numlim_t::infinity(), 0.0)) == -numlim_t::infinity());
    assert(tested_slope(Point(0.0, -numlim_t::infinity())) == 0.0);
    assert(tested_slope(Point(-numlim_t::infinity(), -numlim_t::infinity())) == -numlim_t::infinity());
    assert(tested_slope(Point(numlim_t::infinity(), -numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_slope(Point(-numlim_t::infinity(), numlim_t::infinity())) == -numlim_t::infinity());
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(tested_slope(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(tested_slope(Point(0.0, numlim_t::quiet_NaN())) == 0.0);
    assert(std::isnan(tested_slope(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 302

#if TEST_NUM == 303
  static_assert(std::is_same_v<decltype(steps()), Surface>);
  static_assert(std::is_same_v<decltype(steps(2.0)), Surface>);
  auto expexted_steps_0 = [](Point const) -> Real {return 0.0;};
  auto expexted_steps_1 = [](Point const p) -> Real {return std::floor(p.x);};
  auto expexted_steps_2 = [](Point const p) -> Real {return std::floor(p.x / 2.0);};
  auto expexted_steps_4 = [](Point const p) -> Real {return std::floor(p.x / 4.0);};
  auto tested_steps_0 = steps(0.0);
  auto tested_steps_1 = steps();
  auto tested_steps_2 = steps(2.0);
  auto tested_steps_4 = steps(4.0);
  auto tested_steps_n = steps(-1.0);
  AREA_CHECK(tested_steps_0, expexted_steps_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_steps_1, expexted_steps_1, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_steps_2, expexted_steps_2, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_steps_4, expexted_steps_4, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_steps_n, expexted_steps_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  assert(tested_steps_1(Point(BIG_VAL, 0.0)) == BIG_VAL);
  assert(tested_steps_1(Point(BIG_VAL + 0.5, 0.0)) == BIG_VAL);
  assert(tested_steps_1(Point(BIG_VAL + 1.0, 0.0)) == BIG_VAL + 1.0);
  assert(tested_steps_1(Point(-BIG_VAL, 0.0)) == -BIG_VAL);
  assert(tested_steps_1(Point(-BIG_VAL - 0.5, 0.0)) == -BIG_VAL - 1.0);
  assert(tested_steps_1(Point(-BIG_VAL - 1.0, 0.0)) == -BIG_VAL - 1.0);
  assert(steps(BIG_VAL)(Point(BIG_VAL, 1.0)) == 1.0);
  assert(steps(BIG_VAL + 0.25)(Point(BIG_VAL, 1.0)) == 0.0);
  assert(steps(-BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(steps(-BIG_VAL - 0.25)(Point(1.0, 1.0)) == 0.0);
  if (numlim_t::has_infinity) {
    assert(tested_steps_1(Point(numlim_t::infinity(), 0.0)) == numlim_t::infinity());
    assert(tested_steps_1(Point(0.0, numlim_t::infinity())) == 0.0);
    assert(tested_steps_1(Point(numlim_t::infinity(), numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_steps_1(Point(-numlim_t::infinity(), 0.0)) == -numlim_t::infinity());
    assert(tested_steps_1(Point(0.0, -numlim_t::infinity())) == 0.0);
    assert(tested_steps_1(Point(-numlim_t::infinity(), -numlim_t::infinity())) == -numlim_t::infinity());
    assert(tested_steps_1(Point(numlim_t::infinity(), -numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_steps_1(Point(-numlim_t::infinity(), numlim_t::infinity())) == -numlim_t::infinity());
    assert(steps(numlim_t::infinity())(Point(1.0, 1.0)) == 0.0);
    assert(steps(-numlim_t::infinity())(Point(1.0, 1.0)) == 0.0);
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(tested_steps_1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(tested_steps_1(Point(0.0, numlim_t::quiet_NaN())) == 0.0);
    assert(std::isnan(tested_steps_1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 303

#if TEST_NUM == 304
  static_assert(std::is_same_v<decltype(checker()), Surface>);
  static_assert(std::is_same_v<decltype(checker(2.0)), Surface>);
  auto expexted_checker_0 = [](Point const) -> Real {return 0.0;};
  auto expexted_checker_1 = [](Point const p) -> Real {return fmod(floor(p.x / 1.0) + floor(p.y / 1.0), 2.0) == 0 ? 1.0 : 0.0;};
  auto expexted_checker_2 = [](Point const p) -> Real {return fmod(floor(p.x / 2.0) + floor(p.y / 2.0), 2.0) == 0 ? 1.0 : 0.0;};
  auto expexted_checker_4 = [](Point const p) -> Real {return fmod(floor(p.x / 4.0) + floor(p.y / 4.0), 2.0) == 0 ? 1.0 : 0.0;};
  auto tested_checker_0 = checker(0.0);
  auto tested_checker_1 = checker();
  auto tested_checker_2 = checker(2.0);
  auto tested_checker_4 = checker(4.0);
  auto tested_checker_n = checker(-1.0);
  AREA_CHECK(tested_checker_0, expexted_checker_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_checker_1, expexted_checker_1, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_checker_2, expexted_checker_2, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_checker_4, expexted_checker_4, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_checker_n, expexted_checker_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  assert(tested_checker_1(Point(BIG_VAL, 0.0)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 0.5, 0.0)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 1.0, 0.0)) == 0.0);
  assert(tested_checker_1(Point(BIG_VAL + 1.5, 0.0)) == 0.0);
  assert(tested_checker_1(Point(-BIG_VAL, 0.0)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL - 0.5, 0.0)) == 0.0);
  assert(tested_checker_1(Point(-BIG_VAL - 1.0, 0.0)) == 0.0);
  assert(tested_checker_1(Point(-BIG_VAL - 1.5, 0.0)) == 1.0);
  assert(tested_checker_1(Point(0.0, BIG_VAL)) == 1.0);
  assert(tested_checker_1(Point(0.0, BIG_VAL + 0.5)) == 1.0);
  assert(tested_checker_1(Point(0.0, BIG_VAL + 1.0)) == 0.0);
  assert(tested_checker_1(Point(0.0, BIG_VAL + 1.5)) == 0.0);
  assert(tested_checker_1(Point(0.0, -BIG_VAL)) == 1.0);
  assert(tested_checker_1(Point(0.0, -BIG_VAL - 0.5)) == 0.0);
  assert(tested_checker_1(Point(0.0, -BIG_VAL - 1.0)) == 0.0);
  assert(tested_checker_1(Point(0.0, -BIG_VAL - 1.5)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL, BIG_VAL)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 0.5, BIG_VAL + 0.5)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 1.0, BIG_VAL + 1.0)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 1.5, BIG_VAL + 1.5)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL, -BIG_VAL)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL - 0.5, -BIG_VAL - 0.5)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL - 1.0, -BIG_VAL - 1.0)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL - 1.5, -BIG_VAL - 1.5)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL, -BIG_VAL)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 0.5, -BIG_VAL - 0.5)) == 0.0);
  assert(tested_checker_1(Point(BIG_VAL + 1.0, -BIG_VAL - 1.0)) == 1.0);
  assert(tested_checker_1(Point(BIG_VAL + 1.5, -BIG_VAL - 1.5)) == 0.0);
  assert(tested_checker_1(Point(-BIG_VAL, BIG_VAL)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL - 0.5, BIG_VAL + 0.5)) == 0.0);
  assert(tested_checker_1(Point(-BIG_VAL - 1.0, BIG_VAL + 1.0)) == 1.0);
  assert(tested_checker_1(Point(-BIG_VAL - 1.5, BIG_VAL + 1.5)) == 0.0);
  assert(checker(-BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(checker(-BIG_VAL - 0.125)(Point(1.0, 1.0)) == 0.0);
  if (numlim_t::has_infinity) {
    assert(checker(numlim_t::infinity())(Point(1.0, 1.0)) == 1.0);
    assert(checker(-numlim_t::infinity())(Point(1.0, 1.0)) == 0.0);
  }
  if (numlim_t::has_quiet_NaN) {
    Real res = checker(numlim_t::quiet_NaN())(Point(1.0, 1.0));
    assert(std::isnan(res) || res == 0.0 || res == 1.0);
  }
#endif // 304

#if TEST_NUM == 305
  static_assert(std::is_same_v<decltype(sqr()), Surface>);
  auto expected_sqr = [](Point const p) -> Real {return p.x * p.x;};
  auto tested_sqr = sqr();
  AREA_CHECK(tested_sqr, expected_sqr, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  assert(tested_sqr(Point(100000.0, 0.0)) == 10000000000.0);
  assert(tested_sqr(Point(0.0, BIG_VAL)) == 0.0);
  assert(tested_sqr(Point(100000.0, BIG_VAL)) == 10000000000.0);
  assert(tested_sqr(Point(-100000.0, 0.0)) == 10000000000.0);
  assert(tested_sqr(Point(0.0, -BIG_VAL)) == 0.0);
  assert(tested_sqr(Point(-100000.0, -BIG_VAL)) == 10000000000.0);
  if (numlim_t::has_infinity) {
    assert(tested_sqr(Point(numlim_t::infinity(), 0.0)) == numlim_t::infinity());
    assert(tested_sqr(Point(0.0, numlim_t::infinity())) == 0.0);
    assert(tested_sqr(Point(numlim_t::infinity(), numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_sqr(Point(-numlim_t::infinity(), 0.0)) == numlim_t::infinity());
    assert(tested_sqr(Point(0.0, -numlim_t::infinity())) == 0.0);
    assert(tested_sqr(Point(-numlim_t::infinity(), -numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_sqr(Point(numlim_t::infinity(), -numlim_t::infinity())) == numlim_t::infinity());
    assert(tested_sqr(Point(-numlim_t::infinity(), numlim_t::infinity())) == numlim_t::infinity());
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(tested_sqr(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(tested_sqr(Point(0.0, numlim_t::quiet_NaN())) == 0.0);
    assert(std::isnan(tested_sqr(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 305

#if TEST_NUM == 306
  static_assert(std::is_same_v<decltype(sin_wave()), Surface>);
  auto expected_sin_wave = [](Point const p) -> Real {return std::sin(p.x);};
  auto tested_sin_wave = sin_wave();
  AREA_CHECK(tested_sin_wave, expected_sin_wave, -12.0, 12.0, 0.125, -10.0, 10.0, 0.125, DEF_PRECISION);
  assert(tested_sin_wave(Point(BIG_VAL, 0.0)) == std::sin(BIG_VAL));
  assert(tested_sin_wave(Point(0.0, BIG_VAL)) == std::sin(0.0));
  assert(tested_sin_wave(Point(BIG_VAL, BIG_VAL)) == std::sin(BIG_VAL));
  assert(tested_sin_wave(Point(-BIG_VAL, 0.0)) == std::sin(-BIG_VAL));
  assert(tested_sin_wave(Point(0.0, -BIG_VAL)) == std::sin(0.0));
  assert(tested_sin_wave(Point(-BIG_VAL, -BIG_VAL)) == std::sin(-BIG_VAL));
  if (numlim_t::has_infinity) {
    assert(std::isnan(tested_sin_wave(Point(numlim_t::infinity(), 0.0))));
    assert(tested_sin_wave(Point(0.0, numlim_t::infinity())) == std::sin(0.0));
    assert(std::isnan(tested_sin_wave(Point(numlim_t::infinity(), numlim_t::infinity()))));
    assert(std::isnan(tested_sin_wave(Point(-numlim_t::infinity(), 0.0))));
    assert(tested_sin_wave(Point(0.0, -numlim_t::infinity())) == std::sin(0.0));
    assert(std::isnan(tested_sin_wave(Point(-numlim_t::infinity(), -numlim_t::infinity()))));
    assert(std::isnan(tested_sin_wave(Point(numlim_t::infinity(), -numlim_t::infinity()))));
    assert(std::isnan(tested_sin_wave(Point(-numlim_t::infinity(), numlim_t::infinity()))));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(tested_sin_wave(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(tested_sin_wave(Point(0.0, numlim_t::quiet_NaN())) == std::sin(0.0));
    assert(std::isnan(tested_sin_wave(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 306

#if TEST_NUM == 307
  static_assert(std::is_same_v<decltype(cos_wave()), Surface>);
  auto expected_cos_wave = [](Point const p) -> Real {return std::cos(p.x);};
  auto tested_cos_wave = cos_wave();
  AREA_CHECK(tested_cos_wave, expected_cos_wave, -12.0, 12.0, 0.125, -10.0, 10.0, 0.125, DEF_PRECISION);
  assert(tested_cos_wave(Point(BIG_VAL, 0.0)) == std::cos(BIG_VAL));
  assert(tested_cos_wave(Point(0.0, BIG_VAL)) == std::cos(0.0));
  assert(tested_cos_wave(Point(BIG_VAL, BIG_VAL)) == std::cos(BIG_VAL));
  assert(tested_cos_wave(Point(-BIG_VAL, 0.0)) == std::cos(-BIG_VAL));
  assert(tested_cos_wave(Point(0.0, -BIG_VAL)) == std::cos(0.0));
  assert(tested_cos_wave(Point(-BIG_VAL, -BIG_VAL)) == std::cos(-BIG_VAL));
  if (numlim_t::has_infinity) {
    assert(std::isnan(tested_cos_wave(Point(numlim_t::infinity(), 0.0))));
    assert(tested_cos_wave(Point(0.0, numlim_t::infinity())) == std::cos(0.0));
    assert(std::isnan(tested_cos_wave(Point(numlim_t::infinity(), numlim_t::infinity()))));
    assert(std::isnan(tested_cos_wave(Point(-numlim_t::infinity(), 0.0))));
    assert(tested_cos_wave(Point(0.0, -numlim_t::infinity())) == std::cos(0.0));
    assert(std::isnan(tested_cos_wave(Point(-numlim_t::infinity(), -numlim_t::infinity()))));
    assert(std::isnan(tested_cos_wave(Point(numlim_t::infinity(), -numlim_t::infinity()))));
    assert(std::isnan(tested_cos_wave(Point(-numlim_t::infinity(), numlim_t::infinity()))));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(tested_cos_wave(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(tested_cos_wave(Point(0.0, numlim_t::quiet_NaN())) == std::cos(0.0));
    assert(std::isnan(tested_cos_wave(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 307

#if TEST_NUM == 308
  static_assert(std::is_same_v<decltype(rings()), Surface>);
  static_assert(std::is_same_v<decltype(rings(2.0)), Surface>);
  auto expected_rings_0 = [](Point const) -> Real {return 0.0;};
  auto expected_rings_1 = [](Point const p) -> Real {return std::fmod(sqrt(p.x * p.x + p.y * p.y), 2.0) <= 1.0 ? 1.0 : 0.0;};
  auto expected_rings_2 = [](Point const p) -> Real {return std::fmod(sqrt(p.x * p.x + p.y * p.y), 4.0) <= 2.0 ? 1.0 : 0.0;};
  auto expected_rings_4 = [](Point const p) -> Real {return std::fmod(sqrt(p.x * p.x + p.y * p.y), 8.0) <= 4.0 ? 1.0 : 0.0;};
  auto tested_rings_0 = rings(0.0);
  auto tested_rings_1 = rings();
  auto tested_rings_2 = rings(2.0);
  auto tested_rings_4 = rings(4.0);
  auto tested_rings_n = rings(-1.0);
  AREA_CHECK(tested_rings_0, expected_rings_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_rings_1, expected_rings_1, -10.125, 10.125, 0.25, -10.125, 10.125, 0.25, 0.0);
  AREA_CHECK(tested_rings_1, expected_rings_1, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 0.0);
  AREA_CHECK(tested_rings_2, expected_rings_2, -10.125, 10.125, 0.25, -10.125, 10.125, 0.25, 0.0);
  AREA_CHECK(tested_rings_2, expected_rings_2, -2.0, 2.0, 2.0, -2.0, 2.0, 2.0, 0.0);
  AREA_CHECK(tested_rings_4, expected_rings_4, -10.125, 10.125, 0.25, -10.125, 10.125, 0.25, 0.0);
  AREA_CHECK(tested_rings_4, expected_rings_4, -4.0, 4.0, 4.0, -4.0, 4.0, 4.0, 0.0);
  AREA_CHECK(tested_rings_n, expected_rings_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  assert(tested_rings_1(Point(BIG_VAL + 1.0, 0.0)) == 1.0);
  assert(tested_rings_1(Point(BIG_VAL + 1.5, 0.0)) == 0.0);
  assert(tested_rings_1(Point(-BIG_VAL - 1.0, 0.0)) == 1.0);
  assert(tested_rings_1(Point(-BIG_VAL - 1.5, 0.0)) == 0.0);
  assert(rings(-BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(rings(-BIG_VAL - 0.125)(Point(1.0, 1.0)) == 0.0);
#endif // 308

#if TEST_NUM == 309
  static_assert(std::is_same_v<decltype(ellipse()), Surface>);
  static_assert(std::is_same_v<decltype(ellipse(2.0, 2.0)), Surface>);
  auto expected_ellipse_00 = [](Point const) -> Real {return 0.0;};
  auto expected_ellipse_11 = [](Point const p) -> Real {return p.x * p.x + p.y * p.y <= 1.0 ? 1.0 : 0.0;};
  auto expected_ellipse_12 = [](Point const p) -> Real {return p.x * p.x + p.y * p.y / 4.0 <= 1.0 ? 1.0 : 0.0;};
  auto expected_ellipse_42 = [](Point const p) -> Real {return p.x * p.x / 16.0 + p.y * p.y / 4.0 <= 1.0 ? 1.0 : 0.0;};
  auto tested_ellipse_00 = ellipse(0.0, 0.0);
  auto tested_ellipse_11 = ellipse();
  auto tested_ellipse_12 = ellipse(1.0, 2.0);
  auto tested_ellipse_42 = ellipse(4.0, 2.0);
  auto tested_ellipse_1n = ellipse(1.0, -1.0);
  auto tested_ellipse_n1 = ellipse(-1.0, 1.0);
  auto tested_ellipse_nn = ellipse(-1.0, -1.0);
  AREA_CHECK(tested_ellipse_00, expected_ellipse_00, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_ellipse_11, expected_ellipse_11, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_ellipse_12, expected_ellipse_12, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_ellipse_42, expected_ellipse_42, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_ellipse_1n, expected_ellipse_00, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_ellipse_n1, expected_ellipse_00, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_ellipse_nn, expected_ellipse_00, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  assert(tested_ellipse_11(Point(BIG_VAL, 0.0)) == 0.0);
  assert(tested_ellipse_11(Point(0.0, BIG_VAL)) == 0.0);
  assert(tested_ellipse_11(Point(BIG_VAL, BIG_VAL)) == 0.0);
  assert(tested_ellipse_11(Point(-BIG_VAL, 0.0)) == 0.0);
  assert(tested_ellipse_11(Point(0.0, -BIG_VAL)) == 0.0);
  assert(tested_ellipse_11(Point(-BIG_VAL, -BIG_VAL)) == 0.0);
  assert(tested_ellipse_11(Point(BIG_VAL, -BIG_VAL)) == 0.0);
  assert(tested_ellipse_11(Point(-BIG_VAL, BIG_VAL)) == 0.0);
  assert(ellipse(BIG_VAL, 1.0)(Point(BIG_VAL, 0.0)) == 1.0);
  assert(ellipse(BIG_VAL, 1.0)(Point(BIG_VAL + 0.125, 0.0)) == 0.0);
  assert(ellipse(1.0, BIG_VAL)(Point(0.0, BIG_VAL)) == 1.0);
  assert(ellipse(1.0, BIG_VAL)(Point(0.0, BIG_VAL + 0.125)) == 0.0);
  assert(ellipse(BIG_VAL, BIG_VAL)(Point(BIG_VAL / 2, BIG_VAL / 2)) == 1.0);
  assert(ellipse(BIG_VAL, BIG_VAL)(Point(BIG_VAL, BIG_VAL)) == 0.0);
  assert(ellipse(-BIG_VAL, 1.0)(Point(1.0, 1.0)) == 0.0);
  assert(ellipse(1.0, -BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(ellipse(-BIG_VAL, -BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(ellipse(BIG_VAL, -BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(ellipse(-BIG_VAL, BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  if (numlim_t::has_infinity) {
    assert(tested_ellipse_11(Point(numlim_t::infinity(), 0.0)) == 0.0);
    assert(tested_ellipse_11(Point(0.0, numlim_t::infinity())) == 0.0);
    assert(tested_ellipse_11(Point(numlim_t::infinity(), numlim_t::infinity())) == 0.0);
    assert(tested_ellipse_11(Point(-numlim_t::infinity(), 0.0)) == 0.0);
    assert(tested_ellipse_11(Point(0.0, -numlim_t::infinity())) == 0.0);
    assert(tested_ellipse_11(Point(-numlim_t::infinity(), -numlim_t::infinity())) == 0.0);
    assert(tested_ellipse_11(Point(numlim_t::infinity(), -numlim_t::infinity())) == 0.0);
    assert(tested_ellipse_11(Point(-numlim_t::infinity(), numlim_t::infinity())) == 0.0);
    assert(ellipse(numlim_t::infinity(), numlim_t::infinity())(Point(1.0, 1.0)) == 1.0);
    assert(ellipse(-numlim_t::infinity(), -numlim_t::infinity())(Point(1.0, 1.0)) == 0.0);
  }
  if (numlim_t::has_quiet_NaN) {
    Real res = tested_ellipse_11(Point(numlim_t::quiet_NaN(), 0.0));
    assert(res == 0.0 || res == 1.0);
    res = tested_ellipse_11(Point(0.0, numlim_t::quiet_NaN()));
    assert(res == 0.0 || res == 1.0);
    res = tested_ellipse_11(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()));
    assert(res == 0.0 || res == 1.0);
  }
#endif // 309

#if TEST_NUM == 310
  static_assert(std::is_same_v<decltype(rectangle()), Surface>);
  static_assert(std::is_same_v<decltype(rectangle(2.0, 2.0)), Surface>);
  auto expected_rectangle_00 = [](Point const) -> Real {return 0.0;};
  auto expected_rectangle_11 = [](Point const p) -> Real {return p.x <= 1.0 && p.x >= -1.0 && p.y <= 1.0 && p.y >= -1.0 ? 1.0 : 0.0;};
  auto expected_rectangle_24 = [](Point const p) -> Real {return p.x <= 2.0 && p.x >= -2.0 && p.y <= 4.0 && p.y >= -4.0 ? 1.0 : 0.0;};
  auto expected_rectangle_42 = [](Point const p) -> Real {return p.x <= 4.0 && p.x >= -4.0 && p.y <= 2.0 && p.y >= -2.0 ? 1.0 : 0.0;};
  auto tested_rectangle_00 = rectangle(0.0, 0.0);
  auto tested_rectangle_11 = rectangle();
  auto tested_rectangle_24 = rectangle(2.0, 4.0);
  auto tested_rectangle_42 = rectangle(4.0, 2.0);
  auto tested_rectangle_1n = rectangle(1.0, -1.0);
  auto tested_rectangle_n1 = rectangle(-1.0, 1.0);
  auto tested_rectangle_nn = rectangle(-1.0, -1.0);
  AREA_CHECK(tested_rectangle_00, expected_rectangle_00, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_rectangle_11, expected_rectangle_11, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_rectangle_24, expected_rectangle_24, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_rectangle_42, expected_rectangle_42, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_rectangle_1n, expected_rectangle_00, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_rectangle_n1, expected_rectangle_00, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_rectangle_nn, expected_rectangle_00, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  assert(tested_rectangle_11(Point(BIG_VAL, 0.0)) == 0.0);
  assert(tested_rectangle_11(Point(0.0, BIG_VAL)) == 0.0);
  assert(tested_rectangle_11(Point(BIG_VAL, BIG_VAL)) == 0.0);
  assert(tested_rectangle_11(Point(-BIG_VAL, 0.0)) == 0.0);
  assert(tested_rectangle_11(Point(0.0, -BIG_VAL)) == 0.0);
  assert(tested_rectangle_11(Point(-BIG_VAL, -BIG_VAL)) == 0.0);
  assert(tested_rectangle_11(Point(BIG_VAL, -BIG_VAL)) == 0.0);
  assert(tested_rectangle_11(Point(-BIG_VAL, BIG_VAL)) == 0.0);
  assert(rectangle(BIG_VAL, 1.0)(Point(BIG_VAL, 0.0)) == 1.0);
  assert(rectangle(BIG_VAL, 1.0)(Point(BIG_VAL + 0.125, 0.0)) == 0.0);
  assert(rectangle(1.0, BIG_VAL)(Point(0.0, BIG_VAL)) == 1.0);
  assert(rectangle(1.0, BIG_VAL)(Point(0.0, BIG_VAL + 0.125)) == 0.0);
  assert(rectangle(BIG_VAL, BIG_VAL)(Point(BIG_VAL, BIG_VAL)) == 1.0);
  assert(rectangle(BIG_VAL, BIG_VAL)(Point(BIG_VAL + 0.125, BIG_VAL + 0.125)) == 0.0);
  assert(rectangle(-BIG_VAL, 1.0)(Point(1.0, 1.0)) == 0.0);
  assert(rectangle(1.0, -BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(rectangle(-BIG_VAL, -BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(rectangle(BIG_VAL, -BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(rectangle(-BIG_VAL, BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  if (numlim_t::has_infinity) {
    assert(tested_rectangle_11(Point(numlim_t::infinity(), 0.0)) == 0.0);
    assert(tested_rectangle_11(Point(0.0, numlim_t::infinity())) == 0.0);
    assert(tested_rectangle_11(Point(numlim_t::infinity(), numlim_t::infinity())) == 0.0);
    assert(tested_rectangle_11(Point(-numlim_t::infinity(), 0.0)) == 0.0);
    assert(tested_rectangle_11(Point(0.0, -numlim_t::infinity())) == 0.0);
    assert(tested_rectangle_11(Point(-numlim_t::infinity(), -numlim_t::infinity())) == 0.0);
    assert(tested_rectangle_11(Point(numlim_t::infinity(), -numlim_t::infinity())) == 0.0);
    assert(tested_rectangle_11(Point(-numlim_t::infinity(), numlim_t::infinity())) == 0.0);
    assert(rectangle(numlim_t::infinity(), numlim_t::infinity())(Point(1.0, 1.0)) == 1.0);
    assert(rectangle(-numlim_t::infinity(), -numlim_t::infinity())(Point(1.0, 1.0)) == 0.0);
  }
  if (numlim_t::has_quiet_NaN) {
    Real res = tested_rectangle_11(Point(numlim_t::quiet_NaN(), 0.0));
    assert(res == 0.0 || res == 1.0);
    res = tested_rectangle_11(Point(0.0, numlim_t::quiet_NaN()));
    assert(res == 0.0 || res == 1.0);
    res = tested_rectangle_11(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()));
    assert(res == 0.0 || res == 1.0);
  }
#endif // 310

#if TEST_NUM == 311
  // NOTE: W treści zabrakło wymagania na domyślną szerokość pasków.
  // static_assert(std::is_same_v<decltype(stripes()), Surface>);
  static_assert(std::is_same_v<decltype(stripes(1.0)), Surface>);
  static_assert(std::is_same_v<decltype(stripes(2.0)), Surface>);
  auto expected_stripes_0 = [](Point const) -> Real {return 0.0;};
  auto expected_stripes_1 = [](Point const p) -> Real {return std::fmod(ceil(p.x), 2.0) != 0 ? 1.0 : 0.0;};
  auto expected_stripes_2 = [](Point const p) -> Real {return std::fmod(ceil(p.x / 2.0), 2.0) != 0 ? 1.0 : 0.0;};
  auto expected_stripes_4 = [](Point const p) -> Real {return std::fmod(ceil(p.x / 4.0), 2.0) != 0 ? 1.0 : 0.0;};
  auto tested_stripes_0 = stripes(0.0);
  // NOTE: W treści zabrakło wymagania na domyślną szerokość pasków.
  // auto tested_stripes_1 = stripes();
  auto tested_stripes_1 = stripes(1.0);
  auto tested_stripes_2 = stripes(2.0);
  auto tested_stripes_4 = stripes(4.0);
  auto tested_stripes_n = stripes(-1.0);
  AREA_CHECK(tested_stripes_0, expected_stripes_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_stripes_1, expected_stripes_1, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_stripes_2, expected_stripes_2, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_stripes_4, expected_stripes_4, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  AREA_CHECK(tested_stripes_n, expected_stripes_0, -10.0, 10.0, 0.125, -10.0, 10.0, 0.125, 0.0);
  assert(tested_stripes_1(Point(BIG_VAL, 0.0)) == 0.0);
  assert(tested_stripes_1(Point(BIG_VAL + 0.5, 0.0)) == 1.0);
  assert(tested_stripes_1(Point(BIG_VAL + 1.0, 0.0)) == 1.0);
  assert(tested_stripes_1(Point(-BIG_VAL, 0.0)) == 0.0);
  assert(tested_stripes_1(Point(-BIG_VAL - 1.0, 0.0)) == 1.0);
  assert(tested_stripes_1(Point(-BIG_VAL - 1.5, 0.0)) == 1.0);
  assert(stripes(-BIG_VAL)(Point(1.0, 1.0)) == 0.0);
  assert(stripes(-BIG_VAL - 0.125)(Point(1.0, 1.0)) == 0.0);
  if (numlim_t::has_infinity) {
    assert(stripes(numlim_t::infinity())(Point(-1.0, 1.0)) == 0.0);
    assert(stripes(-numlim_t::infinity())(Point(-1.0, 1.0)) == 0.0);
  }
  if (numlim_t::has_quiet_NaN) {
    Real res = stripes(numlim_t::quiet_NaN())(Point(-1.0, 1.0));
    assert(std::isnan(res) || res == 0.0 || res == 1.0);
  }
#endif // 311

// Seria testów, które nie powinny się kompilować.
#if TEST_NUM == 312
  [[maybe_unused]] auto f = plain(1.0);
#endif

#if TEST_NUM == 313
  [[maybe_unused]] auto f = plain(1.0, 1.0);
#endif

#if TEST_NUM == 314
  [[maybe_unused]] auto f = plain(Point(1.0, 1.0));
#endif

#if TEST_NUM == 315
  [[maybe_unused]] auto f = slope(1.0);
#endif

#if TEST_NUM == 316
  [[maybe_unused]] auto f = slope(1.0, 1.0);
#endif

#if TEST_NUM == 317
  [[maybe_unused]] auto f = slope(Point(1.0, 1.0));
#endif

#if TEST_NUM == 318
  [[maybe_unused]] auto f = steps(1.0, 1.0);
#endif

#if TEST_NUM == 319
  [[maybe_unused]] auto f = steps(Point(1.0, 1.0));
#endif

#if TEST_NUM == 320
  [[maybe_unused]] auto f = steps(1.5, Point(1.0, 1.0));
#endif

#if TEST_NUM == 321
  [[maybe_unused]] auto f = steps(Point(1.0, 1.0), 1.5);
#endif

#if TEST_NUM == 322
  [[maybe_unused]] auto f = sqr(1.0);
#endif

#if TEST_NUM == 323
  [[maybe_unused]] auto f = sqr(1.0, 1.0);
#endif

#if TEST_NUM == 324
  [[maybe_unused]] auto f = sqr(Point(1.0, 1.0));
#endif

#if TEST_NUM == 325
  [[maybe_unused]] auto f = sin_wave(1.0);
#endif

#if TEST_NUM == 326
  [[maybe_unused]] auto f = sin_wave(1.0, 1.0);
#endif

#if TEST_NUM == 327
  [[maybe_unused]] auto f = sin_wave(Point(1.0, 1.0));
#endif

#if TEST_NUM == 328
  [[maybe_unused]] auto f = cos_wave(1.0);
#endif

#if TEST_NUM == 329
  [[maybe_unused]] auto f = cos_wave(1.0, 1.0);
#endif

#if TEST_NUM == 330
  [[maybe_unused]] auto f = cos_wave(Point(1.0, 1.0));
#endif

#if TEST_NUM == 331
  [[maybe_unused]] auto f = ellipse(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 332
  [[maybe_unused]] auto f = ellipse(1.0, 1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 333
  [[maybe_unused]] auto f = ellipse(Point(1.0, 1.0));
#endif

#if TEST_NUM == 334
  [[maybe_unused]] auto f = ellipse(1.0, Point(1.0, 1.0));
#endif

#if TEST_NUM == 335
  [[maybe_unused]] auto f = ellipse(1.0, 1.0, Point(1.0, 1.0));
#endif

#if TEST_NUM == 336
  [[maybe_unused]] auto f = ellipse(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 337
  [[maybe_unused]] auto f = ellipse(Point(1.0, 1.0), 1.0, 1.0);
#endif

#if TEST_NUM == 338
  [[maybe_unused]] auto f = rectangle(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 339
  [[maybe_unused]] auto f = rectangle(1.0, 1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 340
  [[maybe_unused]] auto f = rectangle(Point(1.0, 1.0));
#endif

#if TEST_NUM == 341
  [[maybe_unused]] auto f = rectangle(1.0, Point(1.0, 1.0));
#endif

#if TEST_NUM == 342
  [[maybe_unused]] auto f = rectangle(1.0, 1.0, Point(1.0, 1.0));
#endif

#if TEST_NUM == 343
  [[maybe_unused]] auto f = rectangle(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 344
  [[maybe_unused]] auto f = rectangle(Point(1.0, 1.0), 1.0, 1.0);
#endif

#if TEST_NUM == 345
  [[maybe_unused]] auto f = checker(1.0, 1.0);
#endif

#if TEST_NUM == 346
  [[maybe_unused]] auto f = checker(Point(1.0, 1.0));
#endif

#if TEST_NUM == 347
  [[maybe_unused]] auto f = rings(1.0, 1.0);
#endif

#if TEST_NUM == 348
  [[maybe_unused]] auto f = rings(Point(1.0, 1.0));
#endif

#if TEST_NUM == 349
  [[maybe_unused]] auto f = stripes(1.0, 1.0);
#endif

#if TEST_NUM == 350
  [[maybe_unused]] auto f = stripes(Point(1.0, 1.0));
#endif

#if TEST_NUM == 401
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(rotate(surf, 1.0)), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  for (Real deg = 0.0; deg <= 360.0; deg += 0.5) {
    auto expected_rotate_1 = [test_surface_1, deg](Point const p) -> Real {
      Real const rad = -deg * std::numbers::pi / 180.0;
      return test_surface_1(Point(p.x * std::cos(rad) - p.y * std::sin(rad), p.x * std::sin(rad) + p.y * std::cos(rad)));
    };
    auto expected_rotate_2 = [test_surface_2, deg](Point const p) -> Real {
      Real const rad = deg * std::numbers::pi / 180.0;
      return test_surface_2(Point(p.x * std::cos(rad) - p.y * std::sin(rad), p.x * std::sin(rad) + p.y * std::cos(rad)));
    };
    auto tested_rotate_1 = rotate(test_surface_1, deg);
    auto tested_rotate_2 = rotate(test_surface_2, -deg);
    AREA_CHECK(tested_rotate_1, expected_rotate_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
    AREA_CHECK(tested_rotate_2, expected_rotate_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
  }
  auto fro1 = rotate(test_surface_1, 90.0);
  auto fro2 = rotate(test_surface_1, 90.0 * (BIG_VAL + 1.0));
  assert(is_eq_prec(fro1(Point(BIG_VAL, 0.0)), test_surface_1(Point(0.0, -BIG_VAL)), DEF_PRECISION));
  assert(is_eq_prec(fro1(Point(0.0, -BIG_VAL)), test_surface_1(Point(-BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fro1(Point(-BIG_VAL, BIG_VAL)), test_surface_1(Point(BIG_VAL, BIG_VAL)), DEF_PRECISION));
  assert(is_eq_prec(fro2(Point(1.0, 0.0)), test_surface_1(Point(0.0, -1.0)), DEF_PRECISION));
  assert(is_eq_prec(fro2(Point(0.0, -1.0)), test_surface_1(Point(-1.0, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fro2(Point(-1.0, 1.0)), test_surface_1(Point(1.0, 1.0)), DEF_PRECISION));
  if (numlim_t::has_infinity) {
    auto fro3 = rotate(test_surface_1, numlim_t::infinity());
    assert(std::isnan(fro3(Point(1.0, 0.0))));
    assert(std::isnan(fro3(Point(0.0, -1.0))));
    assert(std::isnan(fro3(Point(-1.0, 1.0))));
  }
  if (numlim_t::has_quiet_NaN) {
    auto fro4 = rotate(test_surface_1, numlim_t::quiet_NaN());
    assert(std::isnan(fro4(Point(1.0, 0.0))));
    assert(std::isnan(fro4(Point(-1.0, 0.0))));
    assert(std::isnan(fro4(Point(1.0, -1.0))));
  }
#endif // 401

#if TEST_NUM == 402
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(translate(surf, Point(1.0, 1.0))), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  for (Real tx = -2.0; tx <= 2.0; tx += 0.25) {
    for (Real ty = -2.0; ty <= 2.0; ty += 0.25) {
      Point const v(tx, ty);
      auto expected_translate_1 = [test_surface_1, v](Point const p) -> Real {return test_surface_1(Point(p.x - v.x, p.y - v.y));};
      auto expected_translate_2 = [test_surface_2, v](Point const p) -> Real {return test_surface_2(Point(p.x - v.x, p.y - v.y));};
      auto tested_translate_1 = translate(test_surface_1, v);
      auto tested_translate_2 = translate(test_surface_2, v);
      AREA_CHECK(tested_translate_1, expected_translate_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
      AREA_CHECK(tested_translate_2, expected_translate_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
    }
  }
  auto ftr1 = translate(test_surface_1, Point(1.5, 1.0));
  auto ftr2 = translate(test_surface_1, Point(BIG_VAL, BIG_VAL + 0.5));
  assert(is_eq_prec(ftr1(Point(BIG_VAL, 0.0)), test_surface_1(Point(BIG_VAL - 1.5, -1.0)), DEF_PRECISION));
  assert(is_eq_prec(ftr1(Point(0.0, -BIG_VAL)), test_surface_1(Point(-1.5, -BIG_VAL - 1.0)), DEF_PRECISION));
  assert(is_eq_prec(ftr1(Point(-BIG_VAL, BIG_VAL)), test_surface_1(Point(-BIG_VAL - 1.5, BIG_VAL - 1.0)), DEF_PRECISION));
  assert(is_eq_prec(ftr2(Point(1.0, 0.0)), test_surface_1(Point(1.0 - BIG_VAL, -BIG_VAL - 0.5)), DEF_PRECISION));
  assert(is_eq_prec(ftr2(Point(0.0, -1.0)), test_surface_1(Point(-BIG_VAL, -1.5 - BIG_VAL)), DEF_PRECISION));
  assert(is_eq_prec(ftr2(Point(-1.0, 1.0)), test_surface_1(Point(-1.0 - BIG_VAL, 0.5 - BIG_VAL)), DEF_PRECISION));
  assert(is_eq_prec(ftr2(Point(BIG_VAL, 0.0)), test_surface_1(Point(0.0, -BIG_VAL - 0.5)), DEF_PRECISION));
  assert(is_eq_prec(ftr2(Point(0.0, -BIG_VAL)), test_surface_1(Point(-BIG_VAL, -2.0 * BIG_VAL - 0.5)), DEF_PRECISION));
  assert(is_eq_prec(ftr2(Point(-BIG_VAL, BIG_VAL)), test_surface_1(Point(-2.0 * BIG_VAL, -0.5)), DEF_PRECISION));
  if (numlim_t::has_infinity) {
    assert(ftr1(Point(numlim_t::infinity(), 0.0)) == test_surface_1(Point(numlim_t::infinity(), -1.0)));
    assert(ftr1(Point(0.0, -numlim_t::infinity())) == test_surface_1(Point(-1.5, -numlim_t::infinity())));
    assert(ftr1(Point(numlim_t::infinity(), numlim_t::infinity())) == test_surface_1(Point(numlim_t::infinity(), numlim_t::infinity())));
    assert(std::isnan(ftr1(Point(-numlim_t::infinity(), numlim_t::infinity()))));
    auto ftr3 = translate(test_surface_1, Point(numlim_t::infinity(), numlim_t::infinity()));
    assert(ftr3(Point(1.0, 0.0)) == test_surface_1(Point(-numlim_t::infinity(), -numlim_t::infinity())));
    assert(ftr3(Point(0.0, -1.0)) == test_surface_1(Point(-numlim_t::infinity(), -numlim_t::infinity())));
    assert(ftr3(Point(-1.0, 1.0)) == test_surface_1(Point(-numlim_t::infinity(), -numlim_t::infinity())));
    assert(std::isnan(ftr3(Point(numlim_t::infinity(), 0.0))));
    assert(ftr3(Point(0.0, -numlim_t::infinity())) == test_surface_1(Point(-numlim_t::infinity(), -numlim_t::infinity())));
    assert(std::isnan(ftr3(Point(-numlim_t::infinity(), numlim_t::infinity()))));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(ftr1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(ftr1(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(ftr1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
    auto ftr4 = translate(test_surface_1, Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()));
    assert(std::isnan(ftr4(Point(1.0, 0.0))));
    assert(std::isnan(ftr4(Point(0.0, -1.0))));
    assert(std::isnan(ftr4(Point(-1.0, 0.0))));
    assert(std::isnan(ftr4(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(ftr4(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(ftr4(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 402

#if TEST_NUM == 403
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(scale(surf, Point(1.0, 1.0))), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  for (Real sx = -2.0; sx <= 2.0; sx += 0.25) {
    for (Real sy = -2.0; sy <= 2.0; sy += 0.25) {
      Point const s1(sx, sy);
      Point const s2(-sx, -sy);
      auto expected_scale_1 = [test_surface_1, s1](Point const p) -> Real {return test_surface_1(Point(p.x / s1.x, p.y / s1.y));};
      auto expected_scale_2 = [test_surface_2, s2](Point const p) -> Real {return test_surface_2(Point(p.x / s2.x, p.y / s2.y));};
      auto tested_scale_1 = scale(test_surface_1, s1);
      auto tested_scale_2 = scale(test_surface_2, s2);
      if (sx != 0.0 && sy != 0.0) {
        AREA_CHECK(tested_scale_1, expected_scale_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
        AREA_CHECK(tested_scale_2, expected_scale_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
      }
    }
  }
  auto fsc1 = scale(test_surface_1, Point(1.5, 0.5));
  auto fsc2 = scale(test_surface_1, Point(BIG_VAL, BIG_VAL + 0.5));
  assert(is_eq_prec(fsc1(Point(BIG_VAL, 0.0)), test_surface_1(Point(BIG_VAL / 1.5, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fsc1(Point(0.0, -BIG_VAL)), test_surface_1(Point(0.0, -BIG_VAL / 0.5)), DEF_PRECISION));
  assert(is_eq_prec(fsc1(Point(-BIG_VAL, BIG_VAL)), test_surface_1(Point(-BIG_VAL / 1.5, BIG_VAL / 0.5)), DEF_PRECISION));
  assert(is_eq_prec(fsc2(Point(1.0, 0.0)), test_surface_1(Point(1.0 / BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fsc2(Point(0.0, -1.0)), test_surface_1(Point(0.0, -1.0 / (BIG_VAL + 0.5))), DEF_PRECISION));
  assert(is_eq_prec(fsc2(Point(-1.0, 1.0)), test_surface_1(Point(-1.0 / BIG_VAL, 1.0 / (BIG_VAL + 0.5))), DEF_PRECISION));
  assert(is_eq_prec(fsc2(Point(BIG_VAL, 0.0)), test_surface_1(Point(1.0, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fsc2(Point(0.0, -BIG_VAL)), test_surface_1(Point(0.0, -BIG_VAL / (BIG_VAL + 0.5))), DEF_PRECISION));
  assert(is_eq_prec(fsc2(Point(-BIG_VAL, BIG_VAL)), test_surface_1(Point(-1.0, BIG_VAL / (BIG_VAL + 0.5))), DEF_PRECISION));
  assert(std::isinf(scale(test_surface_1, Point(0.0, 1.0))(Point(1.0, 1.0))));
  assert(std::isinf(scale(test_surface_1, Point(0.0, 1.0))(Point(-1.0, 1.0))));
  assert(std::isnan(scale(test_surface_1, Point(0.0, 1.0))(Point(0.0, 1.0))));
  assert(std::isinf(scale(test_surface_1, Point(1.0, 0.0))(Point(1.0, 1.0))));
  assert(std::isinf(scale(test_surface_1, Point(1.0, 0.0))(Point(1.0, -1.0))));
  assert(std::isnan(scale(test_surface_1, Point(1.0, 0.0))(Point(1.0, 0.0))));
  assert(std::isinf(scale(test_surface_1, Point(0.0, 0.0))(Point(1.0, 1.0))));
  assert(std::isinf(scale(test_surface_1, Point(0.0, 0.0))(Point(-1.0, -1.0))));
  assert(std::isnan(scale(test_surface_1, Point(0.0, 0.0))(Point(0.0, 0.0))));
  assert(std::isinf(scale(test_surface_2, Point(0.0, 1.0))(Point(1.0, 1.0))));
  assert(std::isinf(scale(test_surface_2, Point(0.0, 1.0))(Point(-1.0, 1.0))));
  assert(std::isnan(scale(test_surface_2, Point(0.0, 1.0))(Point(0.0, 1.0))));
  assert(std::isinf(scale(test_surface_2, Point(1.0, 0.0))(Point(1.0, 1.0))));
  assert(std::isinf(scale(test_surface_2, Point(1.0, 0.0))(Point(1.0, -1.0))));
  assert(std::isnan(scale(test_surface_2, Point(1.0, 0.0))(Point(1.0, 0.0))));
  assert(std::isinf(scale(test_surface_2, Point(0.0, 0.0))(Point(1.0, 1.0))));
  assert(std::isinf(scale(test_surface_2, Point(0.0, 0.0))(Point(-1.0, -1.0))));
  assert(std::isnan(scale(test_surface_2, Point(0.0, 0.0))(Point(0.0, 0.0))));
  if (numlim_t::has_infinity) {
    assert(fsc1(Point(numlim_t::infinity(), 0.0)) == test_surface_1(Point(numlim_t::infinity() / 1.5, 0.0)));
    assert(fsc1(Point(0.0, -numlim_t::infinity())) == test_surface_1(Point(0.0, -numlim_t::infinity() / 0.5)));
    assert(fsc1(Point(numlim_t::infinity(), numlim_t::infinity())) == test_surface_1(Point(numlim_t::infinity() / 1.5, numlim_t::infinity() / 0.5)));
    assert(std::isnan(fsc1(Point(-numlim_t::infinity(), numlim_t::infinity()))));
    auto fsc3 = scale(test_surface_1, Point(numlim_t::infinity(), numlim_t::infinity()));
    assert(fsc3(Point(1.0, 0.5)) == test_surface_1(Point(0.0, 0.0)));
    assert(fsc3(Point(-0.5, -1.0)) == test_surface_1(Point(0.0, 0.0)));
    assert(std::isnan(fsc3(Point(numlim_t::infinity(), 0.0))));
    assert(std::isnan(fsc3(Point(0.0, -numlim_t::infinity()))));
    assert(std::isnan(fsc3(Point(-numlim_t::infinity(), numlim_t::infinity()))));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(fsc1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fsc1(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fsc1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
    auto fsc4 = scale(test_surface_1, Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()));
    assert(std::isnan(fsc4(Point(1.0, 0.0))));
    assert(std::isnan(fsc4(Point(0.0, -1.0))));
    assert(std::isnan(fsc4(Point(-1.0, 0.0))));
    assert(std::isnan(fsc4(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fsc4(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fsc4(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 403

#if TEST_NUM == 404
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(invert(surf)), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  auto expected_invert_1 = [test_surface_1](Point const p) -> Real {return test_surface_1(Point(p.y, p.x));};
  auto expected_invert_2 = [test_surface_2](Point const p) -> Real {return test_surface_2(Point(p.y, p.x));};
  auto tested_invert_1 = invert(test_surface_1);
  auto tested_invert_2 = invert(test_surface_2);
  AREA_CHECK(tested_invert_1, expected_invert_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_invert_2, expected_invert_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  auto fin1 = invert(test_surface_1);
  assert(is_eq_prec(fin1(Point(BIG_VAL, 0.0)), test_surface_1(Point(0.0, BIG_VAL)), 0.0));
  assert(is_eq_prec(fin1(Point(-BIG_VAL, 0.0)), test_surface_1(Point(0.0, -BIG_VAL)), 0.0));
  assert(is_eq_prec(fin1(Point(BIG_VAL, -BIG_VAL)), test_surface_1(Point(-BIG_VAL, BIG_VAL)), 0.0));
  if (numlim_t::has_infinity) {
    assert(fin1(Point(numlim_t::infinity(), 0.0)) == test_surface_1(Point(0.0, numlim_t::infinity())));
    assert(fin1(Point(-numlim_t::infinity(), 0.0)) == test_surface_1(Point(0.0, -numlim_t::infinity())));
    assert(std::isnan(fin1(Point(numlim_t::infinity(), -numlim_t::infinity()))));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(fin1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fin1(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fin1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 404

#if TEST_NUM == 405
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(flip(surf)), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  auto expected_flip_1 = [test_surface_1](Point const p) -> Real {return test_surface_1(Point(-p.x, p.y));};
  auto expected_flip_2 = [test_surface_2](Point const p) -> Real {return test_surface_2(Point(-p.x, p.y));};
  auto tested_flip_1 = flip(test_surface_1);
  auto tested_flip_2 = flip(test_surface_2);
  AREA_CHECK(tested_flip_1, expected_flip_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  AREA_CHECK(tested_flip_2, expected_flip_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, 0.0);
  auto ffl1 = flip(test_surface_1);
  assert(is_eq_prec(ffl1(Point(BIG_VAL, 0.0)), test_surface_1(Point(-BIG_VAL, 0.0)), 0.0));
  assert(is_eq_prec(ffl1(Point(-BIG_VAL, 0.0)), test_surface_1(Point(BIG_VAL, 0.0)), 0.0));
  assert(is_eq_prec(ffl1(Point(BIG_VAL, -BIG_VAL)), test_surface_1(Point(-BIG_VAL, -BIG_VAL)), 0.0));
  if (numlim_t::has_infinity) {
    assert(ffl1(Point(numlim_t::infinity(), 0.0)) == test_surface_1(Point(-numlim_t::infinity(), 0.0)));
    assert(ffl1(Point(-numlim_t::infinity(), 0.0)) == test_surface_1(Point(numlim_t::infinity(), 0.0)));
    assert(ffl1(Point(numlim_t::infinity(), -numlim_t::infinity())) == test_surface_1(Point(-numlim_t::infinity(), -numlim_t::infinity())));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(ffl1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(ffl1(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(ffl1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 405

#if TEST_NUM == 406
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(mul(surf, 1.0)), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  for (Real c = -3.0; c <= 3.0; c += 0.125) {
    auto expected_mul_1 = [test_surface_1, c](Point const p) -> Real {return c * test_surface_1(p);};
    auto expected_mul_2 = [test_surface_2, c](Point const p) -> Real {return -c * test_surface_2(p);};
    auto tested_mul_1 = mul(test_surface_1, c);
    auto tested_mul_2 = mul(test_surface_2, -c);
    AREA_CHECK(tested_mul_1, expected_mul_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
    AREA_CHECK(tested_mul_2, expected_mul_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
  }
  auto fmu1 = mul(test_surface_1, 1.5);
  auto fmu2 = mul(test_surface_1, BIG_VAL);
  assert(is_eq_prec(fmu1(Point(BIG_VAL, 0.0)), 1.5 * test_surface_1(Point(BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu1(Point(-BIG_VAL, 0.0)), 1.5 * test_surface_1(Point(-BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu1(Point(BIG_VAL, -BIG_VAL)), 1.5 * test_surface_1(Point(BIG_VAL, -BIG_VAL)), DEF_PRECISION));
  assert(is_eq_prec(fmu2(Point(1.0, 0.0)), BIG_VAL * test_surface_1(Point(1.0, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu2(Point(-1.0, 0.0)), BIG_VAL * test_surface_1(Point(-1.0, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu2(Point(1.0, -1.0)), BIG_VAL * test_surface_1(Point(1.0, -1.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu2(Point(BIG_VAL, 0.0)), BIG_VAL * test_surface_1(Point(BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu2(Point(-BIG_VAL, 0.0)), BIG_VAL * test_surface_1(Point(-BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fmu2(Point(BIG_VAL, -BIG_VAL)), BIG_VAL * test_surface_1(Point(BIG_VAL, -BIG_VAL)), DEF_PRECISION));
  if (numlim_t::has_infinity) {
    assert(fmu1(Point(numlim_t::infinity(), 0.0)) == 1.5 * test_surface_1(Point(numlim_t::infinity(), 0.0)));
    assert(fmu1(Point(-numlim_t::infinity(), 0.0)) == 1.5 * test_surface_1(Point(-numlim_t::infinity(), 0.0)));
    assert(fmu1(Point(numlim_t::infinity(), numlim_t::infinity())) == 1.5 * test_surface_1(Point(numlim_t::infinity(), numlim_t::infinity())));
    auto fmu3 = mul(test_surface_1, numlim_t::infinity());
    assert(fmu3(Point(1.0, 0.0)) == numlim_t::infinity() * test_surface_1(Point(1.0, 0.0)));
    assert(fmu3(Point(-1.0, 0.0)) == numlim_t::infinity() * test_surface_1(Point(-1.0, 0.0)));
    assert(fmu3(Point(2.0, -1.0)) == numlim_t::infinity() * test_surface_1(Point(2.0, -1.0)));
    assert(std::isnan(fmu3(Point(1.0, -1.0))));
    assert(fmu3(Point(numlim_t::infinity(), 0.0)) == numlim_t::infinity() * test_surface_1(Point(numlim_t::infinity(), 0.0)));
    assert(fmu3(Point(-numlim_t::infinity(), 0.0)) == numlim_t::infinity() * test_surface_1(Point(-numlim_t::infinity(), 0.0)));
    assert(fmu3(Point(numlim_t::infinity(), numlim_t::infinity())) == numlim_t::infinity() * test_surface_1(Point(numlim_t::infinity(), numlim_t::infinity())));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(fmu1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fmu1(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fmu1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
    auto fmu4 = mul(test_surface_1, numlim_t::quiet_NaN());
    assert(std::isnan(fmu4(Point(1.0, 0.0))));
    assert(std::isnan(fmu4(Point(-1.0, 0.0))));
    assert(std::isnan(fmu4(Point(2.0, -1.0))));
    assert(std::isnan(fmu4(Point(1.0, -1.0))));
    assert(std::isnan(fmu4(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fmu4(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fmu4(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 406

#if TEST_NUM == 407
  auto surf = [](Point const) {return 1.0;};
  static_assert(std::is_same_v<decltype(add(surf, 1.0)), Surface>);
  auto test_surface_1 = [](Point const p) {return p.x + p.y;};
  auto test_surface_2 = [](Point const p) {return p.x * p.y;};
  for (Real c = -3.0; c <= 3.0; c += 0.125) {
    auto expected_add_1 = [test_surface_1, c](Point const p) -> Real {return c + test_surface_1(p);};
    auto expected_add_2 = [test_surface_2, c](Point const p) -> Real {return -c + test_surface_2(p);};
    auto tested_add_1 = add(test_surface_1, c);
    auto tested_add_2 = add(test_surface_2, -c);
    AREA_CHECK(tested_add_1, expected_add_1, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
    AREA_CHECK(tested_add_2, expected_add_2, -5.0, 5.0, 0.125, -5.0, 5.0, 0.125, DEF_PRECISION);
  }
  auto fad1 = add(test_surface_1, 1.5);
  auto fad2 = add(test_surface_1, BIG_VAL);
  assert(is_eq_prec(fad1(Point(BIG_VAL, 0.0)), 1.5 + test_surface_1(Point(BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fad1(Point(-BIG_VAL, 0.0)), 1.5 + test_surface_1(Point(-BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fad1(Point(BIG_VAL, -BIG_VAL)), 1.5 + test_surface_1(Point(BIG_VAL, -BIG_VAL)), DEF_PRECISION));
  assert(is_eq_prec(fad2(Point(1.0, 0.0)), BIG_VAL + test_surface_1(Point(1.0, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fad2(Point(-1.0, 0.0)), BIG_VAL + test_surface_1(Point(-1.0, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fad2(Point(1.0, -1.0)), BIG_VAL + test_surface_1(Point(1.0, -1.0)), DEF_PRECISION));
  assert(is_eq_prec(fad2(Point(BIG_VAL, 0.0)), BIG_VAL + test_surface_1(Point(BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fad2(Point(-BIG_VAL, 0.0)), BIG_VAL + test_surface_1(Point(-BIG_VAL, 0.0)), DEF_PRECISION));
  assert(is_eq_prec(fad2(Point(BIG_VAL, -BIG_VAL)), BIG_VAL + test_surface_1(Point(BIG_VAL, -BIG_VAL)), DEF_PRECISION));
  if (numlim_t::has_infinity) {
    assert(fad1(Point(numlim_t::infinity(), 0.0)) == 1.5 + test_surface_1(Point(numlim_t::infinity(), 0.0)));
    assert(fad1(Point(-numlim_t::infinity(), 0.0)) == 1.5 + test_surface_1(Point(-numlim_t::infinity(), 0.0)));
    assert(fad1(Point(numlim_t::infinity(), numlim_t::infinity())) == 1.5 + test_surface_1(Point(numlim_t::infinity(), numlim_t::infinity())));
    auto fad3 = add(test_surface_1, numlim_t::infinity());
    assert(fad3(Point(1.0, 0.0)) == numlim_t::infinity() + test_surface_1(Point(1.0, 0.0)));
    assert(fad3(Point(-1.0, 0.0)) == numlim_t::infinity() + test_surface_1(Point(-1.0, 0.0)));
    assert(fad3(Point(1.0, -1.0)) == numlim_t::infinity() + test_surface_1(Point(2.0, -1.0)));
    assert(fad3(Point(numlim_t::infinity(), 0.0)) == numlim_t::infinity() + test_surface_1(Point(numlim_t::infinity(), 0.0)));
    assert(std::isnan(fad3(Point(-numlim_t::infinity(), 0.0))));
    assert(fad3(Point(numlim_t::infinity(), numlim_t::infinity())) == numlim_t::infinity() + test_surface_1(Point(numlim_t::infinity(), numlim_t::infinity())));
  }
  if (numlim_t::has_quiet_NaN) {
    assert(std::isnan(fad1(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fad1(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fad1(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
    auto fad4 = add(test_surface_1, numlim_t::quiet_NaN());
    assert(std::isnan(fad4(Point(1.0, 0.0))));
    assert(std::isnan(fad4(Point(-1.0, 0.0))));
    assert(std::isnan(fad4(Point(1.0, -1.0))));
    assert(std::isnan(fad4(Point(numlim_t::quiet_NaN(), 0.0))));
    assert(std::isnan(fad4(Point(0.0, numlim_t::quiet_NaN()))));
    assert(std::isnan(fad4(Point(numlim_t::quiet_NaN(), numlim_t::quiet_NaN()))));
  }
#endif // 407

// Seria testów, które nie powinny się kompilować.
#if TEST_NUM == 408
  [[maybe_unused]] auto f = invert();
#endif

#if TEST_NUM == 409
  [[maybe_unused]] auto f = invert(1.0);
#endif

#if TEST_NUM == 410
  [[maybe_unused]] auto f = invert(Point(1.0, 1.0));
#endif

#if TEST_NUM == 411
  [[maybe_unused]] auto f = invert(1.0, 1.0);
#endif

#if TEST_NUM == 412
  [[maybe_unused]] auto f = flip();
#endif

#if TEST_NUM == 413
  [[maybe_unused]] auto f = flip(1.0);
#endif

#if TEST_NUM == 414
  [[maybe_unused]] auto f = flip(Point(1.0, 1.0));
#endif

#if TEST_NUM == 415
  [[maybe_unused]] auto f = flip(1.0, 1.0);
#endif

#if TEST_NUM == 416
  [[maybe_unused]] auto f = mul();
#endif

#if TEST_NUM == 417
  [[maybe_unused]] auto f = mul(1.0);
#endif

#if TEST_NUM == 418
  [[maybe_unused]] auto f = mul(Point(1.0, 1.0));
#endif

#if TEST_NUM == 419
  [[maybe_unused]] auto f = mul(1.0, 1.0);
#endif

#if TEST_NUM == 420
  [[maybe_unused]] auto f = mul(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 421
  [[maybe_unused]] auto f = mul(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 422
  [[maybe_unused]] auto f = add();
#endif

#if TEST_NUM == 423
  [[maybe_unused]] auto f = add(1.0);
#endif

#if TEST_NUM == 424
  [[maybe_unused]] auto f = add(Point(1.0, 1.0));
#endif

#if TEST_NUM == 425
  [[maybe_unused]] auto f = add(1.0, 1.0);
#endif

#if TEST_NUM == 426
  [[maybe_unused]] auto f = add(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 427
  [[maybe_unused]] auto f = add(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 428
  [[maybe_unused]] auto f = rotate();
#endif

#if TEST_NUM == 429
  [[maybe_unused]] auto f = rotate(1.0);
#endif

#if TEST_NUM == 430
  [[maybe_unused]] auto f = rotate(Point(1.0, 1.0));
#endif

#if TEST_NUM == 431
  [[maybe_unused]] auto f = rotate(1.0, 1.0);
#endif

#if TEST_NUM == 432
  [[maybe_unused]] auto f = rotate(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 433
  [[maybe_unused]] auto f = rotate(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 434
  [[maybe_unused]] auto f = translate();
#endif

#if TEST_NUM == 435
  [[maybe_unused]] auto f = translate(1.0);
#endif

#if TEST_NUM == 436
  [[maybe_unused]] auto f = translate(Point(1.0, 1.0));
#endif

#if TEST_NUM == 437
  [[maybe_unused]] auto f = translate(1.0, 1.0);
#endif

#if TEST_NUM == 438
  [[maybe_unused]] auto f = translate(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 439
  [[maybe_unused]] auto f = translate(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 440
  [[maybe_unused]] auto f = translate(Point(1.0, 1.0), Point(1.0, 1.0));
#endif

#if TEST_NUM == 441
  [[maybe_unused]] auto f = translate(1.0, 1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 442
  [[maybe_unused]] auto f = translate(1.0, 1.0, Point(1.0, 1.0));
#endif

#if TEST_NUM == 443
  [[maybe_unused]] auto f = scale();
#endif

#if TEST_NUM == 444
  [[maybe_unused]] auto f = scale(1.0);
#endif

#if TEST_NUM == 445
  [[maybe_unused]] auto f = scale(Point(1.0, 1.0));
#endif

#if TEST_NUM == 446
  [[maybe_unused]] auto f = scale(1.0, 1.0);
#endif

#if TEST_NUM == 447
  [[maybe_unused]] auto f = scale(Point(1.0, 1.0), 1.0);
#endif

#if TEST_NUM == 448
  [[maybe_unused]] auto f = scale(1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 449
  [[maybe_unused]] auto f = scale(Point(1.0, 1.0), Point(1.0, 1.0));
#endif

#if TEST_NUM == 450
  [[maybe_unused]] auto f = scale(1.0, 1.0, 1.0, 1.0);
#endif

#if TEST_NUM == 451
  [[maybe_unused]] auto f = scale(1.0, 1.0, Point(1.0, 1.0));
#endif

#if TEST_NUM == 501
  // NOTE: Akceptujemy rozwiązania, w których wynik evaluate jest ustalony jako Surface.
  auto const h0 = []() {return 1.0;};
  assert(is_eq_prec(evaluate(h0)(Point(1.0, 1.0)), 1.0, 0.0));
  assert(is_eq_prec(evaluate(h0)(Point(BIG_VAL, 1.0)), 1.0, 0.0));

  auto const f1 = [](Point const p) {return 1.5 * p.x + 2.0 * p.y;};
  auto const h1 = [](Real x) {return x + 1.0;};
  assert(is_eq_prec(evaluate(h1, f1)(Point(2.0, 1.0)), 6.0, 0.0));
  assert(is_eq_prec(evaluate(h1, f1)(Point(2.0, BIG_VAL)), 2.0 * BIG_VAL + 4.0, 0.0));

  auto const f2 = [](Point const p) {return 2.0 * p.x + 0.5 * p.y;};
  auto const h2 = [](Real x1, Real x2) {return x1 + x2;};
  assert(is_eq_prec(evaluate(h2, f1, f2)(Point(2.0, -2.0)), 2.0, 0.0));
  assert(is_eq_prec(evaluate(h2, f1, f2)(Point(0.0, -BIG_VAL / 2.5)), -BIG_VAL, 0.0));

  auto const hs = [] <typename... Ts> (Ts... ts) {return (... + ts);};
  auto const f0 = [](Point const) {return 1.0;};
  assert(is_eq_prec(evaluate(hs, f0, f0, f0)(Point(1.0, -1.0)), 3.0, 0.0));
  assert(is_eq_prec(evaluate(hs, f1, f0, f0, f0, f2)(Point(2.0, 2.0)), 15.0, 0.0));
  assert(is_eq_prec(evaluate(hs,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0,
    f0, f0, f0, f0, f0, f0, f0, f0, f0, f0)(Point(0.0, 0.0)), 100.0, 0.0));
#endif // 501

#if TEST_NUM == 502
  assert(evaluate([](){return 1.5;})(Point(-1.0, 2.0)) == 1.5);
  assert(evaluate([](){return true;})(Point(-1.0, 2.0)) == true);

  Real val = 0.0;
  for (size_t k = 0; k <= 1000; ++k) {
    assert(evaluate([&val](){return val;})(Point(1.0, -1.0)) == val);
    val += 0.125;
  }
#endif // 502

#if TEST_NUM == 503
  auto const p = compose()(Point(1.0, 3.0));
  assert(p.x == 1.0 && p.y == 3.0);
  auto const f1 = [](Point const p) {return p.x - p.y;};
  assert(is_eq_prec(compose(f1)(Point(1.0, 3.0)), -2.0, 0.0));
  assert(is_eq_prec(compose(f1)(Point(0.0, BIG_VAL)), -BIG_VAL, 0.0));
  auto const f2 = [](Real const x) {return x * x;};
  assert(is_eq_prec(compose(f1, f2)(Point(1.0, 3.0)), 4.0, 0.0));
  auto const f3 = [](Real const x) {return x + 0.125;};
  assert(is_eq_prec(compose(f1, f3)(Point(0.0, BIG_VAL)), -BIG_VAL + 0.125, 0.0));
  assert(is_eq_prec(compose(f1, f2, f3)(Point(1.0, 3.0)), 4.125, 0.0));
  auto const f4 = [](Real const x) {return std::ceil(x);};
  assert(is_eq_prec(compose(f1, f2, f3, f4)(Point(1.0, 3.0)), 5.0, 0.0));
  auto const f5 = [](Real const x) {return std::cos(x);};
  assert(is_eq_prec(compose(f1, f2, f3, f4, f5)(Point(1.0, 3.0)), std::cos(5.0), 0.0));
  assert(is_eq_prec(compose(f1,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3,
    f3, f3, f3, f3, f3, f3, f3, f3, f3, f3)(Point(4.0, 3.0)), 13.5, 0.0));

  Real const arg = 0.25;
  Real const c = 4.0;
  auto const id = [](auto x) {return x;};
  auto const linear = [&c](auto x) {return x + c;};
  auto const quadratic = [&c](auto x) {return x * x + c;};
  auto const cubic = [&c](auto x) {return x * x * x + x * x + x + c;};

  assert(is_eq_prec(compose()(arg), arg, 0.0));
  assert(is_eq_prec(compose(id)(arg), id(arg), 0.0));
  assert(is_eq_prec(compose(linear)(arg), linear(arg), 0.0));
  assert(is_eq_prec(compose(quadratic)(arg), quadratic(arg), 0.0));
  assert(is_eq_prec(compose(cubic)(arg), cubic(arg), 0.0));
  assert(is_eq_prec(compose(id, linear)(arg), linear(id(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(linear, quadratic)(arg), quadratic(linear(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(quadratic, cubic)(arg), cubic(quadratic(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(linear, id)(arg), id(linear(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(quadratic, linear)(arg), linear(quadratic(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(cubic, quadratic)(arg), quadratic(cubic(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(linear, linear)(arg), linear(linear(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(quadratic, quadratic)(arg), quadratic(quadratic(arg)), DEF_PRECISION));
  assert(is_eq_prec(compose(cubic, cubic)(arg), cubic(cubic(arg)), DEF_PRECISION));

  assert(is_eq_prec(compose(id, linear, quadratic)(arg), quadratic(linear(id(arg))), DEF_PRECISION));
  assert(is_eq_prec(compose(id, linear, quadratic, cubic)(arg), cubic(quadratic(linear(id(arg)))), DEF_PRECISION));
  assert(is_eq_prec(compose(id, linear, quadratic, cubic, id)(arg), id(cubic(quadratic(linear(id(arg))))), DEF_PRECISION));
  assert(is_eq_prec(compose(id, linear, quadratic, cubic, id, linear)(arg), linear(id(cubic(quadratic(linear(id(arg)))))), DEF_PRECISION));
  assert(is_eq_prec(compose(id, linear, quadratic, cubic, id, linear, quadratic)(arg), quadratic(linear(id(cubic(quadratic(linear(id(arg))))))), DEF_PRECISION));
  assert(is_eq_prec(compose(id, linear, quadratic, cubic, id, linear, quadratic, cubic)(arg), cubic(quadratic(linear(id(cubic(quadratic(linear(id(arg)))))))), DEF_PRECISION));
  assert(is_eq_prec(compose(
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id,
      id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id, id)(arg),
    arg, DEF_PRECISION));
#endif // 503

#if TEST_NUM == 504
  // Wywołanie evaluate bez parametrwów nie powinno się kompilwoać.
  evaluate();
#endif

#if TEST_NUM == 505
  // To też nie powinno się kompilować.
  evaluate([](Point const p){return p.x * p.y;});
#endif
}
