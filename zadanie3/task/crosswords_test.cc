/*
 * File:        crosswords_tests.cc
 * Created on:  13/11/2023
 * Author:      Przemysław Rutka
 */

 /* Tests description
 * Group 1 - crosswords_example.cc, stream operator and word collisions
 *           (produce outputs that need to be verified)
 *
 * Group 2 - class constructors and usage with const correctness,
 *           assignments, arithmetics
 *
 * Group 3 - comparisons of words, const correctness of comparison operators
 *
 * Group 4 - forum questions
 *
 * Group 5 - redefinitions, expected assertions, enum type verification,
 *           constants
 *
 * Group 6 - non-compiling codes
 */

#ifdef NDEBUG
  #undef NDEBUG
#endif

/**
 * Includes section
 **/

#include "crosswords.h"

#if TEST_NUM == 101 || (TEST_NUM >= 201 && TEST_NUM <= 203) \
    || (TEST_NUM >= 302 && TEST_NUM <= 305) \
    || (TEST_NUM >= 401 && TEST_NUM <= 404) \
    || (TEST_NUM >= 506 && TEST_NUM <= 509)
#include <cassert>
#endif

#if TEST_NUM == 101
#include <utility>
#endif

#if TEST_NUM >= 101 && TEST_NUM <= 104
#include <iostream>
#endif

#if TEST_NUM == 102 || (TEST_NUM >= 201 && TEST_NUM <= 203) || TEST_NUM == 401 \
    || TEST_NUM == 403 || (TEST_NUM >= 502 && TEST_NUM <= 504)
#include <limits>
#endif

#if TEST_NUM == 105
#include <fstream>
#endif

#if TEST_NUM == 201
#include <cctype>
#endif

#if TEST_NUM >= 301 && TEST_NUM <= 305
#include <compare>
#endif

#if TEST_NUM == 201 || (TEST_NUM >= 302 && TEST_NUM <= 304) || TEST_NUM == 401
#include <string>
#endif

#if (TEST_NUM >= 201 && TEST_NUM <= 203) || TEST_NUM == 301 \
    || (TEST_NUM >= 505 && TEST_NUM <= 510)
#include <type_traits>
#endif

#if (TEST_NUM >= 201 && TEST_NUM <= 203) || TEST_NUM == 510
#include <utility>
#endif

/**
 * Macros section
 **/

#if TEST_NUM == 101 || TEST_NUM == 201 || TEST_NUM == 401
#define WORD_BASIC_ASSERTS(w, sp, ep, o, ci, c, l) \
do { \
    assert(w.get_start_position() == sp); \
    assert(w.get_end_position() == ep); \
    assert(w.get_orientation() == o); \
    assert(w.at(ci) == c); \
    assert(w.length() == l); \
} while (0)
#endif /* 101, 201, 401 */

#if TEST_NUM == 101 || TEST_NUM == 201 || TEST_NUM == 202 || TEST_NUM == 401 \
    || TEST_NUM == 403
#define RECT_AREA_BASE_ASSERTS(ra, lt, rb, s, e) \
do { \
    assert(ra.get_left_top() == lt); \
    assert(ra.get_right_bottom() == rb); \
    assert(ra.size() == s); \
    assert(ra.empty() == e); \
} while(0)
#endif /* 101, 201, 202, 401, 403 */

#if TEST_NUM == 101 || TEST_NUM == 201 || TEST_NUM == 203 || TEST_NUM == 404
#define CROSSWORD_DIM_ASSERTS(cr, sz, cnt) \
do { \
    assert(cr.size() == sz); \
    assert(cr.word_count() == cnt); \
} while(0)
#endif /* 101, 201, 203, 404 */

#if TEST_NUM == 105
#define FILENAME "gen_test_105.out"
#endif

#if TEST_NUM == 201
#define WORD_TEXT_ASSERTS(w, s) \
do { \
    for (size_t k = 1; k < s.length(); ++k) { \
        if (isalpha(w.at(k))) \
            assert(w.at(k) == s[k] || w.at(k) == toupper(s[k])); \
        else \
            assert(w.at(k) == s[k] || w.at(k) == '?'); \
    } \
} while(0)

#define WORD_RECT_AREA_ASSERTS(w, ra, s) \
do { \
    assert(ra.get_left_top() == w.get_start_position()); \
    assert(ra.get_right_bottom() == w.get_end_position()); \
    assert(ra.size() == s); \
    assert(ra.empty() == false); \
} while(0)

#define COPY_MOVE_ONELETTER_WORD_ASSERTS(w, p, o, c) \
do { \
    WORD_BASIC_ASSERTS(w, p, p, o, 0, c, 1); \
    WORD_RECT_AREA_ASSERTS(w, w.rect_area(), dim_t(1, 1)); \
} while(0)
#endif /* 201 */

#if TEST_NUM == 302 || TEST_NUM == 303 || TEST_NUM == 305
#define WORD_COMPARISONS_ASSERTS(w1, w2) \
do { \
    assert(w1 < w2); \
    assert(w1 <= w2); \
    assert(w2 > w1); \
    assert(w2 >= w1); \
    assert(w1 != w2); \
    assert(w2 != w1); \
    assert(!(w1 == w2)); \
    assert(!(w2 == w1)); \
    assert(w1 <=> w2 < 0); \
    assert(w2 <=> w1 > 0); \
    assert(is_lt(w1 <=> w2)); \
    assert(is_lteq(w1 <=> w2)); \
    assert(is_gt(w2 <=> w1)); \
    assert(is_gteq(w2 <=> w1)); \
    assert(is_neq(w1 <=> w2)); \
    assert(is_neq(w2 <=> w1)); \
    assert(!is_eq(w1 <=> w2)); \
    assert(!is_eq(w2 <=> w1)); \
} while(0)
#endif /* 302, 303, 305 */

#if TEST_NUM == 304 || TEST_NUM == 305
#define WORD_EQUALITY_ASSERTS(w1, w2) \
do { \
    assert(w1 == w2); \
    assert(w2 == w1); \
    assert(w1 <= w2); \
    assert(w2 <= w1); \
    assert(w1 >= w2); \
    assert(w2 >= w1); \
    assert(!(w1 < w2)); \
    assert(!(w2 < w1)); \
    assert(!(w1 > w2)); \
    assert(!(w2 > w1)); \
    assert(!(w1 != w2)); \
    assert(!(w2 != w1)); \
    assert(w1 <=> w2 == 0); \
    assert(w2 <=> w1 == 0); \
    assert(!is_lt(w1 <=> w2)); \
    assert(!is_lt(w2 <=> w1)); \
    assert(is_lteq(w1 <=> w2)); \
    assert(is_lteq(w2 <=> w1)); \
    assert(!is_gt(w1 <=> w2)); \
    assert(!is_gt(w2 <=> w1)); \
    assert(is_gteq(w1 <=> w2)); \
    assert(is_gteq(w2 <=> w1)); \
    assert(!is_neq(w1 <=> w2)); \
    assert(!is_neq(w2 <=> w1)); \
    assert(is_eq(w1 <=> w2)); \
    assert(is_eq(w2 <=> w1)); \
} while(0)
#endif /* 304, 305 */

#if TEST_NUM == 401
#define WORD_TRIMMING_TEST(w, sp, ep, o, c0, c1, c2, l, s, e) \
do { \
    WORD_BASIC_ASSERTS(w, sp, ep, o, 0, c0, l); \
    WORD_BASIC_ASSERTS(w, sp, ep, o, 1, c1, l); \
    WORD_BASIC_ASSERTS(w, sp, ep, o, 2, c2, l); \
    RECT_AREA_BASE_ASSERTS(w.rect_area(), sp, ep, s, e); \
} while(0)
#endif /* 401 */

#if TEST_NUM == 202 || TEST_NUM == 402 || TEST_NUM == 403
#define RECT_AREA_SIZE_ASSERTS(ra, s, e) \
do { \
    assert(ra.size() == s); \
    assert(ra.empty() == e); \
} while(0)
#endif /* 202, 402, 403 */

#if TEST_NUM == 403
#define EMPTY_EMBRACE_ASSERTS(ra, p) \
do { \
    RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true); \
    ra.embrace(p); \
    RECT_AREA_BASE_ASSERTS(ra, p, p, dim_t(1, 1), false); \
} while (0)

#define EMPTY_EMBRACE_TEST(ra, ori, p1, p2) \
do { \
    ra = ori; \
    EMPTY_EMBRACE_ASSERTS(ra, p1); \
    ra = ori; \
    EMPTY_EMBRACE_ASSERTS(ra, p2); \
    ra = ori; \
    EMPTY_EMBRACE_ASSERTS(ra, pos_t(0, 0)); \
    ra = ori; \
    EMPTY_EMBRACE_ASSERTS(ra, pos_t(slim_t::max(), 0)); \
    ra = ori; \
    EMPTY_EMBRACE_ASSERTS(ra, pos_t(0, slim_t::max())); \
    ra = ori; \
    EMPTY_EMBRACE_ASSERTS(ra, pos_t(slim_t::max(), slim_t::max())); \
} while(0)
#endif /* 403 */

/**
 * Anonymous namespace section
 **/

