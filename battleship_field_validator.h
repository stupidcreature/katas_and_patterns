#ifndef TEST02_BATTLESHIP_FIELD_VALIDATOR_H
#define TEST02_BATTLESHIP_FIELD_VALIDATOR_H

//https://www.codewars.com/kata/battleship-field-validator/train/cpp
//Write a method that takes a field for well-known board game "Battleship" as an argument and returns true if it has a valid disposition of ships, false otherwise. Argument is guaranteed to be 10*10 two-dimension array. Elements in the array are numbers, 0 if the cell is free and 1 if occupied by ship.
//
//Battleship (also Battleships or Sea Battle) is a guessing game for two players. Each player has a 10x10 grid containing several "ships" and objective is to destroy enemy's forces by targetting individual cells on his field. The ship occupies one or more cells in the grid. Size and number of ships may differ from version to version. In this kata we will use Soviet/Russian version of the game.
//
//Before the game begins, players set up the board and place the ships accordingly to the following rules:
//
//There must be single battleship (size of 4 cells), 2 cruisers (size 3), 3 destroyers (size 2) and 4 submarines (size 1). Any additional ships are not allowed, as well as missing ships.
//
//Each ship must be a straight line, except for submarines, which are just single cell.
//
//The ship cannot overlap or be in contact with any other ship, neither by edge nor by corner.


#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>
#include <vector>


using namespace std;
using field_t = vector<vector<int>>;


class ShipPool {
public:
    ShipPool()
    {
        ship_pool_[0] = 4;
        ship_pool_[1] = 3;
        ship_pool_[2] = 2;
        ship_pool_[3] = 1;
    }

    std::vector<int> GetValidShipSizesWithMaxSize(std::size_t max_ship_size) const
    {
        std::vector<int> ret;
        for (std::size_t i = 0; i < std::min(MAX_SHIP_SIZE, max_ship_size); ++i) {
            if (0 < ship_pool_[i]) {
                ret.push_back(i + 1);
            }
        }
        return ret;
    }

    bool PopShipWithSize(std::size_t ship_size)
    {
        if (ship_size > MAX_SHIP_SIZE || 0 == ship_size) {
            return false;
        }
        if (0 < ship_pool_[ship_size - 1]) {
            --ship_pool_[ship_size - 1];
            return true;
        }
        return false;
    }

private:
    static constexpr std::size_t           MAX_SHIP_SIZE = 4;
    std::array<std::size_t, MAX_SHIP_SIZE> ship_pool_;
};
constexpr std::size_t ShipPool::MAX_SHIP_SIZE;

class Ocean {
public:
    explicit Ocean(field_t&& field)
        : ocean_(std::move(field))
    {
    }

    bool IsFieldOccupied(const std::size_t x, const std::size_t y) const
    {
        return ocean_[x][y] != 0;
    }

    std::size_t GetMaxShipSizeAt(std::size_t x, std::size_t y, const bool is_horizontal) const
    {
        std::size_t max_size = 0;

        while (x < FIELD_SIZE && y < FIELD_SIZE && IsFieldOccupied(x, y)) {
            max_size++;
            if (is_horizontal) {
                ++x;
            } else {
                ++y;
            }
        }
        return max_size;
    }

    bool PlaceShipAt(std::size_t x, std::size_t y, const bool is_horizontal, std::size_t ship_size)
    {
        // no error checking for now
        setShipState(x, y, is_horizontal, ship_size, 0);
        return true;
    }

    void setShipState(size_t x, size_t y, const bool is_horizontal, size_t ship_size, int state)
    {
        while (0 < ship_size) {
            ocean_[x][y] = state;
            if (is_horizontal) {
                ++x;
            } else {
                ++y;
            }
            --ship_size;
        }
    }

    bool AssertNoShipInNeighbouringFields(std::size_t x_, std::size_t y_, const std::size_t ship_size, const bool is_horizontal) const
    {
        const auto x = static_cast<int>(x_);
        const auto y = static_cast<int>(y_);

        std::vector<std::tuple<const int, const int>> fields_to_check;
        if (is_horizontal) {
            fields_to_check.emplace_back(std::make_tuple(x - 1, y));
            fields_to_check.emplace_back(std::make_tuple(x - 1, y - 1));
            fields_to_check.emplace_back(std::make_tuple(x - 1, y + 1));
            fields_to_check.emplace_back(std::make_tuple(x + ship_size, y + 1));
            fields_to_check.emplace_back(std::make_tuple(x + ship_size, y + 1));
            fields_to_check.emplace_back(std::make_tuple(x + ship_size, y + 1));
            for (std::size_t i = x; i < x + ship_size; ++i) {
                fields_to_check.emplace_back(std::make_tuple(x, y - 1));
                fields_to_check.emplace_back(std::make_tuple(x, y + 1));
            }
        } else {
            fields_to_check.emplace_back(std::make_tuple(x + 1, y - 1));
            fields_to_check.emplace_back(std::make_tuple(x, y - 1));
            fields_to_check.emplace_back(std::make_tuple(x - 1, y - 1));
            fields_to_check.emplace_back(std::make_tuple(x + 1, y + ship_size));
            fields_to_check.emplace_back(std::make_tuple(x, y + ship_size));
            fields_to_check.emplace_back(std::make_tuple(x - 1, y + ship_size));
            for (std::size_t i = x; i < x + ship_size; ++i) {
                fields_to_check.emplace_back(std::make_tuple(x - 1, y));
                fields_to_check.emplace_back(std::make_tuple(x + 1, y));
            }
        }
        return std::all_of(fields_to_check.cbegin(), fields_to_check.cend(), [this](const auto& fields) { return this->VerifyFieldUnoccupiedOrOutOfBounds(std::get<0>(fields), std::get<1>(fields)); });
    }

