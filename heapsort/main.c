#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "employee.h"
#include "heap.h"

// TODO: change this?
#define MAXSTRLEN 128

/**
 * Get strings from user and increment histogram
 * @param  The starting histogram (counts per letter)
 */
// void inputStrings(int histogram[])
// {
// 	char buf[MAXSTRLEN] = "";

// 	printf("Enter strings (# to stop):\n");
// 	while (strcmp(buf, "#\n") != 0)
// 	{
// 		// Get the string input by the user
// 		fgets(buf, MAXSTRLEN, stdin);

// 		// Increment letters in histogram
// 		incrementHistogram(buf, histogram, ALPHABET_SIZE);
// 	}
// }

int main(int argc, char *argv[])
{

	// TODO: What should it do if all salaries are same?

	printf("In main\n");
	int salary;

	// TODO max employees?
	int maxEmp = 20;
	Employee emp[maxEmp];

	// Accept user input of names and salaries
	printf("Enter names and salaries (# to quit): \n");

	char buf[MAXSTRLEN] = "";
	int i = 0;
	while (strcmp(buf, "#") != 0)
	{
		// Get the string input by the user and strip off the newline
		printf("Name: ");
		fgets(buf, MAXSTRLEN, stdin);
		buf[strlen(buf) - 1] = 0;

		printf("Salary: ");
		scanf("%d%*c", &salary);

		// Add employee to list
		strcpy(emp[i].name, buf);
		emp[i].salary = salary;
		printf("\n");

		i++;
	}

	int empLen = i - 1;
	printf("Before: ");
	printList(emp, empLen);

	// Sort in descending salary order
	heapSort(emp, empLen);

	printf("After: ");
	printList(emp, empLen);

	return 0;
}