namespace {

#if (TEST_NUM >= 101 && TEST_NUM <= 105) || TEST_NUM == 201 || TEST_NUM == 203 \
    || (TEST_NUM >= 301 && TEST_NUM <= 305) || TEST_NUM == 401 \
    || TEST_NUM == 404 || TEST_NUM == 601 || TEST_NUM == 612 \
    || (TEST_NUM >= 603 && TEST_NUM <= 604) || TEST_NUM == 613 \
    || (TEST_NUM >= 620 && TEST_NUM <= 623)
    using orientation_t::H;
    using orientation_t::V;
#endif

#if TEST_NUM >= 101 && TEST_NUM <= 104
    using std::cout;
#endif

#if TEST_NUM == 102 || TEST_NUM == 105
    using std::endl;
#endif

#if TEST_NUM == 102 || (TEST_NUM >= 201 && TEST_NUM <= 203) || TEST_NUM == 401 \
    || TEST_NUM == 403 || (TEST_NUM >= 502 && TEST_NUM <= 504)
    using slim_t = std::numeric_limits<size_t>;
#endif

#if TEST_NUM == 201 || (TEST_NUM >= 302 && TEST_NUM <= 304) || TEST_NUM == 401
    using std::string;
#endif

#if TEST_NUM == 105
    using std::ofstream;
#endif

#if TEST_NUM == 201
    using std::toupper, std::isalpha;
#endif

#if TEST_NUM >= 201 && TEST_NUM <= 203
    using std::is_class_v;
#endif

#if (TEST_NUM >= 201 && TEST_NUM <= 203) || TEST_NUM == 613 || TEST_NUM == 615 \
    || TEST_NUM == 621
    using std::move;
#endif

#if TEST_NUM >= 201 && TEST_NUM <= 203
    using std::is_copy_assignable_v, std::is_move_assignable_v;
    using std::is_copy_constructible_v, std::is_move_constructible_v;
#endif

#if TEST_NUM == 301
    using std::is_convertible_v, std::weak_ordering;
#endif

#if TEST_NUM >= 302 && TEST_NUM <= 305
    using std::is_eq, std::is_neq, std::is_lt, std::is_lteq;
    using std::is_gt, std::is_gteq;
#endif

#if TEST_NUM == 505
    using std::underlying_type_t;
#endif

#if TEST_NUM == 505 || TEST_NUM == 509 || TEST_NUM == 510
    using std::is_same_v;
#endif

#if TEST_NUM >= 506 && TEST_NUM <= 508
    using std::is_const_v;
#endif

#if TEST_NUM == 510
    using std::pair;
#endif

#if TEST_NUM == 101
    void example_word_tests() {
        Word w1(1, 1, H, "COMPUTER");
        Word w2(3, 1, V, "MEMORY");
        Word w3(1, 5, V, "");

        WORD_BASIC_ASSERTS(w1, pos_t(1, 1), pos_t(8, 1), H, 0, 'C', 8);
        WORD_BASIC_ASSERTS(w2, pos_t(3, 1), pos_t(3, 6), V, 6, DEFAULT_CHAR, 6);
        WORD_BASIC_ASSERTS(w3, pos_t(1, 5), pos_t(1, 5), V, 0,
                           DEFAULT_CHAR, DEFAULT_WORD.length());

        assert(w1 < w3);
        assert(w1 <= w3);
        assert(w2 > w1);
        assert(w2 >= w1);
        assert(w1 != w2);
        assert(w2 > Word(3, 1, H, "MEMORY"));
        assert(w2 == Word(3, 1, V, "MNEMONIC"));
    }

    void example_rect_area_tests() {
        RectArea ra1(pos_t(1, 2), pos_t(10, 7));
        RECT_AREA_BASE_ASSERTS(ra1, pos_t(1, 2), pos_t(10, 7), dim_t(10, 6), false);
        ra1.set_left_top(pos_t(2, 3));
        RECT_AREA_BASE_ASSERTS(ra1, pos_t(2, 3), pos_t(10, 7), dim_t(9, 5), false);
        ra1.set_right_bottom(pos_t(9, 7));
        RECT_AREA_BASE_ASSERTS(ra1, pos_t(2, 3), pos_t(9, 7), dim_t(8, 5), false);

        RectArea ra2(pos_t(10, 7), pos_t(1, 2));
        RECT_AREA_BASE_ASSERTS(ra2, pos_t(10, 7), pos_t(1, 2), dim_t(0, 0), true);

        RectArea ra3(pos_t(1, 2), pos_t(10, 7));
        ra3 *= RectArea(pos_t(4, 5), pos_t(15, 10));
        RECT_AREA_BASE_ASSERTS(ra3, pos_t(4, 5), pos_t(10, 7), dim_t(7, 3), false);

        RectArea ra4 = ra3 * RectArea(pos_t(15, 10), pos_t(15, 11));
        assert(ra4.size() == dim_t(0, 0));
        assert(ra4.empty());

        RectArea ra5(pos_t(2, 3), pos_t(10, 7));
        ra5.embrace(pos_t(4, 5));
        RECT_AREA_BASE_ASSERTS(ra5, pos_t(2, 3), pos_t(10, 7), dim_t(9, 5), false);
        ra5.embrace(pos_t(1, 2));
        RECT_AREA_BASE_ASSERTS(ra5, pos_t(1, 2), pos_t(10, 7), dim_t(10, 6), false);

        assert(DEFAULT_EMPTY_RECT_AREA.size() == dim_t(0, 0));
        assert(DEFAULT_EMPTY_RECT_AREA.empty());

        Word w1(1, 1, V, "COMPUTER");
        RECT_AREA_BASE_ASSERTS(w1.rect_area(), pos_t(1, 1), pos_t(1, 8),
                               dim_t(1, 8), false);
    }

    void example_crossword_tests() {
        Word w1(1, 1, H, "computer");
        Word w2(3, 1, V, "memory");
        Crossword cr1(w1, {w2});
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(8, 6), dim_t(1, 1));
        assert(cr1.insert_word(Word(11, 3, V, "LINUX")));
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(11, 7), dim_t(1, 2));
        assert(!cr1.insert_word(Word(2, 4, H, "programme")));
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(11, 7), dim_t(1, 2));
        assert(!cr1.insert_word(Word(2, 5, H, "programme")));
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(11, 7), dim_t(1, 2));
        assert(cr1.insert_word(Word(2, 5, H, "programming")));
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(12, 7), dim_t(2, 2));
        cout << cr1 << '\n';

        Crossword cr2(Word(10, 7, H, "EXECUTION"), {});
        CROSSWORD_DIM_ASSERTS(cr2, dim_t(9, 1), dim_t(1, 0));
        assert(cr2.insert_word(Word(10, 3, V, "PARSER")));
        CROSSWORD_DIM_ASSERTS(cr2, dim_t(9, 6), dim_t(1, 1));
        assert(cr2.insert_word(Word(13, 7, V, "Code")));
        CROSSWORD_DIM_ASSERTS(cr2, dim_t(9, 8), dim_t(1, 2));
        CROSSWORD_BACKGROUND = '~';
        cout << cr2 << '\n';

        Crossword cr3 = cr1 + cr2;
        CROSSWORD_DIM_ASSERTS(cr3, dim_t(18, 10), dim_t(3, 3));
        CROSSWORD_BACKGROUND = '=';
        cout << cr3 << '\n';
        cr1 += cr2;
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(18, 10), dim_t(3, 3));
        CROSSWORD_BACKGROUND = '.';
        cout << cr1 << '\n';

        Crossword cr4(Word(2, 5, V, "C++20"), {Word(0, 8, H, "C17")});
        cout << cr4;
    }
#endif /* 101 */

#if TEST_NUM == 102
    void stream_operator_tests() {
        // Variable and constant crosswords, various backgrounds,
        // various orders of sending to a stream
        Crossword cr1(Word(0, 0, V, "PROGRAMME"), {});
        Crossword const cr2(Word(0, 0, H, "PROGRAMME"), {});
        cout << cr1 << '\n';
        cout << cr2 << '\n';
        CROSSWORD_BACKGROUND = '*';
        cout << cr1 << '\n';
        cout << cr2 << '\n';
        CROSSWORD_BACKGROUND = ' ';
        cout << cr1 << '\n' << cr2 << endl;
        cout << cr2 << '\n' << cr1 << endl;
        CROSSWORD_BACKGROUND = '#';
        cout << cr2 << endl << cr2 << '\n' << cr1 << endl;
        cout << cr1 << endl << cr1 << '\n' << cr2 << endl;

        // Big coordinates
        size_t const billion = 1000000000;
        CROSSWORD_BACKGROUND = '+';
        cout << Crossword(Word(3 * billion, 6 * billion, H, "X"), {
                    Word(3 * billion + 5, 6 * billion, V, "Y"),
                    Word(3 * billion, 6 * billion + 3, V, "Z"),
                    Word(3 * billion + 5, 6 * billion + 3, H, "W")
                })
             << '\n'
             << Crossword(Word(slim_t::max(), slim_t::max() - 5, V, "OBJECT"), {
                    Word(slim_t::max() - 5, slim_t::max(), H, "ASSERT")
                })
             << endl;

        // One-letter words in various positions
        CROSSWORD_BACKGROUND = '.';
        cout << Crossword(Word(0, 0, H, "A"), {}) << endl;
        cout << Crossword(Word(0, 0, V, "A"), {}) << endl;
        cout << Crossword(Word(3, 7, H, "B"), {}) << endl;
        cout << Crossword(Word(3, 7, V, "B"), {}) << endl;
        cout << Crossword(Word(billion, 0, H, "C"), {}) << endl;
        cout << Crossword(Word(billion, 0, V, "C"), {}) << endl;
        cout << Crossword(Word(0, billion, H, "D"), {}) << endl;
        cout << Crossword(Word(0, billion, V, "D"), {}) << endl;
        cout << Crossword(Word(billion, billion, H, "E"), {}) << endl;
        cout << Crossword(Word(billion, billion, V, "E"), {}) << endl;
        cout << Crossword(Word(slim_t::max(), 0, H, "F"), {}) << endl;
        cout << Crossword(Word(slim_t::max(), 0, V, "F"), {}) << endl;
        cout << Crossword(Word(0, slim_t::max(), H, "G"), {}) << endl;
        cout << Crossword(Word(0, slim_t::max(), V, "G"), {}) << endl;
        cout << Crossword(Word(slim_t::max(), slim_t::max(), H, "H"), {}) << endl;
        cout << Crossword(Word(slim_t::max(), slim_t::max(), V, "H"), {}) << endl;

        // Conversion to uppercase, invalid characters
        CROSSWORD_BACKGROUND = ':';
        cout << Crossword(Word(12, 57, H, "aLgOrItHm"), {})
             << Crossword(Word(34, 71, V, "aLgOrItHm"), {})
             << Crossword(Word(2, 2, H, "ABC"), {Word(3, 1, V, "abc")})
             << Crossword(Word(2, 2, H, "abc"), {Word(3, 1, V, "ABC")})
             << Crossword(Word(2, 2, H, "W3C"), {Word(3, 1, V, "w3c")})
             << Crossword(Word(2, 2, H, "W3C"), {Word(3, 1, V, "w1c")})
             << Crossword(Word(2, 2, H, "<=>"), {Word(3, 1, V, "<?>")})
             << endl;
        CROSSWORD_BACKGROUND = '*';
        cout << Crossword(Word(135, 42, H, "`1234567890-=[];'\\,./"), {
                    Word(135, 44, H, "~!@#$%^&*()_+{}:\"|<>?"),
                    Word(135, 46, H, "qwertyuiopasdfghjklzxcvbnm"),
                    Word(135, 48, H, "QWERTYUIOPASDFGHJKLZXCVBNM"),
                    Word(135, 50, H, " \t\n\r\f\a\b\v\?\'")
                }) << endl;
    }
