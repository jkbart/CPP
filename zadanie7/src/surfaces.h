#ifndef SURFACES_H
#define SURFACES_H

#include "real.h"
#include <cmath>
#include <functional>
#include <numbers>
#include <ostream>

class Point {
public:
  const Real x, y;

  Point(Real _x, Real _y) noexcept : x{_x}, y{_y} {}

  friend std::ostream &operator<<(std::ostream &os,
                                  const Point &point) noexcept {
    return os << point.x << " " << point.y;
  }
};

using Surface = std::function<Real(const Point)>;

// Generuje płaszczyznę f(x, y) = 0.
inline Surface plain() {
  return [](const Point) { return Real{0}; };
}

// Generuje powierzchnię f(x, y) = x.
inline Surface slope() {
  return [](const Point p) { return p.x; };
}

// Generuje powierzchnię schodkową wzdłuż osi X o szerokości schodka s
// (domyślnie 1) i wysokości schodka 1. Dla 0 <= x < s mamy f(x, y) = 0,
// dla -s <= x < 0 mamy f(x, y) = -1 itd. Jeśli s <= 0, to f(x, y) = 0.
inline Surface steps(const Real s = Real{1}) {
  return [=](const Point p) {
    return s <= Real{0} ? Real{0} : std::floor(p.x / s);
  };
}

// Generuje powierzchnię, która jest szachownicą o szerokości kratki s
// (domyślnie 1). Dla 0 <= x < s mamy f(x, y) = 1, gdy 0 <= y < s
// oraz f(x, y) = 0, gdy s <= y < 2 * s itd. Jeśli s <= 0, to f(x, y) = 0.
inline Surface checker(const Real s = Real{1}) {
  return [=](const Point p) {
    return s <= Real{0} ||
                   (Real{0} <
                    std::fmod(std::fabs(std::floor(p.x / s)), Real{2})) ^
                       (Real{0} <
                        std::fmod(std::fabs(std::floor(p.y / s)), Real{2}))
               ? Real{0}
               : Real{1};
  };
}

// Generuje powierzchnię f(x, y) = x * x.
inline Surface sqr() {
  return [](const Point p) { return p.x * p.x; };
}

// Generuje powierzchnię sinusoidalną względem argumentu x.
inline Surface sin_wave() {
  return [](const Point p) { return std::sin(p.x); };
}

// Generuje powierzchnię kosinusoidalną względem argumentu x.
inline Surface cos_wave() {
  return [](const Point p) { return std::cos(p.x); };
}

// Generuje powierzchnię z koncentrycznymi naprzemiennymi pasami szerokości s
// (domyślnie 1) o środku w punkcie (0, 0), gdzie f(x, y) = 1 w najbardziej
// wewnętrznym okręgu (łącznie z tym okręgiem). Jeśli s <= 0, to f(x, y) = 0.
inline Surface rings(const Real s = Real{1}) {
  return [=](const Point p) {
    return !(s <= Real{0}) &&
                   (Real{0} <
                        std::fmod(
                            std::ceil(std::sqrt(p.x * p.x + p.y * p.y) / s),
                            Real{2}) ||
                    (p.x == Real{0} && p.y == Real{0}))
               ? Real{1}
               : Real{0};
  };
}

// Generuje powierzchnię z elipsą o środku w punkcie (0, 0) o półosi długości
// a wzdłuż osi X (domyślnie 1) i o półosi długości b wzdłuż osi Y
// (domyślnie 1). Zachodzi f(x, y) = 1, gdy (x, y) leży wewnątrz lub na brzegu
// elipsy, zaś f(x, y) = 0, w. p.p. Jeśli a <= 0 lub b <= 0, to f(x, y) = 0.
inline Surface ellipse(const Real a = Real{1}, const Real b = Real{1}) {
  return [=](const Point p) {
    return !(a <= Real{0}) && !(b <= Real{0}) &&
                   (p.x * p.x) / (a * a) + (p.y * p.y) / (b * b) <= Real{1}
               ? Real{1}
               : Real{0};
  };
}

