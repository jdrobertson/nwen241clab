#include "stdio.h"

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

int isOperator( char c ){}

int precendence ( char operator1, char operator2 ){}

void push( StackNodePtr *topPtr, char value){}

char pop (StackNodePtr *topPtr, char value){}

char stackTop ( StackNodePtr topPtr){}

int isEmpty( StackNodePtr topPtr ){}

void printStack( StackNodePtr topPtr){}
