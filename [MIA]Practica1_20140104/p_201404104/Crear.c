
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mbr.h"
#include "bloques.h"
#include "reportes.h"
#include "analizador.h"
#include "maestro.h"
#include "raid.h"
#include "Crear.h"





char n_disco[50];

mbr recuperar_mbr(char *path) {

    FILE *archivo = fopen(path, "r+b");
    if (archivo != NULL) {

        rewind(archivo);

        mbr temporal;
        fread(&temporal, sizeof (mbr), 1, archivo);

        //printf("------ %s \n", temporal.nombre);


        fclose(archivo);
        return temporal;

    }

    mbr t;

    return t;

}

int hay_espacio(int tamdisco, int tamparticion, long int posinicial) {

    long int total = posinicial + (tamparticion * 1024 * 1024);
    long int t = tamdisco * 1024 * 1024;

    if (total < t) {//si es menor al disco

        return 1;
    }


    return 0;


}

int existe_nombre(char *nombre, mbr part) {

    if ((strcmp(nombre, part.p1.nombre) == 0) || (strcmp(nombre, part.p2.nombre) == 0) || (strcmp(nombre, part.p3.nombre) == 0) || (strcmp(nombre, part.p4.nombre) == 0)) {


        return 1; //existe nombre

    }



    return 0;
}

int existe_extendida(mbr par) {

    int contador = 0;
    if (strcasecmp(par.p1.tipo, "e") == 0) {

        contador++;
    } else if (strcasecmp(par.p2.tipo, "e") == 0) {

        contador++;
    } else if (strcasecmp(par.p3.tipo, "e") == 0) {

        contador++;
    } else if (strcasecmp(par.p4.tipo, "e") == 0) {
        contador++;
    }

    if (contador >= 1) {

        return 1; //ya existe una extendida
    } else {

        return 0; //no existe ninguna extendida

    }


}

int existe_logica(logic logica, char *nombre) {

    for (int ga = 0; ga < 12; ga++) {

        if (strcmp(logica[ga].nombre, nombre) == 0) {

            return 1;
        }

    }

    return 0;
}

long int ultima_pos(logic logica) {
    int pos = -1;
    for (int i = 0; i < 12; i++) {

        if (logica[i].estado == 0) {
            pos = i;
            if (i == 0) {
                pos = -2;
            }
            break;
        }


    }

    if (pos == -2) {

        return -2;
    } else if (pos == -1) {

        return -1;

    } else {
        logica[pos - 1].tamano * 1024 * 1024;
    }



}

partition enmedio(partition p, int tamano, long int inicio, char*nombre, char*tipo, int numero) {
    p.bloques = 0;
    p.bloques_libres = 0;
    p.estado = 1;
    p.inicio = inicio;
    if (strcasecmp(tipo, "e") == 0) {
        strcpy(p.tipo, tipo);

        for (int i = 0; i < 12; i++) {
            p.logicas[i].bloques_libres = 0;
            p.logicas[i].bloques = 0;
            p.logicas[i].estado = 0;
            p.logicas[i].inicio = 0;
            p.logicas[i].tamano = 0;
            p.logicas[i].no_partition = 0;
            strcpy(p.logicas[i].nombre, "vacia");

        }

    } else {

        strcpy(p.tipo, tipo); //p
    }
    p.no_partition = numero;
    strcpy(p.nombre, nombre);
    p.tamano = tamano;




    return p;
}

