#include <iostream>

#include <calc/minMaxTreeNode.hpp>
#include <game/field.hpp>

#include <game/local.hpp>
#include <game/netPlay.hpp>


void menu()
{
    bool playing = true;
    while (playing) {
        int selection;
        std::cout << " >>> Amoba <<< \n";
        std::cout << "[1] Play against `X`\n";
        std::cout << "[2] Play against `O`\n";
        std::cout << "[3] Listen for incoming game requests\n";
        std::cout << "[4] Try to connect to enemy\n";
        std::cout << "[0] Exit\n";
        std::cout << "Selection> ";
        std::cin >> selection;
        switch (selection) {
        case 1:
            playLocal(Field::Player::PLAYER_X);
            break;
        case 2:
            playLocal(Field::Player::PLAYER_O);
            break;
        case 3:
            listenForEnemy();
            break;
        case 4:
            connectToEnemy();
            break;
        case 0:
            std::cout << "Exiting...\n";
            playing = false;
            break;
        default:
            std::cout << "Invalid command, try again!\n";
        }

        std::cout << '\n';
    }
}


int main() { menu(); }
