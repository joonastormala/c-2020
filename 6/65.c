#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct studentqueue {
    char *name;  // Name of queue member (dynamically allocated)
    struct studentqueue *next;  // (pointer to next queue member)
};

int enqueue(struct studentqueue *q, const char *name)
{
    while(q->next != NULL){
        q = q->next;
    }
    struct studentqueue *new = malloc(sizeof(struct studentqueue));
    new->name = malloc(strlen(name)+1);
    strcpy(new->name, name);
    
    q->next = new;
    new->next = NULL;

    return 1;
}

int dequeue(struct studentqueue *q, char *buffer, unsigned int size)
{
    struct studentqueue *f = q->next;

    if(f == NULL){
        return 0;
    }
    strncpy(buffer, f->name, size);
    buffer[size-1] = '\0';
    q->next = f->next;
    free(f->name);
    free(f);

    return 1;
}

int main(void)
{
    struct studentqueue q = { NULL, NULL };

    int go_on = 1;
    char buffer[100];
    while(go_on) {
        printf("Enter name of the student (\"-\" will end reading): ");
        scanf("%99s", buffer);
        buffer[99] = 0;
        if (strlen(buffer) > 0 && strcmp(buffer, "-")) {
            go_on = enqueue(&q, buffer);
        } else {
            go_on = 0;
        }
    }

    while(dequeue(&q, buffer, 100)) {
	    printf("Fetched %s from queue\n", buffer);
    }

    return 0;
}
