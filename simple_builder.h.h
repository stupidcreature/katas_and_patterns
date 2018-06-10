#ifndef TEST02_SIMPLE_BUILDER_H_H
#define TEST02_SIMPLE_BUILDER_H_H

#include <ostream>
#include <string>
#include <tuple>
#include <vector>

class CodeBuilder {
    std::string                                       class_name_;
    std::vector<std::tuple<std::string, std::string>> elements;


public:
    CodeBuilder(const std::string& class_name)
    {
        class_name_ = class_name;
    }

    CodeBuilder& add_field(const std::string& name, const std::string& type)
    {
        elements.emplace_back(std::make_tuple(name, type));
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj)
    {
        os << "class " << obj.class_name_ << "\n{\n";
        for (const auto& t : obj.elements) {
            os << "  " << get<1>(t) << " " << get<0>(t) << ";\n";
        }
        return os << "};";
    }
};

void simple_builder()
{
    auto cb = CodeBuilder{ "Person" }.add_field("name", "string").add_field("age", "int");
    std::cout << cb;
}

#endif //TEST02_SIMPLE_BUILDER_H_H
