#ifndef TEST02_TWICE_LINEAR_H
#define TEST02_TWICE_LINEAR_H

//Consider a sequence u where u is defined as follows:
//
//The number u(0) = 1 is the first one in u.
//For each x in u, then y = 2 * x + 1 and z = 3 * x + 1 must be in u too.
//There are no other numbers in u.
//
//Ex: u = [1, 3, 4, 7, 9, 10, 13, 15, 19, 21, 22, 27, ...]
//
//1 gives 3 and 4, then 3 gives 7 and 10, 4 gives 9 and 13, then 7 gives 15 and 22 and so on...
//
//#Task: Given parameter n the function dbl_linear (or dblLinear...) returns the element u(n) of the ordered (with <) sequence u.
//
//#Example: dbl_linear(10) should return 22
//
//#Note: Focus attention on efficiency


#include <set>

class DoubleLinear {
public:
    static int dblLinear(int n);
};

int DoubleLinear::dblLinear(int n)
{
    std::set<int> result;

    auto y = [](int x) { return 2 * x + 1; };
    auto z = [](int x) { return 3 * x + 1; };

    result.insert(1);

    for (const auto val : result) {
        result.insert(y(val));
        result.insert(z(val));
        if (result.size() > 2 * static_cast<std::size_t>(n)) {
            break;
        }
    }

    auto it = result.cbegin();
    it      = std::next(it, n);

    return *it;
}


void dotest(int n, int expected)
{
    std::cout << DoubleLinear::dblLinear(n) << " == " << expected << "?\n";
}


void twice_linear()
{
    dotest(10, 22);
    dotest(20, 57);
    dotest(30, 91);
    dotest(50, 175);
}

#endif //TEST02_TWICE_LINEAR_H
