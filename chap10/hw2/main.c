#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct node {
	int data;
	struct node *next;
};


void init(struct node *q, struct node *head, struct node *tail) {
    q -> head = q -> tail = NULL;  
}


void addq(struct node *head, struct node *tail, int data);



int delete(struct node *head, struct node *tail);



int main() {
	char a[100];
	int i = 0;
	while(1) {
	scanf("%d", &node.data);
    addq(node.data);
	a[] += node.data;

	if(isdigit(a[i]) == 0){
      break;
	}
	i++;
	}
	pritnf("%d\n",node.data);

	}


}
