#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "employee.h"
#include "heap.h"

int get3employees(Employee *emp)
{
	int i = 0;
	strcpy(emp[i].name, "Joe Bob");
	emp[i].salary = 40;
	i = 1;
	strcpy(emp[i].name, "Ada Lovelace");
	emp[i].salary = 1;
	i = 2;
	strcpy(emp[i].name, "Grace Hopper");
	emp[i].salary = 120;

	return i + 1;
}

int get10employees(Employee *emp)
{
	// Setup: Create a list of employees
	int i = 0;
	emp[i].salary = 40;
	strcpy(emp[i].name, "Joe Bob");
	i = 1;
	strcpy(emp[i].name, "Ada Lovelace");
	emp[i].salary = 1;
	i = 2;
	strcpy(emp[i].name, "Grace Hopper");
	emp[i].salary = 120;
	i = 3;
	strcpy(emp[i].name, "a");
	emp[i].salary = 30;
	i = 4;
	strcpy(emp[i].name, "b");
	emp[i].salary = 200;
	i = 5;
	emp[i].salary = 400;
	strcpy(emp[i].name, "c");
	i = 6;
	emp[i].salary = 80;
	strcpy(emp[i].name, "d");
	i = 7;
	emp[i].salary = 3;
	strcpy(emp[i].name, "e");
	i = 8;
	strcpy(emp[i].name, "f");
	emp[i].salary = 2;
	i = 9;
	emp[i].salary = 14;
	strcpy(emp[i].name, "g");

	return i + 1;
}

/**
 * Test printing out the list
 * (must be examined visually)
 */
void testPrintList()
{
	// TODO: test void printList(Employee *A, int n)
	// Setup employee
	int maxEmp = 20;
	Employee emp[maxEmp];
	int numEmp = get10employees(emp);
	printList(emp, numEmp);
}

/**
 * Test void swap(Employee *e1, Employee *e2)
 */
void testSwap()
{
	// Simple swap of entries 0 and 1
	// Setup employee
	int maxEmp = 20;
	Employee emp[maxEmp];
	get10employees(emp);
	// Run: swap the first two
	// printf("Before swap:\n");
	// printf("emp0: %s, %d\n", emp[0].name, emp[0].salary);
	// printf("emp1: %s, %d\n", emp[1].name, emp[1].salary);
	swap(&emp[0], &emp[1]);
	// printf("After swap: \n");
	// printf("emp0: %s, %d\n", emp[0].name, emp[0].salary);
	// printf("emp1: %s, %d\n", emp[1].name, emp[1].salary);
	assert(strcmp(emp[1].name, "Joe Bob") == 0);
	assert(strcmp(emp[0].name, "Ada Lovelace") == 0);
	assert(emp[1].salary == 40);
	assert(emp[0].salary == 1);
	printf("Test of swap: passed.\n");

	// TODO: swap with element outside range?
	// swap(&emp[0], &emp[11]);

	// TODO: swap with itself?

	return;
}

void testHeapifyWith0()
{
	// Setup
	int numEmp = 5;
	Employee emp[numEmp];

	// Run
	heapify(emp, 0, 0);

	// Assert
	return;
}

void testHeapifyWith3()
{
	// Setup: Create a list of employees
	int maxEmp = 20;
	Employee emp[maxEmp];
	int numEmp = get3employees(emp);

	// Run
	heapify(emp, 0, numEmp);
	// for (int count = 0; count < numEmp; count++)
	// {
	// 	printf("emp[count].salary: %d\n", emp[count].salary);
	// }

	// Assert
	assert(emp[0].salary == 1);
	assert(emp[1].salary == 40);
	assert(emp[2].salary == 120);
	assert(strcmp(emp[0].name, "Ada Lovelace") == 0);
	assert(strcmp(emp[1].name, "Joe Bob") == 0);
	assert(strcmp(emp[2].name, "Grace Hopper") == 0);

	return;
}

void testHeapifyWith10()
{
	// Setup: Create a list of employees
	int maxEmp = 20;
	Employee emp[maxEmp];
	int numEmp = get10employees(emp);

	// Run
	heapify(emp, 0, numEmp);
	// for (int count = 0; count < numEmp; count++)
	// {
	// 	printf("emp[%d].salary: %d\n", count, emp[count].salary);
	// 	printf("emp[%d].name: %s\n", count, emp[count].name);
	// }

	// Assert
	assert(emp[0].salary == 1);
	assert(emp[1].salary == 30);
	assert(emp[2].salary == 120);
	assert(emp[3].salary == 2);
	assert(emp[4].salary == 200);
	assert(emp[5].salary == 400);
	assert(emp[6].salary == 80);
	assert(emp[7].salary == 3);
	assert(emp[8].salary == 40);
	assert(emp[9].salary == 14);

	assert(strcmp(emp[0].name, "Ada Lovelace") == 0);
	assert(strcmp(emp[1].name, "a") == 0);
	assert(strcmp(emp[2].name, "Grace Hopper") == 0);
	assert(strcmp(emp[3].name, "f") == 0);
	assert(strcmp(emp[4].name, "b") == 0);
	assert(strcmp(emp[5].name, "c") == 0);
	assert(strcmp(emp[6].name, "d") == 0);
	assert(strcmp(emp[7].name, "e") == 0);
	assert(strcmp(emp[8].name, "Joe Bob") == 0);
	assert(strcmp(emp[9].name, "g") == 0);

	return;
}

/**
 * test void heapify(Employee *A, int i, int n)
 */
void testHeapify()
{
	testHeapifyWith3();
	testHeapifyWith10();
	testHeapifyWith0();
	printf("Test of heapify: passed\n");
	return;
}

/**
 * Test BuildHeap(Employee *A, int n)
 */
void testBuildHeap()
{
	// Setup: Create a list of employees
	int maxEmp = 20;
	Employee emp[maxEmp];
	int numEmp = get10employees(emp);

	// Run
	buildHeap(emp, numEmp);

	// Assert
	assert(emp[0].salary == 1);
	assert(emp[1].salary == 2);
	assert(emp[2].salary == 80);
	assert(emp[3].salary == 3);
	assert(emp[4].salary == 14);
	assert(emp[5].salary == 400);
	assert(emp[6].salary == 120);
	assert(emp[7].salary == 40);
	assert(emp[8].salary == 30);
	assert(emp[9].salary == 200);

	return;
}

void testHeapSort()
{
	// Setup: Create a list of employees
	int maxEmp = 20;
	Employee emp[maxEmp];
	int numEmp = get10employees(emp);

	// Run
	heapSort(emp, numEmp);

	// Assert
	assert(emp[9].salary == 1);
	assert(emp[8].salary == 2);
	assert(emp[7].salary == 3);
	assert(emp[6].salary == 14);
	assert(emp[5].salary == 30);
	assert(emp[4].salary == 40);
	assert(emp[3].salary == 80);
	assert(emp[2].salary == 120);
	assert(emp[1].salary == 200);
	assert(emp[0].salary == 400);

	printf("Test of heapSort: passed\n");
}

int main(int argc, char *argv[])
{
	// TODO
	printf("In main\n");

	// TESTS:
	testSwap();
	testHeapify();
	testPrintList();
	testBuildHeap();
	testHeapSort();

	// TODO: test void heapSort(Employee *A, int n)
	// TODO: test void reverse( Employee *A, int start, int end);

	return 0;
}