#ifndef FIELD_INCLUDED
#define FIELD_INCLUDED

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>


// Direction:
enum class RowCountDirection
{
    WEST       = 0u,
    NORTH_WEST = 1u,
    NORTH      = 2u,
    NORTH_EAST = 3u
};

// Class declaration:
class Field
{
public:
    enum class Player
    {
        EMPTY,
        PLAYER_O,
        PLAYER_X
    };

    class FieldBuilderIterator
    {
        Field &_field;

        size_t _x, _y;

        inline void increment();

    public:
        inline FieldBuilderIterator(Field &field);
        inline FieldBuilderIterator(Field &field, const size_t size);

        inline bool operator<(const FieldBuilderIterator &) const;

        inline FieldBuilderIterator &operator++();
        inline FieldBuilderIterator  operator++(int);

        // Build new field setup:
        Field buildField() const;
    };

private:
    std::vector<std::vector<Player>> _field_data;
    std::vector<std::vector<bool>>   _closeness_data;
    size_t                           _placed_down;
    Player                           _player;
    size_t                           _expected_length;
    Player                           _winner;
    Player                           _closeness_player;

public:
    Field(const size_t field_size, const size_t expected_length,
          const Player closeness_player = Player::PLAYER_X,
          const Player player           = Player::PLAYER_X);


    Field(const Field &other, const Player winner_state);

    // Field(Field &&other);
    // Field &operator=(Field &&other);


    // Access methods:
    inline Player getPlayer(const size_t x, const size_t y) const;
    inline bool   isEmpty(const size_t x, const size_t y) const;

    // Write methods:
    inline void setPlayer(const size_t x, const size_t y);
    // inline void setPlayerO(const size_t x, const size_t y);
    // inline void setPlayerX(const size_t x, const size_t y);

    // Util:
    inline size_t size() const;

    inline void printIt(std::ostream &os) const;

    // Winning state:
    Player getWinner() const;
    bool   full() const;


    // MinMaxHelpers:
    // Evaluate field:
    int evaluate() const;

    bool isLeaf() const;

    // Get new level:
    std::vector<Field> getNewLevel();

    // Get iterators:
    FieldBuilderIterator begin();
    FieldBuilderIterator end();


    // Find selected node:
    size_t findSelected(const size_t x, const size_t y) const;
};

// Helper function definitions:
size_t countHorizontally(std::vector<std::vector<Field::Player>> &fieldData,
                         const Field::Player nextLvlPlayer, const size_t x,
                         const size_t y);
size_t countVertically(std::vector<std::vector<Field::Player>> &fieldData,
                       const Field::Player nextLvlPlayer, const size_t x,
                       const size_t y);
size_t countDiagonally0(std::vector<std::vector<Field::Player>> &fieldData,
                        const Field::Player nextLvlPlayer, const size_t x,
                        const size_t y);
size_t countDiagonally1(std::vector<std::vector<Field::Player>> &fieldData,
                        const Field::Player nextLvlPlayer, const size_t x,
                        const size_t y);


// Inline function definitions:
inline std::ostream &operator<<(std::ostream &os, const Field::Player player);


// Implementation of inline methods:
Field::Player Field::getPlayer(const size_t x, const size_t y) const
{
    return _field_data[x][y];
}

bool Field::isEmpty(const size_t x, const size_t y) const
{
    return _field_data[x][y] == Field::Player::EMPTY;
}

void Field::setPlayer(const size_t x, const size_t y)
{
    _field_data[x][y] = _player;

    size_t fieldSize = _field_data.size();

    size_t sx = x - 1;
    size_t sy = y - 1;
    if (x < 1) {
        sx = 0;
    }
    if (y < 1) {
        sy = 0;
    }
    for (size_t i = sx; i < std::min(fieldSize, x + 2); ++i) {
        for (size_t j = sy; j < std::min(fieldSize, y + 2); ++j) {
            _closeness_data[i][j] = true;
        }
    }

    ++_placed_down;
}


size_t Field::size() const { return _field_data.size(); }

// Field iterator:
Field::FieldBuilderIterator::FieldBuilderIterator(Field &field)
    : _field(field)
    , _x(0)
    , _y(0)
{
    bool val;
    if (_field._closeness_player != _field._player) {
        val = _field._placed_down != 0 && !_field._closeness_data[_x][_y];
    } else {
        val = false;
    }
    if (_field._field_data[_x][_y] != Field::Player::EMPTY || val) {
        ++*this;
    }
}

Field::FieldBuilderIterator::FieldBuilderIterator(Field &      field,
                                                  const size_t size)
    : _field(field)
    , _x(size)
    , _y(0)
{}

void Field::FieldBuilderIterator::increment()
{
    if (++_y == _field._field_data.size()) {
        _y = 0;
        ++_x;
    }
}

bool Field::FieldBuilderIterator::
     operator<(const Field::FieldBuilderIterator &other) const
{
    if (this->_x < other._x) {
        return true;
    } else if (this->_x == other._x) {
        return this->_y < other._y;
    } else {
        return false;
    }
}

Field::FieldBuilderIterator &Field::FieldBuilderIterator::operator++()
{
    const size_t fieldSize    = _field._field_data.size();
    const bool   placedStatus = _field._placed_down == 0;
    increment();

    bool makeTrue = false;
    if (_field._closeness_player == _field._player) {
        makeTrue = true;
    }

    while (_x < fieldSize) {
        if (_field._field_data[_x][_y] == Field::Player::EMPTY &&
            (makeTrue || placedStatus || _field._closeness_data[_x][_y])) {
            break;
        }
        increment();
    }

    return *this;
}

Field::FieldBuilderIterator Field::FieldBuilderIterator::operator++(int)
{
    Field::FieldBuilderIterator temp = *this;
    ++*this;
    return temp;
}



inline void Field::printIt(std::ostream &os) const
{
    const size_t fieldSize = _field_data.size();

    std::cout << " ";
    for (size_t i = 0; i < fieldSize; ++i) {
        std::cout << ' ' << i;
    }
    std::cout << " x\n";

    for (size_t i = 0; i < fieldSize; ++i) {
        os << i << ' ' << _field_data[0][i];
        for (size_t j = 1; j < fieldSize; ++j) {
            os << ' ' << _field_data[j][i];
        }
        os << '\n';
    }
    os << "y\n";

    // for (size_t i = 0; i < fieldSize; ++i) {
    //     os << _closeness_data[i][0];
    //     for (size_t j = 1; j < fieldSize; ++j) {
    //         os << ' ' << _closeness_data[i][j];
    //     }
    //     os << '\n';
    // }
}



inline std::ostream &operator<<(std::ostream &os, const Field::Player player)
{
    switch (player) {
    case Field::Player::PLAYER_O:
        os << 'O';
        break;
    case Field::Player::PLAYER_X:
        os << 'X';
        break;
    default:
        os << '.';
    }

    return os;
}


#endif