#endif /* 102 */

#if TEST_NUM == 103
    void word_collision_tests() {
        // A few intersecions in a word
        Crossword cr1(Word(0, 0, H, "ABCD"),
            {Word(3, 0, V, "DEFG"), Word(0, 3, H, "DEFG"), Word(0, 0, V, "ABCD")}
        );
        cout << cr1 << '\n';
        Crossword cr2(Word(0, 0, H, "ABCDEFG"), {
            Word(0, 3, H, "DEFGHIJ"), Word(0, 6, H, "GHIJKLM"),
            Word(0, 0, V, "ABCDEFG"), Word(2, 0, V, "CDEFGHI"),
            Word(4, 0, V, "EFGHIJK"), Word(6, 0, V, "GHIJKLM")
        });
        cout << cr2 << '\n';

        // Some unacceptable intersections
        cout << Crossword(Word(10, 20, H, "TREE"), {Word(11, 20, V, "TREE")});
        cout << Crossword(Word(10, 20, V, "TREE"), {Word(9, 20, H, "TREE")});
        cout << Crossword(Word(10, 20, H, "TREE"), {
                    Word(10, 22, H, "TREE"), Word(10, 20, V, "TREE"),
                    Word(12, 20, V, "TREE"), Word(11, 20, V, "TREE")
                });
        cout << Crossword(Word(2, 2, H, "W3C"), {Word(3, 1, V, "WEC")});
        cout << Crossword(Word(2, 2, H, "WEC"), {Word(3, 1, V, "W3C")});
        cout << Crossword(Word(2, 2, H, "W3C"), {Word(3, 1, V, "WeC")});
        cout << Crossword(Word(2, 2, H, "WeC"), {Word(3, 1, V, "W3C")});
        cout << Crossword(Word(0, 0, V, "ABC"), {
                Word(0, 2, H, "CDE"), Word(1, 2, V, "DEF"), Word(2, 2, V, "EFG")
                });
        cout << Crossword(Word(0, 0, H, "ABC"), {
                Word(2, 0, V, "CDE"), Word(2, 1, H, "DEF"), Word(2, 2, H, "EFG")
                }) << '\n';

        // Neighborhood analysis
        for (size_t w = 8; w <= 12; ++w)
            for (size_t k = 17; k <= 23; ++k)
                cout << Crossword(Word(20, 10, H, "AB"), {Word(k, w, H, "AB")});
        cout << '\n';
        for (size_t w = 7; w <= 12; ++w)
            for (size_t k = 18; k <= 23; ++k)
                cout << Crossword(Word(20, 10, H, "AB"), {Word(k, w, V, "CD")});
        cout << '\n';
        for (size_t w = 8; w <= 13; ++w)
            for (size_t k = 17; k <= 22; ++k)
                cout << Crossword(Word(20, 10, V, "CD"), {Word(k, w, H, "AB")});
        cout << '\n';
        for (size_t w = 7; w <= 13; ++w)
            for (size_t k = 18; k <= 22; ++k)
                cout << Crossword(Word(20, 10, V, "CD"), {Word(k, w, V, "CD")});
        cout << '\n';
        cout << Crossword(Word(0, 0, H, "AB"), {
                    Word(1, 0, V, "BA"), Word(0, 0, V, "AB"), Word(0, 1, H, "BA")
                });
        cout << Crossword(Word(0, 0, H, "AB"), {
                    Word(0, 0, V, "AB"), Word(1, 0, V, "BA"), Word(0, 1, H, "BA")
                }) << '\n';
    }
#endif /* 103 */

#if TEST_NUM == 104
    void big_crossword_test() {
        // 2 * 30000 + 2 line crossword output (~6")
        size_t const cnt = 30000, cnt_h = cnt / 2;
        Word w(0, 0, H, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890");
        Crossword cr(w, {});
        for (size_t l = 1; l < cnt; ++l)
            cr.insert_word(Word(0, 2 * l, H, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890"));
        for (size_t k = 0; k < cnt_h; ++k)
            cr.insert_word(Word(0, 4 * k , V, "AAA"));
        for (size_t k = 1; k < cnt_h; ++k)
            cr.insert_word(Word(2, 4 * k - 2, V, "CCC"));
        cout << cr << '\n';
    }
#endif /* 104 */

#if TEST_NUM == 105
    void writing_to_file_test() {
        ofstream file(FILENAME);
        if (file.is_open()) {
            file << Crossword(Word(10, 10, H, "INPUT"), {
                        Word(14, 8, V, "OUTPUT"), Word(16, 10, H, "LIBRARY"),
                        Word(19, 8, V, "STREAM")
                    }) << endl;
            file.close();
        }
    }
#endif /* 105 */

#if TEST_NUM == 201
    void word_class_usage_tests() {
        static_assert(is_class_v<Word>);

        string str = "ASDFGHJKL:\"|asdfghjkl;'\\ZXCVBNM<>?zxcvbnm,./"
                     "`1234567890-=~!@#$%^&*()_+qwertyuiop[]QWERTYUIOP{}"
                     " \t\n\r\f\a\b\v\?\'";

        // Standard usage
        Word w1(0, 0, H, str.c_str());
        WORD_BASIC_ASSERTS(
            w1, pos_t(0, 0), pos_t(str.length() - 1, 0), H,
            0, str[0], str.length());
        WORD_TEXT_ASSERTS(w1, str);
        WORD_RECT_AREA_ASSERTS(w1, w1.rect_area(), dim_t(str.length(), 1));
        Word w2(1, 0, H, str.c_str());
        WORD_BASIC_ASSERTS(
            w2, pos_t(1, 0), pos_t(str.length(), 0), H, 0, str[0], str.length());
        WORD_TEXT_ASSERTS(w2, str);
        WORD_RECT_AREA_ASSERTS(w2, w2.rect_area(), dim_t(str.length(), 1));
        Word w3(0, 1, H, str.c_str());
        WORD_BASIC_ASSERTS(
            w3, pos_t(0, 1), pos_t(str.length() - 1, 1), H,
            0, str[0], str.length());
        WORD_TEXT_ASSERTS(w3, str);
        WORD_RECT_AREA_ASSERTS(w3, w3.rect_area(), dim_t(str.length(), 1));
        Word w4(0, 0, V, str.c_str());
        WORD_BASIC_ASSERTS(
            w4, pos_t(0, 0), pos_t(0, str.length() - 1), V,
            0, str[0], str.length());
        WORD_TEXT_ASSERTS(w4, str);
        WORD_RECT_AREA_ASSERTS(w4, w4.rect_area(), dim_t(1, str.length()));

        // Const correctness
        Word const cw1(100, 200, H, str.c_str());
        WORD_BASIC_ASSERTS(
            cw1, pos_t(100, 200), pos_t(100 + str.length() - 1, 200), H,
            0, str[0], str.length());
        WORD_TEXT_ASSERTS(cw1, str);
        WORD_RECT_AREA_ASSERTS(cw1, cw1.rect_area(), dim_t(str.length(), 1));

        // Close to trimming
        str = "CD";
        Word w5(slim_t::max() - 1, 0, H, str.c_str());
        WORD_BASIC_ASSERTS(w5, pos_t(slim_t::max() - 1, 0),
                           pos_t(slim_t::max(), 0), H, 0, str[0], str.length());
        WORD_TEXT_ASSERTS(w5, str);
        WORD_RECT_AREA_ASSERTS(w5, w5.rect_area(), dim_t(str.length(), 1));

        Word w6(0, slim_t::max() - 1, V, str.c_str());
        WORD_BASIC_ASSERTS(w6, pos_t(0, slim_t::max() - 1),
                           pos_t(0, slim_t::max()), V, 0, str[0], str.length());
        WORD_TEXT_ASSERTS(w6, str);
        WORD_RECT_AREA_ASSERTS(w6, w6.rect_area(), dim_t(1, str.length()));

        Word w7(slim_t::max() - 1, slim_t::max(), H, str.c_str());
        WORD_BASIC_ASSERTS(
            w7, pos_t(slim_t::max() - 1, slim_t::max()),
            pos_t(slim_t::max(), slim_t::max()), H,
            0, str[0], str.length());
        WORD_TEXT_ASSERTS(w7, str);
        WORD_RECT_AREA_ASSERTS(w7, w7.rect_area(), dim_t(str.length(), 1));

        Word w8(slim_t::max(), slim_t::max() - 1, V, str.c_str());
        WORD_BASIC_ASSERTS(w8, pos_t(slim_t::max(), slim_t::max() - 1),
                           pos_t(slim_t::max(), slim_t::max()), V,
                           0, str[0], str.length());
        WORD_TEXT_ASSERTS(w8, str);
        WORD_RECT_AREA_ASSERTS(w8, w8.rect_area(), dim_t(1, str.length()));
    }

    void word_copy_move_construction_tests() {
        static_assert(is_copy_constructible_v<Word>);
        static_assert(is_move_constructible_v<Word>);

        Word w1(0, 0, H, "");
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w1, pos_t(0, 0), H, '?');
        Word w2(0, 0, V, "");
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w2, pos_t(0, 0), V, '?');
        Word const cw1(100, 200, H, "A");
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw1, pos_t(100, 200), H, 'A');

        Word w3a(Word(100, 200, H, "A")), w3b = Word(100, 200, H, "A");
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w3a, pos_t(100, 200), H, 'A');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w3b, pos_t(100, 200), H, 'A');
        Word w4a(w1), w4b = w1;
        assert(w1.length() == 1);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w4a, pos_t(0, 0), H, '?');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w4b, pos_t(0, 0), H, '?');
        Word w5a(cw1), w5b = cw1;
        assert(cw1.length() == 1);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w5a, pos_t(100, 200), H, 'A');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w5b, pos_t(100, 200), H, 'A');

        Word const cw2a(Word(100, 200, H, "A"));
        Word const cw2b = Word(100, 200, H, "A");
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw2a, pos_t(100, 200), H, 'A');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw2b, pos_t(100, 200), H, 'A');
        Word const cw3a(w1);
        Word const cw3b = w1;
        assert(w1.length() == 1);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw3a, pos_t(0, 0), H, '?');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw3b, pos_t(0, 0), H, '?');
        Word const cw4a(cw1);
        Word const cw4b = cw1;
        assert(cw1.length() == 1);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw4a, pos_t(100, 200), H, 'A');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw4b, pos_t(100, 200), H, 'A');

        Word w6a(move(w4a));
        assert(w4a.length() == 0);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w6a, pos_t(0, 0), H, '?');
        Word w6b = move(w6a);
        assert(w6a.length() == 0);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w6b, pos_t(0, 0), H, '?');

        Word const cw5a(move(w1));
        Word const cw5b = move(w4b);
        assert(w1.length() == 0);
        assert(w4b.length() == 0);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw5a, pos_t(0, 0), H, '?');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw5b, pos_t(0, 0), H, '?');

        Word w7a(move(cw3a));
        Word w7b = move(cw3b);
        assert(cw3a.length() == 1);
        assert(cw3b.length() == 1);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w7a, pos_t(0, 0), H, '?');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(w7b, pos_t(0, 0), H, '?');

        Word const cw6a(move(cw3a));
        Word const cw6b = move(cw3b);
        assert(cw3a.length() == 1);
        assert(cw3b.length() == 1);
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw6a, pos_t(0, 0), H, '?');
        COPY_MOVE_ONELETTER_WORD_ASSERTS(cw6b, pos_t(0, 0), H, '?');
    }

    void word_assignments_tests() {
        static_assert(is_copy_assignable_v<Word>);
        static_assert(is_move_assignable_v<Word>);

        string str1 = "ABC", str2 = "DCBA", str3 = "EDCBA";
        Word w1(20, 10, V, str1.c_str()), w2(10, 20, H, str2.c_str());
        Word const cw(100, 200, V, str3.c_str());
        assert(w2.length() == 4);
        assert(cw.length() == 5);
        WORD_BASIC_ASSERTS(w1, pos_t(20, 10), pos_t(20, 12), V, 0, str1[0],
                           str1.length());
        WORD_TEXT_ASSERTS(w1, str1);
        w1 = w2;
        assert(w2.length() == 4);
        WORD_BASIC_ASSERTS(w1, pos_t(10, 20), pos_t(13, 20), H, 0, str2[0],
                           str2.length());
        WORD_TEXT_ASSERTS(w1, str2);
        w1 = cw;
        assert(cw.length() == 5);
        WORD_BASIC_ASSERTS(w1, pos_t(100, 200), pos_t(100, 204), V, 0, str3[0],
                           str3.length());
        WORD_TEXT_ASSERTS(w1, str3);
        w1 = move(w2);
        assert(w2.length() == 0);
        WORD_BASIC_ASSERTS(w1, pos_t(10, 20), pos_t(13, 20), H, 0, str2[0],
                           str2.length());
        WORD_TEXT_ASSERTS(w1, str2);
        w1 = move(cw);
        assert(cw.length() == 5);
        WORD_BASIC_ASSERTS(w1, pos_t(100, 200), pos_t(100, 204), V, 0, str3[0],
                           str3.length());
        WORD_TEXT_ASSERTS(w1, str3);
    }
