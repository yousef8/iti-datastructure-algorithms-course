#include <iostream>

using namespace std;

int sentinel_linear_search(int arr[], int size, int value_to_find)
{
  int last = arr[size - 1];
  arr[size - 1] = value_to_find;

  int idx{0};
  for (; arr[idx] != value_to_find; ++idx)
    ;

  arr[size - 1] = last;

  if ((idx < size - 1) || (arr[size - 1] == value_to_find))
  {
    return idx;
  }

  return -1;
}

int main()
{
  int arr[]{67, 92, 12, 13, 99, 2};

  int data = 13;

  int idx = sentinel_linear_search(arr, 6, data);

  if (idx == -1)
  {
    cout << "Didn't find anything\n";
  }
  else
  {
    cout << "Found [" << data << "] at idx [" << idx << "]\n";
  }

  return 0;
}