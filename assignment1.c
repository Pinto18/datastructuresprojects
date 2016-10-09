/*************************************************************************************************************************************************
*Nicholas DiPinto
*CS 315 
*Assignment #1 
*
*Write a program that creates a linked list of user inputted integers. The program adds items to the linked list by asking the user if
*he or she would like to add another number to the list. Once the user says that he or she is finished entering numbers into the list, the program
*displays all of the numbers within the list.  
****************************************************************************************************************************************************/

/*******************************Variables************************************************************************************************************************
*listItem = an item within the dynamically structured list which has two components
*someInt = a component of the listItem structure which holds a value that is an integer inputted by the user
*nextInt = a componenet in the listItem structure which points to another listItem structure
*answer = the user inputted response to any of the questions in tthe program, which tell the computer what action to take next
*startPoint = the starting point in the dynamically linked list for whichever task the program is trying to accomplish
*placeHolder = a pointer that points to listItem structures whose purpose is to help the startPoint pointer stay on track and reset when neccessary
*****************************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>


typedef struct listItem
{
  int someInt;
  struct listItem *nextInt;
}LISTITEM; 

main()
{
   char answer;
   LISTITEM *startPoint = NULL, *placeHolder;
   int numSearch, searchCounter;
    
   printf("Welcome! Entering a number less nthan or equal to 0 will exit you out of the program. \n");
   do
   {
       placeHolder = malloc(sizeof(LISTITEM));  //placeHolder points to the newly allocated space in memory
       printf("Enter an integer: ");
       scanf("%d", &(placeHolder->someInt)); //user enters the integer to be put into the list
       placeHolder->nextInt = startPoint;  //the field known as nextInt inside the structure being pointed by placeHolder points to the same place startPoint points to
       startPoint = placeHolder;  //now startPoint points to the place in memory where palceHolder points to
   }
   while((startPoint->someInt) > 0);
       
   //Printing out the entire list   
   printf("Here's your list, from the most recent entry to the oldest: \n    ");
   while(startPoint != NULL)
   {
      printf("%d ", *startPoint);
      startPoint = (startPoint->nextInt);   //the nextInt field of the structure points to the randomInt field of the next structure, startPoint now points to the same field in the next structure
   }
   printf("\n");
}

