/*******************************************************************************
 *Nicholas DiPinto
 *CS 315
 *Assignment #5
 *
 *Write a program that prompts the user to either insert or find a node
 *inside a binary search tree. After each insertion, the program will
 *output the current pre-order and inorder traversals of the binary search
 *tree. Each node will have a char key value with a data string that starts
 *with that node's key value. The data string will be up to 10 characters
 *long and the user will be prompted to enter the data string after inserting
 *the new node.
 ********************************************************************************/

/***********************************************************************Variables*************************************************
 *node = a node that can be inserted into a binary tree
 *key = the key value for a node in the binary tree
 *data = a string which starts with the key value indicated inside the node structure
 *leftChild = a pointer which points to the left descendat of that node
 *rightChild = a pointer which points to the right descendant of the node
 *stackItem = an item created to be part of a linked list which will be implemented as a stack to perform the traversal functions
 *nodePtr = a pointer which points to a node that has been traversed in the binary search tree
 *nextItem = a pointer to the itme in the stack
 *treeNode = a pointer to a pointer of a node. Its purpose is to represent the root node of the binary search tree for insertion
 *newNode = a pointer to the node which will be inserted into the binary search tree
 *trvPtr = a pointer to a node whose purpose is to traverse the binary seach tree
 *keyValue = a character inputted by the user that will be searched for in the binary search tree
 *stack = a pointer to a pointer to a stack item which represents the entire stack of traversed nodes
 *pushedNode = a pointer to the node which will be pushed into the stack of nodes that has been traversed
 *returnedNode = the node returned by a function with a node pointer return type
 *top = a pointer to a stack item which represents the top of the stack
 *userInput = character inputted by user to navigate through the program
 *done = an integer which represents a boolean value of whether a certain operation is finished
 *newNodeCreated = a pointer which points to an adress in memory representing a new node that the user wishes to insert
 *searchKey = character that the user designates they want to search for in the binary search tree
 *nodeStack = a pointer which points to the initialization of the stack of traversed nodes
 *newItem = a pointer which points to the new item which will be inserted into the stack of traversed nodese
 *********************************************************************************************************************************/

/******Pre Processor Definitons************/
#define MAX_STRING_LENGTH 10
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>     //library will be included to use the toupper() finction
/******************************************/

/******Global Structures*******************/
typedef struct node
{
    char key;
    char data[MAX_STRING_LENGTH];
    struct node *leftChild, *rightChild;
}NODE;

typedef struct stackItem
{
    NODE *nodePtr;
    struct stackItem *nextItem;
}STACKITEM;
/******************************************/

/******Function Prototypes*****************/
int insertNode(NODE **treeNode, NODE *newNode);  //insert a new node into the binary search tree
int inOrderTraversal(NODE *trvPtr);   //print out the in order traversal of the binary search tree
int preOrderTraversal(NODE *trvPtr);  //print out the pre order traversal of the binary search tree
int findNode(NODE *trvPtr, char keyValue);  //find a node within the binary search tree
int push(STACKITEM **stack, NODE *pushedNode);  //push a node traversed during one of the traversal functions onto a stack
NODE* pop(STACKITEM **stack);  //remove a node from that stack of traversed nodes
int isEmpty(STACKITEM *top);  //check if the stack of nodes is empty
/******************************************/

