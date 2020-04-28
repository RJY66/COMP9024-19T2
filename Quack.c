// Quack.c: an array-based implementation of a quack
#include "Quack.h"
#define HEIGHT 1000

struct node {
    int array[HEIGHT];
    int top;
};

Quack createQuack(void) {
    Quack q = malloc(sizeof(struct node));
    if (q == NULL) {
        fprintf (stderr, "createQuack: no memory, aborting\n");
        exit(1); // should pass control back to the caller
    }
    q ->top = -1;
    return q;
}

void push(int data, Quack q) {
    if (q == NULL) {
        fprintf(stderr, "push: quack not initialised\n");
    }
    else {
        if (q->top >= HEIGHT-1) {
            fprintf(stderr, "push: quack overflow\n");
        }
        else {
            q->top++;   //第一次push时，因为从-1开始，要先变成0，否则越界。
            q->array[q->top] = data;
        }
    }
    return;
}

void qush(int data, Quack q) { // adds data to the bottom of the array
    if (q == NULL) {
        fprintf(stderr, "qush: quack not initialised\n");
    }
    else {
        if (q->top >= HEIGHT-1) {
            fprintf(stderr, "qush: quack overflow\n");
        }
        else {
            q->top++;                     // next available spot
            int i;
            for (i=q->top; i>=1; i--) {
                q->array[i] = q->array[i-1];// move each element up 1
            }
            q->array[0] = data;
        }
    }
    return;
}


int pop(Quack q) { // return top element, or 0 if error
    int retval = 0;
    if (q == NULL) {
        fprintf(stderr, "pop: quack not initialised\n");
    }
    else {
        if (isEmptyQuack(q)) {
            fprintf(stderr, "pop: quack underflow\n");
        }
        else {
            retval = q->array[q->top]; // top element on stack
            q->top--;
        }
    }
    return retval;
}

void makeEmptyQuack(Quack q) {
    if (q == NULL) {
        fprintf(stderr, "makeEmptyQuack: quack not initialised\n");
    }
    else {
        while (!isEmptyQuack(q)) {
            pop(q);
        }
    }
    return;
}

Quack destroyQuack(Quack q) {
    if (q == NULL) {
        fprintf(stderr, "destroyQuack: quack not initialised\n");
    }
    free(q);
    return q;
}

int isEmptyQuack(Quack q) {
    int empty = 0;
    if (q == NULL) {
        fprintf(stderr, "isEmptyQuack: quack not initialised\n");
    }
    else {
        empty = q->top < 0;
    }
    return empty;
}

void showQuack(Quack q) {
    if (q == NULL) {
        fprintf(stderr, "showQuack: quack not initialised\n");
    }
    else {
        printf("Quack: ");
        if (q->top < 0) {      //为空
            printf("<< >>\n");
        }
        else {
            int i;
            printf("<<");                    // start with a <<
            for (i = q->top; i > 0; --i) {
                printf("%d, ", q->array[i]); // print each element
            }
            printf("%d>>\n", q->array[0]);   // last element includes a >>
        }
    }
    return;
}