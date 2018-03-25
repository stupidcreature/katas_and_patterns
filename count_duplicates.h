#ifndef TEST02_COUNT_DUPLICATES_H
#define TEST02_COUNT_DUPLICATES_H

//Count the number of Duplicates
//
//        Write a function that will return the count of distinct case-insensitive alphabetic characters and numeric digits that occur more than once in the input string. The input string can be assumed to contain only alphabets (both uppercase and lowercase) and numeric digits.
//Example
//
//"abcde" -> 0 # no characters repeats more than once
//"aabbcde" -> 2 # 'a' and 'b'
//"aabBcde" -> 2 # 'a' occurs twice and 'b' twice (bandB)
//"indivisibility" -> 1 # 'i' occurs six times
//"Indivisibilities" -> 2 # 'i' occurs seven times and 's' occurs twice
//"aA11" -> 2 # 'a' and '1'
//"ABBA" -> 2 # 'A' and 'B' each occur twice


#include <algorithm>
#include <map>

size_t duplicateCount(const std::string& in); // helper for tests

size_t duplicateCount(const char* in)
{
    std::string            input{ in };
    std::map<char, size_t> count_map;
    for (const char c : input) {
        count_map[tolower(c)]++;
    }
    return std::count_if(count_map.begin(), count_map.end(), [](const auto& x) { return x.second > 1; });
}


void count_duplicates()
{
    cout << duplicateCount("aabbcde");
}

#endif //TEST02_COUNT_DUPLICATES_H
