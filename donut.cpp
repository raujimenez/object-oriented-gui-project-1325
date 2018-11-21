#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling) : Product(name, price, cost), _frosting{frosting}, _sprinkles{sprinkles}, _filling{filling} {}

Frosting Donut::frosting() { return _frosting; }
bool Donut::sprinkles() { return _sprinkles; }
Filling Donut::filling() { return _filling; }

std::string Donut::to_string()
{
    std::string frosting_string; //get string for frosting
    switch (frosting())
    {
    case (Frosting::Unfrosted):
        frosting_string = "Unfrosted";
        break;
    case (Frosting::Chocolate_top):
        frosting_string = "Chocolate top";
        break;
    case (Frosting::Vanilla_top):
        frosting_string = "Vanilla top";
        break;
    case (Frosting::Pink_top):
        frosting_string = "Pink top";
        break;
    }

    std::string sprinkle_string; //get string for sprinkle
    if (sprinkles())
        sprinkle_string = "With";
    else
        sprinkle_string = "Without";

    std::string filling_string; //get string for filling
    switch (filling())
    {
    case (Filling::Unfilled):
        filling_string = "Unfilled";
        break;
    case (Filling::Creme):
        filling_string = "Creme";
        break;
    case (Filling::Bavarian):
        filling_string = "Bavarian";
        break;
    case (Filling::Strawberry):
        filling_string = "Strawberry";
        break;
    }
    return name() + " $" + std::to_string(price()) + " $" + std::to_string(cost()) + ", Sprinkles: " + sprinkle_string + ", Filling: " + filling_string + ", Frosting: " + frosting_string;
}
