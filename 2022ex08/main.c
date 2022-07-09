#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct school_record SRec;
struct school_record {
    float gpa;
    int credit;
    char name[200];
    SRec *next;
};

typedef int compare_func(const void *, const void *);

SRec *input(char *file, int *count) {
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

    if ((have_gpa & have_credit & have_name)!=1) {
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

        have_gpa = fscanf(infp, "%f", &(tail->gpa));
        have_credit = fscanf(infp, "%d", &(tail->credit));
        have_name = fscanf(infp, "%s", &(tail->name[0]));

        (*count)++;

    } while ((have_gpa & have_credit & have_name) == 1);
    temp->next = NULL;
    free(tail);
    fclose(infp);
    return head;
}

int output(char *file, SRec *sr, int count) {
    FILE *outfp;
    SRec *selected = sr;
    outfp = fopen(file, "w");
    if (outfp == NULL) {
        printf("Write output file error.\n");
        return 1;
    }
    for (int i = 0; i < count; ++i) {
        fprintf(outfp, "%.1f %d %s\n", selected->gpa, selected->credit, selected->name);
        selected = selected->next;
    }
    fclose(outfp);
    return 0;
}

int main(int argc, char *argv[]) {
    SRec *date_p;
    int count;

    if (argc != 4) {
        fprintf(stderr, "Error: wrong number of parameter. Need 4. Now is %d.\n", argc);
        return 1;
    }
    char *mode = argv[1];
    date_p = input(argv[2], &count);
    if (date_p == NULL) {
        return 1;
    }

    if (output(argv[3], date_p, count)) {
        return 1;
    }
}