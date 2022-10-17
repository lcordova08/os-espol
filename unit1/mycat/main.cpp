#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#define MAX_LEN 1024

int main(int argc, char* argv[])
{
    char input_line[MAX_LEN] = {0};  
    if (argc == 2) {
        int input_file = open(argv[1], O_RDONLY);
        if(input_file < 0){
            fprintf(stderr, "no se puede abrir el archivo %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        while(read(input_file, input_line, MAX_LEN) > 0 ){
            size_t es = write(fileno(stdout), input_line, strlen(input_line) + 1);
            if(es <= 0){
                printf(stderr, "no se puede escribir en la salida\n");
                exit(EXIT_FAILURE);
            }
            memset(input_line,0,MAX_LEN);
        }
        close(input_file);
    }
    else if (argc == 1)  {
        while (read(fileno(stdin), input_line, MAX_LEN) > 0){
            size_t es = write(fileno(stdout), input_line, strlen(input_line)+1);
            if(es <= 0){
                printf(stderr,"no se puede escribir en la salida\n ");
                exit(EXIT_FAILURE);
            }
            memset(input_line,0,MAX_LEN);
        }      
    }
    else {
        printf(stderr, "Uso del programa: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}