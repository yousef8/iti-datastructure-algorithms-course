#include <iostream>
#include <string>

template<typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template<typename T>
void selec_sort( T arr[], int size) {
  for (int i = 0; i < size -1; i++){
    int min_index = i;

    for (int j = i+1; j < size; j++){
      if (arr[j] < arr[min_index]){
        min_index = j;
      }
    }

    swap(arr[i], arr[min_index]);
  }
}

int main() {

  std::cout << "---------------Testing Templated Selection Sort------------------\n";

  std::cout << "-------------Integer Array-----------------------\n";
  int int_arr[] = {92, 99, 67, 12};
  std::cout << "Before Sort : ";
  for( int& e : int_arr ){
    std::cout << e << ", ";
  }
  std::cout << std::endl;

  selec_sort(int_arr, 4);

  std::cout << "After Sort : ";
  for( int& e : int_arr ){
    std::cout << e << ", ";
  }
  std::cout << "\n";

  std::cout << "--------------String Array------------------\n";
  std::string str_arr[] = {"yousef", "omar", "muhamed", "fathi", "ahmed", "Ahmed"};

  std::cout << "Before Sort : ";
  for( auto & e : str_arr ){
    std::cout << e << ", ";
  }
  std::cout << "\n";


  selec_sort(str_arr, 5);

  std::cout << "After Sort : ";
  for( auto & e : str_arr ){
    std::cout << e << ", ";
  }
  std::cout << "\n";

  return 0;
}
