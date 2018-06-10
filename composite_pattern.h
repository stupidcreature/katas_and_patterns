#ifndef TEST02_CRTP_H
#define TEST02_CRTP_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ContainsIntegers {
    virtual int* begin() = 0;
    virtual int* end()   = 0;
};

struct SingleValue : ContainsIntegers {
    int value{ 0 };

    SingleValue() = default;

    int* begin() override
    {
        return &value;
    }

    int* end() override
    {
        return &value + 1;
    }

    explicit SingleValue(const int value)
        : value{ value }
    {
    }
};


struct ManyValues : vector<int>, ContainsIntegers {
    void add(const int value)
    {
        push_back(value);
    }

    int* begin() override
    {
        return &this->at(0);
    }

    int* end() override
    {
        return &this->at(size() - 1) + 1;
    }
};


int sum(const vector<ContainsIntegers*> items)
{
    int sum = 0;
    for (const auto& item : items) {
        for (const auto value : *item) {
            sum += value;
        }
    }

    return sum;
}


void composite_pattern()
{
    SingleValue sv{ 1 };
    ManyValues  mv;
    mv.add(2);
    mv.add(3);

    cout << sum({ &sv, &mv }) << '\n';
}

#endif //TEST02_CRTP_H
