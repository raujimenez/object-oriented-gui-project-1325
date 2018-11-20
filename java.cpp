#include "java.h"

Java::Java(std::string name, double price, double cost, int darkness) : Product(name, price, cost), _darkness{darkness} { _shots.push_back(Shot::None); }

int Java::darkness() { return _darkness; }
std::vector<Shot> Java::shots() { return _shots; }

void Java::add_shot(Shot shot) { _shots.push_back(shot); }

std::string Java::to_string()
{
    std::string darkness_string;
    switch (_darkness)
    {
    case (1):
        darkness_string = "Blonde";
        break;
    case (2):
        darkness_string = "Light";
        break;
    case (3):
        darkness_string = "Medium";
        break;
    case (4):
        darkness_string = "Dark";
        break;
    case (5):
        darkness_string = "Extra Dark";
        break;
    default:
        darkness_string = "Extra Dark";
        break;
    }
    std::string shots_string;
    std::vector<int> shot_quantity{0, 0, 0, 0, 0}; //count how many of each shots are inputted
    for (int i{0}; i < _shots.size(); ++i)
    {
        switch (_shots[i])
        {
        case (Shot::None):
            shot_quantity[0] += 1;
            break;
        case (Shot::Chocolate):
            shot_quantity[1] += 1;
            break;
        case (Shot::Vanilla):
            shot_quantity[2] += 1;
            break;
        case (Shot::Peppermint):
            shot_quantity[3] += 1;
            break;
        case (Shot::Hazelnut):
            shot_quantity[4] += 1;
            break;
        }
    }
    shots_string = "None = " + std::to_string(shot_quantity[0]) +
                   "\n\t\t    Chocolate = " + std::to_string(shot_quantity[1]) +
                   "\n\t\t    Vanilla = " + std::to_string(shot_quantity[2]) +
                   "\n\t\t    Peppermint = " + std::to_string(shot_quantity[3]) +
                   "\n\t\t    Hazelnut = " + std::to_string(shot_quantity[4]);

    return _name + " $" + std::to_string(_price) + " $" + std::to_string(_cost) +
           "\n\tDarkeness: " + darkness_string +
           "\n\tShots: " + shots_string;
}
