#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {

    int coeff;
    int expo;
    struct node *next;

} Node;

Node *createPoly(Node *, int);
Node *insert(Node *, int, int);
Node *addPoly(Node *, Node *, Node *);
void display(Node *);

int main() {
    Node *poly1 = NULL, *poly2 = NULL, *poly3 = NULL;
    int n1 = 0, n2 = 0;
    printf("\nEnter number of terms in polynomial 1: ");
    scanf("%d", &n1);
    printf("\n");

    poly1 = createPoly(poly1, n1);
    
    printf("\nFirst polynomial: ");
    display(poly1);
    printf("\n");
    
    printf("\nEnter number of terms in polynomial 2: ");
    scanf("%d", &n2);
    printf("\n");

    poly2 = createPoly(poly2, n2);

    printf("\nSecond polynomial: ");
    display(poly2);
    printf("\n");
    poly3 = addPoly(poly1 -> next, poly2 ->next, poly3);
    printf("\nResultant polynomial after addition: ");
    display(poly3);
    printf("\n\n-----Program successfully executed-----\n\n");

    return 0;
}

Node *createPoly(Node *poly_head, int n) {
    int coeff, expo;
    Node *new;

    // dummy head node 
    new = (Node *)malloc(sizeof(Node));

    if (new == NULL) {

        printf("ERROR: Memory not allocated\n");

        return NULL;
    }

    poly_head = new;

    new -> coeff = 0;
    new -> expo = -1;
    new -> next = NULL;

    for (int i = 1; i <= n; ++i) {
        
        printf("Enter power of x in term %d: ", i);
        scanf("%d", &expo);
        printf("Enter coefficient of x^%d: ", expo);
        scanf("%d", &coeff);
        
        poly_head = insert(poly_head, coeff, expo);
        
    }
    
    return poly_head;
}

Node *insert(Node *poly_head, int coeff, int expo) {

    Node *new, *temp;

    temp = poly_head -> next;

    new = (struct node *)malloc(sizeof(Node));

    new -> coeff = coeff;
    new -> expo = expo;
    new -> next = NULL;

    if (temp == NULL || expo > temp -> expo) {

        new -> next = temp;
        poly_head -> next = new;

    } else {

        while (temp -> next != NULL && temp -> next -> expo >= expo) {
            
            temp = temp -> next;
        
        }

        if (temp -> expo == expo) {

            temp -> coeff += coeff;

            free(new);

        }

        else {

            new -> next = temp -> next;
            temp -> next = new;

        }

    }

    return poly_head;
}

Node *addPoly(Node *poly1, Node *poly2, Node *result_poly) {

    int expo, coeff;
    Node *new;

    // Dummy node for resultant polynomial
    new = (Node *)malloc(sizeof(Node));

    new -> coeff = 0;
    new -> expo = -1;
    new -> next = NULL;

    result_poly = new;

    while (poly1 && poly2) {

        if (poly1 -> expo > poly2 -> expo) {

            expo = poly1 -> expo;
            coeff = poly1 -> coeff;

            result_poly = insert(result_poly, coeff, expo);

            poly1 = poly1 -> next;

        } else if (poly1 -> expo < poly2 -> expo) {

            expo = poly2 -> expo;
            coeff = poly2 -> coeff;

            result_poly = insert(result_poly, coeff, expo);

            poly2 = poly2 -> next;

        } else {

            expo = poly1 -> expo;
            coeff = poly1 -> coeff + poly2 -> coeff;

            result_poly = insert(result_poly, coeff, expo);

            poly1 = poly1 -> next;
            poly2 = poly2 -> next;

        }
    }

    while (poly1 || poly2) {

        if (poly1) {

            expo = poly1 -> expo;
            coeff = poly1 -> coeff;

            result_poly = insert(result_poly, coeff, expo);

            poly1 = poly1 -> next;

        }

        if (poly2) {

            expo = poly2 -> expo;
            coeff = poly2 -> coeff;

            result_poly = insert(result_poly, coeff, expo);

            poly2 = poly2 -> next;

        }

    }

    return result_poly;
}

void display(Node *poly_head) {

    Node *temp = NULL;

    temp = poly_head -> next;

    while (temp != NULL) {

        printf("%d(x^%d)", temp -> coeff, temp -> expo);

        temp = temp -> next;

        if (temp != NULL) {

            printf(" + ");

        }

    }

}