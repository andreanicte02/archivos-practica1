/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   analizador.h
 * Author: nicte
 *
 * Created on 8 de agosto de 2017, 21:40
 */

#include "mbr.h"
#include "bloques.h"

#ifndef ANALIZADOR_H
#define ANALIZADOR_H

long int tbb(long int tp, long int tb);
mbr recuperar_mbrr(char *path);
void reporte_bloques(char *disco);
void reporte_bit(char *disco);
void reporte(char *disco) ;
partition primer_ajuste(FILE *archivo, float total_bloques, long int n, int tcadena, char *cadena, partition p, int id);
void carga_masiva(char *disco, char *particion, int id, char *contenido);
void analizar(char *linea, char*disco, char *particion) ;
void leer(char *path, char*disco, char* particion);

#endif /* ANALIZADOR_H */

