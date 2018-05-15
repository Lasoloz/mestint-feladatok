#include <game/local.hpp>

void playLocal(Field::Player aiPlayer)
{
    // Read field size:
    size_t fieldSize;
    std::cout << "Select field size> ";
    std::cin >> fieldSize;

    if (fieldSize < 3) {
        std::cerr << "Sorry, field must be at least 3 in size!\n";
        return;
    }
    if (fieldSize > 20) {
        std::cerr << "Sorry, field sizes above 20 are too big for this "
                     "application!\n";
        return;
    }

    size_t needed;
    std::cout << "Select how many should be in a row for the winner> ";
    std::cin >> needed;

    if (needed > fieldSize) {
        std::cerr << "Needed count should be less than field size!\n";
        return;
    }

    // Create variables:
    bool playerTurn;

    if (aiPlayer == Field::Player::PLAYER_O) {
        playerTurn = false;
    } else {
        playerTurn = true;
    }

    MinMaxTreeNode<Field> fieldTree(Field(fieldSize, needed, aiPlayer), 0);
    // Select correct depth:
    size_t depth;
    if (fieldSize < 4) {
        depth = 6;
    } else if (fieldSize < 5) {
        depth = 5;
    } else {
        depth = 4;
    }

    // Prevalidate in case of user:
    fieldTree.validate(1);

    size_t currentDepth = depth;

    fieldTree.getNodeVal().printIt(std::cout);

    // Play game:
    while (fieldTree.getNodeVal().getWinner() == Field::Player::EMPTY &&
           !fieldTree.getNodeVal().full()) {
        Field &field = fieldTree.getNodeVal();
        size_t chosen;
        if (playerTurn) {
            // Get coordinates:
            size_t x, y;
            std::cout << "  x coordinate> ";
            std::cin >> x;
            std::cout << "  y coordinate> ";
            std::cin >> y;

            if (x >= field.size() || y >= field.size()) {
                std::cout << "Try again, your coordinates are too big!\n";
                continue;
            }

            if (field.getPlayer(x, y) != Field::Player::EMPTY) {
                std::cout << "Try again, cell already occupied!\n";
                continue;
            }

            chosen = field.findSelected(x, y);
        } else {
            // Validate for ai:
            std::cout << "Computer is thinking...\n";
            chosen = fieldTree.validate_start(currentDepth);
            if (chosen == 0) {
                field.printIt(std::cout);
                break;
            }
            std::cout << "Computer's answer:\n";
        }

        fieldTree.cutTowardChild(chosen - 1);
        field.printIt(std::cout);

        ++currentDepth;
        playerTurn = !playerTurn;
    }

    switch (fieldTree.getNodeVal().getWinner()) {
    case Field::Player::PLAYER_O:
        std::cout << "Winner is player O!\n";
        break;
    case Field::Player::PLAYER_X:
        std::cout << "Winner is player X!\n";
        break;
    default:
        std::cout << "Draw!\n";
    }
}
