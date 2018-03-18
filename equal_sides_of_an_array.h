#ifndef TEST02_EQUAL_SIDES_OF_AN_ARRAY_H
#define TEST02_EQUAL_SIDES_OF_AN_ARRAY_H


#include <algorithm>
#include <vector>

using namespace std;

int get_left_sum(const vector<int>& vector, size_t index)
{
    int sum = 0;
    for_each(vector.begin(), vector.begin() + index, [&sum](int elem) { sum += elem; });
    return sum;
}

int get_right_sum(const vector<int>& vector, size_t index)
{
    int sum = 0;
    for_each(vector.begin() + index + 1, vector.end(), [&sum](int elem) { sum += elem; });
    return sum;
}


//Kata: https://www.codewars.com/kata/equal-sides-of-an-array/train/cpp
int find_even_index(const vector<int>& numbers)
{

    //the naive solution
    for (size_t index = 0; index <= numbers.size() - 1; ++index) {
        if (get_left_sum(numbers, index) == get_right_sum(numbers, index)) {
            return index;
        }
    }

    return -1;
}


#endif //TEST02_EQUAL_SIDES_OF_AN_ARRAY_H
