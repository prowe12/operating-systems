/*
 * heapsort.c
 *
 *  Created on: Jan. 30, 2023
 *      Author: Penny Rowe
 *
 * Note: make with:
 *   $ make --file MakeTests
 */
#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "heap.h"

/**
 * Sorts a list of n employees in descending order
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the heap
 */
void heapSort(Employee *A, int n)
{
	// BuildHeap on the heap
	buildHeap(A, n);

	// Loop over n and:
	// 1) swap A[n-1] with A[0], since A[0] is the smallest number.
	// 2) A[n-1] now sorted in place, so decrement n
	// 3) Heapify the elements from A[0] up to A[n-1] (leaving the newly sorted element alone)
	while (n > 0)
	{
		swap(&A[n - 1], &A[0]);
		n--;
		buildHeap(A, n);
	}
}

/**
 * Given an array A[], we want to get A[] into min-heap property
 * We only need to run heapify() on internal nodes (there are floor(n/2) of them)
 * and we need to run it bottom up (top-down cannot build a heap)
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the heap
 */
void buildHeap(Employee *A, int n)
{
	// Heapify() every element from A[n/2] down-to A[0]
	for (int i = n / 2; i >= 0; i--)
	{
		heapify(A, i, n);
	}
}

/**
 * We want to start with A[i] and percolate it downward
 * if it is greater than either left or right child.
 *
 * @param	*A	Pointer to the list of employees
 * @param	i	Index of current element to heapify
 * @param	n	Size of the heap
 */
void heapify(Employee *A, int i, int n)
{

	// Get index of left and right child of element i
	int ileft = 2 * (i + 1) - 1;
	int iright = 2 * (i + 1);

	// Continue recursion as long as i is within range AND either left_child
	// or right_child are still within range. I think we can just check left child,
	// because it always comes first
	int smaller;

	if ((i >= n) || (ileft >= n))
	{
		return;
	}

	if ((i < n) && (ileft < n) && (iright < n))
	{
		// Determine which child has a smaller salary.
		if (A[ileft].salary <= A[iright].salary)
		{
			smaller = ileft;
		}
		else
		{
			smaller = iright;
		}
	}
	else if ((i < n) && (ileft < n))
	{
		smaller = ileft;
	}
	else if ((i < n) && (iright < n))
	{
		printf("Error: We should not have iright filled in if ileft is not!\n");
	}
	else
	{
		printf("Error: left and right children not as expected!\n");
	}

	// Recursively check if the salary at A[i] > the salary at A[smaller].
	// If it is, swap the two. Then recursively heapify A[smaller].
	if (A[i].salary > A[smaller].salary)
	{
		// Swap
		swap(&A[i], &A[smaller]);

		heapify(A, smaller, n);
	}
}

/**
 * Swaps the locations of two Employees
 * @param *e1 An Employee
 * @param *e2 Another Employee to swap with
 */
void swap(Employee *e1, Employee *e2)
{
	// TODO
	Employee tmp = *e1;
	*e1 = *e2;
	*e2 = tmp;
}

/**
 * Outputs an array of Employees
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
void printList(Employee *A, int n)
{
	int i;
	for (i = 0; i < n - 1; i++)
	{
		printf("[Id=%s ", A[i].name);
		printf("sal=%d], ", A[i].salary);
	}
	// The last one ends in return instead of comma
	printf("[Id=%s ", A[i].name);
	printf("sal=%d]\n", A[i].salary);
	printf("\n");
}
