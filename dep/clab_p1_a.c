#include "stdio.h"
#include "stdlib.h"

// andy piggot bethel (y)

#define PRECEDENCE "+-*/%%^"
#define MAXSIZE 100
#define DEBUG 1

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

	StackNode new;
	new.nextPtr=NULL;
	new.data='\0';

	StackNodePtr topOfStack = &new;

	int inputLen;
	if(DEBUG==1) printf("address of pointer to top is %p\n", &topOfStack);
	push(&topOfStack,'(');
	if(DEBUG==1) printf("pointer to top is %p\n", topOfStack);

	for(int i = 0; i<MAXSIZE; i++){
		if(infix[i]=='\0'){
			infix[i]=')';
			infix[i+1]='\0';
			inputLen = i;
			break;
		}
	}

	int nextInPostfix = 0;

	if(DEBUG==1) printf("infix is now %s\n",infix);
	if(DEBUG==1) printf("address of pointer to top is %p\n", &topOfStack);
	if(DEBUG==1) printf("pointer to top is %p\n", topOfStack);
	if(DEBUG==1) printf("top of stack is %c\n", (topOfStack)->data);

	for(i = 0; i<inputLen; i++){
		if(isOperator(infix[i])){
			if(DEBUG==1) printf("1\n");
			while(isOperator(stackTop(topOfStack))){
				if(precedence(stackTop(topOfStack),infix[i])>=0){
					char toPostfix = pop(&topOfStack);
					postfix[nextInPostfix++] = toPostfix;

				}

			}
			push(&topOfStack,infix[i]);
			//printStack(topOfStack);
		}
		else if(infix[i]=='('){
			if(DEBUG==1) printf("2\n");
			push(&topOfStack, '(');
		}
		else if(infix[i]==')'){
			if(DEBUG==1) printf("3\n");
			if(isOperator(stackTop(topOfStack))){
				if(DEBUG==1) printf("4\n");
				while(stackTop(topOfStack)!='('){
					if(DEBUG==1) printf("5\n");
					char toPostfix = pop(&topOfStack);
					postfix[nextInPostfix++] = infix[i];
					push(&topOfStack,infix[i]);}
				}
				pop(&topOfStack);
			}



			else {
				stackTop(topOfStack);
				if(DEBUG==1) printf("6\n");
				postfix[nextInPostfix++] = infix[i];
		}
		if(isEmpty(topOfStack)) return;

	}


}


int isOperator( char c ){
	int i;
	for(i = 0; i<sizeof(PRECEDENCE); i++){
		if(PRECEDENCE[i]==c){
			printf("%c is an operator\n", c);
			return 1;
		}
	}
	printf("%c is not an operator\n", c);
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

void push( StackNodePtr *topPtrPtr, char value){
	StackNode new;
	new.data=value;
	new.nextPtr=(*topPtrPtr);
	*topPtrPtr=&new;
	printf("Pushed '%c' to stack\n",value);
	if(DEBUG==1) printf("address of pointer to top is %p\n", topPtrPtr);
	if(DEBUG==1) printf("pointer to top is %p\n", &new);
}

char pop (StackNodePtr *topPtrPtr){
	char ans = (*topPtrPtr)->data;
	*topPtrPtr= (*topPtrPtr)->nextPtr;
	printf("Popped '%c' from stack\n",ans);
	return ans;
}

char stackTop ( StackNodePtr topPtr){
	char c = (*topPtr).data;
	printf("top of stack is %c\n", c);
	return c;
}

int isEmpty( StackNodePtr topPtr ){
	if(stackTop(topPtr)=='\0'){
		printf("isEmpty returned 1\n");
		return 1;
	}
	printf("isEmpty returned 0\n");
	return 0;
}

void printStack( StackNodePtr topPtr){
	if(topPtr==NULL) return;
	char c = (*topPtr).data;
	StackNodePtr next = (*topPtr).nextPtr;
	printf("%c\t",c);
	printStack(next);
}
