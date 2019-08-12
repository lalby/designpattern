#include <iostream>
#include<vector>

using namespace std;

class Employee
{
    public:
    int age;
    double salary;
    
    Employee(int a,double sa): age(a),salary(sa){}
    
    void display()
    {
        std::cout<<age<<salary;
    }
};

template <typename T>
class specification 
{   public:
    virtual bool is_satisfied(T*)=0;
};

template <typename T>
class Filter
{   public:
    virtual vector<T*> filter(vector<T*>,
                               specification<T> &)=0;
};

class BetterFilter: public Filter<Employee >
{
   public:
   vector<Employee *> filter(vector<Employee*> e,specification<Employee> &spec) override
   {
       vector<Employee*> temp;
       for(auto &e1:e)
       {
           if(spec.is_satisfied(e1))
           temp.push_back(e1);
       }
       return temp;
   }
};

class agespecification: public specification<Employee>
{ public:
  int age;
  agespecification(int a):age(a){}
  
  bool is_satisfied(Employee *e) override
 {
    return (e->age==age);
 }   
};


int main()
{
    vector<Employee*> ev;
    Employee e(20,34568);
    ev.push_back(&e);
    Employee e1(30,6789);
    ev.push_back(&e1);
    agespecification  age(30);
    BetterFilter bf;
    
    vector<Employee*> t1;
    t1=bf.filter(ev,age);
    
    for(auto x: t1)
    x->display();
    
    
}