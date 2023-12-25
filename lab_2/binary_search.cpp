#include <iostream>

using namespace std;

int binary_search(int arr[], int size, int value_to_find)
{
  int start{0}, end{size - 1};

  while (start <= end)
  {
    int mid = (start + end) / 2;

    if (arr[mid] == value_to_find)
    {
      return mid;
    }

    if (value_to_find < arr[mid])
    {
      end = mid - 1;
    }
    else
    {
      start = mid + 1;
    }
  }

  return -1;
}

int main()
{
  int arr[]{2, 12, 13, 67, 92, 99};

  int data = 13;

  int idx = binary_search(arr, 6, data);

  if (idx == -1)
  {
    cout << "Didn't find anything\n";
  }
  else
  {
    cout << "Found [" << data << "] at idx [" << idx << "]\n";
  }
}