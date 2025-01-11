#include <bits/stdc++.h>
using namespace std;

// proxy design pattern is used as mediator between client and server
// use case :
// 1. Web caching
// 2. Logging request
// 3. Access control
// 4. Load balancing

class Person
{
public:
    virtual void getData(string client) = 0;
    virtual void addData(string client) = 0;
    virtual void deleteData(string client) = 0;
};
class Employee : public Person
{
public:
    void getData(string client)
    {
        cout << "Employee data" << endl;
    }
    void addData(string client)
    {
        cout << "Employee data added" << endl;
    }
    void deleteData(string client)
    {
        cout << "Employee data deleted" << endl;
    }
};
class EmployeeProxy : public Person
{
public:
    Employee *employee;
    EmployeeProxy()
    {
        employee = new Employee();
    }
    void getData(string client)
    {
        employee->getData(client);
    }
    void addData(string client)
    {
        if (client == "user")
            throw "Access Denied";
        employee->addData(client);
    }
    void deleteData(string client)
    {
        if (client == "user")
            throw "Access Denied";
        employee->deleteData(client);
    }
};
int main()
{
    EmployeeProxy *employeeProxy = new EmployeeProxy();
    employeeProxy->getData("admin");
    employeeProxy->addData("admin");
    employeeProxy->deleteData("admin");
    employeeProxy->getData("user");
    employeeProxy->addData("user");
    employeeProxy->deleteData("user");
    return 0;
}
