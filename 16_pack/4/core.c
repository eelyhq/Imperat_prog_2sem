#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    char* regs [256];
} State;

//prints ’ECHO: ’ and all passed strings separated by ’|’
void echo_0(State* state) { // just print "ECHO: " and nothing more
    printf("ECHO: \n");
}

void echo_1( State* state, char* arg0 ) {
    printf("ECHO: %s\n", arg0);
}

void echo_2(State* state, char* arg0, char* arg1 ) {
    printf("ECHO: %s|%s\n", arg0, arg1);
}

void echo_3( State* state, char* arg0, char* arg1, char* arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
}

//prints contents of I-th register (it must not be NULL)
//[idx] contains decimal representation of I
void print_1(State* state, char* idx) {
    int i = atoi(idx); // convert string index to int with func ascii to int
    printf("%s\n", state -> regs[i]);
}

//prints all non-NULL registers with their values (sorted by register number)
void printregs_0(State* state){
    for (int i = 0; i < 256; i++) {
        if (state -> regs[i] != NULL) {
            printf("%d = %s\n", i, state -> regs[i]); // print all non-NULL regs
        }
    }
}

//saves a copy of string [what] into I-th register
//[idx] contains decimal representation of I
void store_2(State* state, char* idx , char* what) {
    int i = atoi(idx); // convert string index to int with func ascii to int
    int len = strlen(what); //  this func doesn't include null terminator in string
    len++; // add null terminator to len

    state -> regs[i] = (char*)malloc(sizeof(char) * len); // allocate memory for register exactly the same as the line size

    memcpy(state -> regs[i], what, len); // strcpy use, when u don't know size of string otherwise memcpy more efficient
}

//copies contents of S-th register into D-th register (S-th register is not NULL)
//[dst] and [src] contain decimal representations of D and S respectively
//BEWARE: [dst] and [src] are allowed to be equal indices
void copy_2(State* state, char* dst, char* src) {
    int dst_i = atoi(dst);// convert strings index to int with func ascii to int
    int src_i = atoi(src);

    if (dst_i == src_i) { // there is equals indexes, so no need to do anything
        return;
    }

    free(state -> regs[dst_i]); // free memory to allocate correct size

    int len = strlen(state -> regs[src_i]); //  this func doesn't include null terminator in string
    len++; // add null terminator to len

    state -> regs[dst_i] = (char*)malloc(sizeof(char) * len); // allocate memory for register exactly the same as the line size

    memcpy(state -> regs[dst_i], state -> regs[src_i], sizeof(char) * len); // strcpy use, when u don't know size of string otherwise memcpy more efficient
}

//assigns NULL to I-th register
//[idx] contains decimal representation of I
void clear_1(State* state, char* idx ) {
    int i = atoi(idx);// convert strings index to int with func ascii to int

    free(state -> regs[i]); // free memory

    state -> regs[i] = NULL; // place null pointer
}