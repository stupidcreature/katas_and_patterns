#ifndef TEST02_SORT_THE_ODD_H
#define TEST02_SORT_THE_ODD_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>


//You have an array of numbers.
//Your task is to sort ascending odd numbers but even numbers must be on their places.
//
//Zero isn't an odd number and you don't need to move it. If you have an empty array, you need to return it.
//
//Example
//
//        sortArray([5, 3, 2, 8, 1, 4]) == [1, 3, 2, 8, 5, 4]

class Kata {
public:
    std::vector<int> sortArray(std::vector<int> array)
    {
        std::deque<int> odd_array;
        for (auto i : array) {
            if (i % 2) {
                odd_array.push_back(i);
            }
        }

        if (odd_array.empty())
            return array;

        std::sort(odd_array.begin(), odd_array.end());

        for (auto& i : array) {
            if (i % 2) {
                i = odd_array[0];
                odd_array.pop_front();
            }
        }

        return array;
    }
};


void sort_the_odd()
{
    std::vector<int> sortArray{ 5, 3, 2, 8, 1, 4 };
    Kata             kata;
    auto             sortedArray = kata.sortArray(sortArray);

    for (auto i : sortedArray)
        std::cout << i << " ";
    std::cout << std::endl;
}

#endif //TEST02_SORT_THE_ODD_H
