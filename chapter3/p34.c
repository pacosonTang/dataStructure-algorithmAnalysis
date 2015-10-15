#include<stdio.h>
#include<malloc.h>

#define ElementType int

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List; 
typedef PtrToNode Position;

List makeEmpty(List);
int isEmpty(List);
int isLast(Position);
Position find(ElementType, List);
void deletePos(ElementType, List);
Position findPrevious(ElementType, List);
void insert(ElementType, Position);
void deleteList(List);
Position header(List);
Position first(List);
Position advance(Position);
ElementType retrieve(Position);

struct Node
{
    ElementType element;
    Position next;
};
//build empty list with head node
List makeEmpty(List head)
{
    head = (List)malloc(sizeof(List));
    head->next = NULL;
    return  head;
}
// if the list is empty or not
int isEmpty(List head)
{    
    return head->next == NULL;   
}
// if the current node p is the last or not
int isLast(Position p)
{
    return p->next == NULL;    
}
// find the position with value e
Position find(ElementType e, List head)
{
    Position p = head->next;
    while(p && p->element != e)         
        p = p->next;     
    return p;             
}
//delete pos or node with value e
void deletePos(ElementType e, List head)
{
    Position p = findPrevious(e, head);        
    Position temp = NULL;

    if(!p)
        return;  
    else {                 
        temp = p->next;
        p->next = p->next->next;
        free(temp);        
    }
}
// find the pos or node previous to one with value e
Position findPrevious(ElementType e, List head)
{
    Position p = head;    
    if(!p)
        return NULL; 
    while (p->next!= NULL && p->next->element != e) 
        p = p->next;
    return p;    
}
// insert the node with value e into the place after pos or node p
void insert(ElementType e, Position p)    
{        
    Position np = (Position)malloc(sizeof(Position));

    if(!np)
        return;   
    np->element = e;
    np->next = p->next;	
    p->next = np;    
}
// delete all of the nodes in list but head node
void deleteList(List head)
{
    Position np = NULL, p = head->next;
    
    head->next = NULL;
    while (p) {
        np = p->next;
        free(p);
        p = np;
    }
}
// return the head node in list
Position header(List head)
{
    return head;
}
// return the first pos or node in list
Position first(List head)
{
    if(head)
        return head->next;
    return NULL;
}
// return pos after the pos or node p
Position advance(Position p)
{
    if(p)        
        return p->next ;    
    return NULL;
}
// return the value pos p or node contains
ElementType retrieve(Position p)
{
    if(p)
        return p->element;
	return -1;
}
//print elements in list
void printList(List head)
{
    Position p = head->next;
    
    while (p) {
        printf("%4d",p->element);
        p = p->next;
    }
    printf("\n");
}
// main func
int main()
{	
	List head;	
	Position p;
	int i;

	head = makeEmpty(head);		

	printf("test for insertion\n");
	for(i = 1; i <= 5; i++)
		insert(i, head);		 
	printList(head);

	printf("\ntest for delete position \n");	
	deletePos(2, head);
	printList(head);
	
	printf("\ntest for isLast element \n");	
	printf("\n%4d is Last: %4d\n", 5, isLast(find(5, head)));
	printf("\n%4d is Last: %4d\n", 1, isLast(find(1, head)));
	
	printf("\nadvance of %4d is %4d \n", 5, retrieve(advance(find(5, head))));	
	printf("\nprevious element %4d is %4d \n", 1, retrieve(findPrevious(1, head)));	
	return 0;
}
