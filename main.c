/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