void particionar(char *nombw, char *tipo, int tamano) {

    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, nombw);
    strcat(path, ".disk");
    FILE *disco = fopen(path, "r+b");


    char nombre[50];
    printf("nombre:\n");
    scanf("%s", nombre);
    //--- path del discois
    //-----asdkjf no se por donde empezar a verifiacrarchivo{}

    if (disco != NULL) {





        if (strcasecmp(tipo, "p") == 0 || strcasecmp(tipo, "e") == 0) { // o extendida


            mbr temporal = recuperar_mbr(path);
            int tamanombr = sizeof (temporal);
            int seguir = 0;
            int esto = 0;


            if (temporal.eliminado == 0) {

                if (temporal.p1.estado == 0) {


                    if (hay_espacio(temporal.tamano, tamano, tamanombr) == 1 && existe_nombre(nombre, temporal) == 0 && existe_extendida(temporal) == 0) {



                        temporal.p1.estado = 1;
                        temporal.p1.no_partition = 1;
                        strcpy(temporal.p1.nombre, nombre);
                        strcpy(temporal.p1.tipo, "p");
                        temporal.p1.inicio = tamanombr;
                        temporal.p1.tamano = tamano; //dejare el tamaño en bits
                        temporal.p1.bloques = 0;
                        temporal.p1.bloques_libres = 0;

                        long int n = (temporal.tamano * 1024 * 1024)-(temporal.p1.tamano * 1024 * 1024) - sizeof (mbr);

                        temporal.libre = n;


                        if (strcasecmp(tipo, "e") == 0) {
                            strcpy(temporal.p1.tipo, "e");
                            for (int i = 0; i < 12; i++) {
                                temporal.p1.logicas[i].bloques_libres = 0;
                                temporal.p1.logicas[i].bloques = 0;
                                temporal.p1.logicas[i].estado = 0;
                                temporal.p1.logicas[i].inicio = 0;
                                temporal.p1.logicas[i].tamano = 0;
                                temporal.p1.logicas[i].no_partition = 0;
                                strcpy(temporal.p1.logicas[i].nombre, "vacia");

                            }


                        }
                        temporal.particiones++;

                        printf("Se creo la particion 1\n");


                    } else {

                        printf("El tamano de la particion excede el tamano del disco \n");
                    }

                } else if (temporal.p2.estado == 0) {

                    long int inicial = (temporal.p1.inicio) + (temporal.p1.tamano * 1024 * 1024);

                    if (hay_espacio(temporal.tamano, tamano, inicial) == 1 && existe_nombre(nombre, temporal) == 0 && existe_extendida(temporal) == 0) {

                        temporal.p2.estado = 1;
                        temporal.p2.no_partition = 2;
                        strcpy(temporal.p2.nombre, nombre);
                        strcpy(temporal.p2.tipo, "p");
                        temporal.p2.inicio = tamanombr + (temporal.p1.tamano * 1024 * 1024);
                        temporal.p2.tamano = tamano;
                        temporal.p2.bloques = 0;
                        temporal.p2.bloques_libres = 0;

                        long int n = (temporal.libre)-(temporal.p2.tamano * 1024 * 1024);
                        temporal.libre = n;
                        if (strcasecmp(tipo, "e") == 0) {
                            strcpy(temporal.p2.tipo, "e");
                            for (int i = 0; i < 12; i++) {
                                temporal.p2.logicas[i].bloques_libres = 0;
                                temporal.p2.logicas[i].bloques = 0;
                                temporal.p2.logicas[i].estado = 0;
                                temporal.p2.logicas[i].inicio = 0;
                                temporal.p2.logicas[i].tamano = 0;
                                temporal.p2.logicas[i].no_partition = 0;
                                strcpy(temporal.p2.logicas[i].nombre, "vacia");

                            }


                        }

                        temporal.particiones++;

                        printf("Se creo la particion 2\n");

                    } else {

                        printf("El tamano de la particion excede el tamano del disco \n");

                    }
                } else if (temporal.p3.estado == 0) {

                    long int inicial = (temporal.p2.inicio) + (temporal.p2.tamano * 1024 * 1024);
                    if (hay_espacio(temporal.tamano, tamano, inicial) == 1 && existe_nombre(nombre, temporal) == 0 && existe_extendida(temporal) == 0) {



                        temporal.p3.estado = 1;
                        temporal.p3.no_partition = 3;
                        strcpy(temporal.p3.nombre, nombre);
                        strcpy(temporal.p3.tipo, "p");
                        temporal.p3.inicio = tamanombr + (temporal.p1.tamano * 1024 * 1024)+ (temporal.p2.tamano * 1024 * 1024);
                        temporal.p3.tamano = tamano;
                        temporal.p3.bloques = 0;
                        temporal.p3.bloques_libres = 0;

                        long int n = (temporal.libre)-(temporal.p3.tamano * 1024 * 1024);
                        temporal.libre = n;


                        if (strcasecmp(tipo, "e") == 0) {
                            strcpy(temporal.p3.tipo, "e");
                            for (int i = 0; i < 12; i++) {
                                temporal.p3.logicas[i].bloques_libres = 0;
                                temporal.p3.logicas[i].bloques = 0;
                                temporal.p3.logicas[i].estado = 0;
                                temporal.p3.logicas[i].inicio = 0;
                                temporal.p3.logicas[i].tamano = 0;
                                temporal.p3.logicas[i].no_partition = 0;
                                strcpy(temporal.p3.logicas[i].nombre, "vacia");

                            }


                        }

                        temporal.particiones++;
                        printf("Se creo la particion 3\n");

                    } else {

                        printf("El tamano de la partic1ion excede el tamano del disco \n");

                    }


                } else if (temporal.p4.estado == 0) {

                    long int inicial = temporal.p3.inicio + (temporal.p3.tamano * 1024 * 1024);

                    if (hay_espacio(temporal.tamano, tamano, inicial) == 1 && existe_nombre(nombre, temporal) == 0 && existe_extendida(temporal) == 0) {

                        temporal.p4.estado = 1;
                        temporal.p4.no_partition = 4;
                        strcpy(temporal.p4.nombre, nombre);
                        strcpy(temporal.p4.tipo, "p");
                        temporal.p4.inicio = tamanombr + (temporal.p1.tamano * 1024 * 1024)+ (temporal.p2.tamano * 1024 * 1024)+(temporal.p3.tamano * 1024 * 1024);
                        temporal.p4.tamano = tamano;
                        temporal.p4.bloques = 0;
                        temporal.p4.bloques_libres = 0;




                        if (strcasecmp(tipo, "e") == 0) {
                            strcpy(temporal.p4.tipo, "e");
                            for (int i = 0; i < 12; i++) {
                                temporal.p4.logicas[i].bloques_libres = 0;
                                temporal.p4.logicas[i].bloques = 0;
                                temporal.p4.logicas[i].estado = 0;
                                temporal.p4.logicas[i].inicio = 0;
                                temporal.p4.logicas[i].tamano = 0;
                                temporal.p4.logicas[i].no_partition = 0;
                                strcpy(temporal.p4.logicas[i].nombre, "vacia");

                            }


                        }


                        temporal.particiones++;
                        long int n = (temporal.libre)-(temporal.p4.tamano * 1024 * 1024);
                        temporal.libre = n;
                        printf("Se creo la particion 4\n");

                    } else {


                        printf("El tamano de la particion excede el tamano del disco \n");

                    }
                } else {

                    printf("Todas las particiones estan ocupadas \n");
                }



                rewind(disco);
                fwrite(&temporal, sizeof (mbr), 1, disco);
                fclose(disco);
            }//-------------EN MEDIO------------------------------------------------------------------
            else if (temporal.eliminado == 1) {

                int seguir = 1;

                if (temporal.p1.estado == 0 && seguir == 1) {

                    long int principio = sizeof (mbr);
                    long int fin;
                    long int ta;
                    long int ta2 = tamano * 1024 * 1024;

                    if (temporal.p2.estado == 0 && temporal.p3.estado == 0 && temporal.p4.estado == 1) {
                        fin = temporal.p4.inicio;
                        ta = fin - principio;

                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p1 = enmedio(temporal.p1, tamano, principio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;
                        }




                    } else if (temporal.p2.estado = 0 && temporal.p3.estado == 1) {
                        fin = temporal.p3.inicio;
                        ta = fin - principio;
                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p1 = enmedio(temporal.p1, tamano, principio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;
                        }


                    } else if (temporal.p2.estado = 1) {
                        fin = temporal.p2.inicio;
                        ta = fin - principio;
                        if (ta2 < ta) { //si taano de la particion es menor a lo que qeuda
                            temporal.particiones++;
                            temporal.p1 = enmedio(temporal.p1, tamano, principio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;
                        }


                    }




                }


                if (temporal.p2.estado == 0 && seguir == 1) {
                    long int inicio;
                    long int fin;
                    long int ta2 = tamano * 1024 * 1024;

                    //--------------------------------------------------------------
                    if (temporal.p1.estado == 0) {

                        inicio = sizeof (mbr);
                    } else if (temporal.p1.estado == 1) {

                        inicio = (temporal.p1.inicio) + (temporal.p1.tamano * 1024 * 1024);

                    }
                    //--------------------------------------------------------------
                    if (temporal.p3.estado == 0 && temporal.p4.estado == 0) {
                        fin = temporal.tamano * 1024 * 1024; // total del disco
                        long int ta = fin - inicio;

                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p2 = enmedio(temporal.p2, tamano, inicio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;
                        }



                    } else if (temporal.p3.estado == 0 && temporal.p4.estado == 1) {
                        fin = temporal.p4.inicio;
                        long int ta = fin - inicio;
                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p2 = enmedio(temporal.p2, tamano, inicio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;

                        }


                    } else if (temporal.p3.estado == 1) {
                        fin = temporal.p3.inicio;
                        long int ta = fin - inicio;
                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p2 = enmedio(temporal.p2, tamano, inicio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;

                        }


                    }

                }

                if (temporal.p3.estado == 0 && seguir == 1) {
                    int inicio;
                    int fin;
                    int ta;
                    long int ta2 = tamano * 1024 * 1024;
                    //-----------------------------------------------
                    if (temporal.p1.estado == 0 && temporal.p2.estado == 0) {
                        inicio = sizeof (mbr);
                        //---mbr
                    } else if (temporal.p1.estado == 1 && temporal.p2.estado == 0) {
                        inicio = temporal.p1.inicio + temporal.p1.tamano * 1024 * 1024;


                    } else if (temporal.p1.estado == 0 && temporal.p2.estado == 1) {
                        inicio = temporal.p2.inicio + temporal.p2.tamano * 1024 * 1024;

                    }

                    //-----------------------------------------------
                    if (temporal.p4.estado == 0) {
                        fin = temporal.tamano * 1024 * 1024;
                        ta = fin - inicio;
                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p3 = enmedio(temporal.p3, tamano, inicio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;
                            seguir = 0;

                        }

                    } else if (temporal.p4.estado == 1) {
                        fin = temporal.p4.inicio;
                        ta = fin - inicio;
                        if (ta2 < ta) {
                            temporal.particiones++;
                            temporal.p3 = enmedio(temporal.p3, tamano, inicio, nombre, tipo, temporal.particiones);
                            temporal.libre = temporal.libre + tamano * 1024 * 1024;

                            seguir = 0;
                        }
                    }

                }


                if (temporal.p4.estado == 0 && seguir == 1) {
                    long int inicio;
                    long int fin;
                    long int ta;
                    long int ta2 = tamano * 1024 * 1024;
                    //---------------------------
                    if (temporal.p1.estado == 1 && temporal.p2.estado == 0 && temporal.p3.estado == 0) {
                        inicio = (temporal.p1.inicio) + (temporal.p1.tamano * 1024 * 1024);

                    } else if (temporal.p2.estado == 1 && temporal.p3.estado == 0) {
                        inicio = (temporal.p2.inicio) +(temporal.p2.tamano * 1024 * 1024);

                    } else if (temporal.p3.estado == 1) {
                        inicio = (temporal.p3.inicio)+ (temporal.p3.tamano * 1024 * 1024);



                    }


                    fin = temporal.tamano * 1024 * 1024;
                    ta = fin - inicio;
                    if (ta2 < ta) {
                        temporal.particiones++;
                        temporal.p4 = enmedio(temporal.p4, tamano, inicio, nombre, tipo, temporal.particiones);
                        temporal.libre = temporal.libre + tamano * 1024 * 1024;
                        seguir = 0;

                    }
                    //si no se pasa del tamaño del disco

                } else {
                    printf("no hay espacion en el disco \n");
                }



                rewind(disco);
                fwrite(&temporal, sizeof (mbr), 1, disco);
                fclose(disco);


                //--------------rescribir mbr

            }
            //-------------------------------------------------FIN EN 


        }//----------------------LGOICAS----------------------------------
        else if (strcasecmp(tipo, "l") == 0) {

            mbr temporal = recuperar_mbr(path);

            if (strcasecmp(temporal.p1.tipo, "e") == 0) {
                //encontrar la particion con estado 0
                int is = -1;
                int ta = 0;
                for (int i = 0; i < 12; i++) {

                    if (temporal.p1.logicas[i].estado == 0) {
                        is = i;
                        if (i == 0) {
                            is = -2;
                        }
                        break;
                    } else {
                        ta = ta + temporal.p1.logicas[i].tamano;
                    }

                }

                if (is == -1) {

                    printf("no hay espacio");
                } else if (is == -2) { //primera posicion
                    if ((ta + tamano) < temporal.p1.tamano) {

                        temporal.p1.logicas[0].estado = 1;
                        temporal.p1.logicas[0].inicio = tamano + temporal.p1.inicio;
                        temporal.p1.logicas[0].tamano = tamano;
                        temporal.p1.logicas[0].no_partition = 1;
                        strcpy(temporal.p1.logicas[0].nombre, nombre);


                    }

                } else {

                    if ((ta + tamano) < temporal.p1.tamano) {

                        temporal.p1.logicas[is].estado = 1;
                        temporal.p1.logicas[is].inicio = (temporal.p1.logicas[is - 1].tamano * 1024 * 1024) + temporal.p1.logicas[is - 1].inicio;
                        temporal.p1.logicas[is].tamano = tamano;
                        temporal.p1.logicas[is].no_partition = is + 1;
                        strcpy(temporal.p1.logicas[is].nombre, nombre);


                    }

                }

            } else if (strcasecmp(temporal.p2.tipo, "e") == 0) {
                int is = -1;
                int ta = 0;
                for (int i = 0; i < 12; i++) {

                    if (temporal.p2.logicas[i].estado == 0) {
                        is = i;
                        if (i == 0) {
                            is = -2;
                        }
                        break;
                    } else {
                        ta = ta + temporal.p2.logicas[i].tamano;
                    }

                }

                if (is == -1) {

                    printf("no hay espacio");
                } else if (is == -2) {
                    if ((ta + tamano) < temporal.p2.tamano) {

                        temporal.p2.logicas[0].estado = 1;
                        temporal.p2.logicas[0].inicio = temporal.p2.inicio;
                        temporal.p2.logicas[0].tamano = tamano;
                        temporal.p2.logicas[0].no_partition = 1;
                        strcpy(temporal.p2.logicas[0].nombre, nombre);



                    } else {
                        printf("error\n");
                    }

                } else {

                    if ((ta + tamano) < temporal.p2.tamano) {


                        temporal.p2.logicas[is].estado = 1;
                        temporal.p2.logicas[is].inicio = (temporal.p2.logicas[is - 1].tamano * 1024 * 1024) + temporal.p2.logicas[is - 1].inicio;
                        temporal.p2.logicas[is].tamano = tamano;
                        temporal.p2.logicas[is].no_partition = is + 1;
                        strcpy(temporal.p2.logicas[is].nombre, nombre);

                    } else {
                        printf("error\n");
                    }

                }



            } else if (strcasecmp(temporal.p3.tipo, "e") == 0) {

                int is = -1;
                int ta = 0;
                for (int i = 0; i < 12; i++) {

                    if (temporal.p3.logicas[i].estado == 0) {
                        is = i;
                        if (i == 0) {
                            is = -2;
                        }
                        break;
                    } else {
                        ta = ta + temporal.p3.logicas[i].tamano;
                    }

                }

                if (is == -1) {

                    printf("no hay espacio");
                } else if (is == -2) {
                    if ((ta + tamano) < temporal.p3.tamano) {

                        temporal.p3.logicas[0].estado = 1;
                        temporal.p3.logicas[0].inicio = tamano, temporal.p3.inicio;
                        temporal.p3.logicas[0].tamano = tamano;
                        temporal.p3.logicas[0].no_partition = 1;
                        strcpy(temporal.p3.logicas[0].nombre, nombre);



                    }

                } else {

                    if ((ta + tamano) < temporal.p3.tamano) {


                        temporal.p3.logicas[is].estado = 1;
                        temporal.p3.logicas[is].inicio = (temporal.p3.logicas[is - 1].tamano * 1024 * 1024) + temporal.p3.logicas[is - 1].inicio;
                        temporal.p3.logicas[is].tamano = tamano;
                        temporal.p3.logicas[is].no_partition = is + 1;
                        strcpy(temporal.p3.logicas[is].nombre, nombre);
                    }

                }


            } else if (strcasecmp(temporal.p4.tipo, "e") == 0) {


                int is = -1;
                int ta = 0;
                for (int i = 0; i < 12; i++) {

                    if (temporal.p4.logicas[i].estado == 0) {
                        is = i;
                        if (i == 0) {
                            is = -2;
                        }
                        break;
                    } else {
                        ta = ta + temporal.p4.logicas[i].tamano;
                    }

                }

                if (is == -1) {

                    printf("no hay espacio");
                } else if (is == -2) {
                    if ((ta + tamano) < temporal.p4.tamano) {

                        temporal.p4.logicas[0].estado = 1;
                        temporal.p4.logicas[0].inicio = tamano, temporal.p4.inicio;
                        temporal.p4.logicas[0].tamano = tamano;
                        temporal.p4.logicas[0].no_partition = 1;
                        strcpy(temporal.p4.logicas[0].nombre, nombre);

                    }

                } else {

                    if ((ta + tamano) < temporal.p4.tamano) {

                        temporal.p4.logicas[is].estado = 1;
                        temporal.p4.logicas[is].inicio = (temporal.p4.logicas[is - 1].tamano * 1024 * 1024) + temporal.p4.logicas[is - 1].inicio;
                        temporal.p4.logicas[is].tamano = tamano;
                        temporal.p4.logicas[is].no_partition = is + 1;
                        strcpy(temporal.p4.logicas[is].nombre, nombre);
                    }

                }


            } else {

                printf("no existe particion extendida, porfavor cree una");
            }

            rewind(disco);
            fwrite(&temporal, sizeof (mbr), 1, disco);
            fclose(disco);

            //reesrcibir el mbr

        }
    } else {

    }

}

