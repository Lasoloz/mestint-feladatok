#include <game/field.hpp>


Field::Field(const size_t field_size, const size_t expected_lenght,
             const Player closeness_player, const Player player)
    : _field_data(field_size,
                  std::vector<Player>(field_size, Field::Player::EMPTY))
    , _closeness_data(field_size, std::vector<bool>(field_size, false))
    , _placed_down(0)
    , _player(player)
    , _expected_length(expected_lenght)
    , _winner(Field::Player::EMPTY)
    , _closeness_player(closeness_player)
{}


Field::Field(const Field &other, const Field::Player winner_state)
    : _field_data(other._field_data)
    , _closeness_data(other._closeness_data)
    , _placed_down(other._placed_down)
    , _player((other._player == Field::Player::PLAYER_O)
                  ? Field::Player::PLAYER_X
                  : Field::Player::PLAYER_O)
    , _expected_length(other._expected_length)
    , _winner(winner_state)
    , _closeness_player(other._closeness_player)
{}



int power(const int num, const int p)
{
    if (p < 0) {
        return 0;
    } else if (p == 0) {
        return 1;
    } else if (p == 1) {
        return num;
    } else if (p % 2 == 0) {
        return power(num * num, p / 2);
    } else {
        return num * power(num * num, (p - 1) / 2);
    }
}

int eval(const int cellVal) { return power(10, cellVal); }


