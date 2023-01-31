/*
 * heapsort.c
 *
 *  Created on: Jan. 30, 2023
 *      Author: Penny Rowe
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
	// int m = n;

	// BuildHeap on the heap
	buildHeap(A, n);

	// Loop over n and:
	// 1) swap A[n-1] with A[0], since A[0] is the smallest number.
	// 2) A[n-1] now sorted in place, so decrement n
	// 3) Heapify the elements from A[0] up to A[n-1] (leaving the newly sorted element alone)
	while (n > 0)
	{
		// printf("%d:\n", n);
		// printList(A, n);
		swap(&A[n - 1], &A[0]);
		n--;
		buildHeap(A, n - 1);
	}
	// printList(A, m);
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
	// printf("In buildHeap\n");
	// Heapify() every element from A[n/2] down-to A[0]
	for (int i = n / 2; i >= 0; i--)
	{
		heapify(A, i, n);
		// printf("%d:\n", i);
		// printList(A, n);
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
		// printf("Out of range: %d,%d,%d not < %d\n", i, ileft, iright, n);
		return;
	}

	// printf("i, ileft, iright, n: %d,%d,%d,%d\n", i, ileft, iright, n);
	if ((i < n) && (ileft < n) && (iright < n))
	{
		// printf("Still in range: %d,%d,%d < %d\n", i, ileft, iright, n);

		// Determine which child has a smaller salary.
		if (A[ileft].salary <= A[iright].salary)
		{
			smaller = ileft;
		}
		else
		{
			smaller = iright;
		}
		// printf("A[ileft].salary %d\n", A[ileft].salary);
		// printf("A[iright].salary %d\n", A[iright].salary);
		// printf("the smaller is %d\n", smaller);
	}
	else if ((i < n) && (ileft < n))
	{
		smaller = ileft;
		// printf("A[iright] does not exist and A[ileft].salary %d\n", A[ileft].salary);
	}
	else if ((i < n) && (iright < n))
	{
		// printf("A[ileft].salary %d\n", A[ileft].salary);
		// printf("A[iright].salary %d\n", A[iright].salary);
		printf("Error: We should not have iright filled in if ileft is not!\n");
	}
	else
	{
		// printf("A[ileft].salary: %d\n", A[ileft].salary);
		// printf("A[iright].salary: %d\n", A[iright].salary);
		printf("Error: left and right children not as expected!\n");
	}

	// Recursively check if the salary at A[i] > the salary at A[smaller].
	// If it is, swap the two. Then recursively heapify A[smaller].
	if (A[i].salary > A[smaller].salary)
	{
		// Swap
		swap(&A[i], &A[smaller]);
		// tmp = A[i].salary;
		// A[i].salary = A[smaller].salary;
		// A[smaller].salary = tmp;

		// printf("Parent salary is now < child salary: %d < %d\n", A[i].salary, A[smaller].salary);
		// printf("Recurse: i = %d\n", smaller);
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
