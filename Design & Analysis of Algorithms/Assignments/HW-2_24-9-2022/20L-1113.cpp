// Abdul Saboor
// 20L-1113
// BDS-5A
// Homework-2 source file

// ----------------------------------------------------------------------------------------------------
#include "20L-1113.h"

void sorting()
{
	int A[1000];
	int B[1000];
	int C[1000];
	for (int i = 0; i < 1000; i++)
	{
		A[i] = (rand() % 1000) + 1;
		B[i] = C[i] = A[i];
	}
	auto arr_size = sizeof(A) / sizeof(A[0]);

	// MERGE SORT
	auto start = chrono::steady_clock::now(); // staring clock

	mergecount = 0;
	mergeSort(A, 0, arr_size - 1);
	cout << "Total number of comaprisons in merge sort: " << mergecount << endl;

	// ending clock and printing
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds: "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;

	// HEAP SORT

	// Function call
	start = chrono::steady_clock::now(); // staring clock
	heapcount = 0;
	heapSort(B, arr_size);
	cout << "\nTotal number of comaprisons in heap sort: " << heapcount << endl;
	end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds: "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;

	// QUICK SORT

	int arr[] = {10, 7, 8, 9, 1, 5};
	int n = sizeof(arr) / sizeof(arr[0]);

	// Function call
	start = chrono::steady_clock::now(); // staring clock
	quickcount = 0;
	quickSort(A, 0, arr_size - 1);
	cout << "\nTotal number of comaprisons in quick sort: " << quickcount << endl;
	end = chrono::steady_clock::now();
	cout << "Elapsed time in milliseconds: "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;
}

int main()
{
	int counts[] = {0, 0, 0};
	int run = 5;
	for (int i = 1; i <= run; i++)
	{
		cout << "******************* Run " << i << " ******************" << endl;
		sorting();
		counts[0] += mergecount;
		counts[1] += heapcount;
		counts[2] += quickcount;
		cout << endl;
	}
	cout << "\n******************* Part B *****************" << endl;
	cout << "Average number of comparisons for merge-sort in " << run << " runs: " << counts[0] / run << endl;
	cout << "Average number of comparisons for heap-sort in " << run << " runs: " << counts[1] / run << endl;
	cout << "Average number of comparisons for quick-sort in " << run << " runs: " << counts[2] / run << endl;
}