#endif /* 201 */

#if TEST_NUM == 202
    void rect_area_class_usage_tests() {
        static_assert(is_class_v<RectArea>);

        // Standard usage
        RectArea ra1(pos_t(10, 10), pos_t(100, 100));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(10, 10), pos_t(100, 100), dim_t(91, 91), false);
        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(20, 10), pos_t(100, 100)),
            pos_t(20, 10), pos_t(100, 100), dim_t(81, 91), false);
        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(10, 20), pos_t(100, 100)),
            pos_t(10, 20), pos_t(100, 100), dim_t(91, 81), false);
        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(10, 10), pos_t(110, 100)),
            pos_t(10, 10), pos_t(110, 100), dim_t(101, 91), false);
        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(10, 10), pos_t(100, 110)),
            pos_t(10, 10), pos_t(100, 110), dim_t(91, 101), false);

        for (int r = -1; r <= 1; ++r)
            for (int c = -1; c <= 1; ++c) {
                ra1.set_left_top(pos_t(10 + c, 10 + r));
                RECT_AREA_BASE_ASSERTS(
                    ra1, pos_t(10 + c, 10 + r), pos_t(100, 100),
                    dim_t(91 - c, 91 - r), false);
            }
        ra1.set_left_top(pos_t(10, 10));
        for (int r = -1; r <= 1; ++r)
            for (int c = -1; c <= 1; ++c) {
                ra1.set_right_bottom(pos_t(100 + c, 100 + r));
                RECT_AREA_BASE_ASSERTS(
                    ra1, pos_t(10, 10), pos_t(100 + c, 100 + r),
                    dim_t(91 + c, 91 + r), false);
            }

        ra1.set_right_bottom(pos_t(12, 12));
        for (size_t r = 10; r <= 12; ++r)
            for (size_t c = 10; c <= 12; ++c) {
                ra1.embrace(pos_t(c, r));
                RECT_AREA_BASE_ASSERTS(
                    ra1, pos_t(10, 10), pos_t(12, 12), dim_t(3, 3), false);
            }
        ra1.embrace(pos_t(9, 10));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(9, 10), pos_t(12, 12), dim_t(4, 3), false);
        ra1.embrace(pos_t(9, 9));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(9, 9), pos_t(12, 12), dim_t(4, 4), false);
        ra1.embrace(pos_t(8, 8));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(8, 8), pos_t(12, 12), dim_t(5, 5), false);
        ra1.embrace(pos_t(13, 12));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(8, 8), pos_t(13, 12), dim_t(6, 5), false);
        ra1.embrace(pos_t(13, 13));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(8, 8), pos_t(13, 13), dim_t(6, 6), false);
        ra1.embrace(pos_t(14, 14));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(8, 8), pos_t(14, 14), dim_t(7, 7), false);

        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(100, 10), pos_t(10, 100)),
            pos_t(100, 10), pos_t(10, 100), dim_t(0, 0), true);
        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(10, 100), pos_t(100, 10)),
            pos_t(10, 100), pos_t(100, 10), dim_t(0, 0), true);
        RECT_AREA_BASE_ASSERTS(
            RectArea(pos_t(100, 100), pos_t(10, 10)),
            pos_t(100, 100), pos_t(10, 10), dim_t(0, 0), true);

        // Const correctness
        RectArea const cra(pos_t(10, 20), pos_t(15, 30));
        RECT_AREA_BASE_ASSERTS(
            cra, pos_t(10, 20), pos_t(15, 30), dim_t(6, 11), false);
        [[maybe_unused]] auto ra_pow2 = cra * cra;

        // Close to assertion
        RectArea ra5(pos_t(0, 0), pos_t(slim_t::max() - 1, 0));
        RECT_AREA_BASE_ASSERTS(
            ra5, pos_t(0, 0), pos_t(slim_t::max() - 1, 0),
            dim_t(slim_t::max(), 1), false);
        RectArea ra6(pos_t(0, 0), pos_t(0, slim_t::max() - 1));
        RECT_AREA_BASE_ASSERTS(
            ra6, pos_t(0, 0), pos_t(0, slim_t::max() - 1),
            dim_t(1, slim_t::max()), false);
        RectArea ra7(pos_t(0, 0), pos_t(slim_t::max() - 1, slim_t::max() - 1));
        RECT_AREA_BASE_ASSERTS(
            ra7, pos_t(0, 0), pos_t(slim_t::max() - 1, slim_t::max() - 1),
            dim_t(slim_t::max(), slim_t::max()), false);
    }

    void rect_area_copy_move_construction_tests() {
        static_assert(is_copy_constructible_v<RectArea>);
        static_assert(is_move_constructible_v<RectArea>);

        RectArea ra1(pos_t(2, 3), pos_t(4, 5));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RectArea const cra1(pos_t(20, 30), pos_t(40, 50));
        RECT_AREA_BASE_ASSERTS(
            cra1, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);

        RectArea ra2a(ra1), ra2b = ra1;
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra2a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra2b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RectArea ra3a(cra1), ra3b = cra1;
        RECT_AREA_BASE_ASSERTS(
            cra1, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            ra3a, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            ra3b, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);

        RectArea const cra2a(ra1);
        RectArea const cra2b = ra1;
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            cra2a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            cra2b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RectArea const cra3a(cra1);
        RectArea const cra3b = cra1;
        RECT_AREA_BASE_ASSERTS(
            cra1, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            cra3a, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            cra3b, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);

        RectArea ra4a(move(ra2a)), ra4b = move(ra2b);
        RECT_AREA_BASE_ASSERTS(
            ra4a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra4b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra2a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra2b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);

        RectArea ra5a(move(cra2a)), ra5b = move(cra2b);
        RECT_AREA_BASE_ASSERTS(
            cra2a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            cra2b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra5a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra5b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);

        RectArea const cra4a(move(ra4a));
        RectArea const cra4b = move(ra4b);
        RECT_AREA_BASE_ASSERTS(
            ra4a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            ra4b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            cra4a, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);
        RECT_AREA_BASE_ASSERTS(
            cra4b, pos_t(2, 3), pos_t(4, 5), dim_t(3, 3), false);

        RectArea const cra5a(move(cra3a));
        RectArea const cra5b = move(cra3b);
        RECT_AREA_BASE_ASSERTS(
            cra3a, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            cra3b, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            cra5a, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
        RECT_AREA_BASE_ASSERTS(
            cra5b, pos_t(20, 30), pos_t(40, 50), dim_t(21, 21), false);
    }

    void rect_area_assignments_tests() {
        static_assert(is_copy_assignable_v<RectArea>);
        static_assert(is_move_assignable_v<RectArea>);

        RectArea ra1(pos_t(1, 2), pos_t(2, 4));
        RectArea ra2(pos_t(3, 10), pos_t(6, 14));
        RectArea const cra(pos_t(5, 15), pos_t(10, 21));
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(1, 2), pos_t(2, 4), dim_t(2, 3), false);
        ra1 = ra2;
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(3, 10), pos_t(6, 14), dim_t(4, 5), false);
        RECT_AREA_BASE_ASSERTS(
            ra2, pos_t(3, 10), pos_t(6, 14), dim_t(4, 5), false);
        ra1 = cra;
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(5, 15), pos_t(10, 21), dim_t(6, 7), false);
        RECT_AREA_BASE_ASSERTS(
            cra, pos_t(5, 15), pos_t(10, 21), dim_t(6, 7), false);
        ra1 = move(ra2);
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(3, 10), pos_t(6, 14), dim_t(4, 5), false);
        RECT_AREA_BASE_ASSERTS(
            ra2, pos_t(3, 10), pos_t(6, 14), dim_t(4, 5), false);
        ra1 = move(cra);
        RECT_AREA_BASE_ASSERTS(
            ra1, pos_t(5, 15), pos_t(10, 21), dim_t(6, 7), false);
        RECT_AREA_BASE_ASSERTS(
            cra, pos_t(5, 15), pos_t(10, 21), dim_t(6, 7), false);
    }

    void rect_area_intersection_tests() {
        // Non-empty
        RectArea ra1(pos_t(1, 1), pos_t(4, 3));
        RectArea ra2(pos_t(4, 3), pos_t(6, 6));
        auto ra = ra1;
        for (size_t r = 3; r <= 6; ++r)
            for (size_t c = 4; c <= 6; ++c) {
                ra1.set_right_bottom(pos_t(c, r));
                ra = ra1 * ra2;
                RECT_AREA_BASE_ASSERTS(ra, pos_t(4, 3), pos_t(c, r),
                    dim_t(c - 4 + 1, r - 3 + 1), false);
                ra = ra2 * ra1;
                RECT_AREA_BASE_ASSERTS(ra, pos_t(4, 3), pos_t(c, r),
                    dim_t(c - 4 + 1, r - 3 + 1), false);
            }
        ra1. set_right_bottom(pos_t(9, 8));
        ra = ra1 * ra2;
        RECT_AREA_BASE_ASSERTS(ra, pos_t(4, 3), pos_t(6, 6), dim_t(3, 4), false);
        ra = ra2 * ra1;
        RECT_AREA_BASE_ASSERTS(ra, pos_t(4, 3), pos_t(6, 6), dim_t(3, 4), false);
        for (size_t r = 3; r <= 6; ++r)
            for (size_t c = 4; c <= 6; ++c) {
                ra1.set_left_top(pos_t(c, r));
                ra = ra1 * ra2;
                RECT_AREA_BASE_ASSERTS(ra, pos_t(c, r), pos_t(6, 6),
                    dim_t(6 - c + 1, 6 - r + 1), false);
                ra = ra2 * ra1;
                RECT_AREA_BASE_ASSERTS(ra, pos_t(c, r), pos_t(6, 6),
                    dim_t(6 - c + 1, 6 - r + 1), false);
            }

        ra = ra2;  // (4, 3), (6, 6)
        ra *= RectArea(pos_t(1, 1), pos_t(4, 3));
        RECT_AREA_BASE_ASSERTS(ra, pos_t(4, 3), pos_t(4, 3), dim_t(1, 1), false);
        ra = ra2;
        ra *= RectArea(pos_t(6, 1), pos_t(9, 3));
        RECT_AREA_BASE_ASSERTS(ra, pos_t(6, 3), pos_t(6, 3), dim_t(1, 1), false);
        ra = ra2;
        ra *= RectArea(pos_t(1, 6), pos_t(4, 8));
        RECT_AREA_BASE_ASSERTS(ra, pos_t(4, 6), pos_t(4, 6), dim_t(1, 1), false);
        ra = ra2;
        ra *= RectArea(pos_t(6, 6), pos_t(9, 8));
        RECT_AREA_BASE_ASSERTS(ra, pos_t(6, 6), pos_t(6, 6), dim_t(1, 1), false);

        // Empty intersection
        RectArea ra3(pos_t(3, 1), pos_t(7, 2));
        RectArea ra4(pos_t(4, 3), pos_t(6, 6));

        for (size_t c = 3; c <= 7; ++c) {
            ra3.set_left_top(pos_t(3, 1));
            ra3.set_right_bottom(pos_t(c, 2));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

            ra3.set_left_top(pos_t(c, 1));
            ra3.set_right_bottom(pos_t(7, 2));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

            ra3.set_left_top(pos_t(3, 7));
            ra3.set_right_bottom(pos_t(c, 8));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

            ra3.set_left_top(pos_t(c, 7));
            ra3.set_right_bottom(pos_t(7, 8));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        }

        for (size_t r = 2; r <= 7; ++r) {
            ra3.set_left_top(pos_t(2, 2));
            ra3.set_right_bottom(pos_t(3, r));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

            ra3.set_left_top(pos_t(2, r));
            ra3.set_right_bottom(pos_t(3, 7));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

            ra3.set_left_top(pos_t(7, 2));
            ra3.set_right_bottom(pos_t(8, r));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

            ra3.set_left_top(pos_t(7, r));
            ra3.set_right_bottom(pos_t(8, 7));
            ra = ra3 * ra4;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
            ra = ra4 * ra3;
            RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        }

        ra = ra2;  // (4, 3), (6, 6)
        ra *= RectArea(pos_t(1, 1), pos_t(3, 2));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = ra2;
        ra *= RectArea(pos_t(7, 1), pos_t(9, 2));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = ra2;
        ra *= RectArea(pos_t(1, 7), pos_t(3, 8));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = ra2;
        ra *= RectArea(pos_t(7, 7), pos_t(9, 8));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        // Empty factors
        ra = RectArea(pos_t(1, 1), pos_t(0, 0))
             * RectArea(pos_t(2, 2), pos_t(3, 3));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(2, 2), pos_t(3, 3))
             * RectArea(pos_t(1, 1), pos_t(0, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(1, 0), pos_t(0, 1))
             * RectArea(pos_t(2, 2), pos_t(3, 3));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(2, 2), pos_t(3, 3))
             * RectArea(pos_t(1, 0), pos_t(0, 1));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(0, 1), pos_t(1, 0))
             * RectArea(pos_t(2, 2), pos_t(3, 3));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(2, 2), pos_t(3, 3))
             * RectArea(pos_t(0, 1), pos_t(1, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(1, 1), pos_t(0, 0))
             * RectArea(pos_t(3, 3), pos_t(2, 2));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(3, 3), pos_t(2, 2))
             * RectArea(pos_t(1, 1), pos_t(0, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(1, 1), pos_t(0, 0))
             * RectArea(pos_t(1, 1), pos_t(0, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 0), pos_t(0, 1))
             * RectArea(pos_t(0, 1), pos_t(1, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 1), pos_t(0, 0))
             * RectArea(pos_t(1, 0), pos_t(0, 1));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 1), pos_t(0, 0))
             * RectArea(pos_t(0, 1), pos_t(1, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(1, 1), pos_t(0, 0));
        ra *= RectArea(pos_t(2, 2), pos_t(3, 3));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 0), pos_t(0, 1));
        ra *= RectArea(pos_t(2, 2), pos_t(3, 3));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(0, 1), pos_t(1, 0));
        ra *= RectArea(pos_t(2, 2), pos_t(3, 3));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(1, 1), pos_t(0, 0));
        ra *= RectArea(pos_t(3, 3), pos_t(2, 2));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);

        ra = RectArea(pos_t(1, 1), pos_t(0, 0));
        ra *= RectArea(pos_t(1, 1), pos_t(0, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 1), pos_t(0, 0));
        ra *= ra;
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 0), pos_t(0, 1));
        ra *= RectArea(pos_t(0, 1), pos_t(1, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 1), pos_t(0, 0));
        ra *= RectArea(pos_t(1, 0), pos_t(0, 1));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
        ra = RectArea(pos_t(1, 1), pos_t(0, 0));
        ra *= RectArea(pos_t(0, 1), pos_t(1, 0));
        RECT_AREA_SIZE_ASSERTS(ra, dim_t(0, 0), true);
    }
