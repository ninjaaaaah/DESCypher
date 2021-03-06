#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DEBUG
#define print_bin(array, length)     \
    for (int i = 0; i < length; i++) \
        printf("%d", array[i]);
#define print_hex(bin, size)                                                                          \
    for (int i = 0; i < size / 4; i++)                                                                \
    {                                                                                                 \
        int num = (bin[i * 4] << 3) + (bin[i * 4 + 1] << 2) + (bin[i * 4 + 2] << 1) + bin[i * 4 + 3]; \
        printf("%X", num);                                                                            \
    }
#define print_row(left, right, key) \
    print_hex(left, 32);            \
    printf("\t");                   \
    print_hex(right, 32);           \
    printf("\t");                   \
    print_hex(key, 48);             \
    printf("\n");
#define debug_hex(array, length) \
    print_hex(array, length)     \
        printf("\n");
#else
#define print_bin(array, length)     \
    for (int i = 0; i < length; i++) \
        printf("%d", array[i]);
#define print_hex(array, length) \
    do                           \
    {                            \
    } while (0)
#define print_row(left, right, key) \
    do                              \
    {                               \
    } while (0)
#endif

char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

char *decimal_to_binary(int decimal)
{
    char *binary = (char *)malloc(sizeof(char) * 8);
    int i = 0;
    while (decimal > 0)
    {
        binary[i] = decimal % 2 + '0';
        decimal = decimal / 2;
        i++;
    }
    for (int j = i; j < 8; j++)
        binary[j] = '0';
    binary[8] = '\0';
    return strrev(binary);
}

void padPlainText(char *plainTextBin, char *paddedText)
{
    strncpy(paddedText, plainTextBin, 64);
    int len = strlen(paddedText);
    for (int i = len; i < 64; i++)
        strcat(paddedText, "0");
}

int *stoi(char *str, int len)
{
    int *arr = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        arr[i] = str[i] - '0';
    return arr;
}

int *atob(char *plaintext)
{
    char *plainTextBin = malloc(sizeof(char) * 8 * 20);
    memset(plainTextBin, 0, sizeof(plainTextBin));
    for (int i = 0; i < strlen(plaintext); i++)
        strcat(plainTextBin, decimal_to_binary((int)plaintext[i]));
    char paddedPlainText[64];
    padPlainText(plainTextBin, paddedPlainText);
    int *outBlock = malloc(sizeof(int) * 64);
    outBlock = stoi(paddedPlainText, 64);
    return outBlock;
}

int StraightPermutationTable[] =
    {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25};

int InitialPermutationTable[] =
    {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7};

int FinalPermutationTable[] =
    {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};

int ExpansionPermutationTable[] =
    {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1};

