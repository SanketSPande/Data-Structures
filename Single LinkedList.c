/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node{
    int nodeIndex;
    int data;
    struct node *next;
}*head;

void createList();
void displayMenu();
void displayList();
void insertionAtBeginning();
void insertionAtEnd();
struct node * createSingleNode();
void insertionAfterANode();
void deleteANode();
int isNodeExists(int nodeNo);
void searchAnElement();
void freeEntireList();
void reverseList(); //To be implemented
void sortList(); //To be implemented

int main(){

    createList();
    displayMenu();
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------

void displayMenu(){
    
    printf("\nMake a choice and Press\n\n 1 to Display List \n 2 to Insert an Element at the beginning \n 3 to Insert an Element after an Element \n 4 to Insert an Element at the end \n 5 to Delete an Element \n 6 to find an Element \n 0 to exit menu \n\n");
    
    int choice;
    printf("choice = ");
    scanf("%d",&choice);

    while(choice){
        
        switch(choice){
        case 1 : displayList();break;
        case 2 : insertionAtBeginning();break;
        case 3 : insertionAfterANode();break;
        case 4 : insertionAtEnd();break;
        case 5 : deleteANode();break;
        case 6 : searchAnElement();break;
        default : printf("Invalid Response");break;
        }
        
        printf("\n-----------------------------------------------------------");
        printf("\nMake a choice and Press\n\n 1 to Display List \n 2 to Insert an Element at the beginning \n 3 to Insert an Element after an Element \n 4 to Insert an Element at the end \n 5 to Delete an Element \n 0 to exit menu \n\n");
        printf("choice = ");
        scanf("%d",&choice);
        
        //free the momory if choice is 0
        if(choice == 0){
            freeEntireList();
        }
        printf("\n");
    }
}

//-----------------------------------------------------------------------------------------------------------------------

void createList(){
    
    printf("Before you begin any operation you have to create a LinkedList \n \n");
    int n;
    
    printf("Enter the number of nodes to be created = ");
    scanf("%d",&n);
    printf("\n");
    if(n<1){
        printf("Enter the number of nodes >=1 ");
        exit(0);
    }
    
    struct node * temp_node;
    struct node * any_node;
    
    //creating the 1st node
    head = createSingleNode(1);
    temp_node = head;

    //create the remaining nodes
    for(int i=2; i<=n;i++){
        
        //create a new node
        any_node = createSingleNode(i);
        
        //connect this newly created node to the previous node
        temp_node->next = any_node;
        temp_node = temp_node->next;
        
    }
        
    printf("\nLinkedList Successfully Created !! \n");
    printf("-----------------------------------------------------------");
}

//-----------------------------------------------------------------------------------------------------------------------

void displayList(){
    
    if(head == NULL){
        printf("Empty List, Cannot Proceed, Please Rerun the Program");
        exit(0);
    }
    //print the elements
    struct node * itr;
    itr = head;
    while(itr){
        printf("\nNode %d data = %d",itr->nodeIndex,itr->data);
        itr = itr->next;
    }
}

//-----------------------------------------------------------------------------------------------------------------------

void insertionAtBeginning(){
    
    if(head == NULL){
        printf("Empty List, Cannot Proceed, Please Rerun the Program");
        exit(0);
    }
    
    //create a new node
    struct node * newNode = createSingleNode(1);
    
    //connect this newly created node to the LinkedList
    newNode -> next = head;
    head = newNode;
    
    //now increase the value of nodeIndex data member by one for each node
    struct node * itr = head -> next;
    while(itr){
        itr -> nodeIndex += 1; 
        itr = itr -> next;
    }
    printf("\nNode Element Successfully Inserted in the Begining !!\n");
}

//-----------------------------------------------------------------------------------------------------------------------

void insertionAtEnd(){
    
    if(head == NULL){
        printf("Empty List, Cannot Proceed, Please Rerun the Program");
        exit(0);
    }
    
    struct node *itr;
    itr = head;
    
    //iterate till the last node
    while(itr -> next != NULL){
        itr = itr -> next;
    }//now itr points to the last node
    
    //create a new node
    struct node * newNode = createSingleNode(itr -> nodeIndex + 1);
    
    //link this new node to the last node of LinkedList
    itr -> next = newNode;
    
    printf("\nNode Element Successfully Inserted at the End !!\n");
}

//-----------------------------------------------------------------------------------------------------------------------

struct node * createSingleNode(int ndIndx){
    
    //create a new node
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    
    if(newNode == NULL){
        printf("Memory allocation Failed \n");
        exit(0);
    }
    
    printf("Enter the data for the node %d = ",ndIndx);
    
    int dta;
    scanf("%d",&dta);
    
    newNode -> nodeIndex = ndIndx;
    newNode -> data = dta;
    newNode -> next = NULL; // temoprary making NULL becoz we dont have any information about next node upto this line of code
    
    return newNode;
}

//-----------------------------------------------------------------------------------------------------------------------

void insertionAfterANode(){
    
    if(head == NULL){
        printf("Empty List, Cannot Proceed, Please Rerun the Program");
        exit(0);
    }
    
    printf("\n*(This program follows 1 based indexing for LinkedList)\n");
    printf("Enter the node number after which you want to insert a node = ");
    int nodeNo;
    scanf("%d",&nodeNo);
    
    //check if the element exists
    int result = isNodeExists(nodeNo);
    if(result == 0){
        printf("\nNode element doesn't exists in the LinkedList, please enter a correct node number\n");
        return;
    }
    
    //iterate till that nodeNo
    struct node * itr = head;
    while(itr -> nodeIndex != nodeNo){
        itr = itr -> next;
    }//now itr points to the node after which new node has to be Inserted
    
    //create a new node
    struct node *newNode = createSingleNode(itr -> nodeIndex + 1);
    
    //point the remaining list by a temoprary pointer so that we wont loose it
    struct node * temp = itr -> next;
    
    //link this new node b/w the node pointed by itr and remaining list
    itr -> next = newNode;
    newNode -> next = temp;
    
    //increase the nodeIndex of nodes after newNode by 1
    while(temp){
        temp -> nodeIndex += 1;
        temp = temp -> next;
    }
    
    printf("\nNode Element Successfully Inserted after node number %d !!\n",nodeNo);

}

//-----------------------------------------------------------------------------------------------------------------------

void deleteANode(){
    
    if(head == NULL){
        printf("Empty List, Cannot Proceed, Please Rerun the Program");
        exit(0);
    }
    
    printf("\n*(This program follows 1 based indexing for LinkedList)\n");
    printf("Enter the node number you want to delete = ");
    int ndNo;
    scanf("%d",&ndNo);
    
    //check if the element exists
    int result = isNodeExists(ndNo);
    if(result == 0){
        printf("\nNode element doesn't exists in the LinkedList, please enter a correct node number\n");
        return;
    }
    
    //create an iterator
    struct node *itr = head;
    
    //case when 1st element is to be deleted
    if(ndNo == 1){
        //create an temp var and point it to the 1st element
        struct node *t = head;
        //point head to the 2nd element
        head = head -> next;
        
        //point itr to head again, for managing the node indices
        itr = head;
        
        //free the 1st element
        free(t);
    }
    
    //case when other than 1st and last element is to be deleted
    else{
        //iterate till a node before that node    ;
    while(itr -> nodeIndex != ndNo-1){
        itr = itr -> next;
    }//now itr points to a node before the node to be deleted
    
    //create an temp var and point it to the element to be deleted
    struct node *t = itr -> next;
    
    //check if it is the last element
    if(t -> next == NULL){
        itr -> next  = NULL;
        //free the memory of deleted element
        free(t);
    }
    
    else{
        //point the next of itr to the node after the node to be deleted 
    itr -> next  = itr -> next -> next;
    
    //free the memory of deleted element
    free(t);
    }
    
    //point itr to the node after the deleted node
    itr = itr -> next;
    
    }
    
    
    //decrease the nodeIndex of all the nodes after the deleted node by 1
    while(itr){
        itr -> nodeIndex -= 1;
        itr = itr -> next;
    }
    
    
    printf("\nNode Element %d Successfully Deleted and Memory Freed !!\n",ndNo);
}

//-----------------------------------------------------------------------------------------------------------------------

int isNodeExists(int nodeNo){
    
    struct node *itr = head;
    //check if the node with provided nodeNo exists
    int flag = 0;
    while(itr){
        if(itr -> nodeIndex == nodeNo){
            flag = 1;
            break;
        }
        itr = itr -> next;
    }
    return flag;
}

//-----------------------------------------------------------------------------------------------------------------------

void searchAnElement(){
    
    int ndData;
    printf("\nEnter the Node Data you want to search = ");
    scanf("%d",&ndData);
    struct node *itr = head;
    //check if the provided data exists 
    while(itr){
        if(itr -> data == ndData){
            printf("\nThe element exists at node number = %d \n",itr -> nodeIndex);
            break;
        }
        itr = itr->next;
    }
}

//-----------------------------------------------------------------------------------------------------------------------

void freeEntireList(){
    
    struct node *current = head;
    struct node *nextptr;
    //free the nodes 1 by 1
    while(current){
        nextptr = current -> next;
        free(current);
        current = nextptr;
    }
    printf("\nMemory of LinkedList Successfully Freed !!\n");
}

//-----------------------------------------------------------------------------------------------------------------------

