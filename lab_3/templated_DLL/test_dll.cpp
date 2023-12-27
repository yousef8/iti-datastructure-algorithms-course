#include <iostream>
#include <string>
#include "dll.hpp"

template <typename T>
void test_deletion(DLL<T> dll)
{
  std::cout << "\n-------------Deletion Feature------------------\n";
  std::cout << "Original DLL : \n";
  dll.display();
  std::cout << std::endl;

  // Test Delete Feature
  // Delete Middle
  std::cout << "Delete Middle Element : \n";
  dll.erase("omar");
  dll.display();
  std::cout << std::endl;

  // Delete Head
  std::cout << "Delete Head Element : \n";
  dll.erase("yousef");
  dll.display();
  std::cout << std::endl;

  // Delete Tail
  std::cout << "Delete Tail Element : \n";
  dll.erase("muhammed");
  dll.display();
  std::cout << std::endl;

  return;
}

template <typename T>
void test_insert_after(DLL<T> dll)
{
  std::cout << "\n----------------Test Insertion After Value--------------------\n";
  std::cout << "Current DLL : ";
  dll.display();

  std::cout << "\nInsert after head: \n";
  dll.insert_after("yousef", "mahmoud");
  dll.display();

  std::cout << "\nInsert after tail: \n";
  dll.insert_after("muhammed", "mazen");
  dll.display();

  std::cout << "\nInsert in middle: \n";
  dll.insert_after("mahmoud", "fathi");
  dll.display();
  std::cout << std::endl;

  return;
}

template <typename T>
void test_insert_idx(DLL<T> dll)
{
  std::cout << "\n----------------Test Insertion @ idx-------------------\n";
  std::cout << "Current DLL : ";
  dll.display();
  std::cout << std::endl;

  std::cout << "Insert @ head : \n";
  dll.insert_at_idx(0, "sayed");
  dll.display();
  std::cout << std::endl;

  std::cout << "Insert @ tail : \n";
  dll.insert_at_idx(3, "mazen");
  dll.display();
  std::cout << std::endl;

  std::cout << "Insert @ middle (e.g. 3) : \n";
  dll.insert_at_idx(3, "mahmoud");
  dll.display();
  std::cout << std::endl;

  return;
}

template <typename T>
void test_reverse(DLL<T> dll)
{
  std::cout << "\n---------------------Test Reverse Feature---------------------------\n";
  std::cout << "Current DLL : ";
  dll.display();
  std::cout << std::endl;

  dll.reverse();
  std::cout << "DLL Reversed : ";
  dll.display();
  std::cout << std::endl;
}

template<typename T>
void test_delete_back(DLL<T> dll){
  std::cout << "\n-------------Deletion From End Feature------------------\n";
  std::cout << "Original DLL : \n";
  dll.display();
  std::cout << std::endl;

  // Test Delete Feature
  // Delete Middle
  std::cout << "Delete Tail: \n";
  T res = dll.delete_back();
  std::cout << "You just deleted " << res << "\n";
  dll.display();
  std::cout << std::endl;

  // Delete Head
  std::cout << "Delete Tail: \n";
  res = dll.delete_back();
  std::cout << "You just deleted " << res << "\n";
  dll.display();
  std::cout << std::endl;

  // Delete Tail
  std::cout << "Delete Tail: \n";
  res = dll.delete_back();
  std::cout << "You just deleted " << res << "\n";
  dll.display();
  std::cout << std::endl;

  return;

}

int main()
{

  // Test Add, Display, and Constructor feature
  std::cout << "\n------------------------Create DLL && Add elements-------------------\n";
  DLL<std::string> dll{"yousef", "omar", "muhammed"};
  dll.display();

  // Test copy Costructor
  std::cout
      << "\n---------------------------Copy DLL------------------------------\n";
  DLL<std::string> dllCpy{dll};
  std::cout << "Copied DLL : \n";
  dllCpy.display();

  // Test Search feature
  std::cout << "\n---------------------Search Feature-----------------\n";
  const Node<std::string> *res = dll.search("yousef");
  if (!res)
  {
    std::cout << "Didn't find anything\n";
  }
  else
  {
    std::cout << "Found a node with value " << res->data << std::endl;
  }
  std::cout << std::endl;

  test_deletion(dll);

  test_insert_after(dll);

  test_insert_idx(dll);

  test_reverse(dll);

  test_delete_back(dll);
  return 0;
}
