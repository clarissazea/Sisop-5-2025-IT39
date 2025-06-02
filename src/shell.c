#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

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

// Fungsi shell utama
void shell() {
    char buf[128];
    char cmd[64];
    char args[2][64];
    char username[64];
    strcpy(username, "user");  // inisialisasi default username

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

    // Skip spasi/tab di awal
    while (*p && (*p == ' ' || *p == '\t')) p++;

    // Ambil command pertama
    i = 0;
    while (*p && *p != ' ' && *p != '\t' && i < 63) {
        cmd[i++] = *p++;
    }
    cmd[i] = '\0';

    // Ambil maksimal 2 argumen
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

    // Jika kurang dari 2 argumen, kosongkan sisanya
    while (argCount < 2) {
        arg[argCount][0] = '\0';
        argCount++;
    }
}
