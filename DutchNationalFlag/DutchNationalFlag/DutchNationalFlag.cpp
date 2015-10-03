// DutchNationalFlag.cpp : Defines the entry point for the console application.
// Not quite the Dutch National Flag problem ...
// Given array containing 0,1 and 2. Sort array in-place so 0's come first then 1's and then 2's

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility> // for std::swap

using std::string;
using std::cout;
using std::endl;
using std::vector;

void sortArray(vector<int>& A)
{
	size_t low = 0;
	size_t high = A.size() - 1;
	size_t i = 0;
	int midVal = 1;

	//for (size_t i = 0; i <= high; i++) {
	while (i <= high) {

		if (A[i] > midVal) {
			std::swap(A[i], A[high]);
			//while (A[high] > midVal && high >= low) 
			high--; 
			// Do not increment i here !!!!!
		}
		else if (A[i] < midVal) {
			std::swap(A[i], A[low]);
			//while (A[low] < midVal && low <= high) 
			low++; i++;
		}
		else {
			i++;
		}

	}

}
// from geeks2geeks.com ...
//void sort012(int a[], int arr_size)
void sort012(vector<int> &a)
{
	int lo = 0;
	//int hi = arr_size - 1;
	int hi = a.size() - 1;
	int mid = 0;

	while (mid <= hi)
	{
		switch (a[mid])
		{
		case 0:
			//swap(&a[lo++], &a[mid++]);
			std::swap(a[lo++], a[mid++]);

			break;
		case 1:
			mid++;
			break;
		case 2:
			//swap(&a[mid], &a[hi--]);
			std::swap(a[mid], a[hi--]);
			break;
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> A = { 2, 1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 2, 0 };
	//vector<int> A = { 2, 1, 0, 0, 0, 0, 1};
	cout << "Array before ..." << endl;
	std::copy(A.begin(), A.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
	
	sortArray(A);
	//sort012(A);
	cout << "Array after sorting ..." << endl;
	std::copy(A.begin(), A.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;


	return 0;
}

