#include <stdio.h>
#include <stdlib.h>
struct element {
    float coff;
    int pow;
    struct element *next;
};

struct element *create(struct element *t, int n) {
    struct element *p = t;

    for (int i = n + 1; i > 0; i--) {
        p->next = malloc(sizeof(struct element));
        printf("type coeffision %d\n", i);
        scanf("%f", &p->coff);
        p->pow = i - 1;
        p = p->next;
        p->next = NULL;
    }
    return t;
}

float insertX(struct element *t, float x) {
    float result = 0.0;
    struct element *p = t->next;
    while (p != NULL) {
        int h = 1;
        for (int i = 0; i < p->pow; i++) {
            h *= x;
        }
        result += h * p->coff;
        p = p->next;
    }
    return result;
}

void prifirstList(struct element *t, int n) {
    struct element *p = t->next;
    while (p != NULL) {
        if (p->next == NULL) {
            printf("%.1f ", p->coff);
        } else {
            printf("%.1f * x^%d + ", p->coff, p->pow);
        }
        p = p->next;
    }
}

struct element *deri(struct element *t) {
    struct element *p = t->next;
    struct element *d = malloc(sizeof(struct element));
    struct element *y = d;
    while (p != NULL) {
        if (p->pow > 0) {
            y->next = malloc(sizeof(struct element));
            y = y->next;
            y->coff = p->coff * p->pow;
            y->pow = p->pow - 1;
            y->next = NULL;
        }
        p = p->next;
    }
    return d;
}

struct element *addL(struct element *t, struct element *t2) {
    struct element *p1 = t->next, *p2 = t2->next;
    struct element *result = malloc(sizeof(struct element));
    struct element *r = result;

    while (p1 != NULL || p2 != NULL) {
        r->next = malloc(sizeof(struct element));
        r = r->next;

        if (p1 != NULL && (p2 == NULL || p1->pow > p2->pow)) {
            r->coff = p1->coff;
            r->pow = p1->pow;
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p2->pow > p1->pow)) {
            r->coff = p2->coff;
            r->pow = p2->pow;
            p2 = p2->next;
        } else {
            r->coff = p1->coff + p2->coff;
            r->pow = p1->pow;
            p1 = p1->next;
            p2 = p2->next;
        }
        r->next = NULL;
    }
    return result;
}

struct element *MULT(struct element *t, struct element *t2, int n) {
    struct element *p1 = t->next;
    struct element *result = malloc(sizeof(struct element));
    result->next = NULL;

    while (p1 != NULL) {
        struct element *p2 = t2->next;
        while (p2 != NULL) {
            struct element *temp = result->next;
            int found = 0;
            while (temp != NULL) {
                if (temp->pow == p1->pow + p2->pow) {
                    temp->coff += p1->coff * p2->coff;
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found) {
                struct element *newNode = malloc(sizeof(struct element));
                newNode->coff = p1->coff * p2->coff;
                newNode->pow = p1->pow + p2->pow;
                newNode->next = result->next;
                result->next = newNode;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return result;
}

int main() {
    int n, z, m, o;
    float x;
    struct element *t = malloc(sizeof(struct element));
    t->next = NULL;
    printf("type the degree of the polynome \n");
    scanf("%d", &n);
    create(t, n);
    printf("the function :\n");
    printf("f (x) =");
    prifirstList(t, n);

    struct element *t2 = malloc(sizeof(struct element));
    t2->next = NULL;
    printf("\n type the degree of the polynome 2 \n");
    scanf("%d", &m);
    create(t2, m);
    printf("\n the function :\n");
    printf("g (x) =");
    prifirstList(t2, m);

    printf("\n choose an operator \n 1 : the result of function on one point x \n 2 : the Derivative of a function \n 3 : addition of two polynome\n 4 : multiplication of two polynome \n");
    scanf("%d", &o);
    switch (o) {
        case 1:
            printf("type the unknown X\n");
            scanf("%f", &x);
            printf("\n choose a function \n 1 : f\n 2 : g\n");
            scanf("%d", &z);
            if (z == 1) {
                printf("\n f(%.2f) = %.2f \n", x, insertX(t, x));
            } else if (z == 2) {
                printf("\n g(%.2f) = %.2f \n", x, insertX(t2, x));
            }
            break;
        case 2:
            printf("\n choose a function \n 1 : f\n 2 : g\n");
            scanf("%d", &z);
            if (z == 1) {
                printf("f'(x) = ");
                prifirstList(deri(t), n);
            } else if (z == 2) {
                printf("g'(x) = ");
                prifirstList(deri(t2), n);
            }
            break;
        case 3:
            printf("f(x) + g(x) =");
            prifirstList(addL(t, t2), n + m);
            break;
        case 4:
            printf("f(x) * g(x) =");
            prifirstList(MULT(t, t2, n), n + m);
            break;
    }
    return 0;
}