// Generuje powierzchnię z prostokątem o środku w punkcie (0, 0) o brzegu
// długości 2a wzdłuż X (domyślnie a = 1) i o brzegu długości 2b wzdłuż osi Y
// (domyślnie b = 1), czyli f(x, y) = 1, gdy (x, y) leży wewnątrz lub na brzegu
// prostokąta, zaś f(x, y) = 0, w. p.p. Jeśli a <= 0 lub b <= 0, to f(x, y) = 0.
inline Surface rectangle(const Real a = Real{1}, const Real b = Real{1}) {
  return [=](const Point p) {
    return !(a <= Real{0}) && !(b <= Real{0}) && std::fabs(p.x) <= a &&
                   std::fabs(p.y) <= b
               ? Real{1}
               : Real{0};
  };
}

// Generuje powierzchnię z paskami o szerokości s, ułożonymi wzdłuż osi X,
// równoległymi do osi Y. Zachodzi f(x, y) = 1, gdy 0 < x <= s oraz f(x, y) = 0,
// gdy -s < x <= 0 itd. Jeśli s <= 0, to f(x, y) = 0.
inline Surface stripes(const Real s) {
  return [=](const Point p) {
    return s <= Real{0} || std::fmod(std::ceil(p.x / s), Real{2}) == Real{0}
               ? Real{0}
               : Real{1};
  };
}

// Obraca dziedzinę powierzchni o kąt wyrażony w stopniach.
inline Surface rotate(const Surface f, const Real deg) {
  return [=](const Point p) {
    return std::invoke(
        f, Point{
               p.x * std::cos(-deg * std::numbers::pi / Real{180}) -
                   p.y * std::sin(-deg * std::numbers::pi / Real{180}),
               p.x * std::sin(-deg * std::numbers::pi / Real{180}) +
                   p.y * std::cos(-deg * std::numbers::pi / Real{180}),
           });
  };
}

// Przesuwa dziedzinę powierzchni o wektor v (typu Point).
inline Surface translate(const Surface f, const Point v) {
  return [=](const Point p) {
    return std::invoke(f, Point{p.x - v.x, p.y - v.y});
  };
}

// Skaluje dziedzinę powierzchni parą współczynników s (typu Point).
inline Surface scale(const Surface f, const Point s) {
  return [=](const Point p) {
    return std::invoke(f, Point{p.x / s.x, p.y / s.y});
  };
}

// Odwraca dziedzinę powierzchni, tzn. zamienia (x, y) na (y, x).
inline Surface invert(const Surface f) {
  return [=](const Point p) { return std::invoke(f, Point{p.y, p.x}); };
}

// Odbija dziedzinę powierzchni względem osi Y, tzn. zamienia x na -x.
inline Surface flip(const Surface f) {
  return [=](const Point p) { return std::invoke(f, Point{-p.x, p.y}); };
}

// Mnoży wartości podanej powierzchni f przez podaną wartość c.
inline Surface mul(const Surface f, const Real c) {
  return [=](const Point p) { return std::invoke(f, p) * c; };
}

// Dodaje podaną wartość c do wartości podanej powierzchni f.
inline Surface add(const Surface f, const Real c) {
  return [=](const Point p) { return std::invoke(f, p) + c; };
}

// Oblicza wartość funkcji h(f1(p), ..., fs(p)).
template <class H, class... Fs> inline auto evaluate(H h, Fs... fs) {
  return [=]([[maybe_unused]] Point p) {
    return std::invoke(h, std::invoke(fs, p)...);
  };
}

// Generuje złożenie funkcji fs(...(f2(f1))...).
inline auto compose() {
  return [](auto &&arg) { return std::forward<decltype(arg)>(arg); };
}

template <class F, class... Fs> inline auto compose(F f, Fs... fs) {
  return [=](auto &&...args) {
    return compose(fs...)(
                       std::invoke(f, std::forward<decltype(args)>(args))...);
  };
}

#endif /* SURFACES_H */