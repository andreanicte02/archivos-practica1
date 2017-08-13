/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stddef.h>
#include <stdio.h>
#include "mbr.h"
#include "bloques.h"
#include <string.h>

int e_l(mbr par) {


    if (strcasecmp(par.p1.tipo, "e") == 0) {
        for (int i = 0; i < 12; i++) {

            if (par.p1.logicas[i].estado == 1) {
                return 1;
            }
        }

    } else if (strcasecmp(par.p2.tipo, "e") == 0) {
        for (int i = 0; i < 12; i++) {

            if (par.p2.logicas[i].estado == 1) {
                return 1;
            }
        }

    } else if (strcasecmp(par.p3.tipo, "e") == 0) {
        for (int i = 0; i < 12; i++) {

            if (par.p3.logicas[i].estado == 1) {
                return 1;
            }
        }

    }else if (strcasecmp(par.p4.tipo, "e") == 0) {
        for (int i = 0; i < 12; i++) {

            if (par.p4.logicas[i].estado == 1) {
                return 1;
            }
        }

    }

    return 0;
}

int existe_disco(char *disco) {

    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    FILE *archivo = fopen(path, "r+b");

    if (archivo != NULL) {
        return 1;
        fclose(archivo);

    }

    return 0;

}

int e_x(mbr par) {

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

void reporte_mbr(char *disco) {

    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    FILE *archivo = fopen(path, "r+b");

    if (archivo != NULL) {
        //------------------mbr
        rewind(archivo);
        mbr temporal;
        fread(&temporal, sizeof (mbr), 1, archivo);
        fclose(archivo);
        //----------------------fin


        FILE* file;
        file = fopen("juego.dot", "w");

        fprintf(file, "digraph juego { \n");
        fprintf(file, "node [shape=plaintext]\n");
        fprintf(file, "a [label=<<TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n");






        fprintf(file, "<TR>\n");
        fprintf(file, "<TD ROWSPAN=\"15\"> mbr: %s </TD>\n", temporal.nombre);

        if (temporal.p1.estado == 1 && strcmp(temporal.p1.tipo, "p") == 0) {

            fprintf(file, "<TD ROWSPAN=\"2\"> Primaria: %s </TD>\n", temporal.p1.nombre);


        } else if (temporal.p1.estado == 1 && strcmp(temporal.p1.tipo, "e") == 0) {

            fprintf(file, "<TD COLSPAN=\"12\"> Extendida: %s </TD>\n", temporal.p1.nombre);

        }

        //------------------------------------------------
        if (temporal.p2.estado == 1 && strcmp(temporal.p2.tipo, "p") == 0) {


            fprintf(file, "<TD ROWSPAN=\"2\"> Primaria: %s </TD>\n", temporal.p2.nombre);


        } else if (temporal.p2.estado == 1 && strcmp(temporal.p2.tipo, "e") == 0) {

            fprintf(file, "<TD COLSPAN=\"12\"> Extendida: %s </TD>\n", temporal.p2.nombre);

        }

        //-----------------------------------------------------------------

        if (temporal.p3.estado == 1 && strcmp(temporal.p3.tipo, "p") == 0) {
            fprintf(file, "<TD ROWSPAN=\"2\"> Primaria: %s </TD>\n", temporal.p3.nombre);

        } else if (temporal.p3.estado == 1 && strcmp(temporal.p3.tipo, "e") == 0) {

            fprintf(file, "<TD COLSPAN=\"12\"> Extendida: %s </TD>\n", temporal.p3.nombre);

        }

        if (temporal.p4.estado == 1 && strcmp(temporal.p4.tipo, "p") == 0) {

            fprintf(file, "<TD ROWSPAN=\"2\"> Primaria: %s </TD>\n", temporal.p4.nombre);

        } else if (temporal.p4.estado == 1 && strcmp(temporal.p4.tipo, "e") == 0) {

            fprintf(file, "<TD COLSPAN=\"12\"> Extendida: %s </TD>\n", temporal.p4.nombre);

        }

        printf("%i", temporal.libre);
        if (temporal.libre > 0) {

            fprintf(file, "<TD ROWSPAN=\"2\"> Vacio: %d </TD>\n", temporal.libre);

        }

        fprintf(file, "</TR> \n");

        if (e_x(temporal) == 1 && e_l(temporal)==1) {

            fprintf(file, "<TR> \n");


            if (temporal.p1.estado == 1 && strcmp(temporal.p1.tipo, "e") == 0) {
                for (int i = 0; i < 12; i++) {

                    if (temporal.p1.logicas[i].estado == 1) {
                        fprintf(file, "<TD> Logica: %s </TD>\n", temporal.p1.logicas[i].nombre);

                    }
                }

            } else if (temporal.p2.estado == 1 && strcmp(temporal.p2.tipo, "e") == 0) {
                for (int i = 0; i < 12; i++) {

                    if (temporal.p2.logicas[i].estado == 1) {
                        fprintf(file, "<TD> Logica: %s </TD>\n", temporal.p2.logicas[i].nombre);

                    }
                }

            } else if (temporal.p3.estado == 1 && strcmp(temporal.p3.tipo, "e") == 0) {

                for (int i = 0; i < 12; i++) {

                    if (temporal.p3.logicas[i].estado == 1) {
                        fprintf(file, "<TD> Logica: %s </TD>\n", temporal.p3.logicas[i].nombre);

                    }
                }
            } else if (temporal.p4.estado == 1 && strcmp(temporal.p4.tipo, "e") == 0) {

                for (int i = 0; i < 12; i++) {

                    if (temporal.p4.logicas[i].estado == 1) {
                        fprintf(file, "<TD> Logica: %s </TD>\n", temporal.p4.logicas[i].nombre);

                    }
                }
            }



            fprintf(file, "</TR> \n");
        }

        fprintf(file, "</TABLE>>];\n");
        fprintf(file, "}");


        fclose(file);
       system("dot -Tpng juego.dot -o juego.png");
       system("xdg-open juego.png");


    } else {

    }






}