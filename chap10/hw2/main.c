#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if (head->next == NULL) {
        head->next = new_node;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int delete(struct node *head, struct node *tail) {
    if (head->next == NULL) {
        return -1;
    }

    struct node *temp = head->next;
    int data = temp->data;
    head->next = temp->next;

    if (head->next == NULL) {
        tail->next = NULL;
    }

    free(temp);
    return data;
}

int main() {
    struct node head = {0, NULL};
    struct node tail = {0, NULL};
    char input[20];

    while (1) {
        scanf("%s", input);

        int is_number = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                is_number = 0;
                break;
            }
        }

        if (is_number) {
            int value = atoi(input);
            addq(&head, &tail, value);
        } else {
            printf("Print queue\n");
            struct node *current = head.next;
            while (current != NULL) {
                printf("%d\n", current->data);
                current = current->next;
            }
            break;
        }
    }

    return 0;
}

