#include "shell.h"
#include "kernel.h"

int textColor = 0x07; //default (putih)

int main() {
  clearScreen(textColor);
  shell();
}

void printString(char *str) {
  while (*str != '\0') {
    interrupt(0x10, 0x0E00 + *str, 0, 0, 0);
    str++;
  }
}

void readString(char *buf) {
  int i = 0;
  char c;
  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0) & 0xFF;
    if (c == 13) {
      buf[i] = '\0';
      printString("\r\n");
      break;
    } else if (c == 8) {
      if (i > 0) {
        i--;
        printString("\b \b");
      }
    } else {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    }
  }
}

void clearScreen(textColor) {
  int i;
  int screenSize = 80 * 25;
  for (i = 0; i < screenSize; i++) {

    putInMemory(0xB800, i * 2, ' ');
    putInMemory(0xB800, i * 2 + 1, textColor);
  }

  interrupt(0x10, 0x0200, 0, 0, 0);
}
