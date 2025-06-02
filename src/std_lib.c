#include "std_lib.h"

int div(int a, int b)
{
    int negatif;
    int hasil;
    int cek_pembagi;
    int shift;

    if (b == 0) return 0; 

    negatif = 0;
    if (a < 0) { a = -a; negatif ^= 1; }
    if (b < 0) { b = -b; negatif ^= 1; }

    hasil = 0;
    cek_pembagi = b;
    shift = 0;

    while ((cek_pembagi << 1) <= a) {
        cek_pembagi <<= 1;
        shift++;
    }

    while (shift >= 0) {
        if (a >= cek_pembagi) {
            a -= cek_pembagi;
            hasil |= (1 << shift);
        }
        cek_pembagi >>= 1;
        shift--;
    }

    return negatif ? -hasil : hasil;
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
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
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

void atoi(char *str, int *num)
{
    int result;
    int sign;

    result = 0;
    sign = 1;

    while (*str == ' ') str++;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    *num = result * sign;
}

// void itoa(int num, char *str)
// {
//     int i, is_negative, j, k;
//     char temp;

//     i = 0;
//     is_negative = 0;

//     if (num == 0) {
//         str[i++] = '0';
//         str[i] = '\0';
//         return;
//     }

//     if (num < 0) {
//         is_negative = 1;
//         num = -num;
//     }

//     while (num > 0) {
//         str[i++] = (num % 10) + '0';
//         num /= 10;
//     }

//     if (is_negative) {
//         str[i++] = '-';
//     }

//     str[i] = '\0';

//     for (j = 0, k = i - 1; j < k; j++, k--) {
//         temp = str[j];
//         str[j] = str[k];
//         str[k] = temp;
//     }
// }
