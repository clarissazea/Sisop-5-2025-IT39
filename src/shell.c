#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

void shell(){
  char buf[128];
  printString("Welcome to EorzeOS!\n");
  while (true) {
    printString("user> ");
    readString(buf);
    printString(buf);
    printString("\r\n");
  }
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

// Tambahkan fungsi bila perlu
