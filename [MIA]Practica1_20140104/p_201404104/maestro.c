/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbr.h"
#include "bloques.h"
#include "master.h"
#include "Crear.h"
#include "analizador.h"

int maestro(char *disco, int tamano) {


    char path[100] = "master.disk";

    FILE *tro = fopen(path, "wb+");
    char path1[100] = "/home/nicte/Escritorio/discos/";
    strcat(path1, disco);
    strcat(path1, ".disk");
    if (tro != NULL) {
        discp temporal;
        temporal.espacio_libre = tamano;
        temporal.estado = 0;
        temporal.id = 0;
        temporal.par_ligcas = 0;
        temporal.par_primarias = 0;
        temporal.par_secundarias = 0;
        strcpy(temporal.nombre, disco);
        strcpy(temporal.path, path1);
        
        fwrite(&temporal, sizeof (temporal), 50, tro);
        
        fclose(tro);
        return 1;



    }

}

