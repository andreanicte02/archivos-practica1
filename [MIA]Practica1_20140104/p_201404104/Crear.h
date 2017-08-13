/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Crear.h
 * Author: nicte
 *
 * Created on 3 de agosto de 2017, 0:23
 */
#include "mbr.h" 

#ifndef CREAR_H
#define CREAR_H

#ifdef __cplusplus
//extern "C" {
    
#endif


mbr recuperar_mbr(char *path);
int hay_espacio(int tamdisco, int tamparticion, long int posinicial);
int existe_nombre(char *nombre, mbr part);
int existe_extendida(mbr par);

int existe_logica(logic logica, char *nombre);
long int ultima_pos(logic logica);
partition enmedio(partition p, int tamano, long int inicio, char*nombre, char*tipo, int numero);

void particionar(char *nombw, char *tipo, int tamano);
void cmbr(int tamano, char *nombre, char *path);
void cdisk(int tamano, char *nombre);
void menu1();
void menu3(char *nombre);
int todasvacias(mbr disco);
void eliminarp(char *nombre, char* disco) ;
long int tb( long int tp, long int tb);
void formato(char *nombre, char* disco);
void solo_crear(char *disco);
void menu4(char *disco);
void menugenera();



#ifdef __cplusplus
//}
#endif

#endif /* CREAR_H */