// Evaluation:
int Field::evaluate() const
{
    typedef std::array<size_t, 4> PlDirCount;
    const size_t                  west       = 0;
    const size_t                  north_west = 1;
    const size_t                  north      = 2;
    const size_t                  north_east = 3;

    const size_t east       = 0;
    const size_t south_east = 1;
    const size_t south      = 2;
    const size_t south_west = 3;

    size_t size = _field_data.size();

    // std::vector<std::vector<int>> evalTag;
    int finalVal = 0;

    std::vector<std::vector<PlDirCount>> oRowCount(
        size, std::vector<PlDirCount>(size));
    std::vector<std::vector<PlDirCount>> xRowCount(
        size, std::vector<PlDirCount>(size));

    for (size_t x = 0; x < size; ++x) {
        for (size_t y = 0; y < size; ++y) {
            bool canGoEast      = x < size - 1;
            bool canGoSouth     = y < size - 1;
            bool canGoSouthEast = canGoEast && canGoSouth;
            bool canGoSouthWest = x > 0 && canGoSouth;
            // int &cell           = evalTag[x][y];
            // cell                = 0;
            // #ugly:
            if (_field_data[x][y] == Player::PLAYER_O) {
                if (canGoEast) {
                    oRowCount[x + 1][y][west] = oRowCount[x][y][west] + 1;
                    // cell += eval(oRowCount[x][y][west]);
                    finalVal += eval(oRowCount[x][y][west]);
                }
                if (canGoSouthEast) {
                    oRowCount[x + 1][y + 1][north_west] =
                        oRowCount[x][y][north_west] + 1;
                    finalVal += eval(oRowCount[x][y][north_west]);
                }
                if (canGoSouth) {
                    oRowCount[x][y + 1][north] = oRowCount[x][y][north] + 1;
                    finalVal += eval(oRowCount[x][y][north]);
                }
                if (canGoSouthWest) {
                    oRowCount[x - 1][y + 1][north_east] =
                        oRowCount[x][y][north_east] + 1;
                    finalVal += eval(oRowCount[x][y][north_east]);
                }
            } else if (_field_data[x][y] == Player::PLAYER_X) {
                if (canGoEast) {
                    xRowCount[x + 1][y][west] = xRowCount[x][y][west] + 1;
                    finalVal -= eval(xRowCount[x][y][west]);
                }
                if (canGoSouthEast) {
                    xRowCount[x + 1][y + 1][north_west] =
                        xRowCount[x][y][north_west] + 1;
                    finalVal -= eval(xRowCount[x][y][north_west]);
                }
                if (canGoSouth) {
                    xRowCount[x][y + 1][north] = xRowCount[x][y][north] + 1;
                    finalVal -= eval(xRowCount[x][y][north]);
                }
                if (canGoSouthWest) {
                    xRowCount[x - 1][y + 1][north_east] =
                        xRowCount[x][y][north_east] + 1;
                    finalVal -= eval(xRowCount[x][y][north_east]);
                }
            }
        }
    }

    for (size_t xx = size; xx > 0; --xx) {
        const size_t x = xx - 1;
        for (size_t yy = size; yy > 0; --yy) {
            const size_t y              = yy - 1;
            bool         canGoWest      = x > 0;
            bool         canGoNorth     = y > 0;
            bool         canGoNorthWest = canGoWest && canGoNorth;
            bool         canGoNorthEast = x < size - 1 && canGoNorth;
            // #ugly:
            if (_field_data[x][y] == Player::PLAYER_O) {
                if (canGoWest) {
                    oRowCount[x - 1][y][east] = oRowCount[x][y][east] + 1;
                    // cell += eval(oRowCount[x][y][west]);
                    finalVal += eval(oRowCount[x][y][east]);
                }
                if (canGoNorthWest) {
                    oRowCount[x - 1][y - 1][south_east] =
                        oRowCount[x][y][south_east] + 1;
                    finalVal += eval(oRowCount[x][y][south_east]);
                }
                if (canGoNorth) {
                    oRowCount[x][y - 1][south] = oRowCount[x][y][south] + 1;
                    finalVal += eval(oRowCount[x][y][south]);
                }
                if (canGoNorthEast) {
                    oRowCount[x + 1][y - 1][south_west] =
                        oRowCount[x][y][south_west] + 1;
                    finalVal += eval(oRowCount[x][y][south_west]);
                }
            } else if (_field_data[x][y] == Player::PLAYER_X) {
                if (canGoWest) {
                    xRowCount[x - 1][y][east] = xRowCount[x][y][east] + 1;
                    // cell += eval(xRowCount[x][y][west]);
                    finalVal -= eval(xRowCount[x][y][east]);
                }
                if (canGoNorthWest) {
                    xRowCount[x - 1][y - 1][south_east] =
                        xRowCount[x][y][south_east] + 1;
                    finalVal -= eval(xRowCount[x][y][south_east]);
                }
                if (canGoNorth) {
                    xRowCount[x][y - 1][south] = xRowCount[x][y][south] + 1;
                    finalVal -= eval(xRowCount[x][y][south]);
                }
                if (canGoNorthEast) {
                    xRowCount[x + 1][y - 1][south_west] =
                        xRowCount[x][y][south_west] + 1;
                    finalVal -= eval(xRowCount[x][y][south_west]);
                }
            }
        }
    }

    switch (_winner) {
    case Field::Player::PLAYER_O:
        finalVal += eval(_expected_length + 1);
        break;
    case Field::Player::PLAYER_X:
        finalVal -= eval(_expected_length + 1);
        break;
    default:
        finalVal += 0;
    }

    return finalVal;
}



// Now comes the ugly part... (And no, I won't reformat this, it should be
// fast and unreadable :)))
size_t countHorizontally(std::vector<std::vector<Field::Player>> &fieldData,
                         const Field::Player nextLvlPlayer, const size_t x,
                         const size_t y)
{
    const size_t fieldSize = fieldData.size();
    size_t       horCount  = 1;
    for (size_t i = x; i > 0; --i) {
        if (fieldData[i - 1][y] == nextLvlPlayer) {
            ++horCount;
        } else {
            break;
        }
    }
    for (size_t i = x + 1; i < fieldSize; ++i) {
        if (fieldData[i][y] == nextLvlPlayer) {
            ++horCount;
        } else {
            break;
        }
    }

    return horCount;
}


size_t countVertically(std::vector<std::vector<Field::Player>> &fieldData,
                       const Field::Player nextLvlPlayer, const size_t x,
                       const size_t y)
{
    const size_t fieldSize = fieldData.size();
    size_t       verCount  = 1;
    for (size_t i = y; i > 0; --i) {
        if (fieldData[x][i - 1] == nextLvlPlayer) {
            ++verCount;
        } else {
            break;
        }
    }
    for (size_t i = y + 1; i < fieldSize; ++i) {
        if (fieldData[x][i] == nextLvlPlayer) {
            ++verCount;
        } else {
            break;
        }
    }

    return verCount;
}


