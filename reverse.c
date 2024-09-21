#include <stdio.h>
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
}
