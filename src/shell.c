#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

unsigned int seed = 12345;  // seed awal untuk random

// Fungsi random sederhana (LCG)
// int rand() {
//     seed = (1103515245 * seed + 12345) & 0x7fffffff;
//     return seed;
// }

// Fungsi membandingkan dua string, hasil 1 jika sama, 0 jika beda
int strEquals(char *s1, char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return 0;
        }
        i++;
    }
    return s1[i] == '\0' && s2[i] == '\0';
}
void handleYogurt() {
    char responses[3][100];
    int count, index;
    int tick;

    strcpy(responses[0], "yo");
    strcpy(responses[1], "ts unami gng </3");
    strcpy(responses[2], "sygau");
    count = 3;

    tick = mod(getBiosTick(),count);
    // Simulasi mod_safe tanpa %
    // index = tick - (tick / count) * count;

    printString("gurt> ");
    // printString(strToInt(getBiosTick()));
    printString(responses[tick]);
    printString("\r\n");
}

// Fungsi konversi string ke integer
int strToInt(char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

// Fungsi konversi integer ke string tanpa memakai operator %
void intToStr(int num, char *str) {
    int i = 0;
    int isNegative = 0;
    int start, end;
    char temp;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int div = num / 10;
        int digit = num - div * 10;
        str[i++] = digit + '0';
        num = div;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    start = 0;
    end = i - 1;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Fungsi shell utama
void shell() {
    char buf[128];
    char cmd[64];
    char args[2][64];
    char username[64];
    strcpy(username, "user");

    printString("Welcome to EorzeOS!\n");
    while (1) {
        printString(username);
        printString("> ");
        readString(buf);

        parseCommand(buf, cmd, args);

        if (strEquals(cmd, "yo")) {
            printString("gurt\r\n");
        } 
        else if (strEquals(cmd, "gurt")) {
            printString("yo\r\n");
        }
        else if (strEquals(cmd, "yogurt")) {
            handleYogurt();
        }
        else if (strEquals(cmd, "user")) {
            if (args[0][0] != '\0') {
                strcpy(username, args[0]);
                printString("Username changed to ");
                printString(username);
                printString("\r\n");
            } else {
                strcpy(username, "user");
                printString("Username changed to user\r\n");
            }
        }
        else if (strEquals(cmd, "add") || strEquals(cmd, "sub") || strEquals(cmd, "mul") || strEquals(cmd, "div")) {
            if (args[0][0] == '\0' || args[1][0] == '\0') {
                printString("Error: Missing arguments\r\n");
            } else {
                int a = strToInt(args[0]);
                int b = strToInt(args[1]);
                int result = 0;
                char resStr[64];

                if (strEquals(cmd, "add")) {
                    result = a + b;
                } 
                else if (strEquals(cmd, "sub")) {
                    result = a - b;
                } 
                else if (strEquals(cmd, "mul")) {
                    result = a * b;
                } 
                else if (strEquals(cmd, "div")) {
                    if (b == 0) {
                        printString("Error: Division by zero\r\n");
                        continue;
                    }
                    result = a / b;
                }

                intToStr(result, resStr);
                printString(resStr);
                printString("\r\n");
            }
        }
        else {
            printString(buf);
            printString("\r\n");
        }
    }
}


// Fungsi parsing input perintah dan argumen
void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int argCount = 0;
    char *p = buf;
    int i;

    while (*p && (*p == ' ' || *p == '\t')) p++;

    i = 0;
    while (*p && *p != ' ' && *p != '\t' && i < 63) {
        cmd[i++] = *p++;
    }
    cmd[i] = '\0';

    while (argCount < 2) {
        while (*p && (*p == ' ' || *p == '\t')) p++;
        if (!*p) break;
        i = 0;
        while (*p && *p != ' ' && *p != '\t' && i < 63) {
            arg[argCount][i++] = *p++;
        }
        arg[argCount][i] = '\0';
        argCount++;
    }

    while (argCount < 2) {
        arg[argCount][0] = '\0';
        argCount++;
    }
}
