/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   master.h
 * Author: nicte
 *
 * Created on 11 de agosto de 2017, 13:49
 */

#ifndef MASTER_H
#define MASTER_H

#include "mbr.h"


typedef struct{

    int id;
    char nombre[50];
    int tamano;
    int par_primarias;
    int par_secundarias;
    int par_ligcas;
    long int espacio_libre;
    char path[200]; 
    int estado;
    
}discp;

#endif /* MASTER_H */

