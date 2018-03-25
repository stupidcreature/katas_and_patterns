#ifndef TEST02_FIBONACCI_TRIBONACCI_AND_FRIENDS_H
#define TEST02_FIBONACCI_TRIBONACCI_AND_FRIENDS_H

//If you have completed the Tribonacci sequence kata, you would know by now that mister Fibonacci has at least a bigger brother. If not, give it a quick look to get how things work.
//
//Well, time to expand the family a little more: think of a Quadribonacci starting with a signature of 4 elements and each following element is the sum of the 4 previous, a Pentabonacci
//(well Cinquebonacci would probably sound a bit more italian, but it would also sound really awful) with a signature of 5 elements and each following element is the sum of the 5 previous, and so on.
//
//Well, guess what? You have to build a Xbonacci function that takes a signature of X elements - and remember each next element is the sum of the last X elements - and returns the first n elements of the so seeded sequence.
//
//xbonacci {1,1,1,1} 10 = {1,1,1,1,4,7,13,25,49,94}
//xbonacci {0,0,0,0,1} 10 = {0,0,0,0,1,1,2,4,8,16}
//xbonacci {1,0,0,0,0,0,1} 10 = {1,0,0,0,0,0,1,2,3,6}
//xbonacci {1,1} produces the Fibonacci sequence


#include <numeric>

std::vector<int> xbonacci(std::vector<int> signature, int n)
{
    std::vector<int> ret = signature;

    if (signature.empty()) {
        throw std::runtime_error("invalid input to funtion xbonacci");
    }

    if (n < signature.size()) {
        ret.resize(n);
        return ret;
    }

    int skip = 0;
    while (n-- > signature.size()) {
        ret.emplace_back(std::accumulate(ret.begin() + skip++, ret.end(), 0));
    }

    return ret;
}

void fibonacci_tribonacci_and_friends()
{
    auto r1 = xbonacci({ 1, 1, 1, 1 }, 10);          // {1,1,1,1,4,7,13,25,49,94}
    auto r2 = xbonacci({ 0, 0, 0, 0, 1 }, 10);       // {0,0,0,0,1,1,2,4,8,16}
    auto r3 = xbonacci({ 1, 0, 0, 0, 0, 0, 1 }, 10); // {1,0,0,0,0,0,1,2,3,6}
    auto r4 = xbonacci({ 1, 1 }, 10);                // produces the Fibonacci sequence

    for (auto i : r4)
        std::cout << i << " ";
    std::cout << std::endl;
}

#endif //TEST02_FIBONACCI_TRIBONACCI_AND_FRIENDS_H
