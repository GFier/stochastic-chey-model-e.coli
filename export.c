#include "export.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern FILE *out_fileTimesDist;
extern FILE *out_fileCheypBias;
extern FILE *out_fileCheypDist;
extern FILE *out_fileFlaState;
extern double dticks;
extern double savespace;

void openfiles (void){
//Archivos de datos
    out_fileTimesDist = fopen("exportdataTimesDist.dat", "w");
    out_fileCheypBias = fopen("exportdataCheypBias.dat", "w");
    out_fileCheypDist = fopen("exportdataCheypDist.dat", "w");
    out_fileFlaState = fopen("exportdataFlaState.dat", "w");

    if(out_fileTimesDist == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    };

    if(out_fileCheypBias == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    };

    if(out_fileCheypDist == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    };

    if(out_fileFlaState == NULL){
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

void savefilesCheypDist(double graba1,double graba2){
    fprintf(out_fileCheypDist,"%5.5f,%5.5f \n",graba1,graba2);
};

void savefilesFlaState(int graba1,int graba2,int graba3,int graba4,double graba5){
    fprintf(out_fileFlaState,"%5i,%5i,%5i,%5i,%5.5f \n",graba1,graba2,graba3,graba4,graba5);
};