void cmbr(int tamano, char *nombre, char *path) {

    mbr nuevo;
    strcpy(nuevo.nombre, nombre);
    nuevo.tamano = tamano;
    nuevo.particiones = 0;
    nuevo.eliminado = 0;
    nuevo.libre = tamano;
    //----------identificando particiones
    nuevo.p1.no_partition = 0;
    nuevo.p1.inicio = -1;
    nuevo.p1.bloques = 0;
    nuevo.p1.bloques_libres = 0;
    strcpy(nuevo.p1.nombre, "vacio");
    strcpy(nuevo.p1.tipo, "f");
    nuevo.p1.tamano = 0;
    nuevo.p1.estado = 0; //es que no se a usado


    nuevo.p2.no_partition = 0;
    nuevo.p2.inicio = -1;
    nuevo.p2.bloques = 0;
    nuevo.p2.bloques_libres = 0;
    strcpy(nuevo.p2.nombre, "vacio");
    strcpy(nuevo.p2.tipo, "f");
    nuevo.p2.tamano = 0;
    nuevo.p2.estado = 0; //es que no se a usado


    nuevo.p3.no_partition = 0;
    nuevo.p3.inicio = -1;
    nuevo.p3.bloques = 0;
    nuevo.p3.bloques_libres = 0;
    strcpy(nuevo.p3.nombre, "vacio");
    strcpy(nuevo.p3.tipo, "f");
    nuevo.p3.tamano = 0;
    nuevo.p3.estado = 0; //es que no se a usado


    nuevo.p4.no_partition = 0;
    nuevo.p4.inicio = -1;
    nuevo.p4.bloques = 0;
    nuevo.p4.bloques_libres = 0;
    strcpy(nuevo.p4.nombre, "vacio");
    strcpy(nuevo.p4.tipo, "f");
    nuevo.p4.tamano = 0;
    nuevo.p4.estado = 0; //es que no se a usado

    //----------- perdoname dios por no optimizar :I 



    FILE *archivo = fopen(path, "r+b"); // si no es ab

    if (archivo != NULL) {

        rewind(archivo);
        fwrite(&nuevo, sizeof (mbr), 1, archivo);
        fclose(archivo);
        //recuperar_mbr(path);
    }



}

