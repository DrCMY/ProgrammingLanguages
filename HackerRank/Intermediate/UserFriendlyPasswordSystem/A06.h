#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define p 131
#define M pow(10,9) + 7

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'authEvents' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_STRING_ARRAY events as parameter.
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;matlab mod function in c++
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */

int* authEvents(int events_rows, int events_columns, char*** events, int* result_count) {

    int ctr, ctrx, ctrr = 0, i, j, k, l, a, *result, resultv[*result_count], flag;
    long double hv[123 - 65 + 1], h, temp;
    char *psw, ha[10];
    psw = (char *)malloc(10 * sizeof(char));
    result = (int *)malloc(events_rows * sizeof(int));
    for (i = 0; i < events_rows; i++){
        j = 0, ctr = 0;
        if (*(*(*(events+i)+j)+ctr) == 's') {
            j = 1;
            while (*(*(*(events+i)+j)+ctr) != '\0'){
                *(psw + ctr) = *(*(*(events+i)+j)+ctr);
                ctr++;
            }
            ctrx = ctr;
            h = 0;
            for (k = 0; k < ctrx; k++){
                a = (int)*(psw + k);
                temp = pow(p, ctrx - k - 1);
                h += (long double) a * temp;
            }
            h = fmod(h, M);
            ctr = 0;
            for (k = 65; k < 123; k++){
                hv[ctr] = 0;
                for (l = 0; l < ctrx ; l++){
                    a = (int)*(psw + l);
                    temp = pow(p, ctrx - l);
                    hv[ctr] += (long double) a * temp;
                }
                hv[ctr] += k;
                hv[ctr] = fmod(hv[ctr], M);
                ctr++;
            }
        }
        else {
            j = 1;
            ctr = 0;
            flag = 0;
            resultv[ctrr] = 0;
            while (*(*(*(events+i)+j)+ctr) != '\0'){
                ha[ctr] = *(*(*(events+i)+j)+ctr);
                ctr++;
            }
            while (ctr != 10)
                ha[ctr++] = '\0';

            long double haint = atoi(ha);
            if (haint == h){
                resultv[ctrr++] = 1;
                flag = 1;
            }
            else {
                ctr = 0;
                for (k = 65; k < 123; k++){
                    if (haint == hv[ctr]){
                        resultv[ctrr++] = 1;
                        flag = 1;
                    }
                    ctr++;
                }
            }
            if (flag == 0)
                ctrr++;
        }
    }
    result = &resultv;
    return result;
}

void A06(){

    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int events_rows = parse_int(ltrim(rtrim(readline())));

    int events_columns = parse_int(ltrim(rtrim(readline())));

    char*** events = malloc(events_rows * sizeof(char**));

    for (int i = 0; i < events_rows; i++) {
        *(events + i) = malloc(events_columns * (sizeof(char*)));

        char** events_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < events_columns; j++) {
            char* events_item = *(events_item_temp + j);

            *(*(events + i) + j) = events_item;
        }
    }

    int result_count = 2;
    int* result = authEvents(events_rows, events_columns, events, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d", *(result + i));
        //fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            printf("\n");
            //fprintf(fptr, "\n");
        }
    }

    printf("\n");
    //fprintf(fptr, "\n");

    //fclose(fptr);

};

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

