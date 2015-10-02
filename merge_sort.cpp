
#include "stdafx.h"

using namespace System;

#include <iostream>
#include <stdio.h>
#include<conio.h>
#include<time.h>

using namespace std;
#define MAX_SIZE	100000


class mrgsort
{
public:

	int NofCompM; //Number of Comparisons
	int	NofSwpM; // Number of Swaps
	
	int uSize; //Size of Array
	int* pArray1;	// For MergeSort

	mrgsort()
	{

		cout << "How many elements for array? (MAX: " << MAX_SIZE << "): ";
		cin >> uSize;
		if (uSize > MAX_SIZE)
			uSize = MAX_SIZE;

		pArray1 = new int[uSize];
		cout << "Memory Allocated" << endl;
	}
	~mrgsort()
	{
		delete[] pArray1;
		cout << "Memory freed" << endl;
	}
	/* Function: Create a random Array */
	void makeArray();
	/* Function: Display Array */
	void dispArray(int *pArray1);
	/*Function: Sort two different parts */
	void merge(int *pArray1, int low, int mid, int high);
	/* Merge and sort all the parts */
	void mergesort(int *pArray1, int low, int high);

};

void mrgsort::makeArray()
{
	cout << "Generate random integer numbers to sort\n";
	for (int i = 0; i < uSize; i++)
	{
		pArray1[i] = rand() % (uSize + 1000);
	}
}

void mrgsort::dispArray(int *pArray1)
{
	cout << "Contents of Array:";
	for (int i = 0; i < uSize; i++)
	{
		if ((i % 10) == 0)
			cout << endl;

		cout << pArray1[i] << " ";
	}
	cout << endl;
}

void mrgsort:: mergesort(int *pArray1, int low, int high)
{
	int mid;
	NofCompM = NofSwpM = 0;

	if (low < high)
	{	
		NofCompM++;
		mid = (low + high) / 2;
		mergesort(pArray1, low, mid);
		mergesort(pArray1, mid + 1, high);
		merge(pArray1, low, high, mid);
	}
	return;
}
void mrgsort::merge(int *pArray1, int low, int high, int mid)
{
	int i, j, k;
	i = low;
	k = low;
	j = mid + 1;
	int *c = new int[uSize]; //Temporary Array

	while (i <= mid && j <= high)
	{
		
		if (pArray1[i] < pArray1[j])
		{
			c[k] = pArray1[i];
			k++;
			i++;
		}
		else
		{
			c[k] = pArray1[j];
			k++;
			j++;
			NofSwpM++;
		}
		NofCompM++;

	}
	while (i <= mid)
	{
		c[k] = pArray1[i];
		k++;
		i++;
	
	}
	while (j <= high)
	{
		c[k] = pArray1[j];
		k++;
		j++;
	}
	for (i = low; i < k; i++)
	{
		pArray1[i] = c[i];
	}
}
int main()
{
	mrgsort m;
	
	m.makeArray();

	m.dispArray(m.pArray1);
	clock_t begin_time = clock();

	m.mergesort(m.pArray1, 0, (m.uSize-1));
	cout << "\nTime Taken for Sorting: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << "\nAfter Sorting: " << endl;
	m.dispArray(m.pArray1);

	cout << "\nNo of Comparisons: " << m.NofCompM << endl;
	cout << "\nNo of Swaps: " << m.NofSwpM << endl;

	getch();
}
