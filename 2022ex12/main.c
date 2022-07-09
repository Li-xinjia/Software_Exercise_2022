#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct school_record SRec;
struct school_record {
    float gpa;
    int credit;
    char name[200];
    SRec *next;
    SRec *left, *right;
};

typedef int compare_func(const void *, const void *);


SRec *input(char *file) {
    FILE *infp;
    infp = fopen(file, "r");
    if (infp == NULL) {
        printf("Read input file error.\n");
        return NULL;
    }
    SRec *head = NULL;

    head = malloc(sizeof(SRec));
    int have_gpa = fscanf(infp, "%f", &(head->gpa));
    int have_credit = fscanf(infp, "%d", &(head->credit));
    int have_name = fscanf(infp, "%s", &(head->name[0]));

    if ((have_gpa & have_credit & have_name) != 1) {
        printf("Empty file or file is broken.\n");
        free(head);
        return NULL;
    }

    SRec *tail = head;
    SRec *temp;
    do {
        temp = tail;
        tail->next = malloc(sizeof(SRec));
        tail = tail->next;

        tail->right = NULL;
        tail->left = NULL;

        have_gpa = fscanf(infp, "%f", &(tail->gpa));
        have_credit = fscanf(infp, "%d", &(tail->credit));
        have_name = fscanf(infp, "%s", &(tail->name[0]));

    } while ((have_gpa & have_credit & have_name) == 1);
    temp->next = NULL;
    free(tail);
    fclose(infp);
    return head;
}

int output(char *file, SRec *sr) {
    FILE *outfp;
    SRec *selected = sr;
    outfp = fopen(file, "w");
    if (outfp == NULL) {
        printf("Write output file error.\n");
        return 1;
    }
    while (selected != NULL) {
        fprintf(outfp, "%.1f %d %s\n", selected->gpa, selected->credit, selected->name);
        selected = selected->next;
    }
    fclose(outfp);
    return 0;
}

SRec *listsort(SRec *list, compare_func *compare) {
    SRec *header = list, *tree = list;

    while (header->next) {
        int order = compare(header->next, tree);
        if (order > 0 && tree->right == NULL) {
            tree->right = header->next;
        } else if (order > 0) {
            tree = tree->right;
            continue;
        } else if (tree->left == NULL) {
            tree->left = header->next;
        } else {
            tree = tree->left;
            continue;
        }
        header = header->next;
        tree = list;
    }
    return tree;
}

int cmpgpa(const void *a, const void *b) {
    return ((SRec *) a)->gpa > ((SRec *) b)->gpa ? 1 : -1;
}

int cmpcredit(const void *a, const void *b) {
    return ((SRec *) a)->credit > ((SRec *) b)->credit ? 1 : -1;
}

int cmpname(const void *a, const void *b) {
    return strcmp(((SRec *) a)->name, ((SRec *) b)->name);
}

SRec *scan(SRec *node, SRec *next) {
    SRec *head = node;

    if (node->left != NULL) {
        head = scan(node->left, node);
    }
    node->next = next;

    if (node->right != NULL) {
        node->next = scan(node->right, next);
    }
    return head;
}

int main(int argc, char *argv[]) {
    SRec *sorted, *date_p;

    if (argc != 4) {
        fprintf(stderr, "Error: wrong number of parameter. Need 4. Now is %d.\n", argc);
        return 1;
    }
    char *mode = argv[1];
    date_p = input(argv[2]);
    if (date_p == NULL) {
        return 1;
    }

    if (strcmp(mode, "gpa") == 0) {
        date_p = listsort(date_p, cmpgpa);
        sorted = scan(date_p, NULL);
    } else if (strcmp(mode, "credit") == 0) {
        date_p = listsort(date_p, cmpcredit);
        sorted = scan(date_p, NULL);
    } else if (strcmp(mode, "name") == 0) {
        date_p = listsort(date_p, cmpname);
        sorted = scan(date_p, NULL);
    } else {
        printf("Don't know what to sort.\n");
        return 1;
    }
    if (output(argv[3], sorted)) {
        return 1;
    }
}