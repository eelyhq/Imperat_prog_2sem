#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    char* regs [256];
} State;

//loads string A from I-th register ([idx0] contains its index)
//loads string B from J-th register ([idx1] contains its index)
//then stores concatenation of A and B into I-th register
//BEWARE: [idx0] and [idx1] are allowed to be equal indices
void concat_2(State* state, char* idx0, char* idx1)
{
    int i = atoi(idx0); // get int indexes from string
    int j = atoi(idx1);

    int len_i = strlen(state -> regs[i]); // str lengths
    int len_j = strlen(state -> regs[j]);

    int size_of_two_strings = len_i + len_j; // sum of str lengths

    char* concat_string = (char*)malloc(sizeof(char) * (size_of_two_strings + 2)); // create a buffer with enough space for two concat strings

    memcpy(concat_string, state -> regs[i], sizeof(char) * (strlen(state -> regs[i]) + 1)); // copy first str in new var

    strcat(concat_string, state -> regs[j]); // concat first and second str in new var

    free(state -> regs[i]); // free memory from old string

    state -> regs[i] = concat_string; // store concat string in i-th register
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

    int num_tokens = 0; // there are at least one token

    char* token = strtok(arg, separator); // take frist arg, there at least one

    while (token != NULL)
    {
        num_tokens++;
        char* new_token = (char*)malloc(sizeof(char) * (strlen(token) + 1)); // allocate memory for token, which will used in regs

        strcpy(new_token, token);
        if (state -> regs[num_tokens] != NULL) free(state -> regs[num_tokens]);
        state -> regs[num_tokens] = new_token;
        token = strtok(NULL, separator);
    }

    char* num_tokens_str = (char*)malloc(sizeof(char) * 11); // allocate memory for one int
    sprintf(num_tokens_str, "%d", num_tokens); // make string from int
    if (state -> regs[0] != NULL) free(state -> regs[0]);
    state -> regs[0] = num_tokens_str;
}