#include "stdio.h"

#define PRECEDENCE "+-*/%%^"

struct stackNode {
	char data;
	struct stackNode *nextPtr;
};



typedef struct stackNode StackNode;

typedef StackNode* StackNodePtr;

void convertToPostfix( char infix[], char postfix[] );

int isOperator( char c );

int precendence ( char operator1, char operator2 );

void push( StackNodePtr *topPtr, char value);

char pop ( StackNodePtr *topPtr, char value);

char stackTop ( StackNodePtr topPtr);

int isEmpty( StackNodePtr topPtr );

void printStack( StackNodePtr topPtr);



int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

void convertToPostfix( char infix[], char postfix[] );

int isOperator( char c ){
	int i;
	for(i = 0; i<sizeof(PRECEDENCE); i++){
		if(PRECEDENCE[i]==c) return 1;
	}
	return 0;
}

int precendence ( char operator1, char operator2 ){
	int i, j;
	for(i = 0; i<sizeof(PRECEDENCE); i++){
		if(PRECEDENCE[i]==operator1) break;
	}
	for(j = 0; j<sizeof(PRECEDENCE); j++){
		if(PRECEDENCE[j]==operator2) break;
	}
	if(i<j) return 1;
	if(i==j) return 0;
	return -1;
}

void push( StackNodePtr *topPtr, char value){}

char pop (StackNodePtr *topPtr, char value){}

char stackTop ( StackNodePtr topPtr){}

int isEmpty( StackNodePtr topPtr ){}

void printStack( StackNodePtr topPtr){}
