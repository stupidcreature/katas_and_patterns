#ifndef TEST02_OPEN_CLOSED_H
#define TEST02_OPEN_CLOSED_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

enum class Color { white,
                   red,
                   blue,
                   yellow,
                   green,
                   black };

enum class Size { tiny,
                  small,
                  medium,
                  large,
                  huge };


struct Product {
    string name;
    Color  color;
    Size   size;
};


template <typename T>
class AndSpecification;

template <typename T>
struct Specification {
    virtual bool is_satisfied(T* product) = 0;

    // optional: define an operator && to return a AndSpecification without the need of
    // manually constructing one by hand
    AndSpecification<T> operator&&(Specification<T>&& other)
    {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T>
struct Filter {
    virtual vector<T*> filter(vector<T*>, Specification<T>& spec) = 0;
};

struct ColorSpecification : Specification<Product> {
    Color color;

    explicit ColorSpecification(Color color)
        : color(color)
    {
    }

    bool is_satisfied(Product* product) override
    {
        return product->color == color;
    }
};


struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(Size size)
        : size(size)
    {
    }

    bool is_satisfied(Product* product) override
    {
        return product->size == size;
    }
};


template <typename T>
struct AndSpecification : Specification<T> {
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second)
        : first(first)
        , second(second)
    {
    }

    bool is_satisfied(T* product) override
    {
        return first.is_satisfied(product) && second.is_satisfied(product);
    }
};

struct BetterFilter : Filter<Product> {
    vector<Product*> filter(vector<Product*> products, Specification<Product>& spec) override
    {
        vector<Product*> result;
        for (auto& p : products) {
            if (spec.is_satisfied(p))
                result.emplace_back(p);
        }
        return result;
    }
};


void open_closed()
{
    Product ProductStorage[] = {
        Product{ "Apple", Color::green, Size::small },
        Product{ "House", Color::white, Size::large },
        Product{ "Frog", Color::green, Size::small },
        Product{ "Meadow", Color::green, Size::large }
    };

    vector<Product*> products;

    for (auto& p : ProductStorage) {
        products.push_back(&p);
    }


    ColorSpecification spec_green(Color::green);
    SizeSpecification  spec_large(Size::large);


    BetterFilter bf;
    for (auto& p : bf.filter(products, spec_green)) {
        cout << p->name << " is green.\n";
    }
    for (auto& p : bf.filter(products, spec_large)) {
        cout << p->name << " is large.\n";
    }

    AndSpecification<Product> green_and_large(spec_green, spec_large);
    for (auto& p : bf.filter(products, green_and_large)) {
        cout << p->name << " is green AND large.\n";
    }


    // using the custom operator one can write this a little bit more compact
    auto combined_spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);
    for (auto& p : bf.filter(products, combined_spec)) {
        cout << p->name << " is green AND large.\n";
    }
}


#endif //TEST02_OPEN_CLOSED_H
