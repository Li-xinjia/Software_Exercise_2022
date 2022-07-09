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
    SRec *header = list, **pp, **now ;
    SRec *temp,*temp_header=NULL;
    if (header == NULL) {
        return NULL;
    }
    while (header->next != NULL) {
        pp = &header;
        now = &header;
        do {
            now = &(*now)->next;
            if (compare(*pp, *now) < 0) {
                pp = now;
            }
        } while ((*now)->next != NULL);
        temp = *pp;
        *pp = (*pp)->next;
        temp->next = temp_header;
        temp_header = temp;
    }
    header->next = temp_header;
    return header;
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

int main(int argc, char *argv[]) {
    SRec *date_p;

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
    } else if (strcmp(mode, "credit") == 0) {
        date_p = listsort(date_p, cmpcredit);
    } else if (strcmp(mode, "name") == 0) {
        date_p = listsort(date_p, cmpname);
    } else {
        printf("Don't know what to sort.\n");
        return 1;
    }
    if (output(argv[3], date_p)) {
        return 1;
    }
}