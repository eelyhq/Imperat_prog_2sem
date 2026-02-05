#include <stdio.h>

int  main() {
    FILE* f_in = fopen("input.txt","r");
    FILE* f_out = fopen("output.txt","w");

    int c = ' ';
    char s1 = '[';
    char s2 = ']';
    char s3 = '\n';
    int f = 0;//флаг, идет ли сейчас строка  в двойных кавычках
    int f2 = 0;//флаг, идет ли сейчас строка непрерывная без кавычек
    int f3 = 0; //флаг, первая ли строка
    while( (c = fgetc(f_in)) != '\n'){
        if (c == '\"') {
            if (f == 0) {
                if (f3 == 1) {
                    fprintf(f_out,"%c", s3);
                }
                f = 1;
                fprintf(f_out,"%c", s1);
                f3 = 1;
            }
            else if (f == 1) {
                fprintf(f_out,"%c", s2);
                f = 0;
                f3 = 1;
            }
        }
        else if (f == 1) {
            fprintf(f_out,"%c", c);
            f3 = 1;
        }
        else {

            if (f2 == 0 && c != ' ') {
                if (f3 == 1) {
                    fprintf(f_out,"%c", s3);
                }
                fprintf(f_out,"%c", s1);
                fprintf(f_out,"%c", c);
                f3 = 1;
                f2 = 1;
            }
            else if (f2 == 1 && c == ' ') {
                fprintf(f_out,"%c", s2);
                f3 = 1;
                f2 = 0;
            }
            else if (f2 == 1) {
                fprintf(f_out,"%c", c);
                f3 = 1;
            }
        }
    }
    if (f2 == 1) {
        fprintf(f_out,"%c", s2);
        f3 = 1;
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}