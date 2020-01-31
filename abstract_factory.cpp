#include <iostream>
#include <memory>
#include <map>

struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) const = 0;
};

struct Tea : HotDrink
{
    void prepare(int volume) const override
    {
        std::cout << "Take tea bag, boil water, pour "
                  << volume
                  << " ml, add some sugar or lemon.\n";
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) const override
    {
        std::cout << "Grind beans, boil water, pour "
                  << volume
                  << " ml, add some sugar or milk.\n";
    }
};

struct HotDrinkFactory
{
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFacory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Coffee>();
    }
};

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hotDrinkFactories;
public:
    DrinkFactory()
    {
        hotDrinkFactories["tea"] = std::make_unique<TeaFacory>();
        hotDrinkFactories["coffee"] = std::make_unique<CoffeeFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name, int volume)
    {
        auto drink = hotDrinkFactories.at(name) -> make();
        drink -> prepare(volume);
        return drink;
    }
};

int main()
{
    DrinkFactory drinkFactory;
    auto tea350 = drinkFactory.make_drink("tea", 350);
    auto tea350 = drinkFactory.make_drink("tea", 350);
    auto tea350 = drinkFactory.make_drink("tea", 350);

    return 0;
}
