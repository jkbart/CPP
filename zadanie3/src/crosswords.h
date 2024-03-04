#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <string>
#include <vector>
#include <iostream>

using pos_t = std::pair<size_t, size_t>;
using dim_t = std::pair<size_t, size_t>;

enum class orientation_t : bool {
    H = false,
    V = true
};

using orientation_t::H;
using orientation_t::V;

inline constinit char CROSSWORD_BACKGROUND = '.';
inline const constinit char DEFAULT_CHAR = '?';
inline const constinit std::string DEFAULT_WORD = "?";
// inline const constinit DEFAULT_EMPTY_RECT_AREA zdefiniowany po definicji konstruktora RectArea.

class RectArea {
  public:
    constexpr RectArea(pos_t leftTop, pos_t rightBottom);

    constexpr pos_t get_left_top() const;
    constexpr pos_t get_right_bottom() const;
    constexpr void set_left_top(pos_t point);
    constexpr void set_right_bottom(pos_t point);
    constexpr dim_t size() const;
    constexpr bool empty() const;
    constexpr void embrace(pos_t point);

    constexpr RectArea operator*(const RectArea &other) const;
    constexpr RectArea &operator*=(const RectArea &other);

  private:
    pos_t leftTop;
    pos_t rightBottom;
};

class Word {
  public:
    Word(size_t x, size_t y, orientation_t orientation, const std::string &text);

    pos_t get_start_position() const;
    pos_t get_end_position() const;
    orientation_t get_orientation() const;
    char at(size_t charIndex) const;
    size_t length() const;
    RectArea rect_area() const;
    bool collides_with(const Word &word) const;

    auto operator<=>(const Word &other) const;
    bool operator==(const Word &other) const;

  private:
    pos_t position;
    orientation_t orientation;
    std::string text;
};

class Crossword {
  public:
    Crossword(const Word &word, const std::initializer_list<Word> &words);
    Crossword(const Crossword &other);
    Crossword(Crossword &&other);

    bool insert_word(const Word &word);
    dim_t size() const;
    dim_t word_count() const;
    std::vector<Word> get_words() const;
    RectArea get_board() const;

    Crossword &operator=(const Crossword &other);
    Crossword &operator=(Crossword &&other);
    Crossword operator+(const Crossword &other) const;
    Crossword &operator+=(const Crossword &other);
    friend std::ostream &operator<<(std::ostream &os, const Crossword &crossword);

  private:
    std::vector<Word> words;
    RectArea board;

    bool collision(const Word &word) const;
};

constexpr RectArea::RectArea(pos_t leftTop, pos_t rightBottom) :
    leftTop(leftTop), rightBottom(rightBottom) {}

inline const constinit RectArea DEFAULT_EMPTY_RECT_AREA = RectArea({1, 1}, {0, 0});

constexpr pos_t RectArea::get_left_top() const {
    return leftTop;
}

constexpr pos_t RectArea::get_right_bottom() const {
    return rightBottom;
}

constexpr void RectArea::set_left_top(pos_t point) {
    leftTop = point;
}

constexpr void RectArea::set_right_bottom(pos_t point) {
    rightBottom = point;
}

constexpr RectArea RectArea::operator*(const RectArea &other) const {
    return RectArea(*this) *= other;
}

constexpr RectArea &RectArea::operator*=(const RectArea &other) {
    pos_t new_leftTop = {std::max(leftTop.first, other.get_left_top().first),
                         std::max(leftTop.second, other.get_left_top().second)};

    pos_t new_rightBottom = {std::min(rightBottom.first, other.get_right_bottom().first),
                             std::min(rightBottom.second, other.get_right_bottom().second)};

    leftTop = new_leftTop;
    rightBottom = new_rightBottom;

    return *this;
}

constexpr dim_t RectArea::size() const {
    if (empty()) {
        return {0, 0};
    }

    return {rightBottom.first - leftTop.first + 1,
            rightBottom.second - leftTop.second + 1};
}

constexpr bool RectArea::empty() const {
    return leftTop.first > rightBottom.first || leftTop.second > rightBottom.second;
}

constexpr void RectArea::embrace(pos_t point) {
    if (empty()) {
        leftTop = point;
        rightBottom = point;
        return;
    }

    if (point.first < leftTop.first) {
        leftTop.first = point.first;
    }

    if (point.second < leftTop.second) {
        leftTop.second = point.second;
    }

    if (point.first > rightBottom.first) {
        rightBottom.first = point.first;
    }

    if (point.second > rightBottom.second) {
        rightBottom.second = point.second;
    }
}

inline Word::Word(size_t x, size_t y, orientation_t orientation, const std::string &text) :
    position({x, y}), orientation(orientation), text(text) {
    if (text == "") {
        this->text = DEFAULT_WORD;
    }

    if (orientation == H && x > SIZE_MAX - this->text.length() + 1) {
        this->text.erase(this->text.end() - (x + this->text.length() - SIZE_MAX - 1), this->text.end());
    }

    if (orientation == V && y > SIZE_MAX - this->text.length() + 1) {
        this->text.erase(this->text.end() - (y + this->text.length() - SIZE_MAX - 1), this->text.end());
    }

    for (char &c : this->text) {
        if ('a' <= c && c <= 'z') {
            c += ((int)'A' - (int)'a');
        } else if (c < 'A' || 'Z' < c) {
            c = DEFAULT_CHAR;
        }
    }
}

