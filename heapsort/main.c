#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "employee.h"
#include "heap.h"

#define MAXSTRLEN 128
#define MAX_EMPLOYEES 10

int main(int argc, char *argv[])
{

	int salary;
	char qcterm; // Will use for quality-controlling user integer input

	Employee emp[MAX_EMPLOYEES];

	// Accept user input of names and salaries
	printf("\nEnter %d names and salaries (enter # to quit early): \n", MAX_EMPLOYEES);

	char buf[MAXSTRLEN] = "";
	int i = 0;
	int notdone = 1;
	while (notdone == 1)
	{

		// Prompt the user for the employee name and strip off the newline
		printf("Name: ");
		fgets(buf, MAXSTRLEN, stdin);
		buf[strlen(buf) - 1] = 0;

		// If the user entered # for the name, quit early.
		if (strcmp(buf, "#") == 0)
		{
			notdone = 0; // Done!
		}
		else
		{
			// Prompt the user to enter the salary. Require an integer
			// to be entered; else quit with a message.
			printf("Salary: ");
			if (scanf("%d%c", &salary, &qcterm) != 2 || qcterm != '\n')
			{
				printf("Please enter an integer for salary.\n");
				return 0;
			}

			// Add employee to list
			strcpy(emp[i].name, buf);
			emp[i].salary = salary;
			printf("\n");
			i++;
		}

		// Exit condition: reached max number of employees
		if (i >= MAX_EMPLOYEES)
		{
			notdone = 0;
		}
	}

	int empLen = i;
	if (empLen <= 0)
	{
		printf("No employess entered; quitting.\n");
		return 0;
	}

	printf("Before: ");
	printList(emp, empLen);

	// Sort in descending salary order
	heapSort(emp, empLen);

	printf("After: ");
	printList(emp, empLen);

	return 0;
}