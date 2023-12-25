#include <iostream>

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void int_selec_sort(int arr[], int size) {
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

  int arr[] = {92, 99, 67, 12};

  int_selec_sort(arr, 4);

  for( int& e : arr ){
    std::cout << e << ", ";
  }
  std::cout << "\n";
  return 0;
}