#endif /* 202 */

#if TEST_NUM == 203
    void crossword_class_usage_tests() {
        static_assert(is_class_v<Crossword>);

        // Standard usage
        Crossword w1(Word(10, 20, H, "ABCD"), {Word(10, 20, H, "XYZ")});
        CROSSWORD_DIM_ASSERTS(w1, dim_t(4, 1), dim_t(1, 0));
        assert(w1.insert_word(Word(10, 20, V, "ABC")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(4, 3), dim_t(1, 1));
        assert(!w1.insert_word(Word(11, 19, V, "ABCD")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(4, 3), dim_t(1, 1));
        assert(w1.insert_word(Word(12, 18, V, "ABC")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(4, 5), dim_t(1, 2));
        assert(!w1.insert_word(Word(13, 20, V, "DEFG")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(4, 5), dim_t(1, 2));
        assert(w1.insert_word(Word(11, 18, H, "3ab.,?")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(7, 5), dim_t(2, 2));
        assert(w1.insert_word(Word(14, 17, V, "C5")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(7, 6), dim_t(2, 3));
        assert(w1.insert_word(Word(16, 17, V, "d.")));
        CROSSWORD_DIM_ASSERTS(w1, dim_t(7, 6), dim_t(2, 4));

        // One-letter words
        Crossword w2(Word(1, 1, H, "X"), {});
        CROSSWORD_DIM_ASSERTS(w2, dim_t(1, 1), dim_t(1, 0));
        assert(!w2.insert_word(Word(1, 1, H, "Y")));
        CROSSWORD_DIM_ASSERTS(w2, dim_t(1, 1), dim_t(1, 0));
        assert(!w2.insert_word(Word(1, 1, H, "X")));
        CROSSWORD_DIM_ASSERTS(w2, dim_t(1, 1), dim_t(1, 0));
        assert(!w2.insert_word(Word(1, 1, V, "Y")));
        CROSSWORD_DIM_ASSERTS(w2, dim_t(1, 1), dim_t(1, 0));
        assert(w2.insert_word(Word(1, 1, V, "X")));
        CROSSWORD_DIM_ASSERTS(w2, dim_t(1, 1), dim_t(1, 1));

        // Const correctness
        Crossword const ccr(Word(0, 0, H, "CROSSWORD"),
                           {Word(5, 0, V, "WORLD")});
        Crossword cr(Word(100, 200, V, "CROSSWORD"),
                    {Word(100, 205, H, "WORLD")});
        CROSSWORD_DIM_ASSERTS(ccr, dim_t(9, 5), dim_t(1, 1));
        [[maybe_unused]] auto cr2 = ccr + cr;
        [[maybe_unused]] auto ccr2 = ccr + ccr;
    }

    void crossword_copy_move_construction_tests() {
        static_assert(is_copy_constructible_v<Crossword>);
        static_assert(is_move_constructible_v<Crossword>);

        Crossword cr1(Word(200, 100, V, "CROSSWORD"), {});
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(1, 9), dim_t(0, 1));
        Crossword const ccr1(Word(0, 0, H, "CROSSWORD"),
                           {Word(5, 0, V, "WORLD")});
        CROSSWORD_DIM_ASSERTS(ccr1, dim_t(9, 5), dim_t(1, 1));

        Crossword cr2a(cr1), cr2b = cr1;
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr2a, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr2b, dim_t(1, 9), dim_t(0, 1));

        Crossword cr3a(ccr1), cr3b = ccr1;
        CROSSWORD_DIM_ASSERTS(ccr1, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(cr3a, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(cr3b, dim_t(9, 5), dim_t(1, 1));

        Crossword const ccr2a(cr1);
        Crossword const ccr2b = cr1;
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(ccr2a, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(ccr2b, dim_t(1, 9), dim_t(0, 1));

        Crossword const ccr3a(ccr1);
        Crossword const ccr3b = ccr1;
        CROSSWORD_DIM_ASSERTS(ccr1, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr3a, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr3b, dim_t(9, 5), dim_t(1, 1));

        Crossword cr4a(move(cr2a)), cr4b = move(cr2b);
        CROSSWORD_DIM_ASSERTS(cr4a, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr4b, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr2a, dim_t(0, 0), dim_t(0, 0));
        CROSSWORD_DIM_ASSERTS(cr2b, dim_t(0, 0), dim_t(0, 0));

        Crossword cr5a(move(ccr2a)), cr5b = move(ccr2b);
        CROSSWORD_DIM_ASSERTS(cr5a, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr5b, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(ccr2a, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(ccr2b, dim_t(1, 9), dim_t(0, 1));

        Crossword const ccr4a(move(cr4a));
        Crossword const ccr4b = move(cr4b);
        CROSSWORD_DIM_ASSERTS(ccr4a, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(ccr4b, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr4a, dim_t(0, 0), dim_t(0, 0));
        CROSSWORD_DIM_ASSERTS(cr4b, dim_t(0, 0), dim_t(0, 0));

        Crossword const ccr5a(move(ccr3a));
        Crossword const ccr5b = move(ccr3b);
        CROSSWORD_DIM_ASSERTS(ccr5a, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr5b, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr3a, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr3b, dim_t(9, 5), dim_t(1, 1));
    }

    void crossword_assignments_tests() {
        static_assert(is_copy_assignable_v<Crossword>);
        static_assert(is_move_assignable_v<Crossword>);

        Crossword cr1(Word(200, 100, V, "CROSSWORD"), {});
        Crossword cr2(Word(10, 20, H, "CROSSWORD"), {Word(20, 20, H, "WORLD")});
        Crossword const ccr(Word(0, 0, H, "CROSSWORD"),
                           {Word(5, 0, V, "WORLD")});
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(1, 9), dim_t(0, 1));
        CROSSWORD_DIM_ASSERTS(cr2, dim_t(15, 1), dim_t(2, 0));
        CROSSWORD_DIM_ASSERTS(ccr, dim_t(9, 5), dim_t(1, 1));
        cr1 = cr1;
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(1, 9), dim_t(0, 1));
        cr1 = cr2;
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(15, 1), dim_t(2, 0));
        CROSSWORD_DIM_ASSERTS(cr2, dim_t(15, 1), dim_t(2, 0));
        cr1 = ccr;
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr, dim_t(9, 5), dim_t(1, 1));
        cr1 = move(cr2);
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(15, 1), dim_t(2, 0));
        CROSSWORD_DIM_ASSERTS(cr2, dim_t(0, 0), dim_t(0, 0));
        cr1 = move(ccr);
        CROSSWORD_DIM_ASSERTS(cr1, dim_t(9, 5), dim_t(1, 1));
        CROSSWORD_DIM_ASSERTS(ccr, dim_t(9, 5), dim_t(1, 1));
    }

    void crossword_joining_tests() {
        // No collision
        Crossword cr1(Word(100, 200, H, "ABC"), {});
        Crossword cr2(Word(104, 200, H, "ABC"), {});
        Crossword cr3(Word(100, 200, V, "ABC"), {});
        Crossword cr4(Word(104, 200, V, "ABC"), {});
        Crossword cr = cr1 + cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(7, 1), dim_t(2, 0));
        cr = cr2 + cr1;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(7, 1), dim_t(2, 0));
        cr = cr1;
        cr += cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(7, 1), dim_t(2, 0));
        cr = cr3 + cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(7, 3), dim_t(1, 1));
        cr = cr2 + cr3;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(7, 3), dim_t(1, 1));
        cr = cr3;
        cr += cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(7, 3), dim_t(1, 1));
        cr = cr1 + cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(5, 3), dim_t(1, 1));
        cr = cr4 + cr1;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(5, 3), dim_t(1, 1));
        cr = cr1;
        cr += cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(5, 3), dim_t(1, 1));
        cr = cr3 + cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(5, 3), dim_t(0, 2));
        cr = cr4 + cr3;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(5, 3), dim_t(0, 2));
        cr = cr3;
        cr += cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(5, 3), dim_t(0, 2));

        // With collision
        Crossword cr5(Word(100, 200, H, "ABCD"), {});
        Crossword cr6(Word(104, 200, V, "WBC"), {});
        cr = cr5 + cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(4, 1), dim_t(1, 0));
        cr = cr2 + cr5;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(3, 1), dim_t(1, 0));
        cr = cr5;
        cr += cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(4, 1), dim_t(1, 0));
        cr = cr6 + cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(1, 3), dim_t(0, 1));
        cr = cr2 + cr6;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(3, 1), dim_t(1, 0));
        cr = cr6;
        cr += cr2;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(1, 3), dim_t(0, 1));
        cr = cr5 + cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(4, 1), dim_t(1, 0));
        cr = cr4 + cr5;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(1, 3), dim_t(0, 1));
        cr = cr5;
        cr += cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(4, 1), dim_t(1, 0));
        cr = cr6 + cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(1, 3), dim_t(0, 1));
        cr = cr4 + cr6;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(1, 3), dim_t(0, 1));
        cr = cr6;
        cr += cr4;
        CROSSWORD_DIM_ASSERTS(cr, dim_t(1, 3), dim_t(0, 1));

        // A boundary case
        cr = Crossword(Word(0, 0, H, "A"), {Word(slim_t::max() - 1, 0, H, "B")})
           + Crossword(Word(slim_t::max() - 1, slim_t::max() - 1, V, "D"),
                       {Word(0, slim_t::max() - 1, V, "C")});
        assert(cr.word_count() == dim_t(2, 2));
        assert(cr.size() == dim_t(slim_t::max(), slim_t::max()));
    }