int main()
{
    NODE *root = NULL, *newNodeCreated;
    char userInput, searchKey;
    int done = 0;
    
    do
    {
        printf("\nEnter choice (lower case is also acceptable)---(I)nsert, (F)ind, (Q)uit: ");
        scanf(" %c", &userInput);   //user enters character to navigate through the program
        switch(userInput)
        {
            case 'I':case 'i':   //user wants to insert a node into the binary search tree
                newNodeCreated = malloc(sizeof(NODE));  //dynamically allocate space in memory for the node
                newNodeCreated->leftChild = NULL;   //set the left and right descendants to help prevent any segmentation faults later on
                newNodeCreated->rightChild = NULL;
                printf("\nEnter node's key value: ");
                scanf(" %c", &(newNodeCreated->key));
                newNodeCreated->key = toupper(newNodeCreated->key);
                printf("\nEnter string of up to 10 characters for \'%c\'s data: ", newNodeCreated->key);
                scanf(" %s", newNodeCreated->data);
                insertNode(&root, newNodeCreated);  //this function will handle insertion of the node into the binary search tree
                printf("\n");
                preOrderTraversal(root);  //this function will handle printing out the pre-order traversal of the nodes of the binary serach tree
                inOrderTraversal(root);   //this function will handle printing out the in-order traversal of the nodes of the binary searach tree
                break;
            case 'F':case 'f':  //user wants to find a node inside the binary search tree
                printf("\nEnter the search key: ");
                scanf(" %c", &searchKey);
                searchKey = toupper(searchKey);
                findNode(root, searchKey);  //this function will handle searching the binary search tree for the node with the key value designated by the user
                break;
            case 'Q':case 'q':  //user wants to quit the program
                done = 1;  //sets the finished flag to true
                break;
            default: //error handling in case the user enters an option not designated by the prompt
                printf("Invalid input. Try again.\n");
                break;
        }
    }
    while(!done);
    printf("Bye!\n");
    return 0;
}

int insertNode(NODE **treeNode, NODE *newNode)
{
    int done = 0;
    NODE *trvPtr = *treeNode;
    
    if(trvPtr == NULL)//SPECIAL CASE: there are no nodes in the binary tree
        *treeNode = newNode;
    else
    {
        while(!done) //keep searching until the pointer reaches a leaf node
        {
            if((newNode->key) < (trvPtr->key))  //if the node's key is less than the current node, then go done to its left subtree
            {
                if(trvPtr->leftChild != NULL)  //if the node already has a left child, then compare the new node to that node
                    trvPtr = trvPtr->leftChild;
                else
                {
                    trvPtr->leftChild = newNode; //if the node does not have a left child, then set the new node as the current node's left child
                    done = 1;
                }
            }
            else if((newNode->key) > (trvPtr->key))  //if the node's key is greater than the current node, then go done to its right subtree
            {
                    if(trvPtr->rightChild != NULL)   //if the node already has a lright child, then compare the new node to that node
                        trvPtr = trvPtr->rightChild;
                    else
                    {
                        trvPtr->rightChild = newNode;   //if the node does not have a right child, then set the new node as the current node's right child
                        done = 1;
                    }
            }
            else  //in case of any strange errors occuring
                printf("ERROR: Something went wrong with insertion.\n");
        }
    }
    return 0;
}

int inOrderTraversal(NODE *trvPtr)
{
    STACKITEM *nodeStack = NULL;
    int done = 0;
    
    printf("In-Order Traversal: ");
    while(!done)   //boolean flag starts the traversal over again with a node from the stack of traversed nodes once trvPtr reaches a leaf node
    {
        while(trvPtr != NULL)  //this while loop will help trvPtr reach down to one of the leaf nodes
        {
            if(trvPtr->leftChild != NULL)  //if the node has a left child, then traverse down the left child
            {
                push(&nodeStack, trvPtr);  //before traversing add the current node to the stack of traversed nodes
                trvPtr = trvPtr->leftChild;
            }
            else
            {
                printf("%c ", toupper(trvPtr->key));  //visit the node
                trvPtr = trvPtr->rightChild;  //traverse down to the right child of the node
            }
        }
        if(isEmpty(nodeStack)) //if statement only occurs once trvPtr reaches each of the leaf nodes
            done = 1;  //traversal of binary search tree is finished
        else
        {
            trvPtr = pop(&nodeStack);  //pop a node from the stack of traversed nodes so trvPtr can continue traversing through the binary search tree
            printf("%c ", toupper(trvPtr->key)); //visit the node popped from the stack
            trvPtr = trvPtr->rightChild;  //traverse down the right child of the node
        }
    }
    printf("\n");
    return 0;

}

