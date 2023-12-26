#include <bits/stdc++.h>
using namespace std;
class Observer;
class Observable
{
public:
    virtual void Register(Observer *observer) = 0;
    virtual void Unregister(Observer *observer) = 0;
    virtual void notify() = 0;
    virtual void setData(int cnt) = 0;
    virtual int getData() = 0;
};
class Observer
{
public:
    virtual void update(Observable *Observable) = 0;
};
class ConcreteObservable : public Observable
{

    unordered_set<Observer *> observerList;

public:
    int cnt = 0;

    void Register(Observer *observer)
    {
        observerList.insert(observer);
    }
    void Unregister(Observer *observer)
    {
        observerList.erase(observer);
    }

    void notify()
    {
        for (auto o : observerList)
        {
            o->update(this);
        }
    }

    void setData(int cnt)
    {
        if (this->cnt == 0)
        {
            notify();
        }
        this->cnt += cnt;
    }

    int getData()
    {
        return this->cnt;
    }
};
class ObserverA : public Observer
{
public:
    void update(Observable *obj)
    {
        cout << "ObserverA is updated : " << obj->getData() << endl;
    }
};

class ObserverB : public Observer
{
public:
    void update(Observable *obj)
    {
        cout << "ObserverB is updated : " << obj->getData() << endl;
    }
};
int main()
{

    ConcreteObservable observable;

    ObserverA A;
    ObserverB B;
    observable.Register(&A);
    observable.Register(&B);
    observable.setData(1);
    return 0;
}