#include "export.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern FILE *out_fileTimesDist;
extern FILE *out_fileCheypBias;
extern double dticks;
extern double savespace;

void openfiles (void){
//Archivos de datos
    out_fileTimesDist = fopen("exportdataTimesDist.dat", "w");
    out_fileCheypBias = fopen("exportdataCheypBias.dat", "w");


    if(out_fileTimesDist == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    };

    if(out_fileCheypBias == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    };
};

void savefilesTimesDist(double graba1,double graba2){
    fprintf(out_fileTimesDist,"%5.5f,%5.5f \n",graba1,graba2);
};

void savefilesCheypBias(double graba1,double graba2,double graba3,double graba4,double graba5,double graba6){
    fprintf(out_fileCheypBias,"%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f \n",graba1,graba2,graba3,graba4,graba5,graba6);
};