void cdisk(int tamano, char *nombre) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, nombre);
    strcat(path, ".disk");
    FILE *archivo = fopen(path, "wb+");

    if (archivo != NULL) {
        char byte = '\0';

        for (int conta = 0; conta < tamano; conta++) {
            for (int x = 0; x < 1024; x++) {

                fwrite(&byte, sizeof (byte), 1024, archivo);

            }

        }

        fclose(archivo);
        cmbr(tamano, nombre, path);

    } else {

        printf("ERROR AL CREAR DISCO");

    }






}

void menu1() {
    int tamano;
    char nombre[50];
    printf("Ingrese el tamaño de disco que va a crear en MB: \n");
    scanf("%d", &tamano);
    printf("Ingrese el nombre del disco: \n");
    scanf("%s", nombre);


    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, nombre);
    strcat(path, ".disk");
    FILE *archivo = fopen(path, "rb");

    if (archivo == NULL) {
        maestro(nombre, tamano);
        cdisk(tamano, nombre);
        printf("Se creo disco \n");
        Raid1(nombre);

    } else {
        printf("Ya existe un disco con ese nobmre \n");

    }


}

void menu3(char *nombre) { //menu para las particiones

    char path[150] = "/home/nicte/Escritorio/discos/";

    //char nombre [50];

    char t_part[1];
    int tamano;


    //printf("Disco que va particionar: \n");
    //scanf("%s", nombre);
    strcat(path, nombre);
    strcat(path, ".disk");

    FILE *archivo = fopen(path, "r+b");

    if (archivo != NULL) {
        fclose(archivo);

        printf("Tipo de particion \n");
        scanf("%s", t_part);

        printf("Tamano de la particion \n"); // aca todavia la particion no tiene formato
        scanf("%d", &tamano); //los bloques quedaron de 50 mb todos
        particionar(nombre, t_part, tamano);

    } else {

        printf("El disco no existe \n"); //RECORDAR MONTAR ESTAS ONDAS;
    }


}

