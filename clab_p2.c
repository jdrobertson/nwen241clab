#include "stdio.h"
#include "stdlib.h"

// andy piggot bethel (y)

#define OPERATORS "+-*/%%^"
#define MAXSIZE 100 //defines max size of input, 100 should be easily sufficient for most purposes
#define Node_Size sizeof(StackNode) //macro for size of a node when allocating memory, just cleans up code

struct stackNode {
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int evaluatePostfixExpression( char *expr);
int calculate (int op1, int op2, char operator);
void push( StackNodePtr *topPtr, int value);
int pop ( StackNodePtr *topPtr);
int isEmpty( StackNodePtr topPtr );
void printStack( StackNodePtr topPtr);
int isOperator( char c);
int power(int power, int base);

int main(int argc, char const *argv[])
{
	printf("Enter a postfix expression:\n");

	char postfix[MAXSIZE]; //defines char array for entering the postfix expression
	scanf("%s",postfix); //reads postfix expression from user into the postfix variable
	
	int ans = evaluatePostfixExpression(postfix); //calls to evaluate the expression
	
	printf("The value of the expression is: %d\n",ans);
	
	return 0;
}

int evaluatePostfixExpression( char *expr ){

	StackNodePtr head = (StackNodePtr)malloc(Node_Size); //allocate memory for first node
	head->nextPtr=NULL; //the bottom node of stack always has nextPtr=NULL
	head->data='\0'; //the bottom node of stack always has data='\0' (escape character)
	
	char temp;
	
	//the code below is related to the request to add a '\0' character to the end of the postfix expression
	//in reality, when a user enters their expression the character is automatically added to denote the end of the string
	//so it is not really necessary to add this via code
	//the code below simply allows the user to verify that the character is contained within the expression, if necessary

	/*for(int i = 0; i<MAXSIZE; i++){
		temp = expr[i];
		if(temp=='\0'){
			printf("End of String character detected\n");
			break;
		}
	}*/

	for(int i = 0; i<MAXSIZE; i++){ //iterate through the expression
		temp = expr[i];
		if(temp=='\0') break; //break the loop at the end of the string
		if(isOperator(temp)){ //if the current char is an operator
			int x = pop(&head); //calculate the last two stack pushes with the current operator
			printStack(head);	//print stack whenever it is altered (recurring theme)
			int y = pop(&head);
			printStack(head);
			push(&head, calculate(x,y,expr[i])); //push the calculation result back onto the stack
		}
		else{
			int value = ((int) temp) - ((int) '0'); //if the character is not an operator it must be a number, so compute its value
			push(&head, value); //and push it onto the stack
		}
		printStack(head);


	}
	return pop(&head); //when the loop has finished running pop the last value of the stack and return it
}

int calculate( int op1, int op2, char operator){ //function to calculate with two operands and an operator
	if(operator=='+') return op2+op1;
	if(operator=='-') return op2-op1;
	if(operator=='*') return op2*op1;
	if(operator=='/') return op2/op1;
	if(operator=='^') return power(op1,op2); //uses fancy power function I wrote myself rather than using a library, just easier to manager and predict (and good practice)
	if(operator=='%') return op2%op1;
	return 0; //this should never happen because the only way this function could be called is with a valid operator, but it stops a compiler warning
}

void push( StackNodePtr *topPtr, int value){
	StackNodePtr new = (StackNodePtr)malloc(Node_Size); //allocate memory for new node and assign address to pointer new
	new->data = value; //set data and nextPtr to new value and the previous top of stack
	new->nextPtr = (*topPtr);
	*topPtr = new; //set topPtr (used globally) to point to the new node
}

int pop (StackNodePtr *topPtr){
	if((*topPtr)->nextPtr==NULL){
		return '\0'; //do not pop off the default valued node (as this keeps the stack alive, so to speak)
	}
	int ans = (*topPtr)->data; //retrieve data from top stack item
	StackNodePtr toFree = *topPtr; //retrieve memory address to free
	*topPtr = (*topPtr)->nextPtr; // set global stack head pointer to the next node down
	free(toFree); //free the memory that was being used by the top node
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
		int c = topPtr->data; //retrieve data to print
		printf("%d\t",c);
		topPtr = topPtr->nextPtr; //move the topPtr down one node so next time it will print a lower down stackNode (sequentially)

	}
}

int isOperator( char c ){ 
	int i;
	for(i = 0; i<sizeof(OPERATORS); i++){
		if(OPERATORS[i]==c){
			//printf("%c is an operator\n",c);
			return 1;
		}
	}
	//printf("%c is not an operator\n",c);
	return 0;
}

int power(int power, int base){ //my custom power function, works for any integers including a power of 0 which returns 1 in all cases
	int ans = 1;
	for(int i =0; i<power; i++){
		ans*=base;
	}
	return ans;
}