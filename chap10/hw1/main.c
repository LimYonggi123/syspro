#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SZIE 100;
int stack[MAX_STACK_SZIE];

struct node {
	int data;
	struct node *next;
};

void push(struct node *top, int data) {
    stack[++top] = data;
	return;
   
}

int pop(struct node *top) {
     return stack[top--];
}


int main() {
	int i;

	do {
	scanf("%d", &node.data);
	if((double)node.data % 1 != 0) {
		break;
	}
	push(data)
	i++;
	}while(1);

	printf("Print stack");
    for(int k = i; k <= 0; k--)
		node.data = pop();
	printf("%d", pop());

}