    static const std::size_t FIELD_SIZE = 10;

private:
    bool VerifyFieldUnoccupiedOrOutOfBounds(int x, int y) const
    {
        if (x < 0 || x >= static_cast<int>(FIELD_SIZE) || y < 0 || y >= static_cast<int>(FIELD_SIZE)) {
            return true;
        }
        return ocean_[x][y] == 0;
    }

    vector<vector<int>> ocean_;
};

struct BattleshipRulesValidater {
    static bool deep_validation(std::size_t x, std::size_t y, Ocean& ocean, ShipPool& ship_pool)
    {

        while (true) {
            //if end of playing field and no more ships in ship pool
            //if there are still ships to place the given placement is not valid
            if (y == Ocean::FIELD_SIZE) {
                bool testval = ship_pool.GetValidShipSizesWithMaxSize(4).empty();
                return testval;
            }

            //first try to place the ships horizontally
            if (ocean.IsFieldOccupied(x, y)) {
                auto max_ship_size_at_position_horizontal = ocean.GetMaxShipSizeAt(x, y, true);
                auto max_ship_size_at_position_vertical   = ocean.GetMaxShipSizeAt(x, y, false);
                auto is_horizontal                        = false;
                auto max_ship_size                        = max_ship_size_at_position_vertical;
                if (max_ship_size_at_position_horizontal >= max_ship_size_at_position_vertical) {
                    is_horizontal = true;
                    max_ship_size = max_ship_size_at_position_horizontal;
                }

                //no valid ship to place available in pool
                auto ships_to_place = ship_pool.GetValidShipSizesWithMaxSize(max_ship_size);
                if (ships_to_place.empty()) {
                    std::cout << "no more ships in pool to place at: " << x << " " << y << std::endl;
                    return false;
                }

                auto ship_size = std::max_element(ships_to_place.cbegin(), ships_to_place.cend());
                ship_pool.PopShipWithSize(*ship_size);

                if (!ocean.AssertNoShipInNeighbouringFields(x, y, *ship_size, is_horizontal)) {
                    std::cout << "ship cannot be placed placed at x=" << x << ", y=" << y << " size="
                              << *ship_size << " " << (is_horizontal ? "horizontally" : "vertically")
                              << " as there is a violation of rules concerning unoccupied neighbouring fields."
                              << std::endl;
                    return false;
                }

                ocean.PlaceShipAt(x, y, is_horizontal, *ship_size);
                if (deep_validation(x, y, ocean, ship_pool)) {
                    std::cout << "ship placed at x=" << x << ", y=" << y << " size=" << *ship_size << " "
                              << (is_horizontal ? "horizontally" : "vertically") << std::endl;
                    return true;
                } else {
                    return false;
                }
            }

            ++x;
            if (x >= Ocean::FIELD_SIZE) {
                x = 0;
                ++y;
            }
        }
    }

    static bool ValidateRules(const Ocean& ocean)
    {
        ShipPool ship_pool;
        Ocean    ocean_state = ocean;

        return deep_validation(0, 0, ocean_state, ship_pool);
    }
};

bool validate_battlefield(vector<vector<int>> field)
{
    Ocean ocean(std::forward<field_t>(field));

    return BattleshipRulesValidater::ValidateRules(ocean);
}


#include "igloo/igloo.h"
#include "igloo/igloo_alt.h"
using namespace igloo;

void battleship_field_validator()
{
    //    Describe(your_validate_battlefield_function){
    //        It(should_work_for_a_sample_test_case){
    //            Assert::That(validate_battlefield(vector<vector<int>>{
    //                             vector<int>{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
    //                             vector<int>{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
    //                             vector<int>{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 0 },
    //                             vector<int>{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    //                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    //                             vector<int>{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
    //                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    //                             vector<int>{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    //                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    //                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }),
    //                         Equals(true));
    //}
    //}
    //;

    Describe(your_validate_battlefield_function){
        It(should_work_for_a_sample_test_case){
            Assert::That(validate_battlefield(vector<vector<int>>{
                             vector<int>{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
                             vector<int>{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
                             vector<int>{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 0 },
                             vector<int>{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
                             vector<int>{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
                             vector<int>{ 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
                             vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }),

                         Equals(true));
}
}
;
TestRunner::RunAllTests(0, nullptr);
}
#endif //TEST02_BATTLESHIP_FIELD_VALIDATOR_H
