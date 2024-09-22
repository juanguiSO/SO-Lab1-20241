#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // Necesario para usar la estructura stat

// Estructura para almacenar una línea
typedef struct Line
{
    char *line;
    struct Line *next;
} Line;

// Función para agregar una línea a la lista enlazada
Line *add_line_to_list(Line *head, char *line)
{
    Line *new_node = (Line *)malloc(sizeof(Line));
    if (new_node == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    new_node->line = strdup(line);
    if (new_node->line == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    new_node->next = head;
    return new_node;
}

// Función para liberar la memoria de la lista enlazada
void free_line_list(Line *head)
{
    Line *current = head;
    while (current != NULL)
    {
        Line *temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }
}

// Función para leer líneas de longitud indefinida
ssize_t read_line_from_file(char **line_pointer, size_t *n, FILE *stream)
{
    if (*line_pointer == NULL || *n == 0)
    {
        *n = 128; // Tamaño inicial del buffer
        *line_pointer = malloc(*n);
        if (*line_pointer == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
    }

    ssize_t num_chars = getline(line_pointer, n, stream);
    if (num_chars == -1)
    {
        return -1; // Error o fin de archivo
    }

    return num_chars;
}

// Función para verificar si dos archivos son el mismo (hardlinked)
int are_files_same(const char *file1, const char *file2)
{
    struct stat stat1, stat2;

    // Obtener información del primer archivo
    if (stat(file1, &stat1) != 0)
    {
        exit(1);
    }

    // Obtener información del segundo archivo
    if (stat(file2, &stat2) != 0)
    {
        exit(1);
    }

    // Comparar el número de dispositivo e inodo
    return (stat1.st_dev == stat2.st_dev && stat1.st_ino == stat2.st_ino);
}

// Función principal
int main(int argc, char *argv[])
{
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    Line *lines = NULL;
    char *buffer = NULL;
    size_t buffer_size = 0;

    // Manejo de argumentos
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if (argc == 2)
    {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    if (argc == 3)
    {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        output_file = fopen(argv[2], "w");
        if (output_file == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            exit(1);
        }

        if (strcmp(argv[1], argv[2]) == 0 || are_files_same(argv[1], argv[2]))
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
    }

    // Leer el archivo de entrada línea por línea y agregar a la lista
    while (read_line_from_file(&buffer, &buffer_size, input_file) != -1)
    {
        lines = add_line_to_list(lines, buffer);
    }

    // Imprimir las líneas en orden inverso
    Line *current = lines;
    while (current != NULL)
    {
        fprintf(output_file, "%s", current->line);
        current = current->next;
    }

    // Limpiar
    free_line_list(lines);
    free(buffer); // Liberar el buffer
    if (input_file != stdin)
        fclose(input_file);
    if (output_file != stdout)
        fclose(output_file);

    return 0;
}