/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mbr.h
 * Author: nicte
 *
 * Created on 3 de agosto de 2017, 1:08
 */

#ifndef MBR_H
#define MBR_H

typedef struct{
    char nombre[50];
    int no_partition;
    long int tamano;
    long int inicio; //creo que tambien puedo manejar el estado con el inicio
    int bloques;
    int bloques_libres;
    int estado;
  

}logic [12];

typedef struct{
    char nombre[50];
    int no_partition;
    int tamano;
    long int inicio; //creo que tambien puedo manejar el estado con el inicio
    int bloques;
    int bloques_libres;   
    char tipo [1];
    logic logicas;
    int estado;

  
    

}partition;


typedef struct{

     char nombre[50];
     int tamano;
     int particiones;
     partition p1;
     partition p2;
     partition p3;
     partition p4;
     int libre;
     int eliminado; 
}mbr;

#endif /* MBR_H */

