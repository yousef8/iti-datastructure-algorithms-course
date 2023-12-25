#include <iostream>
#include <string>

class Employee {
public:
  Employee(std::string name, int salary): name{name}, salary{salary}, id{id_generator++}
  {
  }

  friend bool operator < (const Employee& emp1, const Employee& emp2);
  friend std::ostream& operator << (std::ostream& out, Employee& emp );


private:
  int static id_generator;
  std::string name;
  int salary;
  int id;
};
int Employee::id_generator = 0;

bool operator < (const Employee& emp1, const Employee& emp2) {
  return emp1.id < emp2.id;
}

std::ostream& operator << (std::ostream& out, Employee& emp) {
  out << emp.id << ": My name is " << emp.name << " and i get paid " << emp.salary << std::endl;
  return out;
}

class Compare {
  public:
    virtual bool cmp(const Employee& a, const Employee& b)  = 0;
};

class Desc: public Compare {
  public:
    bool cmp(const Employee& a, const Employee& b) override {
      return !(a < b);
    }
};

class Asc: public Compare {
  public:
    bool cmp(const Employee& a, const Employee& b) override {
      return (a < b);
    }

};

template<typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

void bubble_sort(Employee arr[], int size, Compare* cmp) {
  for (int i {0}; i < size -1; ++i){
    for (int j {0}; j < size -1 - i; ++j){
      if (cmp->cmp(arr[j+1], arr[j]) ){
        swap(arr[j], arr[j+1]);
      }
    }
  }
}

int main() {
  Employee emp1 = Employee("yousef", 22000);
  Employee emp2 = Employee("omar", 33000);
  Employee emp3 = Employee("omar", 33000);
  Employee emp4 = Employee("omar", 33000);
  Employee emp5 = Employee("omar", 33000);
  Employee emp6 = Employee("omar", 33000);

  Employee arr[] = {emp5, emp4, emp6, emp3, emp2, emp1};

  std::cout << "Before Sorting : \n";
  for(Employee &  e : arr){
    std::cout << e;
  }
  
  Compare* cmp = new Desc;
  bubble_sort(arr, 6, cmp);


  std::cout << "After Sorting : \n";
  for(Employee &  e : arr){
    std::cout << e;
  }

  return 0;
}
