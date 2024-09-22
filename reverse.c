#include <stdio.h>

// Función para verificar si dos archivos son el mismo (hardlinked)
     int are_files_same(const char *file1, const char *file2) {
         struct stat stat1, stat2;
     
         // Obtener información del primer archivo
         if (stat(file1, &stat1) != 0) {
             exit(1);
         }
     
         // Obtener información del segundo archivo
         if (stat(file2, &stat2) != 0) {
             exit(1);
         }
     
         // Comparar el número de dispositivo e inodo
         return (stat1.st_dev == stat2.st_dev && stat1.st_ino == stat2.st_ino);
     }

int main(int argc, char *argv[])
{
     // 1. Verificación de cantidad de argumentos en la línea de comandos
     if (argc > 3)
     {
          fprintf(stderr, "usage: reverse <input> <output>\n");
          return 1;
     }

     // 2. Verificar que el archivo existe
     FILE *fp;
     fp = fopen(argv[1], "r");
     if (!fp)
     {
          fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
          return 1;
     }
     // 2. Verificar que los archivos sean diferentes
     if (strcmp(argv[1], argv[2]) == 0 || are_files_same(argv[1], argv[2])) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
     }
     
}
