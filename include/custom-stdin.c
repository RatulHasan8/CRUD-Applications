#include <custom-stdin.h>

int readInt() {
    // Terminate all \n character in stdout, if it was printed right before calling this function
    scanf("\n");
    int invalid = 0, result = 0, multiply = 1;
    char current = '-';
    while (1) {
        scanf("%c", &current);
        if (current == '\n')
            break;
        if (current == '-' && result == 0) {
            multiply = -1;
            continue;
        }
        current -= '0';
        if (current >= 0 && current <= 9)
            result = (result * 10) + current;
        else
            invalid = 1;
    }
    if (invalid)
        result = 0;
    return result * multiply;
}

double readDouble() {
    scanf("\n");
    int multiply = 1;
    double result = 0, invalid = 0, decimalEnd = 0;
    char current = '-';
    while (1) {
        scanf("%c", &current);
        if (current == '\n')
            break;
        if (current == '-' && result == 0) {
            multiply = -1;
            continue;
        }
        if (current == '.')
            decimalEnd = 1;
        else {
            current -= '0';
            if (current >= 0 && current <= 9) {
                result = (result * 10) + current;
                decimalEnd *= 10;
            }
            else
                invalid = 1;
        }
    }
    if (invalid)
        return 0;
    return (result / (decimalEnd == 0 ? 1 : decimalEnd)) * multiply;
}

void readLine(int totalCharsToRead, char *cache) {
    scanf("\n");
    char current = '-';
    for (int i = 0; i < totalCharsToRead; i++) {
        scanf("%c", &current);
        if (current == '\n') {
            cache[i] = '\0';
            break;
        }
        cache[i] = current;
    }
}

// Unsafe method, because cache can run out of memory
void readWholeLine(char *cache) {
    scanf("\n");
    int i = 0;
    char current = '-';
    while (1) {
        scanf("%c", &current);
        if (current == '\n') {
            cache[i] = '\0';
            break;
        }
        cache[i++] = current;
    }
}