#endif /* 203 */

#if TEST_NUM == 302
    void word_comparison_tests() {
        string str = "ABC";

        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(1, 0, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(1, 0, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(1, 1, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(1, 1, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, V, str.c_str()), Word(1, 0, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, V, str.c_str()), Word(1, 0, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, V, str.c_str()), Word(1, 1, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, V, str.c_str()), Word(1, 1, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, H, str.c_str()), Word(1, 0, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, H, str.c_str()), Word(1, 0, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, H, str.c_str()), Word(1, 1, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, H, str.c_str()), Word(1, 1, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, V, str.c_str()), Word(1, 0, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, V, str.c_str()), Word(1, 0, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, V, str.c_str()), Word(1, 1, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 1, V, str.c_str()), Word(1, 1, V, str.c_str()));

        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(0, 1, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(0, 1, V, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, V, str.c_str()), Word(0, 1, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(Word(0, 0, V, str.c_str()), Word(0, 1, V, str.c_str()));

        WORD_COMPARISONS_ASSERTS(Word(0, 0, H, str.c_str()), Word(0, 0, V, str.c_str()));
    }
#endif

#if TEST_NUM == 303
    void const_word_comparison_tests() {
        string str = "XYZ";
        Word const w1(10, 20, H, str.c_str());
        Word const w2(20, 10, H, str.c_str());
        Word const w3(30, 40, H, str.c_str());
        Word const w4(11, 20, H, str.c_str());
        Word const w5(20, 11, H, str.c_str());
        Word const w6(30, 40, V, str.c_str());
        WORD_COMPARISONS_ASSERTS(w1, Word(11, 20, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(w2, Word(20, 11, H, str.c_str()));
        WORD_COMPARISONS_ASSERTS(w3, Word(30, 40, V, str.c_str()));

        WORD_COMPARISONS_ASSERTS(Word(10, 20, H, str.c_str()), w4);
        WORD_COMPARISONS_ASSERTS(Word(20, 10, H, str.c_str()), w5);
        WORD_COMPARISONS_ASSERTS(Word(30, 40, H, str.c_str()), w6);

        WORD_COMPARISONS_ASSERTS(w1, w4);
        WORD_COMPARISONS_ASSERTS(w2, w5);
        WORD_COMPARISONS_ASSERTS(w3, w6);
    }
#endif

#if TEST_NUM == 304
    void word_equality_tests() {
        string str = "MIMUW";
        Word w1(200, 200, H, str.c_str()), w2(200, 200, H, str.c_str());
        Word w3(300, 200, H, str.c_str()), w4(300, 200, H, str.c_str());
        Word w5(200, 300, H, str.c_str()), w6(200, 300, H, str.c_str());
        Word w7(200, 200, V, str.c_str()), w8(200, 200, V, str.c_str());
        Word w9(300, 200, V, str.c_str()), w10(300, 200, V, str.c_str());
        Word w11(200, 300, V, str.c_str()), w12(200, 300, V, str.c_str());

        WORD_EQUALITY_ASSERTS(w1, w2);
        WORD_EQUALITY_ASSERTS(w1, w1);
        WORD_EQUALITY_ASSERTS(w3, w4);
        WORD_EQUALITY_ASSERTS(w3, w3);
        WORD_EQUALITY_ASSERTS(w5, w6);
        WORD_EQUALITY_ASSERTS(w5, w5);
        WORD_EQUALITY_ASSERTS(w7, w8);
        WORD_EQUALITY_ASSERTS(w7, w7);
        WORD_EQUALITY_ASSERTS(w9, w10);
        WORD_EQUALITY_ASSERTS(w9, w9);
        WORD_EQUALITY_ASSERTS(w11, w12);
        WORD_EQUALITY_ASSERTS(w11, w11);
    }

    void const_word_equality_tests() {
        string str = "ASCII";
        Word const w1(20000, 20000, H, str.c_str());
        Word w2(20000, 20000, H, str.c_str());
        Word const w3(30000, 20000, H, str.c_str());
        Word w4(30000, 20000, H, str.c_str());
        Word const w5(20000, 30000, H, str.c_str());
        Word w6(20000, 30000, H, str.c_str());
        Word const w7(20000, 20000, V, str.c_str());
        Word w8(20000, 20000, V, str.c_str());
        Word const w9(30000, 20000, V, str.c_str());
        Word w10(30000, 20000, V, str.c_str());
        Word const w11(20000, 30000, V, str.c_str());
        Word w12(20000, 30000, V, str.c_str());

        WORD_EQUALITY_ASSERTS(w1, w2);
        WORD_EQUALITY_ASSERTS(w1, w1);
        WORD_EQUALITY_ASSERTS(w3, w4);
        WORD_EQUALITY_ASSERTS(w3, w3);
        WORD_EQUALITY_ASSERTS(w5, w6);
        WORD_EQUALITY_ASSERTS(w5, w5);
        WORD_EQUALITY_ASSERTS(w7, w8);
        WORD_EQUALITY_ASSERTS(w7, w7);
        WORD_EQUALITY_ASSERTS(w9, w10);
        WORD_EQUALITY_ASSERTS(w9, w9);
        WORD_EQUALITY_ASSERTS(w11, w12);
        WORD_EQUALITY_ASSERTS(w11, w11);
    }
#endif /* 304 */

#if TEST_NUM == 305
    void distinguishable_equivalent_words_tests() {
        Word w1(200, 200, H, "ABC"), w2(200, 200, H, "ABCD");
        Word w3(200, 200, H, "ABC"), w4(200, 200, H, "XYZ");
        Word w5(200, 200, H, "ABC"), w6(200, 200, H, "ABW");
        Word w7(200, 200, H, "ABC"), w8(200, 200, H, "");

        assert(w1.length() != w2.length());
        WORD_EQUALITY_ASSERTS(w1, w2);
        assert(w3.at(0) != w4.at(0));
        WORD_EQUALITY_ASSERTS(w3, w4);
        assert(w5.at(2) != w6.at(2));
        WORD_EQUALITY_ASSERTS(w5, w6);
        assert(w7.length() != w8.length());
        WORD_EQUALITY_ASSERTS(w7, w8);
    }

    void distinguishable_inequivalent_words_tests() {
        Word w1(2000, 200, H, "ABC"), w2(3000, 200, H, "ABCD");
        Word w3(2000, 200, H, "ABC"), w4(3000, 200, H, "XYZ");
        Word w5(2000, 200, H, "ABC"), w6(3000, 200, H, "ABW");
        Word w7(2000, 200, H, ""), w8(3000, 200, H, "ABC");

        assert(w1.length() != w2.length());
        WORD_COMPARISONS_ASSERTS(w1, w2);
        assert(w3.at(0) != w4.at(0));
        WORD_COMPARISONS_ASSERTS(w3, w4);
        assert(w5.at(2) != w6.at(2));
        WORD_COMPARISONS_ASSERTS(w5, w6);
        assert(w7.length() != w8.length());
        WORD_COMPARISONS_ASSERTS(w7, w8);
    }
#endif /* 305 */

#if TEST_NUM == 401
    void scope_exceeding_words_tests() {
        string str = "ABC";

        WORD_TRIMMING_TEST(
            Word(slim_t::max(), 0, H, str.c_str()),
            pos_t(slim_t::max(), 0), pos_t(slim_t::max(), 0), H,
            str[0], DEFAULT_CHAR, DEFAULT_CHAR, 1, dim_t(1, 1), false
        );
        WORD_TRIMMING_TEST(
            Word(slim_t::max() - 1, 0, H, str.c_str()),
            pos_t(slim_t::max() - 1, 0), pos_t(slim_t::max(), 0), H,
            str[0], str[1], DEFAULT_CHAR, 2, dim_t(2, 1), false
        );
        WORD_TRIMMING_TEST(
            Word(slim_t::max() - 2, 0, H, str.c_str()),
            pos_t(slim_t::max() - 2, 0), pos_t(slim_t::max(), 0), H,
            str[0], str[1], str[2], 3, dim_t(3, 1), false
        );

        WORD_TRIMMING_TEST(
            Word(0, slim_t::max(), V, str.c_str()),
            pos_t(0, slim_t::max()), pos_t(0, slim_t::max()), V,
            str[0], DEFAULT_CHAR, DEFAULT_CHAR, 1, dim_t(1, 1), false
        );
        WORD_TRIMMING_TEST(
            Word(0, slim_t::max() - 1, V, str.c_str()),
            pos_t(0, slim_t::max() - 1), pos_t(0, slim_t::max()), V,
            str[0], str[1], DEFAULT_CHAR, 2, dim_t(1, 2), false
        );
        WORD_TRIMMING_TEST(
            Word(0, slim_t::max() - 2, V, str.c_str()),
            pos_t(0, slim_t::max() - 2), pos_t(0, slim_t::max()), V,
            str[0], str[1], str[2], 3, dim_t(1, 3), false
        );
    }
#endif /* 401 */

#if TEST_NUM == 402
    void coordinates_equality_tests() {
        size_t x1 = 11, x2 = 34, y1 = 8, y2 = 19;

        // Equality of coordinates
        RECT_AREA_SIZE_ASSERTS(
            RectArea(pos_t(x1, y1), pos_t(x1, y2)), dim_t(1, y2 - y1 + 1), false
        );
        RECT_AREA_SIZE_ASSERTS(
            RectArea(pos_t(x1, y1), pos_t(x2, y1)), dim_t(x2 - x1 + 1, 1), false
        );
        RECT_AREA_SIZE_ASSERTS(
            RectArea(pos_t(x1, y1), pos_t(x1, y1)), dim_t(1, 1), false
        );
    }
#endif /* 402 */

#if TEST_NUM == 403
    void embracing_empty_area_tests() {
        size_t x1 = 11, x2 = 34, y1 = 8, y2 = 19;

        RectArea era(DEFAULT_EMPTY_RECT_AREA);
        EMPTY_EMBRACE_TEST(
            era, DEFAULT_EMPTY_RECT_AREA, pos_t(x1, y1), pos_t(x2, y2)
        );
        EMPTY_EMBRACE_TEST(
            era, RectArea(pos_t(x2, y1), pos_t(x1, y2)),
            pos_t(x2, y1), pos_t(x1, y2)
        );
        EMPTY_EMBRACE_TEST(
            era, RectArea(pos_t(x1, y2), pos_t(x2, y1)),
            pos_t(x1, y2), pos_t(x2, y1)
        );
        EMPTY_EMBRACE_TEST(
            era, RectArea(pos_t(x2, y2), pos_t(x1, y1)),
            pos_t(x2, y2), pos_t(x1, y1)
        );
    }
#endif /* 403 */

#if TEST_NUM == 404
    void horizontal_overlapping_tests() {
        CROSSWORD_DIM_ASSERTS(
            Crossword(Word(5, 7, H, "ABC"), {Word(6, 7, H, "BCD")}),
            dim_t(3, 1), dim_t(1, 0)
        );
        CROSSWORD_DIM_ASSERTS(
            Crossword(Word(5, 7, V, "ABC"), {Word(5, 8, V, "BCD")}),
            dim_t(1, 3), dim_t(0, 1)
        );
    }

    void diagonal_word_spacing_tests() {
        CROSSWORD_DIM_ASSERTS(
            Crossword(Word(5, 7, H, "ABC"), {
                Word(8, 6, H, "ABC"), Word(8, 8, H, "ABC"),
                Word(2, 6, H, "ABC"), Word(2, 8, H, "ABC"),
                Word(8, 4, V, "ABC"), Word(8, 8, V, "ABC"),
                Word(4, 4, V, "ABC"), Word(4, 8, V, "ABC")
            }),
            dim_t(3, 1), dim_t(1, 0)
        );
        CROSSWORD_DIM_ASSERTS(
            Crossword(Word(5, 7, V, "ABC"), {
                Word(6, 6, H, "ABC"), Word(6, 10, H, "ABC"),
                Word(2, 6, H, "ABC"), Word(2, 10, H, "ABC"),
                Word(6, 4, V, "ABC"), Word(6, 10, V, "ABC"),
                Word(4, 4, V, "ABC"), Word(4, 10, V, "ABC")
            }),
            dim_t(1, 3), dim_t(0, 1)
        );
    }
#endif /* 404 */

} /* anonymous namespace */

/**
 * Program section
 **/

int main() {
// TEST: crosswords_example.cc
#if TEST_NUM == 101
    example_word_tests();
    example_rect_area_tests();
    example_crossword_tests();
#endif

#if TEST_NUM == 102
    stream_operator_tests();
#endif

#if TEST_NUM == 103
    word_collision_tests();
#endif

#if TEST_NUM == 104
    big_crossword_test();
#endif

#if TEST_NUM == 105
    writing_to_file_test();
#endif

// TEST: Word class
#if TEST_NUM == 201
    word_class_usage_tests();
    word_copy_move_construction_tests();
    word_assignments_tests();
#endif

// TEST: RectArea class
#if TEST_NUM == 202
    rect_area_class_usage_tests();
    rect_area_copy_move_construction_tests();
    rect_area_assignments_tests();
    rect_area_intersection_tests();
#endif

// TEST: Crossword class
#if TEST_NUM == 203
    crossword_class_usage_tests();
    crossword_copy_move_construction_tests();
    crossword_assignments_tests();
    crossword_joining_tests();
#endif

// TESTS: comparisons of words
#if TEST_NUM == 301
    static_assert(is_convertible_v<decltype(Word(0, 0, H, "ABC") <=> Word(2, 0, V, "CBA")), weak_ordering>);
#endif

#if TEST_NUM == 302
    word_comparison_tests();
#endif

#if TEST_NUM == 303
    const_word_comparison_tests();
#endif

#if TEST_NUM == 304
    word_equality_tests();
    const_word_equality_tests();
#endif

#if TEST_NUM == 305
    distinguishable_equivalent_words_tests();
    distinguishable_inequivalent_words_tests();
#endif

// TESTS: forum questions
#if TEST_NUM == 401
    scope_exceeding_words_tests();
#endif

#if TEST_NUM == 402
    coordinates_equality_tests();
#endif

#if TEST_NUM == 403
    embracing_empty_area_tests();
#endif

#if TEST_NUM == 404
    horizontal_overlapping_tests();
    diagonal_word_spacing_tests();
#endif

// TESTS: expected assertions
#if TEST_NUM == 502
    // RectArea ra(pos_t(0, 0), pos_t(slim_t::max(), 0));
    // [[maybe_unused]] auto s = ra.size();
#endif

#if TEST_NUM == 503
    // RectArea ra(pos_t(0, 0), pos_t(0, slim_t::max()));
    // [[maybe_unused]] auto s = ra.size();
#endif

#if TEST_NUM == 504
    // RectArea ra(pos_t(0, 0), pos_t(slim_t::max(), slim_t::max()));
    // [[maybe_unused]] auto s = ra.size();
#endif

// TEST: enum type verification
#if TEST_NUM == 505
     static_assert(is_same_v<underlying_type_t<orientation_t>, bool>);
#endif

// TESTS: verification of constants
#if TEST_NUM == 506
    static_assert(is_const_v<decltype(DEFAULT_CHAR)>);
    assert(DEFAULT_CHAR == '?');
#endif

#if TEST_NUM == 507
    static_assert(is_const_v<decltype(DEFAULT_WORD)>);
    assert(DEFAULT_WORD.length() == 1 && DEFAULT_WORD.at(0) == '?');
#endif

#if TEST_NUM == 508
    static_assert(is_const_v<decltype(DEFAULT_EMPTY_RECT_AREA)>);
    assert(DEFAULT_EMPTY_RECT_AREA.empty());
#endif

#if TEST_NUM == 509
    static_assert(is_same_v<decltype(CROSSWORD_BACKGROUND), char>);
    assert(CROSSWORD_BACKGROUND == '.');
#endif

// TEST: pos_t and dim_t types verification
#if TEST_NUM == 510
    static_assert(is_same_v<pos_t, pair<size_t, size_t>>);
    static_assert(is_same_v<dim_t, pair<size_t, size_t>>);
#endif

// TESTS: non-compiling const value modification
#if TEST_NUM == 511
    DEFAULT_CHAR = DEFAULT_CHAR;
#endif

#if TEST_NUM == 512
    DEFAULT_WORD = DEFAULT_WORD;
#endif

#if TEST_NUM == 513
    DEFAULT_EMPTY_RECT_AREA = DEFAULT_EMPTY_RECT_AREA;
#endif

#if TEST_NUM == 514
    DEFAULT_WORD[0] = 0;
#endif

// The first one in this group must compile.
#if TEST_NUM == 601
    [[maybe_unused]] auto cr = Crossword(Word(0, 0, H, "ABC"),
                                        {Word(1, 0, V, "BCDE")});
#endif

// TESTS: non-compiling constructors
#if TEST_NUM == 602
    Word w;
#endif

#if TEST_NUM == 603
    Word w(0, 0, H);
#endif

#if TEST_NUM == 604
    Word w(0, 0, V);
#endif

#if TEST_NUM == 605
    Word w(0, 0, true, "WORD");
#endif

#if TEST_NUM == 606
    Word w(0, 0, false, "WORD");
#endif

#if TEST_NUM == 607
    RectArea ra;
#endif

#if TEST_NUM == 608
    RectArea ra(pos_t(0, 0));
#endif

#if TEST_NUM == 609
    RectArea ra(0, 1, 2, 3);
#endif

#if TEST_NUM == 610
    Crossword cr;
#endif

#if TEST_NUM == 611
    Crossword cr({});
#endif

// TESTS: non-compiling const correctness
#if TEST_NUM == 612
    Word const cw(0, 0, H, "WORD");
    Word w(100, 100, V, "WORLD");
    cw = w;
#endif

#if TEST_NUM == 613
    Word const cw(0, 0, H, "WORD");
    Word w(100, 100, V, "WORLD");
    cw = move(w);
#endif

#if TEST_NUM == 614
    RectArea const cra(pos_t(0, 0), pos_t(10, 20));
    RectArea ra(pos_t(1, 1), pos_t(10, 20));
    cra = ra;
#endif

#if TEST_NUM == 615
    RectArea const cra(pos_t(0, 0), pos_t(10, 20));
    RectArea ra(pos_t(1, 1), pos_t(10, 20));
    cra = move(ra);
#endif

#if TEST_NUM == 616
    RectArea const cra(pos_t(0, 0), pos_t(10, 20));
    RectArea ra(pos_t(1, 1), pos_t(10, 20));
    cra *= ra;
#endif

#if TEST_NUM == 617
    RectArea const cra(pos_t(0, 0), pos_t(10, 20));
    cra.embrace(pos_t(100, 200));
#endif

#if TEST_NUM == 618
    RectArea const cra(pos_t(0, 0), pos_t(10, 20));
    cra.set_left_top(pos_t(1, 2));
#endif

#if TEST_NUM == 619
    RectArea const cra(pos_t(0, 0), pos_t(10, 20));
    cra.set_right_bottom(pos_t(5, 10));
#endif

#if TEST_NUM == 620
    Crossword const ccr(Word(0, 0, H, "CROSSWORD"), {});
    Crossword cr(Word(0, 0, V, "CROSSWORD"), {});
    ccr = cr;
#endif

#if TEST_NUM == 621
    Crossword const ccr(Word(0, 0, H, "CROSSWORD"), {});
    Crossword cr(Word(0, 0, V, "CROSSWORD"), {});
    ccr = move(cr);
#endif

#if TEST_NUM == 622
    Crossword const ccr(Word(0, 0, H, "CROSSWORD"), {});
    ccr.insert_word(Word(0, 0, V, "CROSSWORD"));
#endif

#if TEST_NUM == 623
    Crossword const ccr(Word(0, 0, H, "CROSSWORD"), {});
    Crossword cr(Word(0, 0, V, "CROSSWORD"), {});
    ccr += cr;
#endif

} /* the end of main */
