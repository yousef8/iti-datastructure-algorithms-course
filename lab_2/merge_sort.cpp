#include <iostream>

using namespace std;

void merge(int arr[], int start, int mid, int end)
{
  int left_size = mid - start + 1;
  int left_arr[left_size]{};

  int right_size = end - mid;
  int right_arr[right_size]{};

  // copy the left array
  for (int i{0}; i < left_size; ++i)
  {
    left_arr[i] = arr[start + i];
  }

  // copy the right array
  for (int i{0}; i < right_size; ++i)
  {
    right_arr[i] = arr[mid + 1 + i];
  }

  int left_idx{0}, right_idx{0}, merge_idx{start};
  while (left_idx < left_size && right_idx < right_size)
  {

    if (left_arr[left_idx] < right_arr[right_idx])
    {
      arr[merge_idx++] = left_arr[left_idx++];
    }
    else
    {
      arr[merge_idx++] = right_arr[right_idx++];
    }
  }

  while (left_idx < left_size)
  {
    arr[merge_idx++] = left_arr[left_idx++];
  }

  while (right_idx < right_size)
  {
    arr[merge_idx++] = right_arr[right_idx++];
  }
}

void merge_sort(int arr[], int start, int end)
{
  if (start < end)
  {
    int mid = (start + end) / 2;
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, start, mid, end);
  }
}

int main()
{
  int arr[] = {67, 92, 12, 99, 13, 2};

  merge_sort(arr, 0, 5);

  for (auto &e : arr)
  {
    cout << e << " ";
  }
  cout << "\n";
  return 0;
}