int SubstitutionTables[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

int ParityDropTable[] =
    {
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4};

int KeyCompressionTable[] =
    {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32};

int ShiftTable[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void permute(int n, int m, int *inBlock, int *outBlock, int *permutationTable)
{
    for (int i = 0; i < m; i++)
        outBlock[i] = inBlock[permutationTable[i] - 1];
}

void split(int n, int m, int *inBlock, int *leftBlock, int *rightBlock)
{
    for (int i = 0; i < m; i++)
    {
        leftBlock[i] = inBlock[i];
        rightBlock[i] = inBlock[i + m];
    }
}

void combine(int n, int m, int *leftBlock, int *rightBlock, int *outBlock)
{
    for (int i = 0; i < n; i++)
    {
        outBlock[i] = leftBlock[i];
        outBlock[i + n] = rightBlock[i];
    }
}

void shiftLeft(int block[28], int numOfShifts)
{
    for (int i = 0; i < numOfShifts; i++)
    {
        int T = block[0];
        for (int j = 1; j < 28; j++)
            block[j - 1] = block[j];
        block[27] = T;
    }
}

void exclusiveOr(int n, int *firstBlock, int *secondBlock, int *outBlock)
{
    for (int i = 0; i < n; i++)
        outBlock[i] = firstBlock[i] ^ secondBlock[i];
}

void key_generator(int keyWithParities[64], int RoundKeys[16][48])
{
    int cipherKey[56];
    int leftKey[28], rightKey[28];
    int preRoundKey[56];

    permute(64, 56, keyWithParities, cipherKey, ParityDropTable);
    split(56, 28, cipherKey, leftKey, rightKey);
    for (int round = 0; round < 16; round++)
    {
        shiftLeft(leftKey, ShiftTable[round]);
        shiftLeft(rightKey, ShiftTable[round]);
        combine(28, 56, leftKey, rightKey, preRoundKey);
        permute(56, 48, preRoundKey, RoundKeys[round], KeyCompressionTable);
        // debug_hex(RoundKeys[round], 48);
    }
}

void copy(int n, int *inBlock, int *outBlock)
{
    for (int i = 0; i < n; i++)
        outBlock[i] = inBlock[i];
}

void substitute(int *inBlock, int *outBlock)
{
    int row, col, value;
    for (int i = 0; i < 8; i++)
    {
        row = (inBlock[i * 6] << 1) + inBlock[i * 6 + 5];
        col = (inBlock[i * 6 + 1] << 3) + (inBlock[i * 6 + 2] << 2) + (inBlock[i * 6 + 3] << 1) + inBlock[i * 6 + 4];
        value = SubstitutionTables[i][row][col];

        for (int j = 0; j < 4; j++)
            outBlock[i * 4 + j] = (value >> (3 - j)) & 1;
    }
}

void function(int *inBlock, int *RoundKey, int *outBlock)
{
    int T1[48], T2[48], T3[32];
    permute(32, 48, inBlock, T1, ExpansionPermutationTable);
    exclusiveOr(48, T1, RoundKey, T2);
    substitute(T2, T3);
    permute(32, 32, T3, outBlock, StraightPermutationTable);
}

void swapper(int *inBlock, int *outBlock)
{
    int T[32];
    copy(32, inBlock, T);
    copy(32, outBlock, inBlock);
    copy(32, T, outBlock);
}

void mixer(int *leftBlock, int *rightBlock, int *RoundKey)
{
    int T1[32], T2[32], T3[32];
    copy(32, rightBlock, T1);
    function(T1, RoundKey, T2);
    exclusiveOr(32, leftBlock, T2, T3);
    copy(32, T3, leftBlock);
}

void cipher(int *plainBlock, int RoundKeys[16][48], int *cipherBlock)
{
    int inBlock[64], outBlock[64];
    int leftBlock[32], rightBlock[32];

    permute(64, 64, plainBlock, inBlock, InitialPermutationTable);
    split(64, 32, inBlock, leftBlock, rightBlock);
    for (int round = 0; round < 16; round++)
    {
        mixer(leftBlock, rightBlock, RoundKeys[round]);
        if (round != 15)
            swapper(leftBlock, rightBlock);
        // print_row(leftBlock, rightBlock, RoundKeys[round]);
    }
    combine(32, 64, leftBlock, rightBlock, outBlock);
    permute(64, 64, outBlock, cipherBlock, FinalPermutationTable);
    print_bin(cipherBlock, 64);
}

int paritycheck(int *key)
{
    for (int i = 0; i < 8; i++)
    {
        int parity = 0;
        for (int j = 0; j < 8; j++)
            parity += key[i * 8 + j];
        if (parity % 2 == 0)
            return 0;
    }
    return 1;
}

int main()
{
    char plainText[64];
    int ciphertext[64];
    char keyWithParities[65];
    memset(plainText, 0, 64);
    memset(keyWithParities, 0, 65);

    fgets(plainText, 64, stdin);
    fgets(keyWithParities, 65, stdin);

    if (strlen(plainText) > 20)
        plainText[20] = '\0';
    else
        plainText[strlen(plainText) - 1] = '\0';

    int *key = stoi(keyWithParities, 64);
    if (!paritycheck(key))
    {
        printf("invalid key\n");
        return 0;
    }

    int RoundKeys[16][48];
    key_generator(key, RoundKeys);
    int blocks = strlen(plainText) / 8 + (strlen(plainText) % 8 != 0);
    for (int i = 0; i < blocks; i++)
    {
        char *plainBlockString = malloc(sizeof(char) * 8);
        strncpy(plainBlockString, plainText + i * 8, 8);
        int *plainBlock = atob(plainBlockString);
        cipher(plainBlock, RoundKeys, ciphertext);
    }
    printf("\n");
    return 0;
}