size_t countDiagonally0(std::vector<std::vector<Field::Player>> &fieldData,
                        const Field::Player nextLvlPlayer, const size_t x,
                        const size_t y)
{
    const size_t fieldSize  = fieldData.size();
    size_t       diag0Count = 1;
    for (size_t i = x, j = y; i > 0 && j > 0; --i, --j) {
        if (fieldData[i - 1][j - 1] == nextLvlPlayer) {
            ++diag0Count;
        } else {
            break;
        }
    }
    for (size_t i = x + 1, j = y + 1; i < fieldSize && j < fieldSize;
         ++i, ++j) {
        if (fieldData[i][j] == nextLvlPlayer) {
            ++diag0Count;
        } else {
            break;
        }
    }

    return diag0Count;
}


size_t countDiagonally1(std::vector<std::vector<Field::Player>> &fieldData,
                        const Field::Player nextLvlPlayer, const size_t x,
                        const size_t y)
{
    const size_t fieldSize  = fieldData.size();
    size_t       diag1Count = 1;
    for (size_t i = x, j = y + 1; i > 0 && j < fieldSize; --i, ++j) {
        if (fieldData[i - 1][j] == nextLvlPlayer) {
            ++diag1Count;
        } else {
            break;
        }
    }
    for (size_t i = x + 1, j = y; i < fieldSize && j > 0; ++i, --j) {
        if (fieldData[i][j - 1] == nextLvlPlayer) {
            ++diag1Count;
        } else {
            break;
        }
    }

    return diag1Count;
}


// Field iterator:
Field Field::FieldBuilderIterator::buildField() const
{
    Field::Player nextLvlPlayer = Field::Player::PLAYER_O;
    if (_field._player == Field::Player::PLAYER_O) {
        nextLvlPlayer = Field::Player::PLAYER_X;
    }

    // Check winner:
    if (countHorizontally(_field._field_data, nextLvlPlayer, _x, _y) >=
            _field._expected_length ||
        countVertically(_field._field_data, nextLvlPlayer, _x, _y) >=
            _field._expected_length ||
        countDiagonally0(_field._field_data, nextLvlPlayer, _x, _y) >=
            _field._expected_length ||
        countDiagonally1(_field._field_data, nextLvlPlayer, _x, _y) >=
            _field._expected_length) {
        Field temp(_field, nextLvlPlayer);
        temp.setPlayer(_x, _y);

        return temp;
    } else {
        Field temp(_field, Field::Player::EMPTY);
        temp.setPlayer(_x, _y);
        return temp;
    }
}


std::vector<Field> Field::getNewLevel()
{
    std::vector<Field> result;
    for (auto builder = begin(); builder < end(); ++builder) {
        result.push_back(builder.buildField());
    }

    return result;
}


// Iterators:
Field::FieldBuilderIterator Field::begin()
{
    if (_winner != Field::Player::EMPTY) {
        return Field::FieldBuilderIterator(*this, _field_data.size());
    } else {
        return Field::FieldBuilderIterator(*this);
    }
}

Field::FieldBuilderIterator Field::end()
{
    return Field::FieldBuilderIterator(*this, _field_data.size());
}



Field::Player Field::getWinner() const { return _winner; }



size_t Field::findSelected(const size_t x, const size_t y) const
{
    size_t fieldSize = _field_data.size();
    size_t count     = 1;

    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < fieldSize; ++j) {
            if (_field_data[i][j] == Field::Player::EMPTY) {
                ++count;
            }
        }
    }

    for (size_t j = 0; j < y; ++j) {
        if (_field_data[x][j] == Field::Player::EMPTY) {
            ++count;
        }
    }

    return count;
}


bool Field::full() const
{
    size_t fieldSize = _field_data.size();
    return _placed_down >= (fieldSize * fieldSize);
}
