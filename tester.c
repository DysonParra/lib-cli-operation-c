/*
 * @fileoverview    {FileName}
 *
 * @version         2.0
 *
 * @author          Dyson Arley Parra Tilano <dysontilano@gmail.com>
 *
 * @copyright       Dyson Parra
 * @see             github.com/DysonParra
 *
 * History
 * @version 1.0     Implementation done.
 * @version 2.0     Documentation added.
 */
#include "operation.h"
#include "tester.h"
#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Entrada principal del sistema.
 *
 * @param argc cantidad de argumentos pasados en la linea de comandos.
 * @param argv argumentos de la linea de comandos.
 * @return {0} si el programa se ejecutó correctamente.
 */
int main(int argc, char** argv) {
    /*-
    char array2[50];
    copyArray(array, array2, 6, 10);
    printf("-%s-\n", array2);
    */

    printFile("test/file.xml");

    /*-
    char input[500] = "abc\n\n\nc\t\te";
    char output[500] = "";
    printf("%s\n", input);
    printArray(input);
    printf("\n");
    sprintArray(output, input);
    printf("%s", output);
    */

    /*-
    char number[256] = "-.345";
    printf("%d\n", validateNumber(number, strlen(number)));
    printf("%f", getNumber((char*)"index=1\n"));
    */

    /*-
    char array[256] = "\"\"     aa \"prueaaa\" ?# \"esaaa\"  .html";
    printArray(array);
    printf("\n");
    printf("%d\n", isALetter(array[4]));
    printf("%d\n", iqualChar(array[4], 'A'));
    printf("%d\n", countCharacters(array, 'a'));
    */

    /*-
    char array1[256] = "()      AAaa \"prueaaa\" ?# \"esaaa\"  .html";
    char array2[50] = "()       aaAA ";
    printArray(array1);
    printf("\n");
    printArray(array2);
    printf("\n");
    printf("%d\n", compareArrays(array1, array2, 7));
    printf("%d\n", cmpArs(array1, array2, 7));
    */

    /*-
    char array[256] = "     \n()        aa \"pruebaaa\" ?# \"esaaa\"  .html\t\n";
    printArray(array);
    printf("\n");
    printf("%d\n", findWord(array, (char*)"ueb", 0, strlen(array)));
    printf("%d\n", findFirstDifferentChar(array, 3, ' ', '  ', '\n'));
    printf("%d\n", findLastDifferentChar(array, 3, ' ', '   ', '\n'));
    */

    /*-
    char array1[256] = " \n() ( ( \"12345\"--( \"pruebaaa\" ) ?# \"esaaa\")  .html\t";
    char array2[256] = "eoooo";

    printf("|");
    printArray(array1);
    printf("|\n");
    int pos = getTextBetween(array2, array1, (char*)"\"", (char*)"\"", 1);
    printf("|");
    printArray(array1);
    printf("|\n");

    printf("%d: |", pos);
    printArray(array2);
    printf("|\n");

    //if (pos != -1)
    //  printf("%s'\n", &array1[pos]);
    */

    /*-
    char array1[256] = "gcc -Wall -o -m -f -rm -a prub prub.c";
    //char array1[256] = "gcc";
    char* array2 = malloc(50000*sizeof(char));
    memcpy(array2, array1, strlen(array1)+1);
    printf("%p '%s'\n", array1, array1);
    printf("%p '%s'\n", array2, array2);

    char** flags = NULL;
    flags = splitArray(array2, (char*)" -");

    printf("\n%p\n", flags);
    for (int i =0; i<=1000; i++)
        if (flags[i] != NULL) {
            printf("%p '%s'\n", flags[i], flags [i]);
            if (i) {
                flags[i][-2] = ' ';
                flags[i][-1] = '-';
            }
        }
        else
            break;

    printf("\n%p\n", flags);
    free(flags);
    printf("\n%p\n", flags);
    */

    char* array;
    char array2[200];
    array = (char*)malloc(256 * sizeof(char));
    sprintf(array, "%s", "\"  \"\taa \"prueaaa\" ?# \"esaaa\"  .html");
    // sprintf(array, "%s", "NDV9fX1dfQ__&Signature=qrfnp");
    printf("'%s'\n", array);
    replaceWord(array, array2, (char*)"aa", (char*)"a");
    // replaceWord(array, array,(char*)"&", (char*)"%26");
    printf("'%s'\n", array);
    printf("'%s'\n", array2);

    /*-
    char array[256] = "123456789abcdefghijklmnopqrstuvwxyz";
    printf("'%s'\n", array);
    invertText(array, 9, 15);
    printf("'%s'\n", array);
    */

    /*-
    char array[256] = "\"prue:a\".html";
    printf("'%s'\n", array);
    replaceInvalidCharacters(array, (char*)"-");
    printf("'%s'\n", array);
    */

    /*-
    char* array;
    array = (char*)malloc(256*sizeof(char));
    sprintf(array, "%s", "Select a option:");
    //char array[400] = "ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®¬½¼¡«»░▒▓│┤ÁÂÀ©╣║╗╝¢¥┐└┴┬├─┼ãÃ╚╔╩ ╦╠═╬¤ðÐÊËÈıÍÎÏ┘┌█▄¦Ì▀ÓßÔÒõÕµþÞÚÛÙýÝ¯´≡±‗¾¶§÷¸°¨·¹³²■";
    printf("-%s-\n", array);
    replaceUTF8CharToAscii(array);
    printf("-%s-\n", array);
    */

    /*-
    printf("-%s-\n", array);
    replaceHtmlCharacters(array);
    printf("-%s-\n", array);
    */

    return 0;
}
