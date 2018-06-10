#ifndef TEST02_DEPENDENCY_INVERSION_H
#define TEST02_DEPENDENCY_INVERSION_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Person {
public:
    Person(std::string&& name, int age)
        : name(std::move(name))
        , age{ age }
    {
    }

public:
    std::string name;
    int         age;
};


enum class RelationShip { parent,
                          child,
                          sibbling };


class RelationshipBrowser {
public:
    virtual vector<Person> get_all_children_by_name(string name) const = 0;
};


class RelationshipStorage : public RelationshipBrowser {
public:
    using RelationshipDefinition = tuple<Person, RelationShip, Person>;
    vector<RelationshipDefinition> relations;

    void add_relationship(Person person1, RelationShip relationship, Person person2)
    {
        relations.emplace_back(RelationshipDefinition(person1, relationship, person2));
    }

    vector<Person> get_all_children_by_name(string name) const override
    {
        vector<Person> result;
        for (auto& rel : relations) {
            if (get<0>(rel).name == name && get<1>(rel) == RelationShip::parent) {
                result.push_back(get<2>(rel));
            }
        }
        return result;
    }
};

class RelationshipResearcher {
public:
    explicit RelationshipResearcher(const RelationshipStorage& relationshipStorage)
        : relationshipStorage_(relationshipStorage)
    {
    }
    const RelationshipStorage& relationshipStorage_;

    vector<Person> get_all_children_by_name(string name)
    {
        return relationshipStorage_.get_all_children_by_name(name);
    }
};


void dependency_inversion()
{

    Person parent{ "Udo", 42 };
    Person child1{ "Elisa", 3 };
    Person child2{ "Isabella", 0 };

    RelationshipStorage rs;
    rs.add_relationship(parent, RelationShip::parent, child1);
    rs.add_relationship(parent, RelationShip::parent, child2);

    rs.add_relationship(child1, RelationShip::sibbling, child2);
    rs.add_relationship(child2, RelationShip::sibbling, child1);

    std::cout << parent.name << " is " << parent.age << " years old."
              << std::endl;

    auto children = rs.get_all_children_by_name("Udo");

    for (auto& child : children) {
        std::cout << "Udo has a child with the name: " << child.name << "\n";
    }
}


#endif //TEST02_DEPENDENCY_INVERSION_H
