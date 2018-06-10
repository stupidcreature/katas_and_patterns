#ifndef TEST02_FUTURES_AND_PROMISES_H
#define TEST02_FUTURES_AND_PROMISES_H

#include <future>
#include <iostream>

//from: https://www.youtube.com/watch?v=QIHy8pXbneI @approx. 50min
//#include <experimental/future>
//template <typename T>
//auto split(std::future<T>& x)
//{
//    auto            tmp = std::move(x);
//    std::promise<T> p;
//    x = p.get_future();
//
//    // mutable: allows body to modify the parameters captured by copy, and to call their non-const member functions
//    //capture with initializer list, see: http://en.cppreference.com/w/cpp/language/lambda and https://stackoverflow.com/questions/36188694/lambda-capture-to-use-the-initializer-or-not-to-use-it
//    return tmp.then([_p = std::move(p)](auto _tmp) mutable {
//
//        //split exception
//        if (_tmp.has_exception()) {
//            auto error = _tmp.get_exception_ptr();
//            _p.set_exception(error);
//            std::rethrow_exception(error);
//        }
//
//        auto value = _tmp.get();
//        _p.set_value(value);
//        return value;
//    });
//}

void futures_and_promises()
{
    std::promise<int> p;
    auto              f = p.get_future();

    p.set_value(42);
    std::cout << f.get() << std::endl;
}

#endif //TEST02_FUTURES_AND_PROMISES_H
