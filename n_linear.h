#ifndef TEST02_N_LINEAR_H
#define TEST02_N_LINEAR_H

//This kata generalizes Twice Linear. You may want to attempt that kata first.
//Sequence
//
//        Consider an integer sequence U(m) defined as:
//
//m is a given non-empty set of positive integers.
//U(m)[0] = 1, the first number is always 1.
//For each x in U(m), and each y in m, x * y + 1 must also be in U(m).
//No other numbers are in U(m).
//U(m) is sorted, with no duplicates.
//
//Sequence Examples
//U(2, 3) = [1, 3, 4, 7, 9, 10, 13, 15, 19, 21, 22, 27, ...]
//
//1 produces 3 and 4, since 1 * 2 + 1 = 3, and 1 * 3 + 1 = 4.
//
//3 produces 7 and 10, since 3 * 2 + 1 = 7, and 3 * 3 + 1 = 10.
//U(5, 7, 8) = [1, 6, 8, 9, 31, 41, 43, 46, 49, 57, 64, 65, 73, 156, 206, ...]
//
//1 produces 6, 8, and 9.
//
//6 produces 31, 43, and 49.
//Task:
//
//Implement n_linear or nLinear: given a set of postive integers m, and an index n, find U(m)[n], the nth value in the U(m) sequence.
//Tips
//
//        Tests use large n. Slow algorithms may time-out.
//Tests use large m. Algorithms which multiply further than neccessary may overflow.
//Linear run time and memory usage is possible.
//How can you build the sequence iteratively, without growing extra data structures?


#include <cmath>
#include <cstdint>
#include <iostream>
#include <set>
#include <zconf.h>

uint32_t n_linear(const std::set<uint32_t>& m, size_t n)
{
    std::set<uint64_t> result;
    result.insert(1);

    for (auto x_it = result.cbegin(); x_it != result.cend(); ++x_it) {
        //    for (const auto x : result) {
        for (const auto y : m) {
            //            result.insert(x * y + 1);
            //            std::cout << x << " * " << y << " + 1 == " << x * y + 1 << std::endl;
            result.insert(*x_it * y + 1);
            //            std::cout << *x_it << " * " << y << " + 1 == " << *x_it * y + 1 << std::endl;
        }
        if (result.size() > n * (1 + std::log(n))) {
            break;
        }
    }

    auto it = result.cbegin();
    it      = std::next(it, n);

    return static_cast<uint32_t>(*it);
}

void do_n_linear()
{
    //    std::cout << "206 == " << n_linear({ 5, 7, 8 }, 14) << "?\n";
    std::cout << "3172655773 == " << n_linear({ 10, 13 }, 741) << "?" << std::endl;
    //    std::cout << "22 == " << n_linear({ 2, 3 }, 10) << "?\n";
    //    std::cout << "22 == " << n_linear({ 3, 2 }, 10) << "?\n";
    //    std::cout << "64 == " << n_linear({ 5, 7, 8 }, 10) << "?\n";
    //    std::cout << "65 == " << n_linear({ 5, 7, 8 }, 11) << "?\n";
}

#endif //TEST02_N_LINEAR_H
