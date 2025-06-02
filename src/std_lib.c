#include "std_lib.h"

int div(int a, int b)
{
    if (b == 0) {
        printString("Error: Division by zero\r\n");
        return '\0';
    }
    return a / b;
}

int mod(int a, int b)
{
    int negatif;
    int cek_pembagi;
    int shift;

    if (b == 0) return -1;

    negatif = 0;
    if (a < 0) { a = -a; negatif = 1; }
    if (b < 0) { b = -b; }

    cek_pembagi = b;
    shift = 0;

    while ((cek_pembagi << 1) <= a) {
        cek_pembagi <<= 1;
        shift++;
    }

    while (shift >= 0) {
        if (a >= cek_pembagi) {
            a -= cek_pembagi;
        }
        cek_pembagi >>= 1;
        shift--;
    }

    return negatif ? -a : a;
}

int strcmp(char *str1, char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

void strcpy(char *dst, char *src)
{
    while ((*dst++ = *src++));
}

void clear(byte *buf, unsigned int size)
{
    unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

int atoi(char *str)
{
    int result;
    int sign;
    int i;
    
    result = 0;
    sign = 1;
    i = 0;

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

void itoa(int num, char *str)
{
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
