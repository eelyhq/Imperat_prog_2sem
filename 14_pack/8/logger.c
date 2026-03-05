#include <stdio.h>
#include <stdarg.h>

FILE* stream = NULL;

int successful_calls = 0;

void logSetFile(FILE *file) {
    stream = file;
}

void logPrintf(const char *format, ...) {
    if (stream == NULL) {
        return;
    }
    va_list ap;
    va_start(ap, format);

    vfprintf(stream, format, ap);

    va_end(ap);
    successful_calls++;
}

int getLogCallsCount() {
    return successful_calls;
}
