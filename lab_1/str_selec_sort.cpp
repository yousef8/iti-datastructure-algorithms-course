#include <iostream>
#include <string>

void swap(std::string &a, std::string &b) {
  std::string tmp = a;
  a = b;
  b = tmp;
}

void str_selec_sort( std::string arr[], int size) {
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

  std::string arr[] = {"yousef", "omar", "muhamed", "fathi", "ahmed"};

  str_selec_sort(arr, 5);

  for( auto & e : arr ){
    std::cout << e << ", ";
  }
  std::cout << "\n";
  return 0;
}
