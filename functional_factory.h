#ifndef TEST02_FUNCTIONAL_FACTORY_H
#define TEST02_FUNCTIONAL_FACTORY_H

#include <functional>
#include <iostream>
#include <map>
#include <memory>

class ProductBase {
protected:
    std::string type;
    std::string product_name;

public:
    friend std::ostream& operator<<(std::ostream& os, const ProductBase& base)
    {
        os << "type: " << base.type << " product_name: " << base.product_name;
        return os;
    }
    virtual std::unique_ptr<ProductBase> make(const std::string& name) = 0;
    virtual ~ProductBase()                                             = default;
};

class Product1 : public ProductBase {

public:
    //    Product1(){};
    std::unique_ptr<ProductBase> make(const std::string& name) override
    {
        auto p          = std::make_unique<Product1>();
        p->type         = "Product 1";
        p->product_name = name;
        return p;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product1& product)
    {
        os << static_cast<const ProductBase&>(product);
        return os;
    }
};

class Product2 : public ProductBase {

public:
    //    Product2() {}
    std::unique_ptr<ProductBase> make(const std::string& name) override
    {
        auto p          = std::make_unique<Product2>();
        p->type         = "Product 2";
        p->product_name = name;
        return p;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product2& product)
    {
        os << static_cast<const ProductBase&>(product);
        return os;
    }
};


enum class product_types { product1,
                           product2 };


class ProductFactory {
};


class FunctionalProductFactory {
    std::map<product_types, std::function<std::unique_ptr<ProductBase>()>> factories;

public:
    FunctionalProductFactory()
    {
        factories[product_types::product1] = [] {
            return Product1::make("product1");
        };
        factories[product_types::product2] = [] {
            auto p = std::make_unique<Product2>();
            return Product2::make("product2");
        };
    }
    std::unique_ptr<ProductBase> make_product(const product_types type)
    {
        return factories[type]();
    }
};

void functional_factory()
{
    FunctionalProductFactory pf;
    auto                     product = pf.make_product(product_types::product1);
    std::string              n       = product->product_name;
    std::string              t       = product->type;
    std::cout << *product.get();
}

#endif //TEST02_FUNCTIONAL_FACTORY_H
