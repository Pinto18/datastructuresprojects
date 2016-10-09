/*******************************************************************************
*Nicholas DiPinto
*CS 315
*Assignment #3
*
*Write a program that implements a queue inside a (one way) circular linked list. 
*The program can only use one pointer to traverse the list. The list must behave
*like a queue structure with the inclusion of a removal and insertion function
*where items are removed from the front and inserted in the rear.
********************************************************************************/

/************************************ Variables *********************************
*qItem = an item within the circular linked list
*itemChar = the char value stored inside the qItem structure
*nextItem = a pointer that points to the next item in the list
*Q = a pointer which is designed to always point to the rear of the circular linked list
*newQItem = a pointer to a new item created for the list
*theRear = a pointer to a QITEM pointer which creates side effects affecting the position of the Q pointer inside the insertion and deletion functions
*userInput = char input inputted by the user
*newItemCreated = a temporary pointer to a QITEM created for insertion
*delPtr = a pointer which points to an item in the queue which will be removed from the queue
********************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct qItem
{
	char itemChar;
	struct qItem *nextItem;
}QITEM;

int insertItem(QITEM **theRear, QITEM *newQItem);
int delItem(QITEM **theRear);
main()
{
	char userInput;
	QITEM *Q = NULL, *newItemCreated;
     
	printf("This program implements a queue of individual characters in a circular list using only a single pointer to the circular list; separate pointers to the front and rear elements of the queue are not used.\n");
	do
	{
        	printf("\nEnter \"i\" to insert a new element, \"r\" to remove an element, \"q\" to quit: ");
		scanf(" %c", &userInput);
		switch(userInput)
		{
			case 'i':     //insert an item into the rear of the list
				newItemCreated = malloc(sizeof(QITEM));
				printf("Enter character to be enqueued (inserted): ");
				scanf(" %c", &(newItemCreated->itemChar));
				newItemCreated->nextItem = NULL;
				insertItem(&Q, newItemCreated);
				break;
			case 'r':     //remove an item from the front of the list
				if(Q != NULL)  //check if there are any items in the list
					delItem(&Q);  //if there are item(s), delete the front item
				else
					printf("Nothing to remove; the queue is empty.\n");  //if there are no items in the list, then tell the user
				break;
			case 'q':     //user wants to quit the program
				break;
			default:
				printf("Not a valid input. Try again.\n");
		}
	}
	while(userInput != 'q');
	printf("Bye!\n");
}

int insertItem(QITEM **theRear, QITEM *newQItem)
{
	if(*theRear == NULL) //check to see if the list is empty
	{
		*theRear = newQItem;
		newQItem->nextItem = newQItem;
	}
	else  //General Case
	{
		newQItem->nextItem = (*theRear)->nextItem;
		(*theRear)->nextItem = newQItem;
		*theRear = (*theRear)->nextItem;
	}
	return 0;
}

int delItem(QITEM **theRear)
{
	QITEM *delPtr = (*theRear)->nextItem; //delPtr points to the item we consider to be the front of the list

	if((*theRear) == delPtr)  //there is only one item in the list
	{
		printf("The character removed was an \"%c\"\n", delPtr->itemChar);
		free(delPtr);
		(*theRear) = NULL;
	}
	else //General Case
	{	
		(*theRear)->nextItem = ((*theRear)->nextItem)->nextItem;  //set the rear item's next pointer to point to the item after the item we consider to be the front item of the list
		printf("The character removerd was an \"%c\"\n", delPtr->itemChar);
		free(delPtr); //delete the item that was at the front of the list
	}
	return 0;
}
