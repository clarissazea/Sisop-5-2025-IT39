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

// Menambahkan fungsi
void executeCommand(char *cmd, char arg[2][64]) {
  if (strCompare(cmd, "echo") == 0) {
    printString(arg[0]);
    printString("\n");
  } else if (strCompare(cmd, "clear") == 0) {
    clearScreen();
    setTextColor(0x07); // White (default)
    strCopy(currentPrompt, "user>");
  } else if (strCompare(cmd, "help") == 0) {
    printString("Available commands:\n");
    printString("  echo [text]              - Prints text\n");
    printString("  clear                    - Clears screen and reset color\n");
    printString("  grandcompany [name]      - Join a Grand Company\n");
    printString("     maelstrom, twinadder, immortalflames\n");
  } else if (strCompare(cmd, "grandcompany") == 0) {
    if (strCompare(arg[0], "maelstrom") == 0) {
      clearScreen();
      setTextColor(0x04); // Red
      strCopy(currentPrompt, "user@Storm>");
    } else if (strCompare(arg[0], "twinadder") == 0) {
      clearScreen();
      setTextColor(0x0E); // Yellow
      strCopy(currentPrompt, "user@Serpent>");
    } else if (strCompare(arg[0], "immortalflames") == 0) {
      clearScreen();
      setTextColor(0x01); // Blue
      strCopy(currentPrompt, "user@Flame>");
    } else {
      printString("Unknown Grand Company: ");
      printString(arg[0]);
      printString("\n");
    }
  } else {
    printString("Command not found: ");
    printString(cmd);
    printString("\n");
  }
}