int todasvacias(mbr disco) {
    if (disco.p1.estado == 0 && disco.p2.estado == 0 && disco.p3.estado == 0 && disco.p4.estado == 0) {
        return 1;
    }

    return 0;
}

void eliminarp(char *nombre, char* disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    mbr temporal = recuperar_mbr(path);
    //verificar si el disco existe
    if (strcasecmp(nombre, temporal.p1.nombre) == 0) {

        temporal.p1.no_partition = 0;
        temporal.p1.inicio = -1;
        temporal.p1.bloques = 0;
        temporal.p1.bloques_libres = 0;
        strcpy(temporal.p1.nombre, "vacio");
        strcpy(temporal.p1.tipo, "f");
        temporal.p1.tamano = 0;
        temporal.p1.estado = 0; //es que no se a usado
        temporal.particiones--;
        temporal.libre = temporal.libre + temporal.p1.tamano * 1024 * 1024;

        printf("se elimino la particion 1\n");


    } else if (strcasecmp(nombre, temporal.p2.nombre) == 0) {
        temporal.p2.no_partition = 0;
        temporal.p2.inicio = -1;
        temporal.p2.bloques = 0;
        temporal.p2.bloques_libres = 0;
        strcpy(temporal.p2.nombre, "vacio");
        strcpy(temporal.p2.tipo, "f");
        temporal.p2.tamano = 0;
        temporal.p2.estado = 0; //es que no se a usado
        temporal.libre = temporal.libre + temporal.p2.tamano * 1024 * 1024;
        temporal.particiones--;
        printf("se elimino la particion 2\n");


    } else if (strcasecmp(nombre, temporal.p3.nombre) == 0) {

        temporal.p3.no_partition = 0;
        temporal.p3.inicio = -1;
        temporal.p3.bloques = 0;
        temporal.p3.bloques_libres = 0;
        strcpy(temporal.p3.nombre, "vacio");
        strcpy(temporal.p3.tipo, "f");
        temporal.p3.tamano = 0;
        temporal.p3.estado = 0; //es que no se a usado
        temporal.libre = temporal.libre + temporal.p3.tamano * 1024 * 1024;
        temporal.particiones--;
        printf("se elimino la particion 3\n");

    } else if (strcasecmp(nombre, temporal.p4.nombre) == 0) {

        temporal.p4.no_partition = 0;
        temporal.p4.inicio = -1;
        temporal.p4.bloques = 0;
        temporal.p4.bloques_libres = 0;
        strcpy(temporal.p4.nombre, "vacio");
        strcpy(temporal.p4.tipo, "f");
        temporal.p4.tamano = 0;
        temporal.p4.estado = 0; //es que no se a usado
        temporal.libre = temporal.libre + temporal.p4.tamano * 1024 * 1024;
        temporal.particiones--;
        printf("se elimino la particion 4\n");

    } else {
        printf("la particion no existe \n");
    }

    if (todasvacias(temporal) == 1) {

        temporal.eliminado = 0;
        temporal.libre = temporal.tamano;
        printf("se elimaron todas las particiones 1\n");
    }



    FILE *archivo = fopen(path, "r+b"); // si no es ab

    if (archivo != NULL) {

        rewind(archivo);
        fwrite(&temporal, sizeof (mbr), 1, archivo);
        fclose(archivo);
        //recuperar_mbr(path);
    }






}

