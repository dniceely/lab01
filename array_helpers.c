#include "array_helpers.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    unsigned int ar_length = 0;
    FILE *file = fopen(filepath, "r");

    // Este primer if intenta abrir el archivo, si no lo logra printea un error.
    if (file == NULL) 
    {
        fprintf(stderr, "No pudo abrirse el archivo '%s'\n", filepath);
        return 0;
    }

    // El segundo if leera el tamañao del array especificado en la primer linea del archivo, si no puede, printea un error y cierra el archivo.
    if (fscanf(file, "%u", &ar_length) != 1) 
    {
        fprintf(stderr, "No pudo leerse el tamaño del array en el archivo.\n");
        fclose(file);
        return 0;
    }

    // Este if verifica que el array no pase el limite de tamaño definido.
    if (ar_length > max_size) 
    {
        fprintf(stderr, "El tamaño del array sobrepasa el limite.\n");
        fclose(file);
        return 0;
    }

    // Lee los elementos en el array y frena si alguno no se puede leer.
    for (unsigned int i = 0; i < ar_length; i++) 
    {
        if (fscanf(file, "%d", &array[i]) != 1) 
        {
            fprintf(stderr, "Hubo un problema leyendo los elementos.\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return ar_length;
    // Los elementos del array se fueron guardadno en el scanf y la función devuelve además el tamaño del array.
}

void array_dump(int a[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
}

bool array_is_sorted(int a[], unsigned int length) {
    bool res_parcial = true;
    for (unsigned int i = 0; i < length-1; i++)
    {
        if (a[i] <= a[i+1])
        {
            res_parcial = res_parcial && true;
        }
        else
        {
            res_parcial = res_parcial && false;
        }
    }
    
return res_parcial;
}