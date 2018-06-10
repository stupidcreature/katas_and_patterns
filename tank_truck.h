#ifndef TEST02_TANK_TRUCK_H
#define TEST02_TANK_TRUCK_H

//To introduce the problem think to my neighbor who drives a tanker truck. The level indicator is down and he is worried
// because he does not know if he will be able to make deliveries. We put the truck on a horizontal ground and measured
// the height of the liquid in the tank.
//
//Fortunately the tank is a perfect cylinder and the vertical walls on each end are flat. The height of the remaining
// liquid is h, the diameter of the cylinder is d, the total volume is vt (h, d, vt are positive or null integers).
// You can assume that h <= d.
//
//Could you calculate the remaining volume of the liquid? Your function tankvol(h, d, vt) returns an integer which
// which is the truncated result (e.g floor) of your float calculation.

// https://de.wikipedia.org/wiki/Kreissegment

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


class VolTank {
public:
    static int tankVol(int h, int d, int vt)
    {
        const auto diameter     = static_cast<double>(d);
        const auto radius       = diameter / 2.0;
        const auto volume_total = static_cast<double>(vt);
        const auto height       = static_cast<double>(h);

        const double length = volume_total / (M_PI / 4.0 * diameter * diameter);
        const double alpha  = 2.0 * std::acos(1.0 - height / radius);
        const double area   = (radius * radius / 2.0) * (alpha - std::sin(alpha));

        return static_cast<int>(std::floor(area * length));
    }
};

void dotest(int h, int d, int vt, int expected)
{
    std::cout << "h=" << h << " d=" << d << " vt=" << vt << " Result=" << VolTank::tankVol(h, d, vt) << " expected to be: " << expected << std::endl;
};

void tank_truck()
{
    dotest(5, 7, 3848, 2940);
    dotest(2, 7, 3848, 907);
    dotest(2, 8, 5026, 982);
    dotest(4, 9, 6361, 2731);
}

#endif //TEST02_TANK_TRUCK_H
