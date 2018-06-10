#ifndef TEST02_SIMPLE_FACTORY_H
#define TEST02_SIMPLE_FACTORY_H

#include <ostream>
#include <string>

using namespace std;

struct PersonFromFactory {
    int    id;
    string name;

    friend ostream& operator<<(ostream& os, const PersonFromFactory& person)
    {
        os << "id: " << person.id << " name: " << person.name;
        return os;
    }

    friend class PersonFactory;
};

class PersonFactory {
public:
    PersonFromFactory create_person(const string& name)
    {
        static int        id;
        PersonFromFactory p;
        p.name = name;
        p.id   = id++;
        return std::move(p);
    }
};


void simple_factory()
{
    PersonFactory pf;
    auto          p = pf.create_person("name");
    std::cout << p;
}

#endif //TEST02_SIMPLE_FACTORY_H
