#include "shell.h"
#include "kernel.h"

int textColor = 0x07; // default: putih

int main() {
    clearScreen();
    shell();
    while (1);
}

void printString(char *str) {
    while (*str != '\0') {
        interrupt(0x10, (0x0E << 8) + *str, textColor, 0, 0);
        str++;
    }
}

void readString(char *buf) {
    int i = 0;
    char c;

    while (1) {
        c = interrupt(0x16, 0, 0, 0, 0);

        if (c == 0x0D) {  // Enter
            buf[i] = '\0';
            printString("\r\n");
            break;
        } else if (c == 0x08) {  // Backspace
            if (i > 0) {
                i--;
                printString("\b \b");
            }
        } else {
            buf[i] = c;
            i++;
            interrupt(0x10, (0x0E << 8) + c, textColor, 0, 0);
        }
    }
}

void clearScreen() {
    int i;
    for (i = 0; i < 25 * 80; i++) {
        interrupt(0x10, (0x0E << 8) + ' ', 0x07, 0, 0);
    }
    interrupt(0x10, 0x0200, 0, 0, 0); // Kursor ke kiri atas
}
