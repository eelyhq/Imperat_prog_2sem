#include "pack.h"
#include <string.h>
#include <stdarg.h>

int pack ( char * buffer , const char * format , ...) {
    va_list ap;
    va_start(ap, format);
    int len = 0;
    for (int i = 0; format[i] != '\0';) {
        if (format[i + 1] == 'd') {
            int val = va_arg(ap, int);
            if (buffer != NULL) {
                memcpy(buffer + len, &val, 4);
            }
            len += 4;
            i+=2;
        }
        else if (format[i+1] == 'l') {
            double val = va_arg(ap, double);
            if (buffer != NULL) {
                memcpy(buffer + len, &val, 8);
            }
            len += 8;
            i+=3;
        }
        else if (format[i+1] == 's') {
            char* val = va_arg(ap, char*);
            int str_len = strlen(val) + 1;
            if (buffer != NULL) {
                memcpy(buffer + len, val, str_len );
            }
            len += str_len;
            i+=2;
        }
    }
    va_end(ap);
    return len;
}