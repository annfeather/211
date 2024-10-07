#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **fgetline(FILE *f);
int comparator(const void *s, const void *l);
static int j = 1;

int main() {
    if (fopen("test.txt", "r") == NULL)
        return EXIT_FAILURE;
    FILE *f = fopen("test.txt", "r");
    char **a = fgetline(f);
    fclose(f);
    qsort(a, j, sizeof(char *), comparator);
    FILE *f2 = fopen("newOne.txt", "w");
    if (f2 == NULL) return EXIT_FAILURE;
    for (int i = 0; i < j; i++){
        fputs(a[i], f2);
        fputs("\n", f2);
        free(a[i]);
    }
    fclose(f2);
    free(a);
    return 0;
}

char **fgetline(FILE *f) {
    const int size = 8;
    int c, cnt = 1, i = 0;
    char *st = malloc(sizeof(char)*size), *b, **pr = malloc(sizeof(char)*size), **pr1;
    pr = malloc(sizeof(char*) * size); // Выделение памяти для массива строк
    if (pr == NULL) exit(EXIT_FAILURE);
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            st[i] = 0;
            pr[j-1] = st;
            j++;
            if (j >= size) {
                pr1 = realloc(pr, sizeof(char*)*size*j);
                if (pr1 == NULL) exit(EXIT_FAILURE);
                pr = pr1;
            }
            i = 0;
            cnt = 1;
            st = NULL;
            continue;
        }
        b = realloc(st, sizeof(char)*size*cnt);
        if (b == NULL) {
            free(b);
            exit(EXIT_FAILURE);
        }
        st = b;
        st[i] = c;
        i++;
        if (i >= size*cnt*sizeof(char))
            cnt++;
    } 
    b = realloc(st, sizeof(char)*i);
    if (b == NULL) {
        free(b);
        exit(EXIT_FAILURE);
    }
    st = b;
    st[i] = 0;
    pr1 = realloc(pr, sizeof(char*)*j);
    pr = pr1;
    pr[j-1] = st;
    return pr;
}

int comparator(const void *s, const void *l) {
    return strcmp(*(char **)s, *(char **)l);
}
