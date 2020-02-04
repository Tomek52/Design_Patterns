#include <iostream>
#include <memory>

struct Address
{
    std::string street, city;
    int suite;

    Address (std::string street, std::string city, int suite)
        : street(street)
        , city(city)
        , suite(suite)
    {}

    Address (const Address& address)
        : street(address.street)
        , city(address.city)
        , suite(address.suite)
    {}

    friend std::ostream& operator << (std::ostream &os, const Address& address)
    {
        os << address.street << " " << address.city << " " << address.suite << std::endl;
    }
};

struct Contact
{
    std::string name;
    std::unique_ptr<Address> address;

    Contact(const std::string& name, std::unique_ptr<Address> address)
        : name(name)
        , address(std::move(address))
    {}

    Contact(const Contact& contact)
        : name(contact.name)
        , address(std::make_unique<Address>(contact.address->street, contact.address->city, contact.address->suite))
       {}

    static Contact getPrototype()
    {
        auto address =  std::make_unique<Address>("Legnicka 30", "Wroclaw", 100);
        return {"", std::move(address)};
    }

    friend std::ostream& operator << (std::ostream &os, const Contact& contact)
    {
        os <<"name: " << contact.name << ", address: " << *contact.address;
    }
};

int main()
{
    Contact john = Contact::getPrototype();
    john.name = "John Smith";
    std::cout<< john;
    return 0;
}
