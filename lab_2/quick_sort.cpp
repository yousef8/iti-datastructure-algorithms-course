#include <iostream>

int partition(int arr[], int lb, int ub)
{
  int start_idx = lb;
  int end_idx = ub;
  int pivot_idx = start_idx;

  while (start_idx < end_idx)
  {
    while (arr[start_idx] <= arr[pivot_idx])
    {
      ++start_idx;
    }

    while (arr[end_idx] > arr[pivot_idx])
    {
      --end_idx;
    }

    if (start_idx < end_idx)
    {
      std::swap(arr[start_idx], arr[end_idx]);
    }
  }

  std::swap(arr[pivot_idx], arr[end_idx]);
  return end_idx;
}

void quick_sort(int arr[], int lb, int ub)
{
  if (lb < ub)
  {
    int pivot_idx = partition(arr, lb, ub);
    quick_sort(arr, lb, pivot_idx - 1);
    quick_sort(arr, pivot_idx + 1, ub);
  }
}

int main()
{
  int arr[] = {67, 92, 67, 12, 99, 13, 2};

  std::cout << "Before Sorting : ";
  for (auto &e : arr)
  {
    std::cout << e << ", ";
  }
  std::cout << "\n";

  quick_sort(arr, 0, 6);

  std::cout << "After Sorting: ";
  for (auto &e : arr)
  {
    std::cout << e << ", ";
  }
  std::cout << "\n";
  std::cout << "Hello World\n";
  return 0;
}
