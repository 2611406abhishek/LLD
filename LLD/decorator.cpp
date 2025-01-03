#include <bits/stdc++.h>
using namespace std;
class BasePizza
{
public:
    virtual int cost() = 0;
};
class Cheese : public BasePizza
{
public:
    int cost()
    {
        return 100;
    }
};
class Margrhita : public BasePizza
{
public:
    int cost()
    {
        return 150;
    }
};
class ToppingDecorator : public BasePizza
{
public:
    virtual int cost() = 0;
};
class ExtraCheese : public ToppingDecorator
{
    BasePizza *pizza_;

public:
    ExtraCheese(BasePizza *pizza)
    {
        pizza_ = pizza;
    }
    int cost()
    {
        return pizza_->cost() + 10;
    }
};
class Mushroom : public ToppingDecorator
{
    BasePizza *pizza_;

public:
    Mushroom(BasePizza *pizza)
    {
        pizza_ = pizza;
    }
    int cost()
    {
        return pizza_->cost() + 20;
    }
};
int main()
{

    // create a cheese pizza
    BasePizza *cheesePizza = new Cheese();
    cout << "print simple cheese pizza cost " << cheesePizza->cost() << endl;

    // creata cheese pizza with extra cheese
    ExtraCheese *extraCheesePizza = new ExtraCheese(cheesePizza);
    cout << "print cheese pizza cost with extra cheese " << extraCheesePizza->cost() << endl;

    // create a cheese pizza with extra cheese and extra mushroom
    Mushroom *extraMushroomCheesePizza = new Mushroom(extraCheesePizza);
    cout << " print cheese pizza cost with extra cheese and mushroom" << extraMushroomCheesePizza->cost() << endl;

    // create a marghita pizza
    Margrhita *margrhita = new Margrhita();
    cout << "print margarhita pizza cost" << margrhita->cost() << endl;

    // margarhita pizza with extra mushroom
    Mushroom *margrhitaWithExtraMushroom = new Mushroom(margrhita);
    cout << "print margarhita with extra mushroom topings " << margrhitaWithExtraMushroom->cost() << endl;
}