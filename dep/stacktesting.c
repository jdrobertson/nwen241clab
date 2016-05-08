#include "stdio.h"
#include "stdlib.h"

// andy piggot bethel (y)

#define PRECEDENCE "+-*/%%^"
#define MAXSIZE 100
#define Node_Size sizeof(StackNode)

struct stackNode {
	char data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int isOperator( char c );
int precedence ( char operator1, char operator2 );
void push( StackNodePtr *topPtr, char value);
char pop ( StackNodePtr *topPtr);
char stackTop ( StackNodePtr topPtr);
int isEmpty( StackNodePtr topPtr );
void printStack( StackNodePtr topPtr);

int main(int argc, char const *argv[])
{
	StackNodePtr head = malloc(Node_Size);
	head->nextPtr=NULL;
	head->data='\0';
	//	the 'default' stack item has nextPtr=NUll and data='\0'

	push(&head,'2');
	push(&head,'5');
	push(&head,'1');
	printStack(head);
	pop(&head);
	printf("stackTop returned %c\n", stackTop(head));
	printStack(head);
	pop(&head);
	printStack(head);
	printf("isempty returned %d\n", isEmpty(head));
	pop(&head);
	printf("isempty returned %d\n", isEmpty(head));
	return 0;
}


void push( StackNodePtr *topPtr, char value){
	StackNodePtr new = (StackNodePtr)malloc(Node_Size);
	new->data = value;
	new->nextPtr = (*topPtr);
	*topPtr = new;
}

char pop (StackNodePtr *topPtr){
	if((*topPtr)->nextPtr==NULL){
		return '\0';
	}
	char ans = (*topPtr)->data;
	StackNodePtr toFree = *topPtr;
	*topPtr = (*topPtr)->nextPtr;
	free(toFree);
	return ans;
}

char stackTop ( StackNodePtr topPtr){
	char ans = topPtr->data;
	return ans;
}

int isEmpty( StackNodePtr topPtr ){
	int ans;
	if(topPtr->nextPtr==NULL) ans = 1;
	else ans = 0;
	return ans;
}

void printStack( StackNodePtr topPtr){
	while(1){
		if(topPtr->nextPtr==NULL){
			printf("NULL\n");
			return;
		}
		char c = topPtr->data;
		printf("%c\t",c);
		topPtr = topPtr->nextPtr;
		
	}
}
