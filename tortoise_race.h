#ifndef TEST02_TORTOISE_RACE_H
#define TEST02_TORTOISE_RACE_H

//Two tortoises named A and B must run a race. A starts with an average speed of 720 feet per hour.
//Young B knows she runs faster than A, and furthermore has not finished her cabbage.
//
//When she starts, at last, she can see that A has a 70 feet lead but B's speed is 850 feet per hour.
//How long will it take B to catch A?
//
//More generally: given two speeds v1 (A's speed, integer > 0) and v2 (B's speed, integer > 0)
//and a lead g (integer > 0) how long will it take B to catch A?
//
//The result will be an array [hour, min, sec] which is the time needed in hours,
//minutes and seconds (don't worry for fractions of second).
//
//If v1 >= v2 then return nil, nothing, null, None or {-1, -1, -1} for C++, C, Go, Nim, [] for Kotlin.
//
//Examples:
//  race(720, 850, 70) => [0, 32, 18]
//  race(80, 91, 37)   => [3, 21, 49]

#include <cmath>

class Tortoise {
public:
    static std::vector<int> race(int v1, int v2, int g)
    {
        // s1 = v1 * t + g
        // s2 = v2 * t
        // Condition: s1 == s2
        // v1 * t + g == v2 * t
        // v1 + g / t == v2
        // t  = g / (v2 - v1)

        float dummy = 16777216;
        float delta = 0.1;
        while (dummy < 16777217) {
            dummy += delta;
        }

        if (v2 <= v1) {
            return { -1, -1, -1 };
        }

        double t = 1.0 * g / (v2 - v1);

        auto hours   = static_cast<int>(std::floor(t));
        auto minutes = static_cast<int>(std::floor(60.0 * (t - std::floor(t))));
        auto seconds = static_cast<int>(std::floor(3600.0 * (t - 1.0 * hours - 1.0 * minutes / 60.0)));
        if (seconds == 60) {
            seconds = 0;
            minutes += 1;
        }
        if (minutes == 60) {
            minutes = 0;
            hours += 1;
        }

        return { hours, minutes, seconds };
    }
};

std::ostream& operator<<(std::ostream& stream, const std::vector<int>& vec)
{
    stream << '{';
    for (const auto i : vec) {
        stream << ' ' << i;
    }
    stream << " }";

    return stream;
}

void tortoise_race()
{
    std::cout << Tortoise::race(720, 850, 70) << '\n';    //{0, 32, 18}
    std::cout << Tortoise::race(820, 81, 550) << '\n';    //{-1, -1, -1}
    std::cout << Tortoise::race(80, 91, 37) << std::endl; //{3, 21, 49}
}
#endif //TEST02_TORTOISE_RACE_H
