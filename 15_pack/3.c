#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500005

int To

int pos = 0;

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

ParseExpr(char* buffer) {
    double res = ParseMonome(buffer);
    char* token = PeekToken(buffer);
    while (token != NULL && (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)) {
        char* oper = ReadToken(buffer);

        double val = ParseMonome(buffer);

        if (strcmp(oper, "+") == 0) {
            res = res + val;
        }
        else {
            res = res - val;
        }
        free(token);
        free(oper);

        token = PeekToken(buffer);
    }
    return res;
}

ParseMonome() {
bcmp()
}

double ParseAtom(char* buffer) {
    char* t = PeekToken(buffer);

    if (t == NULL) {
        return 0;
    }

    double res = 0;

    if (strcmp(t, "(") == 0) {
        free(t);
        free(ReadToken(buffer));

        res = ParseExpr(buffer);

        ReadToken(buffer);

        free(ReadToken(buffer));
    }
    else {
        res = atof(t);
        free(t);
        free(ReadToken(buffer));
    }
    return res;
}

int main() {
    FILE* f_in = fopen("input.txt", "r");

    char* buffer = malloc(sizeof(char) * MAX);

    fgets(buffer, MAX, f_in);


}