long int tb(long int tp, long int tb) {
    long int n = (tp) / (1 + tb);
    return n;



}

void formato_rapido(char *nombre, char*disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    FILE *archivo = fopen(path, "r+b"); // si no es ab

    if (archivo != NULL) {
        fclose(archivo);

        mbr temporal = recuperar_mbr(path);
        int sd = sizeof (temporal);
        bloques te;
        te.archivo = 0;
        te.id = 0;
        strcpy(te.datos, "va");
        te.estado = 0;
        long int n = 0;

        if (strcmp(temporal.p1.nombre, nombre) == 0 && strcmp(temporal.p1.tipo, "p") == 0) {

            FILE *disk = fopen(path, "r+b"); // si no es ab
            char c = '0';
            n = tb(temporal.p1.tamano * 1024 * 1024, sizeof (te));
            fseek(disk, sizeof (mbr), SEEK_SET); //en el principio de la particion 1

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }

            fclose(disk);

        } else if (strcmp(temporal.p2.nombre, nombre) == 0 && strcmp(temporal.p2.tipo, "p") == 0) {


            n = tb(temporal.p2.tamano * 1024 * 1024, sizeof (te));
            FILE *disk = fopen(path, "r+b");
            char c = '0';
            fseek(disk, 0, SEEK_SET);

            for (double i = 0; i < temporal.p2.inicio; i++) { //inicio

                fseek(disk, sizeof (c), SEEK_CUR);

            }

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }


            fclose(disk);


        } else if (strcmp(temporal.p3.nombre, nombre) == 0 && strcmp(temporal.p3.tipo, "p") == 0) {

            n = tb(temporal.p3.tamano * 1024 * 1024, sizeof (te));
            FILE *disk = fopen(path, "r+b");
            char c = '0';
            fseek(disk, 0, SEEK_SET);

            for (double i = 0; i < temporal.p3.inicio; i++) {

                fseek(disk, sizeof (c), SEEK_CUR);

            }

            //printf("%ld -1 \n", ftell(disk));

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }

            fclose(disk);


        } else if (strcmp(temporal.p4.nombre, nombre) == 0 && strcmp(temporal.p4.tipo, "p") == 0) {

            n = tb(temporal.p4.tamano * 1024 * 1024, sizeof (te));
            FILE *disk = fopen(path, "r+b");
            char c = '0';
            fseek(disk, 0, SEEK_SET);

            for (double i = 0; i < temporal.p4.inicio; i++) {

                fseek(disk, sizeof (c), SEEK_CUR);

            }


            //printf("%ld -1 \n", ftell(disk));

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }

            fclose(disk);


        }




    } else {


        printf("no existe \n");
    }



}

