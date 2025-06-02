#include "shell.h"
#include "kernel.h"

int main() {
    clearScreen();
    shell();
    while (1);
}

void printString(char *str)
{
  while (*str != '\0') {
    interrupt(0x10, 0x0E * 256 + *str, 0, 0, 0);
    str++;
  }
}

void readString(char *buf)
{
  int i = 0;
  char c;

  while (1) {
    c = interrupt(0x16, 0, 0, 0, 0);

    if (c == 0x0D) {
      buf[i] = '\0';
      printString("\r\n");
      break;
    } else if (c == 0x08) {
      if (i > 0) {
        i--;
        printString("\b \b");
      }
    } else {
      buf[i] = c;
      i++;
      interrupt(0x10, 0x0E * 256 + c, 0, 0, 0);
    }
  }
}

void clearScreen()
{
  int i;
  for (i = 0; i < 25 * 80; i++) {
    interrupt(0x10, 0x0E * 256 + ' ', 0, 0, 0);
  }

  interrupt(0x10, 0x0200, 0, 0, 0);
}
