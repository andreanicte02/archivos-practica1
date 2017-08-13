#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mbr.h"
#include "bloques.h"
#include <sys/stat.h>
#include <time.h>

long int tbb(long int tp, long int tb) {

    long int n = (tp) / (1 + tb);
    return n;

}

mbr recuperar_mbrr(char *path) {

    FILE *archivo = fopen(path, "r+b");
    if (archivo != NULL) {
        rewind(archivo);
        mbr temporal;
        fread(&temporal, sizeof (mbr), 1, archivo);
        fclose(archivo);
        return temporal;
    }

    mbr t;
    return t;

}

void mejor_ajuste() {

}

void peor_ajuste() {

}

void reporte_bloques(char *disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    mbr temporal = recuperar_mbrr(path);

    FILE *archivo = fopen(path, "r+b");
    FILE *reporte = fopen("r_bloques.blqs", "w");
    if (archivo != NULL) {

        char nombre[50];
        printf("Ingrese el nomre de la particion\n");
        scanf("%s", nombre);

        if (strcmp(temporal.p1.nombre, nombre) == 0) {
            fseek(archivo, sizeof (temporal), SEEK_SET);

            long int n = tbb(temporal.p1.tamano * 1024 * 1024, sizeof (bloques));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);

            fprintf(reporte, "---------------------------------------\n");
            char c = '0';
            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                bloques b;
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|ID: %i Correlativo: %i Contenido: %s|", b.archivo, b.id, b.datos);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }





        } else if (strcmp(temporal.p2.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p2.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p2.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|ID: %i Correlativo: %i Contenido: %s|", b.archivo, b.id, b.datos);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }



        } else if (strcmp(temporal.p3.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p3.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p3.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }
            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|ID: %i Correlativo: %i Contenido: %s|", b.archivo, b.id, b.datos);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }




        } else if (strcmp(temporal.p4.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p4.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p4.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|ID: %i Correlativo: %i Contenido: %s|", b.archivo, b.id, b.datos);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }

        }


        fclose(archivo);

    }
    fclose(reporte);
    system("xdg-open r_bloques.blqs");

}

void reporte_bit(char *disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    mbr temporal = recuperar_mbrr(path);

    FILE *archivo = fopen(path, "r+b");
    FILE *reporte = fopen("r_bm.bits", "w");
    if (archivo != NULL) {

        char nombre[50];
        printf("Ingrese el nomre de la particion\n");
        scanf("%s", nombre);
        if (strcmp(temporal.p1.nombre, nombre) == 0) {
            fseek(archivo, sizeof (temporal), SEEK_SET);
            bloques b;
            long int n = tbb(temporal.p1.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");
            char c = '0';
            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {

                fread(&c, sizeof (c), 1, archivo);

                if (c == '0') {
                    fprintf(reporte, "|%c|", c);
                } else {
                    fprintf(reporte, "|%c|", c);
                }

                if (extra == 49) {

                    fprintf(reporte, "\n");
                    extra = 0;
                }

            }







        } else if (strcmp(temporal.p2.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p2.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;
            long int n = tbb(temporal.p2.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {

                fread(&c, sizeof (c), 1, archivo);

                if (c == '0') {
                    fprintf(reporte, "|%c|", c);
                } else {
                    fprintf(reporte, "|%c|", c);
                }

                if (extra == 49) {

                    fprintf(reporte, "\n");
                    extra = 0;
                }

            }





        } else if (strcmp(temporal.p3.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p3.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p3.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");


            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {

                fread(&c, sizeof (c), 1, archivo);

                if (c == '0') {
                    fprintf(reporte, "|%c|", c);
                } else {
                    fprintf(reporte, "|%c|", c);
                }

                if (extra == 49) {

                    fprintf(reporte, "\n");
                    extra = 0;
                }

            }



        } else if (strcmp(temporal.p4.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p4.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p4.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }


            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {

                fread(&c, sizeof (c), 1, archivo);

                if (c == '0') {
                    fprintf(reporte, "|%c|", c);
                } else {
                    fprintf(reporte, "|%c|", c);
                }

                if (extra == 49) {

                    fprintf(reporte, "\n");
                    extra = 0;
                }

            }



        }





        fclose(archivo);
    }
    fclose(reporte);
    system("xdg-open r_bm.bits");
    

}

void reporte(char *disco) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");
    mbr temporal = recuperar_mbrr(path);

    FILE *archivo = fopen(path, "r+b");
    FILE *reporte = fopen("r_id.ids", "w");

    if (archivo != NULL) {
        char nombre[50];
        printf("Ingrese el nomre de la particion\n");
        scanf("%s", nombre);

        if (strcmp(temporal.p1.nombre, nombre) == 0) {
            fseek(archivo, sizeof (temporal), SEEK_SET);
            bloques b;
            long int n = tbb(temporal.p1.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");
            char c = '0';
            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|%i|", b.archivo);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }





        } else if (strcmp(temporal.p2.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p2.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p2.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|%i|", b.archivo);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }



        } else if (strcmp(temporal.p3.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p3.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p3.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);

            char fe[200];
            struct tm fecha = *localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);



            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|%i|", b.archivo);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }



        } else if (strcmp(temporal.p4.nombre, nombre) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);

            for (long int i = 0; i < temporal.p4.inicio; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            bloques b;

            long int n = tbb(temporal.p4.tamano * 1024 * 1024, sizeof (b));
            fprintf(reporte, "Disco: %s \n", disco);
            fprintf(reporte, "Particon: %s \n", nombre);
            
                 char fe[200];
            struct tm  fecha=*localtime(&(time_t){time(NULL)});
            strcpy(fe, asctime(&fecha));
            fprintf(reporte, "Fecha de reporte: %s \n", fe);
            
            
            
            fprintf(reporte, "---------------------------------------\n");

            for (long int i = 0; i < n; i++) {

                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int extra = 0;
            for (long int i = 0; i < n; i++, extra++) {
                fread(&b, sizeof (b), 1, archivo);

                if (b.estado != 0) {
                    fprintf(reporte, "|%i|", b.archivo);

                } else {
                    fprintf(reporte, "|_|");
                }

                if (extra == 49) {
                    fprintf(reporte, "\n");
                    extra = 0;
                }


            }

        }




        fclose(archivo);
    }
    fclose(reporte);
    system("xdg-open r_id.ids");
    


}

partition primer_ajuste(FILE *archivo, float total_bloques, long int n, int tcadena, char *cadena, partition p, int id) {
    // el archiv esta posicionado en el inicio de cada particion
    //total bloques por archivo //n total de 0 y unos
    char uno = '1';
    char cero = '0';
    int contador = 0;
    char dato = '0';
    int total_pasados;
    long int sobra;
    long int otro;
    //posicionarse en el inicio de la particion;
    //encontrar un cero
    for (int i = 0; i < n; i++) {
        fread(&dato, sizeof (dato), 1, archivo);
        if (dato == '0') {
            contador++;
        } else if (dato == '1') {

            contador = 0;
        }

        if (contador >= total_bloques) {

            fseek(archivo, -1 * contador, SEEK_CUR); //regresa el cursor
            total_pasados = (i + 1);
            otro = total_pasados - contador;
            sobra = n - (i + 1);
            break;
        }

    }

    for (int i = 0; i < total_bloques; i++) {

        fwrite(&uno, sizeof (uno), 1, archivo);

    }

    int d = ftell(archivo);
    //escribir bloques

    for (long int i = 0; i < sobra; i++) { //posiciona al final del bitmap // situarse al inicio de la posicion de la particion y sumarle n
        fseek(archivo, sizeof (cero), SEEK_CUR);

    }
    d = ftell(archivo);


    printf("%ld inicio de los bloques", ftell(archivo));
    for (int i = 0; i < (total_pasados - contador); i++) {
        fseek(archivo, sizeof (bloques), SEEK_CUR);

    }


    int c = 0;

    for (int i = 0; i < contador; i++) {
        char actual[50];

        for (int l = 0; l < 50; l++) {
            actual[l] = '\0';
        }
        bloques blo;

        for (int x = 0; x < 50; x++, c++) {
            actual[x] = cadena[c]; //me caga la relatividad
            if (c == tcadena - 1) {

                break;
            }
        }
        blo.archivo = id;
        blo.estado = 1;
        strcpy(blo.datos, actual);
        blo.id = otro;
        otro++;
        p.bloques_libres++;
        p.bloques = n;
        fwrite(&blo, sizeof (blo), 1, archivo);

    }

    return p;


}

void carga_masiva(char * disco, char * particion, int id, char * contenido) {
    char path[100] = "/home/nicte/Escritorio/discos/";
    strcat(path, disco);
    strcat(path, ".disk");

    bloques bloque;
    mbr temporal = recuperar_mbrr(path);
    int ifsd = sizeof (temporal);


    FILE *archivo = fopen(path, "r+b"); // si no es ab
    if (archivo != NULL) {

        //----------------------------------------------------particion1
        if (strcmp(temporal.p1.nombre, particion) == 0) {

            fseek(archivo, sizeof (temporal), SEEK_SET);
            int longitud = strlen(contenido);
            float totalbloques = longitud / (50.0);
            long int n = tbb(temporal.p1.tamano * 1024 * 1024, sizeof (bloque));
            temporal.p1 = primer_ajuste(archivo, totalbloques, n, longitud, contenido, temporal.p1, id);



        } else if (strcmp(temporal.p2.nombre, particion) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);
            for (double i = 0; i < temporal.p2.inicio; i++) {
                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int longitud = strlen(contenido);
            int totalbloques = longitud / 50;
            long int n = tbb(temporal.p2.tamano * 1024 * 1024, sizeof (bloque));
            temporal.p2 = primer_ajuste(archivo, totalbloques, n, longitud, contenido, temporal.p2, id);



        } else if (strcmp(temporal.p3.nombre, particion) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);
            for (double i = 0; i < temporal.p3.inicio; i++) {
                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int longitud = strlen(contenido);
            int totalbloques = longitud / 50;
            long int n = tbb(temporal.p3.tamano * 1024 * 1024, sizeof (bloque));
            temporal.p3 = primer_ajuste(archivo, totalbloques, n, longitud, contenido, temporal.p3, id);




        } else if (strcmp(temporal.p4.nombre, particion) == 0) {

            char c = '0';
            fseek(archivo, 0, SEEK_SET);
            for (double i = 0; i < temporal.p4.inicio; i++) {
                fseek(archivo, sizeof (c), SEEK_CUR);
            }

            int longitud = strlen(contenido);
            int totalbloques = longitud / 50;
            long int n = tbb(temporal.p4.tamano * 1024 * 1024, sizeof (bloque));
            temporal.p4 = primer_ajuste(archivo, totalbloques, n, longitud, contenido, temporal.p4, id);

        }

        fseek(archivo, 0, SEEK_SET);
        fwrite(&temporal, sizeof (temporal), 1, archivo);
        fclose(archivo);
    } else {


    }


}

void analizar(char *linea, char*disco, char *particion) {
    //printf("%s \n", linea);

    int d_p = 0;
    char id[100] = "";
    char contenido[10000] = "";
    int estado = 0;
    int conta = 0;
    int conta2 = 0;
    for (int i = 0; i < 10000; i++) {
        //printf("%c--",linea[i]);

        if (linea[i] == NULL) {
            //printf("%s ----cib:%s \n", id, contenido);
            carga_masiva(disco, particion, atoi(id), contenido);
            break;

        }

        if (estado == 0) {





            if (linea[i] == ':' && d_p == 0) {
                estado = 1;
                d_p = 1;
            } else if (linea[i] == ':' && d_p == 1) {
                estado = 2;

            }

        } else if (estado == 1) {

            if (linea[i] == '}') {
                int d = atoi(id);
                //   printf("---ID: %i:", d);

                i = i - 1;
                estado = 0;
            } else {


                id[conta] = linea[i];
                conta++;

            }


        } else if (estado == 2) {



            contenido[conta2] = linea[i];
            conta2++;


        }

    }


}

void leer(char *path, char*disco, char* particion) {

    FILE *arhivo;

    if ((arhivo = fopen(path, "r+")) != NULL) {

        int cont = 0;
        while (feof(arhivo) == 0) {

            char linea[10000];
            fgets(linea, 10000, arhivo);

            analizar(linea, disco, particion);

        }
    }




}



