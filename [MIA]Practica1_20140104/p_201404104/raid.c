#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *abrirDisco_RAID1(char* path) {
    FILE* fp;
    if ((fp = fopen(path, "rb+")) == NULL) {
        strcat(path, "_raid1");
        if ((fp = fopen(path, "rb+")) == NULL) {
            printf("el disco no existe ni en el raid");
            exit(1);
        }
    }
    return fp;
}

void Raid1(char* disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    char comando[1000]="/home/nicte/Escritorio/discos/";
    
    strcat(comando,disco);
    strcat(comando,".raid.disk");
    FILE* fp = fopen(path, "r+b");
    
    
    if(fp!= NULL){
        char nuevo[1000];
        sprintf(nuevo, "cp %s %s", path, comando);
        system(nuevo);
        fclose(fp);
    }
            
    

}
