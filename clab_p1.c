#include "stdio.h"
#include "stdlib.h"

// andy piggot bethel (y)

#define PRECEDENCE "+-*/%%^" //defines the precedence order of operators (and serves as list for determining operator membership)
#define MAXSIZE 100 //defines max size of input, 100 should be easily sufficient for most purposes
#define Node_Size sizeof(StackNode) //macro for size of a node when allocating memory, just cleans up code

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

	char infix[MAXSIZE]; //defines char array to read input into
	scanf("%s",infix); //reads in infix string from user
	
	char postfix[MAXSIZE];
	printf("The original infix expression is:\n%s\n",infix);
	
	convertToPostfix(infix,postfix);
	
	printf("The expression in postfix notation is:\n%s\n",postfix);
	
	return 0;
}

void convertToPostfix( char infix[], char postfix[] ){

	StackNodePtr head = (StackNodePtr)malloc(Node_Size); //allocate memory for first node
	head->nextPtr=NULL; //the bottom node of stack always has nextPtr=NULL
	head->data='\0'; //the bottom node of stack always has data='\0' (escape character)

	int inputLen;
	push(&head,'('); //push a left parenthesis onto stack

	for(int i = 0; i<MAXSIZE; i++){ //this loop adds the right parenthesis to the infix string
		if(infix[i]=='\0'){
			infix[i]=')';
			infix[i+1]='\0';
			inputLen = i;
			break;
		}
	}

	int nextInPostfix = 0; //used to keep track of next available character in the postfix (output string)

	for(int i = 0; i<inputLen+1; i++){ //go through all of the input characters and process them ( plus one (the escape character))
		if(isOperator(infix[i])){ //if current input char is an operator
			while(isOperator(stackTop(head))){ //run this loop while the top item in the stack is an operator (except if broken)
				if(precedence(stackTop(head),infix[i])>=0){ //pop stack to postfix if the top stack operator is of higher precedence than the current input operator
					char toPostfix = pop(&head);
					printStack(head);
					postfix[nextInPostfix++] = toPostfix; //uses ++ after variable name to increment so it doesn't get overwritten

				}
				
				else break; //stops the loop running on the same character forever if the precedence is lesser

			}
			push(&head,infix[i]); //push the current operator onto the stack for future use
			printStack(head);
		}
		else if(infix[i]=='('){ //if current input char is ( then push it onto the stack
			push(&head, '(');
			printStack(head);
		}
		else if(infix[i]==')'){ //if current input char is )
			
			if(isOperator(stackTop(head))){ //if the top of the stack is an operator
				while(stackTop(head)!='('){ //pop off stack into postfix output until top of the stack is a left parenthesis
					char toPostfix = pop(&head);
					printStack(head);
					postfix[nextInPostfix++] = toPostfix; 
				}
				pop(&head); //pop off the extraneous parenthesis
				if(!isEmpty(head)) printStack(head);
			}
		}


		else { //if the input character is just a number then add it to postfix
				postfix[nextInPostfix++] = infix[i];
		}
		
		if(isEmpty(head)) {
			printf("The stack is empty.\n");
			postfix[nextInPostfix++] = '\0'; //adds end to postfix string so it prints correctly when compiled on ECS machines
			return;
		}
		
	}




}
int isOperator( char c ){
	int i;
	for(i = 0; i<sizeof(PRECEDENCE); i++){ //loop to check if c is in the list of operators (defined as PRECEDENCE, preprocessor directive)
		if(PRECEDENCE[i]==c){
			return 1;
		}
	}
	return 0;
}

int precedence ( char operator1, char operator2 ){
	int i, j;
	for(i = 0; i<sizeof(PRECEDENCE); i++){ //two loops which determine positions of given operators in the precendence list
		if(PRECEDENCE[i]==operator1) break;
	}
	for(j = 0; j<sizeof(PRECEDENCE); j++){ //second loop
		if(PRECEDENCE[j]==operator2) break;
	}
	if(i>j) return 1; //if precedence of operator 1 is greater then i will be larger than j, so returns 1
	if(i==j) return 0; //if precedence of operators is equal then return 0
	return -1; //otherwise op2 must be precedent over op1 so return -1
}

void push( StackNodePtr *topPtr, char value){
	StackNodePtr new = (StackNodePtr)malloc(Node_Size); //allocate memory for new node and assign address to pointer new
	new->data = value; //set data and nextPtr to new value and the previous top of stack
	new->nextPtr = (*topPtr);
	*topPtr = new; //set topPtr (used globally) to point to the new node
}

char pop (StackNodePtr *topPtr){
	if((*topPtr)->nextPtr==NULL){
		return '\0'; //do not pop off the default valued node (as this keeps the stack alive, so to speak)
	}
	char ans = (*topPtr)->data; //retrieve data from top stack item
	StackNodePtr toFree = *topPtr; //retrieve memory address to free
	*topPtr = (*topPtr)->nextPtr; // set global stack head pointer to the next node down
	free(toFree); //free the memory that was being used by the top node
	return ans;
}

char stackTop ( StackNodePtr topPtr){
	char ans = topPtr->data; //retrieve data from the top of the stack but do not change the stack
	return ans;
}

int isEmpty( StackNodePtr topPtr ){
	int ans;
	if(topPtr->nextPtr==NULL) ans = 1; //stack is empty if there is no address in the pointer to the next node (because head must be default node)
	else ans = 0;
	return ans;
}

void printStack( StackNodePtr topPtr){
	while(1){
		if(topPtr->nextPtr==NULL){
			printf("NULL\n"); //stop printing after the default node has been reached
			return;
		}
		char c = topPtr->data; //retrieve data to print
		printf("%c\t",c);
		topPtr = topPtr->nextPtr; //move the topPtr down one node so next time it will print a lower down stackNode (sequentially)
		
	}
}