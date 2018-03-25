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

        long double t = static_cast<long double>(g) / (static_cast<long double>(v2) - static_cast<long double>(v1));

        long double hours   = std::floor(t);
        long double minutes = std::floor(60.0 * (t - hours));
        long double seconds = std::floor(3600.1 * (t - hours - minutes / 60.0));

        auto hours_i   = static_cast<int>(hours);
        auto minutes_i = static_cast<int>(minutes);
        auto seconds_i = static_cast<int>(seconds);

        return { hours_i, minutes_i, seconds_i };
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
