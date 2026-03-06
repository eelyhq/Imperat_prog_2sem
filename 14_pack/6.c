#include <stdio.h>
#include <stdlib.h>

double Function(double);

int main()
{
    FILE* f_in = fopen("input.txt","r");
    FILE* f_out = fopen("output.txt","w");

    int M;

    fscanf(f_in ,"%d", &M);

    for (int i = 0; i < M; i++)
    {
        double x;
        fscanf(f_in,"%lf", &x);
        double delta = 0.00000001;
        double y_delta;
        double y = Function(x);
        double res;
        if (x + delta >= 1)
        {
            y_delta = Function(x - delta);
            res = (y - y_delta ) / delta;
        }
        else
        {
            y_delta = Function(x + delta);
            res = (y_delta - y) / delta;
        }
        fprintf(f_out, "%.15lf\n", res);
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}