int preOrderTraversal(NODE *trvPtr)
{
    STACKITEM *nodeStack = NULL;
    int done = 0;
    
    printf("Pre-Order Traversal: ");
    while(!done)  //boolean flag starts the traversal over again with a node from the stack of traversed nodes once trvPtr reaches a leaf node
    {
        while(trvPtr != NULL)  //this while loop will help trvPtr reach down to one of the leaf nodes
        {
            printf("%c ", toupper(trvPtr->key)); //visit the node
            if(trvPtr->leftChild != NULL)  //if the node has a left child, then traverse down the left child
            {
                push(&nodeStack, trvPtr);  //before traversing add the current node to the stack of traversed nodes
                trvPtr = trvPtr->leftChild;
            }
            else
                trvPtr = trvPtr->rightChild; //traverse down the right child of the node
        }
        if(isEmpty(nodeStack))  //if statement only occurs once trvPtr reaches each of the leaf nodes
            done = 1;  //traversal of binary search tree is finished
        else
        {
            trvPtr = pop(&nodeStack);  //pop a node from the stack of traversed nodes so trvPtr can continue traversing through the binary search tree
            trvPtr = trvPtr->rightChild;  //traverse down the right child of the node
        }
    }
    printf("\n");
    return 0;
}

int push(STACKITEM **stack, NODE *pushedNode)
{
    STACKITEM *newItem = malloc(sizeof(STACKITEM));
    newItem->nodePtr = pushedNode;
    
    if(isEmpty(*stack))  //pushing a node onto an empty stack
    {
        newItem->nextItem = NULL;  //this statement helps prevent segmentation faults later on
        *stack = newItem;
    }
    else  //there are currently other nodes inside the stack
    {
        newItem->nextItem = (*stack);  //set the new item to be at the top of the stack
        *stack = newItem;
    }
    return 0;
}

NODE* pop(STACKITEM **stack)
{
    STACKITEM *delPtr;
    NODE *returnedNode;
    
    if(isEmpty(*stack))  //error handling if the program tries to pop from an empty stack
        return NULL;
    else
    {
        delPtr = (*stack);  //point to the top item in the stack
        *stack = (*stack)->nextItem;  //set the second item in the stack to the top of the stack
        delPtr->nextItem = NULL;  //avoid possible segmentation faults
        returnedNode = delPtr->nodePtr;  //get the node we want the program to return
        free(delPtr); //free up the memory allocated by the item that was at the top of the stack
    }
    return returnedNode;
}

int isEmpty(STACKITEM *top)
{
    if(top == NULL)
        return 1;  //returns 1 if the stack is empty
    else
        return 0;  //returns 0 if the stack is not empty
}

int findNode(NODE *trvPtr, char keyValue)
{
    STACKITEM *nodeStack = NULL;
    int done = 0, keyNotFound = 1;

    
    if(trvPtr == NULL)  //user wants us to search through an empty tree
        printf("There are no nodes in this tree to search.\n");

    else    //tree is not empty
    {
        //performing an pre-order traversal to search all of the nodes for the search key
        while(!done)  //boolean flag starts the traversal over again with a node from the stack of traversed nodes once trvPtr reaches a leaf node
        {
            while(trvPtr != NULL)  //this while loop will help trvPtr reach down to one of the leaf nodes
            {
                if ((trvPtr->key) == keyValue)
                {
                    printf("\nFound the string \"%s\" there.\n", trvPtr->data);  //visit the node
                    keyNotFound = 0;  //indicates that the key was found and we can stop the while loop
                }
                if(trvPtr->leftChild != NULL) //if the node has a left child, then traverse down the left child
                {
                    push(&nodeStack, trvPtr);  //before traversing add the current node to the stack of traversed nodes
                    trvPtr = trvPtr->leftChild;
                }
                else
                    trvPtr = trvPtr->rightChild;  //traverse down the right child of the node
            }
            if(isEmpty(nodeStack)) //if statement only occurs once trvPtr reaches each of the leaf nodes
                done = 1;  //traversal of binary search tree is finished
            else
            {
                trvPtr = pop(&nodeStack);  //pop a node from the stack of traversed nodes so trvPtr can continue traversing through the binary search tree
                trvPtr = trvPtr->rightChild; //traverse down the right child of the node
            }
        }
        if(done && keyNotFound) //error handling in case the user wants to find a node that does not exist within the binary search tree
            printf("\nNo node exists that contains that key.\n");
    }
    return 0;
}