void formato(char *nombre, char* disco) { //---------------ARREGLAR
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    FILE *archivo = fopen(path, "r+b"); // si no es ab

    if (archivo != NULL) {
        fclose(archivo);

        mbr temporal = recuperar_mbr(path);
        int sd = sizeof (temporal);
        bloques te;
        te.archivo = 0;
        te.id = 0;
        strcpy(te.datos, "va");
        te.estado = 0;
        long int n = 0;

        if (strcmp(temporal.p1.nombre, nombre) == 0 && strcmp(temporal.p1.tipo, "p") == 0) {

            FILE *disk = fopen(path, "r+b"); // si no es ab
            char c = '0';
            n = tb(temporal.p1.tamano * 1024 * 1024, sizeof (te));
            fseek(disk, sizeof (mbr), SEEK_SET); //en el principio de la particion 1

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }
            //printf("%ld -fin1\n", ftell(disk));
            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&te, sizeof (te), 1, disk);
            }


            //printf("%ld -fin2\n", ftell(disk));








            fclose(disk);

        } else if (strcmp(temporal.p2.nombre, nombre) == 0 && strcmp(temporal.p2.tipo, "p") == 0) {


            n = tb(temporal.p2.tamano * 1024 * 1024, sizeof (te));
            FILE *disk = fopen(path, "r+b");
            char c = '0';
            fseek(disk, 0, SEEK_SET);

            for (double i = 0; i < temporal.p2.inicio; i++) {

                fseek(disk, sizeof (c), SEEK_CUR);

            }

            //printf("%ld -1 \n", ftell(disk));

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }
            //printf("%ld -fin1\n", ftell(disk));


            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&te, sizeof (te), 1, disk);
            }


            //printf("%ld -3 \n", ftell(disk));


            fclose(disk);


        } else if (strcmp(temporal.p3.nombre, nombre) == 0 && strcmp(temporal.p3.tipo, "p") == 0) {

            n = tb(temporal.p3.tamano * 1024 * 1024, sizeof (te));
            FILE *disk = fopen(path, "r+b");
            char c = '0';
            fseek(disk, 0, SEEK_SET);

            for (double i = 0; i < temporal.p3.inicio; i++) {

                fseek(disk, sizeof (c), SEEK_CUR);

            }

            //printf("%ld -1 \n", ftell(disk));

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }
            //printf("%ld -fin1\n", ftell(disk));


            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&te, sizeof (te), 1, disk);
            }


            //printf("%ld -3 \n", ftell(disk));




            fclose(disk);


        } else if (strcmp(temporal.p4.nombre, nombre) == 0 && strcmp(temporal.p4.tipo, "p") == 0) {

            n = tb(temporal.p4.tamano * 1024 * 1024, sizeof (te));
            FILE *disk = fopen(path, "r+b");
            char c = '0';
            fseek(disk, 0, SEEK_SET);

            for (double i = 0; i < temporal.p4.inicio; i++) {

                fseek(disk, sizeof (c), SEEK_CUR);

            }


            //printf("%ld -1 \n", ftell(disk));

            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&c, sizeof (c), 1, disk);
            }
           //printf("%ld -fin1\n", ftell(disk));


            for (long int i = 0; i < n; i++) { //bitmapas
                fwrite(&te, sizeof (te), 1, disk);
            }


            //printf("%ld -3 \n", ftell(disk));
            fclose(disk);


        }




    } else {


        printf("no existe \n");
    }



}

