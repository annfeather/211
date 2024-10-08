#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **fgetlines(char ** list);
int comparator(const void *s, const void *l);
int count_str(char *buf, long);

struct data{
    char * buffer;
    char ** list_of_fucking_pointers;
    int cnt_str;
} all;

int main(void) {
    FILE *f = fopen("test.txt", "r");
    if (f == NULL) return EXIT_FAILURE;

    fseek(f, 0, SEEK_END);
    long len_f = ftell(f);
    rewind(f);
    all.buffer = (char *)malloc(sizeof(char) * len_f);
    if (all.buffer == NULL) return 2;
    size_t result = fread(all.buffer, sizeof(char), len_f, f);

    all.cnt_str = count_str(all.buffer, result);

    all.list_of_fucking_pointers = calloc(all.cnt_str, sizeof(char *));
    all.list_of_fucking_pointers = fgetlines(all.list_of_fucking_pointers);
    fclose(f);
    qsort(all.list_of_fucking_pointers, all.cnt_str, sizeof(char *), comparator);
////////////////////////////////////////OUTPUT///////////////////////////////////
    FILE *f2 = fopen("newOne.txt", "w");
    if (f2 == NULL) return EXIT_FAILURE;
    for (int i = 0; i < all.cnt_str; i++){
        printf("%s\n", all.list_of_fucking_pointers[i]);
        fputs(all.list_of_fucking_pointers[i], f2);
        fputs("\n", f2);
    }
    fclose(f2);
    free(all.list_of_fucking_pointers);
    free(all.buffer);
    return 0;
}

int count_str(char *buf, long len_) {
    int cnt = 0;
    for (int i = 0; i<len_ ; i++) {
        if (buf[i] != '\n') continue;
        cnt++;
    }
    cnt++;
    return cnt;
}

char **fgetlines(char ** list) {
    int sum = 0;
    for (int i = 0, num_str = 0; num_str < all.cnt_str ; i++) {
        if (all.buffer[i] == '\n') {
            all.buffer[i] = '\0';
            list[num_str] = all.buffer + sum;
            sum = i+1;
            num_str++;
        }
    }
    return list;
}

int comparator(const void *s, const void *l) {
    return strcmp(*(char **)s, *(char **)l);
}
