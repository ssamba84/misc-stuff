# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

/*
 *   The code enclosed below will be all one needs to add to structures of any type and link them 
 *   together.
 *   
 *   What makes this possible is the container_of function that given the pointer and variable 
 *   name of any member of a structure and the type name of the parent structure,  gets us the
 *   starting address of the parent structure.  We are helped here by the offsetof function
 *   available in stddef.h			
 *	
 *   1. 	struct {	typex x;
 *   ..				...
 *   N				typey y;		
 *				...} parent;
 *
 *	for the structure above, offsetof(parent, y) will be N and (&y-N) will point to the head of 
 *	the parent variable
*/

/*****************************************START************************************************/
typedef struct {
	void *next;//, *prev; use prev if you need a doubly linked list
} list_head;

#define container_of(ptr, type, member) \
 (type *)((char *)(ptr) - offsetof(type,member))

/*  list_add will always add the new entry inbetween the first and the second entry in the list but
 *  it should be easily modified to suit your needs as should be the get_next and forall macros
*/

void list_add(list_head * entry, list_head * head){
	list_head * nxt = head->next;
	head->next = entry;
	entry->next = nxt;
}

#define get_next(p)	\
 (p->chain.next? container_of((p->chain.next), llist, chain ) : NULL)

# define forall(cur, head)	\
 for(cur = head; cur!= NULL; cur = get_next(cur))

/*****************************************STOP*************************************************/

/*
 * client code follows below
*/

typedef struct {
	int data;
	// member included to chain the structure
	list_head chain;
}llist;

llist * newllist(int data){
	llist * res = (llist *)malloc(sizeof(llist));
	res->data = data;
        //ofcourse you've to initialize.	
	res->chain.next = NULL; //res->chain.prev = NULL;
	return res;
}


void main(){
	llist *head = NULL, *cur, *temp, *temp2, *temp3;
	head = newllist(5);
	temp = newllist(2);
	temp2 = newllist(21);
	temp3 = newllist(3);
	list_add(&temp->chain, &head->chain);
	list_add(&temp2->chain, &head->chain);
	list_add(&temp3->chain, &head->chain);
	forall(cur, head){
		printf("%d\n",cur->data);
	}
	/*
	 * output would be 
	$./a.out
	5
	3
	21
	2

	*/
}
