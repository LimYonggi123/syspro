#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = top->next;
    top->next = new_node;
}

int pop(struct node *top) {
    if (top->next == NULL) {
        return -1;
    }
    struct node *temp = top->next;
    int data = temp->data;
    top->next = temp->next;
    free(temp);
    return data;
}

int main() {
    struct node stack = {0, NULL};
    float input;

    while (1) {
        if (scanf("%f", &input) != 1) {
            break;
        }

        int value = (int)input;
        push(&stack, value);

        if (value != input) {
            printf("Print stack\n");

            struct node *current = stack.next;
            while (current != NULL) {
                printf("%d\n", current->data);
                current = current->next;
            }
            break;
        }
    }

    return 0;
}