inline pos_t Word::get_start_position() const {
    return position;
}

inline pos_t Word::get_end_position() const {
    if (orientation == H) {
        return {position.first + text.length() - 1, position.second};
    } else {
        return {position.first, position.second + text.length() - 1};
    }
}

inline orientation_t Word::get_orientation() const {
    return orientation;
}

inline char Word::at(size_t charIndex) const {
    if (charIndex >= text.length()) {
        return DEFAULT_CHAR;
    }

    return text[charIndex];
}

inline size_t Word::length() const {
    return text.length();
}

inline RectArea Word::rect_area() const {
    return RectArea(get_start_position(), get_end_position());
}

inline auto Word::operator<=>(const Word &other) const {
    auto cmp = position.first <=> other.position.first;

    if (cmp == 0) {
        cmp = position.second <=> other.position.second;

        if (cmp == 0) {
            cmp = orientation <=> other.orientation;
        }
    }

    return cmp;
}

inline bool Word::operator==(const Word &other) const {
    return position.first == other.position.first && 
        position.second == other.position.second && 
        orientation == other.orientation;
}

inline bool Word::collides_with(const Word &word) const {
    RectArea Area1 = rect_area();
    RectArea Area2 = word.rect_area();

    RectArea Frame1 = RectArea(Area1);

    Frame1.embrace({get_start_position().first == 0 ? 0 : get_start_position().first - 1,
                    get_start_position().second == 0 ? 0 : get_start_position().second - 1});

    Frame1.embrace({get_end_position().first == SIZE_MAX ? SIZE_MAX : get_end_position().first + 1,
                    get_end_position().second == SIZE_MAX ? SIZE_MAX : get_end_position().second + 1});

    if ((Frame1 * Area2).empty()) {
        return false;
    }

    if (get_orientation() == word.get_orientation()) {
        return true;
    } else {
        RectArea commonPoint = Area1 * Area2;

        if (commonPoint.empty()){
            return true;
        }

        size_t index1 = std::max(commonPoint.get_left_top().first - get_start_position().first,
                                commonPoint.get_left_top().second - get_start_position().second);

        size_t index2 = std::max(commonPoint.get_left_top().first - word.get_start_position().first,
                                commonPoint.get_left_top().second - word.get_start_position().second);

        return at(index1) != word.at(index2);
    }
}

inline Crossword::Crossword(const Word &word, const std::initializer_list<Word> &wordsToAdd) :
    board(DEFAULT_EMPTY_RECT_AREA) {
    insert_word(word);

    for (auto &w : wordsToAdd) {
        insert_word(w);
    }
}

inline Crossword::Crossword(const Crossword &other) : 
    words(other.words), board(other.board) {

}

inline Crossword::Crossword(Crossword &&other) : 
    words(std::move(other.words)), board(std::move(other.board)) {
        other.board = DEFAULT_EMPTY_RECT_AREA;
}

inline bool Crossword::insert_word(const Word &word) {
    if (collision(word)) {
        return false;
    }

    words.push_back(word);
    board.embrace(word.get_start_position());
    board.embrace(word.get_end_position());
    return true;
}

inline dim_t Crossword::size() const {
    return board.size();
}

inline dim_t Crossword::word_count() const {
    size_t h = 0, v = 0;

    for (auto &w : words) {
        if (w.get_orientation() == H) {
            ++h;
        } else {
            ++v;
        }
    }

    return {h, v};
}

inline std::vector<Word> Crossword::get_words() const {
    return words;
}

inline RectArea Crossword::get_board() const {
    return board;
}

inline Crossword &Crossword::operator=(const Crossword &other) {
    words = other.words;
    board = other.board;
    return *this;
}

inline Crossword &Crossword::operator=(Crossword &&other) {
    words = std::move(other.words);
    board = std::move(other.board);
    other.board = DEFAULT_EMPTY_RECT_AREA;
    return *this;
}

inline Crossword Crossword::operator+(const Crossword &other) const {
    return Crossword(*this) += other;
}

inline Crossword &Crossword::operator+=(const Crossword &other) {
    for (auto &w : other.get_words()) {
        insert_word(w);
    }

    return *this;
}

inline bool Crossword::collision(const Word &word) const {
    for (auto &w : words) {
        if (word.collides_with(w)) {
            return true;
        }
    }

    return false;
}

inline std::ostream &operator<<(std::ostream &os, const Crossword &crossword) {
    pos_t start = crossword.get_board().get_left_top();
    size_t rows = crossword.size().second + 2;
    size_t cols = crossword.size().first + 2;

    std::vector<std::vector<char>> board(rows, std::vector<char>(cols, CROSSWORD_BACKGROUND));

    for (auto &word : crossword.get_words()) {
        size_t size = word.length();
        pos_t position = word.get_start_position();
        orientation_t orientation = word.get_orientation();
        position.first = position.first - start.first + 1;
        position.second = position.second - start.second + 1;

        for (size_t i = 0; i < size; ++i) {
            board[position.second][position.first] = word.at(i);
            
            if (orientation == H) {
                ++position.first;
            } else {
                ++position.second;
            }
        }
    }
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (j) {
                os << " ";
            }
            os << board[i][j];
        }
        os << std::endl;
    }

    return os;
}

#endif /*CROSSWORD_H*/