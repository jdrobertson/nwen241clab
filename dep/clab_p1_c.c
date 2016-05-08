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

void convertToPostfix( char infix[], char postfix[] );
int isOperator( char c );
int precedence ( char operator1, char operator2 );
void push( StackNodePtr *topPtr, char value);
char pop ( StackNodePtr *topPtr);
char stackTop ( StackNodePtr topPtr);
int isEmpty( StackNodePtr topPtr );
void printStack( StackNodePtr topPtr);

int main(int argc, char const *argv[])
{
	printf("Enter the infix expression.\n");

	char infix[MAXSIZE];
	scanf("%s",infix);
	
	char postfix[MAXSIZE];
	printf("The original infix expression is:\n%s\n",infix);
	
	convertToPostfix(infix,postfix);
	
	printf("The expression in postfix notation is:\n%s\n",postfix);
	
	return 0;
}

void convertToPostfix( char infix[], char postfix[] ){

	StackNodePtr head = (StackNodePtr)malloc(Node_Size);
	head->nextPtr=NULL;
	head->data='\0';

	int inputLen;
	push(&head,'(');

	for(int i = 0; i<MAXSIZE; i++){
		if(infix[i]=='\0'){
			infix[i]=')';
			infix[i+1]='\0';
			inputLen = i;
			break;
		}
	}

	int nextInPostfix = 0;

	for(int i = 0; i<inputLen; i++){
		printf("test");
		if(isOperator(infix[i])){
			while(isOperator(stackTop(head))){
				if(precedence(stackTop(head),infix[i])>=0){
					char toPostfix = pop(&head);
					postfix[nextInPostfix++] = toPostfix;

				}
				else break;

			}
			push(&head,infix[i]);
			//printStack(topOfStack);
		}
		else if(infix[i]=='('){
			push(&head, '(');
		}
		else if(infix[i]==')'){
			printf("test");
			if(isOperator(stackTop(head))){
				while(stackTop(head)!='('){
					
					char toPostfix = pop(&head);
					postfix[nextInPostfix++] = infix[i];
					push(&head,infix[i]);}
				}
				pop(&head);
			}



			else {
				stackTop(head);
				postfix[nextInPostfix++] = infix[i];
		}
		if(isEmpty(head)) {
			printf("isempty1\n");
			return;
		}
		printStack(head);
		printf("%s\n",postfix);
	}


}


int isOperator( char c ){
	int i;
	for(i = 0; i<sizeof(PRECEDENCE); i++){
		if(PRECEDENCE[i]==c){
			//printf("%c is an operator\n",c);
			return 1;
		}
	}
	//printf("%c is not an operator\n",c);
	return 0;
}

int precedence ( char operator1, char operator2 ){
	int i, j;
	for(i = 0; i<sizeof(PRECEDENCE); i++){
		if(PRECEDENCE[i]==operator1) break;
	}
	for(j = 0; j<sizeof(PRECEDENCE); j++){
		if(PRECEDENCE[j]==operator2) break;
	}
	if(i>j) return 1;
	if(i==j) return 0;
	return -1;
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