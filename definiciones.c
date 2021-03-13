#include "definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
// For Main
double dticks =0.0;
double ddt=scaletime*0.00001; // Step time
double tiempo =0.0;
double dtickshut = 50000.0;// Time for shutting
double savespace=100.0; // Sample frequency

//nfla is the flagella number
//nbac is the bacteria number
// Parametrization for 3 flagella with unstimulated Tumble Bias =0.15

//For Solver
// CHEY-P
double cheyp[nbac][nfla];
double MU[nbac][nfla];
double mu=3.0;// Steady molar CheY-P concentration
double deltaMU=0.1;// MU increments
double MUcut=4.0;// Upper bound for MU which ends program
double THETA =1.0/scaletime;
double QCH=0.7/(scaletime);// Noise intensity
double CRT = 3.01;// Upper threshold
double CTR =2.59;// lower threshold
double tmpcheyp[nbac][nfla];
int shift[nbac][nfla]; // 1->RUN - 0->TUMBLE
double etta=0.0;
int doingshift[nbac][nfla];
double tumbletimes[nbac];
double tmpruntimes[nbac];
double runtimes[nbac];
double tmptumbletimes[nbac];
int datacounter[nbac];
//For Statistics:
double meanrun=0.0;
double meantumble=0.0;
double varrun=0.0;
double vartumble=0.0;
double meanrENbias=0.0;
double meantENbias=0.0;
double meanrbias=0.0;
double meantbias=0.0;
double varrENbias=0.0;
double vartENbias=0.0;
double varrbias=0.0;
double vartbias=0.0;
double tmpbiast[nbac];
double tmpbiasr[nbac];
double biast[nbac];
double biasr[nbac];
int globaldoingshift[nbac];
int globaldatacounter=0;
int RTstate[nbac]; // Run -> 0 Tumble -> 1
int bootcount=0;
double meancheyp=0.0;

// User define NUMBERS
double PI=3.14159265358979323846;
double TPI = 2.0*3.14159265358979323846;

//Outputs
FILE *out_fileTimesDist;
FILE *out_fileCheypBias;

// Others
char *car = "ok";

// Initialize all arrays
void initializearrays(void){

    for(int k=0;k < nbac;k++){
        globaldoingshift[k]=0;
        tumbletimes[k]=0.0;
        runtimes[k]=0.0;
        tmpruntimes[k]=0.0;
        tmptumbletimes[k]=0.0;
        biasr[k]=0.0;
        biast[k]=0.0;
        tmpbiast[k]=0.0;
        tmpbiasr[k]=0.0;
        datacounter[k]=0;
        for(int i=0;i < nfla;i++){
            if(bootcount==0){
                MU[k][i]=mu;
            };
            doingshift[k][i]=0;
            if(MU[k][i] > CRT){
                shift[k][i]=1;tmpcheyp[k][i]=CRT;RTstate[k]=1;
            }
            else if(MU[k][i] < CTR){
                shift[k][i]=0;tmpcheyp[k][i]=CTR;RTstate[k]=0;
            };
            cheyp[k][i]=0.0;
            tmpcheyp[k][i]=mu;
        };
    };
};
