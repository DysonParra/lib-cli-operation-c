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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

CALLING void copyArray(char* input, char* output, int start, int end);

#if (!defined STATIC_LIB_) && (!defined NO_DLL_MAIN_)
/**
 * Entrada principal de la dll (creado si no se indica que es biblioteca estática)
 *
 * @param instance identificador del módulo.
 * @param reason   razón de la llamada.
 * @param reserved argumento reservado.
 * @return {@code TRUE} si se completó exitosamente la llamada, caso contrario {@code FALSE}.
 */
BOOL APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    /*
     * Evalúa la razón de la llamada a la dll.
     */
    switch (reason) {
        /*
         * Se cargó la dll en el proceso actual.
         */
        case DLL_PROCESS_ATTACH:
            // printf("%s\n", "DLL_PROCESS_ATTACH");
            break;

        /*
         * Se liberó la dll en el proceso actual.
         */
        case DLL_PROCESS_DETACH:
            // printf("%s\n", "DLL_PROCESS_DETACH");
            break;

        /*
         * Se cargó la dll en un nuevo hilo.
         */
        case DLL_THREAD_ATTACH:
            // printf("%s\n", "DLL_THREAD_ATTACH");
            break;

        /*
         * Se liberó la dll en el nuevo hilo.
         */
        case DLL_THREAD_DETACH:
            // printf("%s\n", "DLL_THREAD_DETACH");
            break;
    }

    return TRUE;
}
#endif

/**
 * FIXME: Description of {@code copyArray}.
 * Copia el contenido de un array parámetro (input) a otro (output) desde start hasta end.
 */
LANGUAGE DLLIMPORT CALLING void copyArray(char* input, char* output, int start, int end) {
    if (end > (int)(strlen(input)))                 // Si end es mayor a la longitud del array input.
        end = (int)(strlen(input));                 // A end le lleva la longitud del array input.

    if (start >= 0 && end >= 0) {                   // Solo copia el array si start y end son mayores o iguales que cero.
        for (int i = 0; i <= end - start + 1; i++)  // Recorre input la cantidad de posiciones que digan el final menos el inicio.
            if (i == end - start + 1)               // Si termina de recorrer esa cantidad de posiciones.
                output[i] = 0;                      // Marca el fin de la cadena.
            else                                    // Si no ha terminado.
                output[i] = input[i + start];       // Almacena el caracter actual en output.
    } else                                          // Si start o end son menores que cero.
        output[0] = 0;                              // Pone output como un array vacío.
}

/**
 * FIXME: Description of {@code printFile}.
 * Imprime el contenido de un archivo (parámetro array) en consola.
 */
LANGUAGE DLLIMPORT CALLING void printFile(char* array) {
    FILE* file = fopen(array, "r+");        // Abre el archivo indicado por array.
    char line[10000];                       // Almacenará cada línea del archivo.

    for (int i = 1; i < 60000; i++) {       // Recorre cada línea del archivo.
        fgets(line, 1000, file);            // Obtiene la siguiente línea del archivo.

        if (feof(file))                     // Si treminó de recorrer el archivo.
            break;                          // Sale del ciclo.

        printf("%3d %s", i, line);          // Muestra la línea actual.
    }
}

/**
 * FIXME: Description of {@code printArray}.
 * Imprime un array sin los caracteres de escape.
 */
