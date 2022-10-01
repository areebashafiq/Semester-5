// Abdul Saboor
// 20L-1113
// BDS-5A
// Homework-2 header file

// ----------------------------------------------------------------------------------------------------

/*
Code taken from following source:
https://www.geeksforgeeks.org/merge-sort/

All comments are removed and modifications where made are listed in comment.
*/

#include<iostream>
#include<cstdlib>
#include<chrono>
using namespace std;

int mergecount = 0;

void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne], * rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++) rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		mergecount++; // incrementing count on comparison
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne)
	{
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

// ----------------------------------------------------------------------------------------------------

/*
Code taken from following source:
https://www.geeksforgeeks.org/heap-sort/

All comments are removed and modifications where made are listed in comment.
*/

int heapcount = 0; // counting swaps

void heapify(int arr[], int N, int i)
{

	int largest = i;

	int l = 2 * i + 1;

	int r = 2 * i + 2;

	if (l < N && arr[l] > arr[largest])
		largest = l;

	if (r < N && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapcount++; // incrementing count
		heapify(arr, N, largest);
	}
}

void heapSort(int arr[], int N)
{

	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);

	for (int i = N - 1; i > 0; i--) {

		swap(arr[0], arr[i]);
		heapcount++; // incrementing count
		heapify(arr, i, 0);
	}
}

// ----------------------------------------------------------------------------------------------------

/*
Code taken from following source:
https://www.geeksforgeeks.org/quick-sort/

All comments are removed and modifications where made are listed in comment.
*/

int quickcount = 0;


int partition(int arr[], int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);
	quickcount++; // incrementing counter

	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
			quickcount++; // incrementing count
		}
	}

	return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

	if (start >= end)
		return;

	int p = partition(arr, start, end);

	quickSort(arr, start, p - 1);

	quickSort(arr, p + 1, end);
}