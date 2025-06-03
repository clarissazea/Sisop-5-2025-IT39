#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

unsigned int seed = 12345;

int textColor = 0x07;
enum GCType { NONE, STORM, SERPENT, FLAME };
enum GCType currentGC = NONE;

void shell() {
    char buf[128];
    char cmd[64];
    char args[2][64];
    char username[64];
    strcpy(username, "user");

    printString("Welcome to EorzeOS!\n");
    while (1) {
        printString(username);
        if (currentGC == STORM) printString("@Storm");
        else if (currentGC == SERPENT) printString("@Serpent");
        else if (currentGC == FLAME) printString("@Flame");
        printString("> ");

        readString(buf);
        parseCommand(buf, cmd, args);

        if (strcmp(cmd, "yo")) {
            printString("gurt\r\n");
        } else if (strcmp(cmd, "gurt")) {
            printString("yo\r\n");
        } else if (strcmp(cmd, "yogurt")) {
            handleYogurt();
        } else if (strcmp(cmd, "user")) {
            if (args[0][0] != '\0') {
                strcpy(username, args[0]);
                printString("Username changed to ");
                printString(username);
                printString("\r\n");
            } else {
                strcpy(username, "user");
                printString("Username changed to user\r\n");
            }
        } else if (strcmp(cmd, "grandcompany")) {
            if (strcmp(args[0], "maelstrom")) {
                textColor = 0x0C; // merah terang
                clearScreen(textColor);
                currentGC = STORM;
            } else if (strcmp(args[0], "twinadder")) {
                textColor = 0x0E; // kuning
                clearScreen(textColor);
                currentGC = SERPENT;
            } else if (strcmp(args[0], "immortalflames")) {
                textColor = 0x09; // biru
                clearScreen(textColor);
                currentGC = FLAME;
            } else {
                printString("Error: Unknown Grand Company\r\n");
            }
        } else if (strcmp(cmd, "clear")) {
            textColor = 0x07;
            clearScreen(textColor);
            currentGC = NONE;
            printString("Para Grand Company sedih, kamu netral.\r\n");
        } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
            if (args[0][0] == '\0' || args[1][0] == '\0') {
                printString("Error: Missing arguments\r\n");
            } else {
                int a = atoi(args[0]);
                int b = atoi(args[1]);
                int result = 0;
                char resStr[64];

                if (strcmp(cmd, "add")) result = a + b;
                else if (strcmp(cmd, "sub")) result = a - b;
                else if (strcmp(cmd, "mul")) result = a * b;
                else if (strcmp(cmd, "div")) result = div(a, b);

                itoa(result, resStr);
                printString(resStr);
                printString("\r\n");
            }
        } else {
            printString(buf);
            printString("\r\n");
        }
    }
}

void handleYogurt() {
    char responses[3][100];
    int count, tick;

    strcpy(responses[0], "yo");
    strcpy(responses[1], "ts unami gng </3");
    strcpy(responses[2], "sygau");
    count = 3;

    tick = mod(getBiosTick(), count);

    printString("gurt> ");
    printString(responses[tick]);
    printString("\r\n");
}

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
