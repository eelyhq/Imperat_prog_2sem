#include <stdio.h>

int main()
{
    FILE* f_in = fopen("input.txt", "r");
    FILE* f_out = fopen("output.txt", "w");

    int c;
    int f1 = 0;
    int f4 = 0;

    while (1)
    {
        c = fgetc(f_in);

        if (c == '\\')
        {
            slashes++;
            continue;
        }

        if (c == '\n')
        {
            if (slashes > 0)
            {
                if (f4 == 0)
                {
                    fprintf(f_out, "[");
                    f4 = 1;
                }
                for (int k = 0; k < slashes; k++) fprintf(f_out, "\\");
            }
            break;
        }

        if (c == '"')
        {
            int n = slashes / 2;
            for (int k = 0; k < n; k++)
            {
                if (f4 == 0)
                {
                    fprintf(f_out, "[");
                    f4 = 1;
                }
                fprintf(f_out, "\\");
            }

            if (slashes % 2 == 1)
            {
                if (f4 == 0)
                {
                    fprintf(f_out, "[");
                    f4 = 1;
                }
                fprintf(f_out, "\"");
            }
            else
            {
                if (f4 == 0)
                {
                    fprintf(f_out, "[");
                    f4 = 1;
                }
                if (f1 == 0) f1 = 1; else f1 = 0;
            }
            slashes = 0;
        }
        else
        {
            if (slashes > 0)
            {
                if (f4 == 0)
                {
                    fprintf(f_out, "[");
                    f4 = 1;
                }
                for (int k = 0; k < slashes; k++) fprintf(f_out, "\\");
                slashes = 0;
            }

            if ((c == ' ' || c == '\t' || c == '\n') && f1 == 0)
            {
                if (f4 == 1)
                {
                    fprintf(f_out, "]\n");
                    f4 = 0;
                }
            }
            else
            {
                if (c != '\n' && c != '\r')
                {
                    if (f4 == 0)
                    {
                        fprintf(f_out, "[");
                        f4 = 1;
                    }
                    fprintf(f_out, "%c", c);
                }
            }
        }
    }

    if (f4 == 1)
    {
        fprintf(f_out, "]\n");
    }

    fclose(f_in);
    fclose(f_out);
    return 0;
}
