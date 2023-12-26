// Strategy interface
#include <bits/stdc++.h>
using namespace std;

class Strategy
{
public:
    virtual void Algorithm() = 0;
};

// Concrete strategies
class ConcreteStrategyA : public Strategy
{
public:
    void Algorithm()
    {
        cout << "Strategt A" << endl;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    void Algorithm()
    {
        cout << "Strategt B" << endl;
    }
};

// Context
class Context
{
private:
    Strategy *strategy_;

public:
    Context(Strategy *strategy) : strategy_(strategy) {}

    void SetStrategy(Strategy *strategy)
    {
        strategy_ = strategy;
    }
    void Execute()
    {
        strategy_->Algorithm();
    }
};

int main()
{
    // Create a context and pass it a concrete strategy
    Context context(new ConcreteStrategyA());
    context.Execute();

    // Change the strategy and execute the algorithm again
    context.SetStrategy(new ConcreteStrategyB());
    context.Execute();

    return 0;
}