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



//loads string A from I-th register ([idx0] contains its index)
//loads string B from J-th register ([idx1] contains its index)
//then stores concatenation of A and B into I-th register
//BEWARE: [idx0] and [idx1] are allowed to be equal indices
void concat_2(State* state, char* idx0, char* idx1)
{
    int i = atoi(idx0); // get int indexes from string
    int j = atoi(idx1);

    int len_i = strlen(state[i]); // str lengths
    int len_j = strlen(state[j]);

    int size_of_two_strings = len_i + len_j; // sum of str lengths

    char* concat_string = (char*)malloc(sizeof(char) * (size_of_two_strings + 2)); // create a buffer with enough space for two concat strings

    memcpy(concat_string, state[i], sizeof(char) * strlen(state[i])); // copy first str in new var

    strcat(concat_string, state[j]); // concat first and second str in new var

    free(state[i]); // free memory from old string

    state[i] = concat_string; // store concat string in i-th register
}

//extracts sequence of tokens/words separated by underscore character from string [arg]
//puts K –- number of tokens into 0-th register
//puts the tokens into 1-th, 2-th, ..., K-th registers (in correct order)
void tokenize_1(State* state, char* arg )
{
    if (arg == NULL)
    {
        return;
    }
    if (strlen(arg) == 0)
    {
        return;
    }

    char* separator = "_"; // separator - underscore

    char* token = (char*)malloc(sizeof(char) * 1001); // because the longest arg may be 971 bytes
    int num_tokens = 0; // there are at least one token

    token = strtok(arg, separator);

    while (token)
    {
        num_tokens++;
        state[num_tokens] = token;
        char* token = (char*)malloc(sizeof(char) * 1001);
        token = strtok(arg, separator);
    }

    free(token); // because we create one extra token

    char* num_tokens_str = (char*)malloc(sizeof(char) * 11); // allocate memory for one int
    sprintf(num_tokens_str, "%d", num_tokens); // make string from int

    state[0] = num_tokens_str;
}


int main()
{

}
