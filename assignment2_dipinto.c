/*************************************************************************************************************************************************
 *Nicholas DiPinto
 *CS 315
 *Assignment # 2
 *
 *Write a program that creates a linked list of user inputted integers. If the user indicates that they want to insert a number into the list, then
 *the program will insert the item into the linked list at a position based upon its value. The list will be organized from least to greatest value.
 *If the user indicates that they want to remove an item from the list, then the program will that remove an item. If the number to be removed does
 *exist within the list, then an error message will appear. After changing the list, the program will display what numbers are currently in the list.
 *Once the user says that he or she is finished entering numbers into the list, then the program will quit.
 ****************************************************************************************************************************************************/

/*******************************Variables************************************************************************************************************************
 *listItem = an item within the dynamically structured list which has two components
 *someInt = a component of the listItem structure which holds a value that is an integer inputted by the user
 *nextInt = a componenet in the listItem structure which points to another listItem structure
 *userInput = the user inputted response to navigate through the program
 *startPoint = the starting point in the dynamically linked list for whichever task the program is trying to accomplish
 *trvPtr = a pointer that points to listItem structure whose purpose is to traverse the list
 *newItem = a newItem to be inserted into the list
 *delPtr = pointer that points to an item in the list that the user wants to delete
 *delValue = a value to be deleted from the list as specified by the user
 *****************************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct listItem
{
    int someInt;
    struct listItem *nextInt;
}LISTITEM;

int printList(LISTITEM *printPtr);
main()
{
    char userInput;
    LISTITEM *startPoint = NULL, *trvPtr, *newItem, *delPtr;
    int delValue;
    
    do
    {
        printf("What do you want to do? [Enter i for insert, r for remove, or q to quit]: ");
        scanf(" %c", &userInput);
        
        switch(userInput)
        {
            case 'i':
                /******************************************** Insertion *********************************************/
                newItem = malloc(sizeof(LISTITEM));
                printf("Value to be inserted: ");
                scanf("%d", &(newItem->someInt));  //user inputs new integer to be inserted
                newItem->nextInt = NULL;
                if(startPoint == NULL)    //if the number is being inputted into an empty list
                {
                    newItem->nextInt = startPoint;
                    startPoint = newItem;
                }
                else // list is not currently empty
                {
                    trvPtr = startPoint;       //start at the beginning of the list
                    if(newItem->someInt < trvPtr->someInt) //newItem can be inserted at the beginning of the list
                    {
                        newItem->nextInt = startPoint;
                        startPoint = newItem;
                    }
                    else  //newItem cannot be placed at the beginning of the list
                    {
                        while((trvPtr->nextInt != NULL) && ((newItem->someInt) > ((trvPtr->nextInt)->someInt)))  //traverse the list
                            trvPtr = trvPtr->nextInt;  //increment trvPtr through the list
                        if(trvPtr->nextInt == NULL)  //trvPtr stopped incrementing because it reached the end of the list
                            trvPtr->nextInt = newItem;   //placing the number at the end of the list
                        else    //trvPtr stopped because it found a number in the list greater than the one inputted by the user
                        {
                            newItem->nextInt = trvPtr->nextInt;
                            trvPtr->nextInt = newItem;
                        }
                    }
                }
                /**************************************** End of Insertion ********************************************/
                printList(startPoint);
                break;
            case 'r':
                /*************************************** Deletion ****************************************************/
                //ask user what value they want to be deleted
                if(startPoint == NULL)  //the list is empty
                    printf("Cannot remove, list is empty.\n");
                else  //the list is not empty
                {
                    printf("Value to be deleted: ");
                    scanf("%d", &delValue);
                    trvPtr = startPoint;   //trv starts at the beginning of the list
                    if(trvPtr->someInt == delValue)  //the value to be deleted is at the start of the list
                    {
                        startPoint = startPoint->nextInt;
                        free(trvPtr);
                    }
                    else if(trvPtr->nextInt == NULL)   //there is only one item in the list and it does not match delValue
                        printf("%d is not in the list.\n", delValue);
                    else //the list is not empty and there is more than item in the list
                    {
                        if(trvPtr->nextInt == NULL)   //there is only one item in the list and it does not match
                        {
                            printf("%d is not in the list.\n", delValue);
                            break;
                        }
                        while(((trvPtr->nextInt)->nextInt != NULL) && ((trvPtr->nextInt)->someInt != delValue))  //traverse the list
                            trvPtr = trvPtr->nextInt; //increment trvPtr through the list
                        if((trvPtr->nextInt)->someInt == delValue)   //trvPtr found the delValue
                        {
                            delPtr = trvPtr->nextInt;  //delPtr points to the item that needs to be deleted
                            trvPtr->nextInt = (trvPtr->nextInt)->nextInt;   //remove the item to be deleted from the list
                            free(delPtr);
                        }
                        else //trvPtr could not find delValue within the list
                            printf("%d is not in the list\n", delValue);
                    }
                }
                /*************************************** End of Deletion *********************************************/
                printList(startPoint);
                break;
            case 'q':
                break;
            default:
                printf("Not a valid input. Try again. \n");
        }
    }
    while(userInput != 'q');
    printf("Bye!\n");
}

int printList(LISTITEM *printPtr)  //printing out the entire list
{
   if(printPtr == NULL)
      printf("Done, your list is now empty.\n");
   else
   {
      while(printPtr != NULL)
      {
         if(printPtr->nextInt != NULL)
            printf("%d->", printPtr->someInt);
         else
            printf("%d", printPtr->someInt);
         printPtr = printPtr->nextInt;
      }
   }
}