LANGUAGE DLLIMPORT CALLING void printArray(char* array) {
// Crea macro para imprimir caracteres de escape.
#define printChar(character)      \
    case character:               \
        printf("%s", #character); \
        break

    for (int i = 0; i < strlen(array); i++) {   // Recorre el array de entrada.
        switch (array[i]) {                     // Evalua el caracter actual.
            printChar('\n');                    // Imprime el caracter de escape.
            printChar('\r');                    // Imprime el caracter de escape.
            printChar('\t');                    // Imprime el caracter de escape.
            printChar('\a');                    // Imprime el caracter de escape.
            printChar('\b');                    // Imprime el caracter de escape.
            printChar('\v');                    // Imprime el caracter de escape.
            // printChar('\?');                 // Imprime el caracter de escape.
            // printChar('\"');                 // Imprime el caracter de escape.

            default:                            // Si no es un caracter de escape.
                printf("%c", array[i]);         // Imprime el caracter actual.
                break;                          // Termina de evaluar el caracter actual.
        }
    }

#undef printChar                                // Borra macro para imprimir caracteres de escape.
}

/**
 * FIXME: Description of {@code sprintArray}.
 * Copia un array de entrada en otro sin los caracteres de escape.
 */
LANGUAGE DLLIMPORT CALLING void sprintArray(char* output, char* input) {
// Crea macro para imprimir caracteres de escape.
#define printChar(character)                                \
    case character:                                         \
        sprintf(&output[strlen(output)], "%s", #character); \
        break

    for (int i = 0; i < strlen(input); i++) {                       // Recorre el array de entrada.
        switch (input[i]) {                                         // Evalua el caracter actual.
            printChar('\n');                                        // Imprime el caracter de escape.
            printChar('\r');                                        // Imprime el caracter de escape.
            printChar('\t');                                        // Imprime el caracter de escape.
            printChar('\a');                                        // Imprime el caracter de escape.
            printChar('\b');                                        // Imprime el caracter de escape.
            printChar('\v');                                        // Imprime el caracter de escape.
            // printChar('\?');                                     // Imprime el caracter de escape.
            // printChar('\"');                                     // Imprime el caracter de escape.

            default:                                                // Si no es un caracter de escape.
                sprintf(&output[strlen(output)], "%c", input[i]);   // Imprime el caracter actual.
                break;                                              // Termina de evaluar el caracter actual.
        }
    }

#undef printChar                                                    // Borra macro para imprimir caracteres de escape.
}

/**
 * FIXME: Description of {@code isANumber}.
 * Verifica si un caracter es un número, un signo, un punto o un indicador exponencial. Devuelve 1 caso afirmativo o caso contrario 0.
 */
LANGUAGE DLLIMPORT CALLING int isANumber(char c) {
    if ((c >= 48 && c <= 57) || c == '+' || c == '-' || c == '.' || c == 'e' || c == 'E')   // Si el caracter es un número.
        return 1;                                                                           // Devuelve 1 indicando que es un número.
    else                                                                                    // Si el caracter no es un número.
        return 0;                                                                           // Devuelve 0 indicando que no es un número.
}

/**
 * FIXME: Description of {@code validateNumber}.
 * Valida si un array tiene un número válido.
 */
LANGUAGE DLLIMPORT CALLING int validateNumber(char* array, int size) {
    int result = 0; // Crea variable que dirá si el array tiene un número válido (por defecto no).
    int status = 1; // crea variable que dirá el stado actual del array.

// Crea macro para evalúar el estado actual del array.
#define statusCase(stat, point, sign, exponent, number) \
    case stat:                                          \
        switch (array[i]) {                             \
            case '.':                                   \
                status = point;                         \
                break;                                  \
                                                        \
            case '-':                                   \
            case '+':                                   \
                status = sign;                          \
                break;                                  \
                                                        \
            case 'e':                                   \
            case 'E':                                   \
                status = exponent;                      \
                break;                                  \
                                                        \
            default:                                    \
                if (array[i] >= '0' && array[i] <= '9') \
                    status = number;                    \
                else                                    \
                    status = 0;                         \
        }                                               \
        break

    for (int i = 0; i < size; i++) {    // Recorre array.
        switch (status) {               // Evalúa el estado actual del array.
            statusCase(1, 9, 2, 0, 3);  // Si el estado actual es "No se han leído números".
            statusCase(2, 9, 0, 0, 3);  // Si el estado actual es "Signo de número natural".
            statusCase(3, 4, 0, 6, 3);  // Si el estado actual es "Digito de número natural".
            statusCase(4, 0, 0, 6, 5);  // Si el estado actual es "Punto de inicio decimal".
            statusCase(5, 0, 0, 6, 5);  // Si el estado actual es "Digito de número decimal".
            statusCase(6, 0, 7, 0, 8);  // Si el estado actual es "Indicador exponencial".
            statusCase(7, 0, 0, 0, 8);  // Si el estado actual es "Signo de número exponencial".
            statusCase(8, 0, 0, 0, 8);  // Si el estado actual es "Digito de número exponencial".
            statusCase(9, 0, 0, 0, 5);  // Si el estado actual es "Punto antes de algún digito".
            statusCase(0, 0, 0, 0, 0);  // Si el estado actual es "Número no válido".
        }

        // printf("%c %d\n", array[i], status);
        if (status == 0)                // Si se obtuvo estado inválido luego de evaluar el caracter actual.
            break;                      // Sale del for.
    }

#undef statusCase // Borra la macro usada para evalúar el estado actual del array.

    switch (status) {   // Evalúa el estado final.
        case 3:         // Si el estado final es "Digito de número natural".
        case 4:         // Si el estado final es "Punto de inicio decimal".
        case 5:         // Si el estado final es "Digito de número decimal".
        case 8:         // Si el estado final es "Digito de número exponencial".
            result = 1; // Pone result en uno indicando que es un número válido.
            break;      // Termina de valuar el estado final.
    }

    return result; // Devuelve si es o no un número válido.
}

/**
 * FIXME: Description of {@code getNumber}.
 * Obtiene los caracteres numéricos de un array (en float).
 */
LANGUAGE DLLIMPORT CALLING double getNumber(char* array) {
    char number[strlen(array)];                     // Crea array con la longitud del array parámetro.
    int numberPos = 0;                              // Crea variable que dirá la posición actual del array nnumber.

    for (int i = 0; i < (int)strlen(array); i++)    // Recorre array.
        if (isANumber(array[i])) {                  // Si array en la posición actual tiene un caracter numérico.
            number[numberPos] = array[i];           // Almacena el caracter actual en number.
            numberPos++;                            // Pasa a la siguiente posición de number.
        }

    number[numberPos] = 0;                          // Marca el final de number.
    // printf("-%s-\n", number);                    // Muestra number.
    // printf("-%f-\n", atof(number));              // Muestra number.

    if (validateNumber(number, numberPos))          // Si el array number es un número válido.
        return (double)atof(number);                // Devuelve el array number en float.
    else                                            // Si no es un número válido.
        return 0.0;                                 // Devuelve cero indicando número no válido.
}

/**
 * FIXME: Description of {@code isALetter}.
 * Evalúa si un caracter es una letra. Devuelve 1 caso afirmativo o caso contrario 0.
 */
LANGUAGE DLLIMPORT CALLING int isALetter(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return 1;
    else
        return 0;
}

/**
 * FIXME: Description of {@code iqualChar}.
 * Evalúa si dos caracteres son iguales (tomando igual mayúsculas y minúsculas para el caso de las letras).
 */
LANGUAGE DLLIMPORT CALLING int iqualChar(char c1, char c2) {
    int charType = -1;                          // Crea variable que dirá el tipo de caracter de c1 (0 = minúscula, 1 = mayúscula, -1 = otro caracter).

    if (c1 >= 97 && c1 <= 122)                  // Si c1 es una letra minúscula.
        charType = 0;                           // Indica que es una letra minúscula.
    elif (c1 >= 65 && c1 <= 90)                 // Si c1 es una letra mayúscula.
        charType = 1;                           // Indica que es una letra mayúscula.

    if (c1 == c2                                // Si los caracteres son iguales.
        || (charType == 1 && c1 == c2 - 32)     // Si c1 es una letra mayúscula c2 una letra minúscula.
        || (!charType && c1 == c2 + 32))        // Si c1 es una letra minúscula c2 una letra mayúscula.
        return 1;                               // Devuelve uno indicando que los caracteres son iguales.
    else                                        // Si los caracters no son iguales y no son una letra mayúscula y una minúscula.
        return 0;                               // Devueleve ccero indicando que los caracteres no son iguales.
}

/**
 * FIXME: Description of {@code countCharacters}.
 * Cuenta la cantidad de veces que aparece character en el array input.
 */
LANGUAGE DLLIMPORT CALLING int countCharacters(char* input, char character) {
    int quantity = 0;                               // Variable que dirá la cantidad de veces que se encontró el caracter.

    for (int i = 0; i < (int)(strlen(input)); i++)  // Recorre el array input.
        if (input[i] == character)                  // Si encuentra el caracter indicado.
            quantity++;                             // Aumenta quantity.

    return quantity;                                // Devuelve la cantidad de veces que encontró el caracter.
}

/**
 * FIXME: Description of {@code compareArrays}.
 * Compara dos arrays difirenciando mayúsculas y minúsculas, quentity indica la cantidad de caracteres.
 */
LANGUAGE DLLIMPORT CALLING int compareArrays(char* array1, char* array2, int quantity) {
    int result = 1;                                 // Variable para almacenar el resultado.

    if ((array1 == NULL && array2 != NULL)          // Si el primer array es NULL y el segundo no.
        || (array1 != NULL && array2 == NULL))      // Si el primer array no es NULL y el segundo si.
        result = 0;                                 // Pone result en cero indicando que ambos arrays son diferentes.
    elif (!(array1 == NULL && array2 == NULL))      // Si ambos array no son NULL.

        for (int i = 0; i < quantity; i++)          // Recorre anmbos array.
        if (!iqualChar(array1[i], array2[i])) {     // Si los caracteres actuales no son iguales.
        result = 0;                                 // Indica que los array no son iguales.
        break;                                      // Sale del for.
    }

    return result;                                  // Devuelve el valor de result.
}

/**
 * FIXME: Description of {@code findWord}.
 * Encuentra una palabra en un array empazando a buscar desde la posición start del array hasta la posición end.
 */
LANGUAGE DLLIMPORT CALLING int findWord(char* array, char* word, int start, int end) {
    int result = -1; // Crea variable que va tener la posición donde encuentre word.

    if (end > (int)(strlen(array)))                                                 // Si end es mayor que la longitud total del array.
        end = (int)(strlen(array));                                                 // A end le lleva la longitud del array.

    /*-
    if (strlen(array)>10000) {
        printf("%d %d (%d to %d)\n", start, end, start, (int)(end-strlen(word)));   // Muestra los valores de start y de end.
        printf("%d %d\n", (int)(strlen(array)), (int)(strlen(word)));               // Muestra las longitudes de cada array.
        printf("-%s-\n", word);
    }
    */

    // Si la longitud de la palabra a buscar es menor o igual que la del array donde se buscará y ninguno de los arrays está vacío.
    if ((int)(strlen(array)) >= (int)(strlen(word)) && (int)(strlen(array)) != 0 && (int)(strlen(word)) != 0)
        for (int i = start; i <= (int)(end - strlen(word)); i++) {                  // Recorre array desde start hasta end menos la longitud de la palabra a buscar.
            // printf("%d en en for\n", i);
            for (int j = 0; j < (int)(strlen(word)); j++)                           // Recorre word.
                if (array[i + j] != word[j])                                        // Si el caracter actual en el array no es igual al caracter actual en word.
                    break;                                                          // Sale del for.
            elif (j == (int)(strlen(word)) - 1)                                     // Si termina de recorrer word (word no está en array).
                result = i;                                                         // A result le asigna i.

            if (result != -1)                                                       // Si result no es -1 (encontró la palabra).
                break;                                                              // Sale del for.
        }

    return result;                                                                  // Devuelve result.
}

/**
 * FIXME: Description of {@code findFirstDifferentChar}.
 * Encuentra en un array la posición del primer elemento diferente a los indicados como parámetro.
 */
LANGUAGE DLLIMPORT CALLING int findFirstDifferentChar(char* array, int nargs, ...) {
    char args[nargs];                                               // Crea array para almacenar los parámetros.
    va_list ap;                                                     // Crea una lista de parámetros.
    va_start(ap, nargs);                                            // Inicializa la lista de parámetros.

    for (int i = 0; i < nargs; i++)                                 // Recorre la lista de parámetros.
        args[i] = va_arg(ap, int);                                  // Almacena el parámetro en args.

    va_end(ap);                                                     // Finaliza la lista de parámetros.

    // for (int i = 0; i < nargs; i++)                              // Recorre el array con los parámetros.
    //   printf("Argumento %d = %d -%c-\n", i, args[i], args[i]);   // Muestra el parámetro actual.

    // printf("-%s-\n", array);                                     // Muestra el array parámetro.
    int iqual = 0;                                                  // Crea variable que dirá si el caracter actual es igual a alguno de los parámetros.
    int start = -1;                                                 // Crea variable que dirá la posicion del primer caracter diferente a los parámetros.

    for (int i = 0; i < (int)(strlen(array)); i++) {                // Recorre el array desde el inicio.
        iqual = 0;                                                  // Inicializa iqual en 0 (no es igual a alguno de los parámetros).
        for (int j = 0; j < nargs; j++)                             // Recorre el array de parámetros.
            if (array[i] == args[j])                                // Si el caracter actual es igual a alguno de los parámetros.
                iqual++;                                            // Pone iqual en 1 (si es igual a alguno de los parámetros).

        if (!iqual) {                                               // Si el caracter actual es diferente a todos los parámetros.
            start = i;                                              // A start le lleva la posición actual del array.
            break;                                                  // Sale del for.
        }
    }

    return start;                                                   // Devuelve la posición del primer elemento diferente a los parámetros.
}

/**
 * FIXME: Description of {@code findLastDifferentChar}.
 * Encuentra en un array la posición del último elemento diferente a los indicados como parámetro.
 */
LANGUAGE DLLIMPORT CALLING int findLastDifferentChar(char* array, int nargs, ...) {
    char args[nargs];                                               // Crea array para almacenar los parámetros.
    va_list ap;                                                     // Crea una lista de parámetros.
    va_start(ap, nargs);                                            // Inicializa la lista de parámetros.

    for (int i = 0; i < nargs; i++)                                 // Recorre la lista de parámetros.
        args[i] = va_arg(ap, int);                                  // Almacena el parámetro en args.

    va_end(ap); // Finaliza la lista de parámetros.

    // for (int i = 0; i < nargs; i++)                              // Recorre el array con los parámetros.
    //   printf("Argumento %d = %d -%c-\n", i, args[i], args[i]);   // Muestra el parámetro actual.

    // printf("-%s-\n", array);                                     // Muestra el array parámetro.
    int iqual = 0;                                                  // Crea variable que dirá si el caracter actual es igual a alguno de los parámetros.
    int end = -1;                                                   // Crea variable que dirá la posicion del primer caracter diferente a los parámetros.

    for (int i = (int)(strlen(array) - 1); i >= 0; i--) {           // Recorre el array desde el final.
        iqual = 0;                                                  // Inicializa iqual en 0 (no es igual a alguno de los parámetros).
        for (int j = 0; j < nargs; j++)                             // Recorre el array de parámetros.
            if (array[i] == args[j])                                // Si el caracter actual es igual a alguno de los parámetros.
                iqual++;                                            // Pone iqual en 1 (si es igual a alguno de los parámetros).

        if (!iqual) {                                               // Si el caracter actual es diferente a todos los parámetros.
            end = i;                                                // A end le lleva la posición actual del array.
            break;                                                  // Sale del for.
        }
    }

    return end;                                                     // Devuelve la posición del último elemento diferente a los parámetros.
}

/**
 * FIXME: Description of {@code getTextBetween}.
 * Obtiene un texto encerrado entre comillas ("****") en input, number indica el número de palabra a encontrar ("1" "2" "3" ...).
 */
LANGUAGE DLLIMPORT CALLING int getTextBetween(char* output, char* input, char* open, char* close, int number) {
    char* found = input;                                    // Crea puntador para almacenar la posición donde encuentre la palabra indicada por open.
    int start = -1;                                         // Crea variable para buscar palabras dentro de input.
    int end = -1;                                           // Crea variable para buscar palabras dentro de input.

    for (int i = 1; i <= number; i++) {                     // Recorre input tantas veces como diga number.
        start = findWord(found, open, 0, strlen(found));    // Obtiene la palabra indicada por open.

        if (start == -1)                                    // Si no se encontró la palabra.
            break;                                          // Sale del ciclo.

        found += (start + strlen(open));                    // Actualiza la posición deonde se encontró la palabra.
        // printf("op: '%s'\n", found);                     // Muestra la posición donde encontró open.
    }

    if (start != -1) {                                      // Si se encontró la palabra indicada poropen.
        start = found - input;                              // A start le lleva la posiciónn en el array de entrada.
        end = findWord(found, close, 0, strlen(found));     // Obtiene la palabra indicada por close.
        // printf("cl: '%s'\n", &found[end]);               // Muestra la posición donde encontró close.

        if (end != -1) {                                    // Si se encontró la palabra indicada por close.
            memcpy(output, found, end);                     // Copia la palabra encerrada entre open y close en output.
            output[end] = 0;                                // Marca el final de output.
        } else                                              // Si no se encontró la palabra.
            output[0] = 0;                                  // Marca el fin de la cadena al inicio de output.

    } else                                                  // Si no se encontró la palabra.
        output[0] = 0;                                      // Marca el fin de la cadena al inicio de output.

    return start;                                           // Devuelve la posición en input donde encontró la palabra.
}

/**
 * FIXME: Description of {@code splitArray}.
 * Divide un array en n-array cada que encuentre la cadena indicada por "word".
 */
LANGUAGE DLLIMPORT CALLING char** splitArray(char* array, char* word) {
    int arraySize = (int)strlen(array);                                     // Obtiene la longitud del array parámetro.
    int wordSize = (int)strlen(word);                                       // Obtiene la longitud de la palabra parámetro.
    char** values = malloc(((arraySize / wordSize) + 2) * sizeof(char**));  // Crea array de apuntadores que tendrá los apuntadores a cada aparición de word.
    int valueNumber = 0;                                                    // Variable que contará la cantidad de veces que aparezca "word".

    values[valueNumber] = &array[0];                                        // Almacena en la primera posión de values la posición de inicio de array.

    for (int i = 0; i < arraySize; i++)                                     // Recorre array.
        if (!strncmp(&array[i], word, wordSize)) {                          // Si encuentra la palabra indicada por word.
            valueNumber++;                                                  // Aumenta la cantidad de veces que aparece la palabra.
            values[valueNumber] = &array[i];                                // Almacena el apuntador a la palabra.
        }

    values[valueNumber + 1] = NULL;                                         // Marca el fin de los apuntadores.

    values = realloc(values, (valueNumber + 2) * sizeof(char**));           // Redimensiona el tamaño del array de apuntadores.

    for (int i = 1; i <= valueNumber; i++) {                                // Recorre el array de apuntadores desde el segundo elemento.
        values[i][0] = 0;                                                   // Marca el fin de la cadena en el array.
        values[i] += wordSize;                                              // Actualiza el puntero actual a después de la palabra.
    }

    return values;                                                          // Devuelve el array con los apuntadores.
}

/**
 * FIXME: Description of {@code replaceWord}.
 * Reemplaza la palabra indicada en el array "word" por la indicada en el array "replacedWord" en el array input.
 */
LANGUAGE DLLIMPORT CALLING void replaceWord(char* input, char* output, char* word, char* replacedWord) {
    int inputSize = (int)strlen(input);                                     // Crea variable con la longitud del array de entrada.
    int wordSize = (int)strlen(word);                                       // Crea variable con la longitud de la palabra a buscar.
    int replacedSize = (int)strlen(replacedWord);                           // Crea variable con la longitud de la palabra con que seemplazará.

    // char* output = NULL;                                                 // Crea array que tendrá el resultado de reemplazar las palabras.

    int pos = 0;                                                            // Variable usada para almacenar la posición donde encuentre la palabra.
    char* auxIn = NULL;                                                     // Variable usada para recorrer el array de entrada.
    char* auxOut = NULL;                                                    // Variable usada para recorrer el array con las palabras reemplazadas.

    if (inputSize != 0) {                                                   // Si el array de entrada no es un array vacío.
        // output = (char*)malloc((inputSize*replacedSize)*sizeof(char));   // Inicializa ouput con la cantidad de caracteres de input por los de word (máximo número de reemplazos).
        auxIn = input;                                                      // Almacena la primera posición del array de entrada.
        auxOut = output;                                                    // Almacena la primera posición del array de salida.
        while (pos != -1) {                                                 // Mientras encuentre la palabra.
            pos = findWord(auxIn, word, 0, inputSize);                      // Obtiene la posición de la palabra.

            if (pos != -1) {                                                // Si encuentra la palabra.
                memcpy(auxOut, auxIn, pos);                                 // Copia al array de salida el contenido antes de encontrar la palabra.
                memcpy(&auxOut[pos], replacedWord, replacedSize);
                auxIn += (pos + wordSize);                                  // Pone el puntero del array de entrada luego de la palabra a reemplazar.
                auxOut += (pos + replacedSize);                             // Pone el puntero del array de salida luego de la palabra reemplazada.
                inputSize -= (pos + wordSize);                              // Reduce el tamaño del array de entrada.
            } else {                                                        // Si no encuentra la palabra.
                memcpy(auxOut, auxIn, inputSize);                           // Copia al array de salida el contenido antes de encontrar el fin de input.
                auxOut[inputSize] = 0;                                      // Marca el fin de la cadena en el array de salida.
            }
        }
    }
}

/**
 * FIXME: Description of {@code invertText}.
 * Invierte los caracteres de un texto que hayan entre la posición start y end.
 */
LANGUAGE DLLIMPORT CALLING void invertText(char* input, int start, int end) {
    char array[end - start]; // Crea array donde se copiarán los caracteres a invertir.

    for (int i = start; i <= end; i++) // Recorre input dede start hasta end.
        array[i - start] = input[i];   // Almacena en array el caracter actual de input.

    // printf("%s\n", array);                                                        // Muestra array.

    for (int i = start; i <= end; i++) // Recorre input dede start hasta end.
        input[i] = array[end - i];     // Almacena en input el caracter actual de array.
}

/**
 * FIXME: Description of {@code replaceInvalidCharacters}.
 * Borra los caracteres no permitidos en nombres de archivos con el array indicado por replacedCharacter.
 */
LANGUAGE DLLIMPORT CALLING void replaceInvalidCharacters(char* fileName, char* replacedCharacter) {
// Crea macro con el código para reemplazar caracteres.
#define replace(l) replaceWord(fileName, fileName, (char*)(l), replacedCharacter)
    replace("\\");
    replace("\"");
    replace("/");
    replace(":");
    replace("*");
    replace("?");
    replace("<");
    replace(">");
    replace("|");
// Borra la macro con el código para reemplazar caracteres.
#undef replace
}

/**
 * FIXME: Description of {@code replaceUTF8CharToAscii}.
 * Reemplaza caracteres UTF-8 con caracteres de ascii extendido en un array input para que este pueda verse bien en cmd.
 */
LANGUAGE DLLIMPORT CALLING void replaceUTF8CharToAscii(char* input) {
    char newChar[4] = ""; // Array que almacenará cada caracter en ascii extendido.
    char characters[384] = "ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®¬½¼¡«»░▒▓│┤ÁÂÀ©╣║╗╝¢¥┐└┴┬├─┼ãÃ╚╔╩╦╠═╬¤ðÐÊËÈıÍÎÏ┘┌█▄¦Ì▀ÓßÔÒõÕµþÞÚÛÙýÝ¯´≡±‗¾¶§÷¸°¨·¹³²■";
    char oldChar[4] = "";

    int suma = 0;
    for (int i = 0; i < 127; i++) {

        if ((i >= 48 && i <= 51) || (i >= 57 && i <= 61) || (i >= 63 && i <= 69) || (i >= 72 && i <= 78) || (i >= 89 && i <= 92) || (i == 95) || (i == 112) || (i == 114) || (i == 126)) {
            memcpy(oldChar, &characters[i + suma], 3);
            newChar[0] = i + 128;
            suma += 2;
            replaceWord(input, input, oldChar, newChar);
            // printf("%3d \"%s\"\n", i+128, input);
            // printf("%3d %s\n", i+128, input);
        } else {
            // memcpy(oldChar, &characters[i+suma], 2);
            // newChar[0] = i+128;
            suma++;
            // printf("%3d \"%s\" \"%s\"\n", i+128, oldChar, newChar);
        }
    }

    suma = 0;
    oldChar[2] = 0;

    for (int i = 0; i < 127; i++) {
        if (!((i >= 48 && i <= 51) || (i >= 57 && i <= 61) || (i >= 63 && i <= 69) || (i >= 72 && i <= 78) || (i >= 89 && i <= 92) || (i == 95) || (i == 112) || (i == 114) || (i == 126))) {
            memcpy(oldChar, &characters[i + suma], 2);
            newChar[0] = i + 128;
            suma++;
            replaceWord(input, input, oldChar, newChar);
            // printf("%3d \"%s\" \"%s\"\n", i+128, oldChar, newChar);
            // printf("%3d %s\n", i+128, input);
        } else {
            // memcpy(oldChar, &characters[i+suma], 3);
            // newChar[0] = i+128;
            suma += 2;
            // printf("%3d \"%s\" \"%s\"\n", i+128, oldChar, newChar);
        }
    }
}

/**
 * FIXME: Description of {@code convertHtmCharToAscii}.
 * Obtiene el equivalente ascii de un caracter html.
 */
LANGUAGE DLLIMPORT CALLING int convertHtmCharToAscii(char* htmlChar) {
    char ascii = 0;                                                             // Crea variable que almacenará el caracter ascii equivalente.

    if ((int)(strlen(htmlChar)) != 3 || htmlChar[0] != '%')                     // Si el array htmlChar no contiene un caracter html encodeado.
        return ascii;                                                           // Devuelve 0 indicando caracter no válido.
    else {                                                                      // Si htmlChar es un caracter válido.
                                                                                // Crea array con todos los posibles caracteres ascci en los que es posible convertir htmlChar.
        char htmlCharacters[500] = "  !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~  ,ƒ\".┼¥^°S<E Z  '´\"\".--~ªs>æ zÿ ¡¢£ ¥|§¨©ª«¬¯®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁ ÃÄÅÆÇÈÉ ËÌÍÎÏÐÑÒÓÔÕÖ ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";

        replaceUTF8CharToAscii(htmlCharacters);                                 // Reemplaza los caracteres no ascii de htmlCharacters con caracteres ascii.

        /*-
        for (int i = 0; i < (int)(strlen(htmlCharacters)); i++)
            printf("%03d %c\n", i+1, htmlCharacters[i]);
        */

        char htmlAux[3];                                                        // Crea array que tendrá una copia del array parámetro.
        for (int i = 0; i <= 3; i++)
            htmlAux[i] = htmlChar[i];

        for (int i = 1; i < 3; i++)                                             // Recorre htmlAux.
            if (htmlAux[i] < 58)                                                // Si en la posición actual hay un número (0...9).
                htmlAux[i] = htmlAux[i] - 48;                                   // Convierte el caracter numérico en un número.
        elif (htmlAux[i] < 71)                                                  // Si en la posición actual hay una letra mayúscula (A...F).
            htmlAux[i] = htmlAux[i] - 55;                                       // Convierte la letra en su equivalente númerico en hexadecimal (10..15).
        elif (htmlAux[i] < 103)                                                 // Si en la posición actual hay una letra minúscula (a...f).
            htmlAux[i] = htmlAux[i] - 87;                                       // Convierte la letra en su equivalente númerico en hexadecimal (10..15).

        ascii = htmlCharacters[htmlAux[1] * 16 - 31 + htmlAux[2]];              // A ascii le lleva el caracter del array htmlCharacters en la posición indicada por la fórmula.
        // printf("\%c %d %d (pos %d)\n", '%', htmlAux[1],htmlAux[2], ascii);   // Muestra el caracter obtenido.

        return ascii;                                                           // Devuelve el equivalente ascii.
    }
}

/**
 * FIXME: Description of {@code replaceHtmlCharacters}.
 * Cambia caracteres de un array encodeados en html por caracteres ascii.
 */
LANGUAGE DLLIMPORT CALLING void replaceHtmlCharacters(char* input) {
    // printf("..%s..\n", input);                                               // Muestra el array original.
    int size = (int)(strlen(input));                                            // Crea size con la longitud del array input.
    int htmlPos[(int)(strlen(input) / 3)];                                      // Crea array para almacenar la posición de cada caracter html.
    int pos = 0;                                                                // Crea variable que indicará la última posición donde se encontró un caracter html.
    int quantity = 0;                                                           // Crea variable que dirá cuantos caracteres html se han encontrado.
    char htmlChar[10];                                                          // Crea array que tendrá cada uno de los caracteres html encontrados.
    int asciiChar = 0;                                                          // Crea variable que tendrá cada caracter html en su equivalente ascii.
    char aux[size];                                                             // Crea array para almacenar las partes del array input entre las que hay dos caracateres html (%??.....%??).
    char output[size * 2];                                                      // Crea array que tendrá el array con los caracteres html reemplazados.

    while (pos != -1) {                                                         // Recorre el array input.
        pos = findWord(input, (char*)"\%", pos + 1, (int)(strlen(input)));      // Si encuentra el inicio de un caracter html.
        htmlPos[quantity] = pos;                                                // Almacena la posición del caracter en htmlPos.

        if (pos == -1)                                                          // Si findWord no encuentra más caracteres html.
            htmlPos[quantity] = size;                                           // Almacena la longitud de input en htmlPos.
        quantity++;                                                             // Aumenta quantity.
    }

    copyArray(input, output, 0, htmlPos[0] - 1);                                // Copia en output los caracteres de input hasta encontrar el primer caracter html.
    // printf("..%s..\n", output);                                              // Muestra output.
    // printf("\n\n\n");                                                        // Muestra saltos de línea.

    for (int i = 0; i < size; i++) {                                            // Recorre input.
        if (htmlPos[i] == size)                                                 // Si htmlPos indica que no hay más caracteres html.
            break;                                                              // Sale del for.
        else {
            copyArray(input, aux, htmlPos[i] + 3, htmlPos[i + 1] - 1);          // Copia en aux los caracteres que estan entre dos caracteres html.
            copyArray(input, htmlChar, htmlPos[i], htmlPos[i] + 2);             // Copia en htmlChar el caracter html encontrado.
            asciiChar = convertHtmCharToAscii(htmlChar);                        // Almacena en asciiChar el valor en ascii de htmlChar.
            // printf("%02d \"%s %c\" \"%s\"\n", i, htmlChar, asciiChar, aux);  // Muestra los arrays.

            // printf("..%s..\n", output);                                      // Muestra output.
            sprintf(output, "%s%c%s", output, asciiChar, aux);                  // Almacena en output lo que tiene más el caracter en ascii seguido de aux.
            // printf("..%s..\n", output);                                      // Muestra output.
            // printf("\n\n\n");                                                // Muestra saltos de línea.
        }
    }

    sprintf(input, "%s", output);                                               // Almacena en input el array con los caracteres html convertidos en ascii.
    // printf("..%s..\n", input);                                               // Muestra output.
}
