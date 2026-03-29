#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# pragma comment ( linker , "/ STACK :50000000 ")

#define MAX 500005

int pos = 0;

double ParseExpr(char* buffer);

char* ReadToken(char* buffer) {
    while (isspace(buffer[pos])) {
        pos++;
    }

    if (buffer[pos] == '\0') {
        return NULL;
    }

    if (buffer[pos] == '+' || buffer[pos] == '-' || buffer[pos] == '*' || buffer[pos] == '/' || \
        buffer[pos] == '(' || buffer[pos] == ')') {
        char* token = malloc(2 * sizeof(char));
        token[0] = buffer[pos];
        token[1] = '\0';
        pos++;
        return token;
    }

    int left = pos;

    while (isdigit(buffer[pos])) {
        pos++;
    }

    int len = pos - left;
    char* token = malloc(sizeof(char) * (len + 1));
    strncpy(token, buffer + left, len);
    token[len] = '\0';
    return token;
}

char*  PeekToken(char* buffer) {
    int oldPos = pos;
    char* token = ReadToken(buffer);
    pos = oldPos;
    return token;
}

double ParseAtom(char* buffer) {
    char* t = PeekToken(buffer);

    if (t == NULL) {
        return 0;
    }

    double res = 0;

    if (strcmp(t, "-") == 0)
    {
        free(t);
        free(ReadToken(buffer));
        res = -ParseAtom(buffer);
    }
    else if (strcmp(t, "(") == 0) {
        free(t);
        free(ReadToken(buffer));

        res = ParseExpr(buffer);

        free(ReadToken(buffer));
    }
    else {
        res = atof(t);
        free(t);
        free(ReadToken(buffer));
    }
    return res;
}

double ParseMonome(char* buffer) {
    double res = ParseAtom(buffer);
    char* token = PeekToken(buffer);
    while (token != NULL && (strcmp(token, "*") == 0 || strcmp(token, "/") == 0))
    {
        free(token);
        char* oper = ReadToken(buffer);

        double val = ParseAtom(buffer);

        if (strcmp(oper, "*") == 0)
        {
            res = res * val;
        }
        else
        {
            res = res / val;
        }

        free(oper);

        token = PeekToken(buffer);
    }
    if (token != NULL)
    {
        free(token);
    }
    return res;
}

double ParseExpr(char* buffer) {
    double res = ParseMonome(buffer);
    char* token = PeekToken(buffer);
    while (token != NULL && (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)) {
        free(token);
        char* oper = ReadToken(buffer);

        double val = ParseMonome(buffer);

        if (strcmp(oper, "+") == 0) {
            res = res + val;
        }
        else {
            res = res - val;
        }

        free(oper);

        token = PeekToken(buffer);

    }
    if (token != NULL)
    {
        free(token);
    }
    return res;
}

int main() {
    FILE* f_in = fopen("/home/eely/CLionProjects/Imperat_prog_2sem/15_pack/input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");

    char* buffer = malloc(sizeof(char) * MAX);

    fgets(buffer, MAX, f_in);

    double res = ParseExpr(buffer);

    fprintf(f_out,"%.12lf", res);

    fclose(f_in);
    fclose(f_out);

    return 0;
}