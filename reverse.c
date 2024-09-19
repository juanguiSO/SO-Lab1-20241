#include<stdio.h>
int main (int argc, char *argv[])
{

 // Verificación de cantidad de argumentos en la línea de comandos
    if (argc == 3) {
         return 0;
       
    }else{
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
        }

   

}