void solo_crear(char *disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    //------------------------------------------------------
    char linea_comando[100];
    int id;
    char particion[50];

    printf("Contenido:= ");
    scanf(" %[^\n]s", linea_comando);
    printf("\n");

    printf("ID:= ");
    scanf(" %i", &id);
    printf("\n");

    printf("Particion:= ");
    scanf(" %s", particion);
    printf("\n");


    carga_masiva(disco, particion, id, linea_comando);



}

void menu4(char *disco) {

    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    
    //printf("%s",path);
    int is = 0;

    while (is == 0) {
        FILE *archivo = fopen(path, "r+b"); // si no es ab

        if (archivo != NULL) {
            fclose(archivo); //si se caga todo quitar esto

            printf("1. Crear particiones \n");
            printf("2. Dar formato \n");
            printf("3. Eliminar particiones \n");
            printf("4. Reporte del disco \n");
            printf("5. Carga masiva\n");
            printf("6. Reporte id \n");
            printf("7. Reporte bm \n");
            printf("8. Reporte archivos\n");
            printf("9. Formato Rapido \n");
            printf("10. Formateo Completo \n");
            printf("11. Crear archivos \n");
            printf("n. Salir\n");

            int opcion = 0;
            scanf("%i", &opcion);

            if (opcion == 1) {
                menu3(disco);
                Raid1(disco);

            } else if (opcion == 2) {

                char nombre[50];
                printf("Ingrese el nombre de la paMontarrticion para dar formato:\n");
                scanf("%s", nombre);
                formato(nombre, disco);
                Raid1(disco);

            } else if (opcion == 3) {

                char nombre[50];
                printf("Ingrese el nombre de la particion \n");
                scanf("%s", nombre);
                eliminarp(nombre, disco);
                Raid1(disco);

            } else if (opcion == 4) {

                reporte_mbr(disco);
                Raid1(disco);

            } else if (opcion == 5) {

                char carga[50]; //--- ruta
                char particion[50]; //--- particion
                printf("Ingrese la ruta del archivo\n");
                scanf("%s", carga);
                printf("Ingrese el nombre de la particion a la que se le va efectuar la carga:\n");
                scanf("%s", particion); //verificar si existe la particion
                mbr temporal = recuperar_mbr(path);
                if (existe_nombre(particion, temporal) == 1) {

                    leer(carga, disco, particion);
                } else {
                    printf("La particion que indico no existe");
                }

                Raid1(disco);
                //1leer(carga, disco);


            } else if (opcion == 6) {
                reporte(disco);
                Raid1(disco);

            } else if (opcion == 7) {
                reporte_bit(disco);
                Raid1(disco);
            } else if (opcion == 8) {
                reporte_bloques(disco);
                Raid1(disco);
            } else if (opcion == 9) {

                char nombre[50];
                printf("Ingrese el nombre de la particion para dar formato rapido:\n");
                scanf("%s", nombre);
                formato(nombre, disco);
                Raid1(disco);


            } else if (opcion == 10) {

                char nombre[50];
                printf("Ingrese el nombre de la particion para dar formato completo:\n");
                scanf("%s", nombre);
                formato(nombre, disco);
                Raid1(disco);


            } else if (opcion == 11) {

                solo_crear(disco);
                Raid1(disco);
            } else {
                is = 1;
            }



        } else {
            printf("no existe el disco");
            break;
        }
    }

}

void menugenera() {

    int fj = 0;

    while (fj == 0) {
        int opcion = 0;
        printf("MENU: \n");
        printf("1. Crear disco: \n");
        printf("2. Montar disco: \n");



        printf("n. Salir: \n");

        scanf("%d", &opcion);

        if (opcion == 1) {

            menu1();
        } else if (opcion == 3) {

        } else if (opcion == 4) {

        } else if (opcion == 5) {

        } else if (opcion == 6) {


        } else if (opcion == 7) {

        } else if (opcion = 2) {

            char disco [50];
            printf("Disco que va montar:\n");
            scanf("%s", disco);


            char path[100] = "/home/nicte/Escritorio/discos/";
            strcat(path, disco);
            strcat(path, ".disk");

            char path2[100] = "/home/nicte/Escritorio/discos/";
            strcat(path2, disco);
            strcat(path2, ".raid.disk");

            //----------si existe el normal solo asi
            FILE *primero = fopen(path, "rb");
            FILE *segundo = fopen(path2, "rb");
            
            if (primero != NULL) {
               
                menu4(disco);
                rewind(primero);
                fclose(primero);
                
            } else if (primero == NULL && segundo != NULL) {
                char otro[100];
                strcpy(otro,disco);
                strcat(otro,".raid");
                menu4(otro);
                rewind(segundo);
                fclose(segundo);
                printf("se cargo el raid\n");

            }else{
            
                printf("el disco no existe\n");
            }

            //--------------si no existe el normal pero si el raid mando el raid

            //----------- si no no existe

        } else {

            fj = 1;
        }





    }

}


