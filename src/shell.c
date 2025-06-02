#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

unsigned int seed = 12345;  // seed awal untuk random
//emang ngaruh yh? ~Adly

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
    } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
      if (args[0][0] == '\0' || args[1][0] == '\0') {
        printString("Error: Missing arguments\r\n");
      } else {
        int a = atoi(args[0]);
        int b = atoi(args[1]);
        int result = 0;
        char resStr[64];

        if (strcmp(cmd, "add")) {
          result = a + b;
        } else if (strcmp(cmd, "sub")) {
          result = a - b;
        } else if (strcmp(cmd, "mul")) {
          result = a * b;
        } else if (strcmp(cmd, "div")) {
          result = div(a, b);
        }

        itoa(result, resStr);
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
    // printString(atoi(getBiosTick()));
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

// Tambahkan fungsi bila perlu
