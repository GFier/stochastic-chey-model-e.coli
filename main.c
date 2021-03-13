//Header:
//////////////////////////////////////////////////////////////////////////////////////////////////
// This code was written by Guido Fier and checked by Marcos Torres using open source Code Blocks.
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "definiciones.h"

//FUNCTIONS
extern void cheypsolver(double initcond,int idn,int idf);
extern void transicionRT(double cheypvalue,int idn,int idf);
extern void savefilesTimesDist(double graba1,double graba2);
extern void savefilesCheypBias(double graba1,double graba2,double graba3,double graba4,double graba5,double graba6);
extern void openfiles(void);
extern void statistical(double runtime,double tumbletime,int count);
extern void savefilesCheypDist(double graba1,double graba2);
extern void initializearrays(void);
extern void reboot(void);
extern void meanbias(void);
extern double crossfla(void);
extern void savefilesFlaState(int graba1,int graba2,int graba3,int graba4,double graba5);
//VARIABLES
extern double tmpcheyp[nbac][nfla];
extern double MU[nbac][nfla];
extern double tumbletimes[nbac];
extern double tmpruntimes[nbac];
extern double runtimes[nbac];
extern double tmptumbletimes[nbac];
extern int doingshift[nbac][nfla];
extern double tiempo;
extern double dticks;
extern double ddt;
extern double dtickshut;
extern char *car;
extern double meanrun;
extern double meantumble;
extern double varrun;
extern double vartumble;
extern double biast[nbac];
extern double biasr[nbac];
extern int shift[nbac][nfla];
extern int fladir[nbac][nfla];
extern double crosscor[nbac];
extern int globaldoingshift[nbac];
extern int datacounter[nbac];
extern int globaldatacounter;
extern int RTstate[nbac];
extern double deltaMU;
extern double mu;
extern double MUcut;
extern double meantENbias;
extern double meanrENbias;
extern double meanENCrossFla;
extern double tmpbiast[nbac];
extern double tmpbiasr[nbac];
extern int bootcount;
extern double savespace;
extern double meancheyp;
extern double CrossFlaAVT;

//MAIN

int main(void){

srand(time(NULL)); // Random seed for Generator
openfiles(); // Opens .dat output files
initializearrays(); // Initialize arrays

while(1){


   for(int k=0;k < nbac;k++){
        int sumshift=0;

        //Obtains the molar concentration of CheY-P for each flagella and the rotation direction at each time
        for(int j=0;j < nfla;j++){
            cheypsolver(tmpcheyp[k][j],k,j);
            transicionRT(tmpcheyp[k][j],k,j);
            sumshift= sumshift + shift[k][j];
            if(shift[k][j]==0){fladir[k][j]=1;}
            else if(shift[k][j]==1){fladir[k][j]=0;};
        };

    //Selects Run or Tumble Motion (or CCW oe CW for nfla=1) as a function of the rotation direction, transitions are controled by globaldoingshift[k]
    globaldoingshift[k]=0;
    int bloqueo=0;

        for(int j=0;j < nfla;j++){
            if(doingshift[k][j] == 2){ // At least one flagella went from CW to CCW
                doingshift[k][j]=0;
                if(sumshift == nfla){ // All flagella are in CCW mode -> transition to Run
                    globaldoingshift[k]=2;
                    //j=2*nfla;
                    bloqueo =1;
                }
                else{globaldoingshift[k]=0;}; // At least one flagella remains in CW mode and bacteria remains in Tumble mode
            }
            if(bloqueo==0){
                if(doingshift[k][j] == 1){ // At least one flagella went from CCW to CW, sufficient condition by veto rule to induce a Tumble
                    doingshift[k][j]=0;
                    if(RTstate[k]==0){ // Bacteria was in Run mode -> transition to Tumble
                        globaldoingshift[k]=1;
                        j=2*nfla;
                    };
                }
                else{globaldoingshift[k]=0;}; // No transition occurs
            };
        };

        if(globaldoingshift[k] ==1){ // RUN -> TUMBLE
            globaldoingshift[k]=0;
            //To obtain TTD y RTD
            tumbletimes[k]=tiempo;
            if(datacounter[k] > 2){
                tmpruntimes[k]=tiempo-runtimes[k];
                biasr[k]=biasr[k] +tmpruntimes[k];
            };
            RTstate[k]=1; // Tumble mode
        }
        else if(globaldoingshift[k] ==2){ // TUMBLE -> RUN
            globaldoingshift[k]=0;
            //To obtain TTD y RTD
            runtimes[k]=tiempo;
            if(datacounter[k] > 2){
                tmptumbletimes[k]=tiempo-tumbletimes[k];
                //savefilesTimesDist(tmpruntimes[k],tmptumbletimes[k]);
                biast[k]=biast[k]+tmptumbletimes[k];
                tmpbiast[k]=biast[k]/tiempo;
                tmpbiasr[k]=biasr[k]/tiempo;
            };
            RTstate[k]=0; // Run mode
            datacounter[k]++;
            if(datacounter[k] > 2){
                globaldatacounter++;
                statistical(tmpruntimes[k],tmptumbletimes[k],globaldatacounter);
            };
        };

       //if(RTstate[k]==1){
            //crosscor[k]=1.0/3.0*((double)fladir[k][0]*(double)fladir[k][1]+(double)fladir[k][0]*(double)fladir[k][2]+(double)fladir[k][1]*(double)fladir[k][2]);
            //crosscor[k]=((double)fladir[k][0]*(double)fladir[k][1]);
            //crosscor[k]=((double)fladir[k][0]*(double)fladir[k][0]);
        //printf("Cross Cor Fla ind %5.5f \n", crosscor[k]);
       // };

    };
    meanbias();// Function to obtain ensmable bias

    // Saves data from one flagella to obtain Steady state PDF
    if(tiempo > 10.0 && fmod(dticks,1000.0)==0.0){
        //savefilesCheypDist(tmpcheyp[0][0],meancheyp/(nfla*nbac*(dticks)));
        //savefilesCheypDist(tmpcheyp[0][0],tiempo);
        savefilesFlaState(fladir[0][0],fladir[0][1],fladir[0][2],RTstate[0],tiempo);
        //printf("Fladir %5i \n", fladir[0][0]);
    };


//Time Evolution:

    dticks = dticks +1.0;
    tiempo=dticks*ddt;
    CrossFlaAVT = CrossFlaAVT+ crossfla();

        if(fmod(dticks,1000000.0)==0.0){
//            printf("<CheyP> %5.5f \n",meancheyp/(nfla*nbac*(dticks))); // Gives mean value of chey-p, Steady mean value obtain analitically -> <chey-p>=1.888 for mu=2.1.
            printf("time %5.5f \n",tiempo);
            printf("Complete %: %5.5f \n",100.0*tiempo/(dtickshut));
//            printf("mean run time %5.5f \n",meanrun/(double)globaldatacounter);
//            printf("sigma run time %5.5f \n",sqrt(varrun/(double)globaldatacounter));
//            printf("mean tumble time %5.5f \n",meantumble/(double)globaldatacounter);
//            printf("sigma tumble time %5.5f \n",sqrt(vartumble/(double)globaldatacounter));
            printf("bias tumble %5.5f \n",meantENbias);
            printf("Cross Cor Fla %5.5f \n",CrossFlaAVT/(double)dticks);
//            printf("COUNTER %5if \n",globaldatacounter);
//            printf("Mu %5.5f \n",MU[0][0]);
//            printf("bias run %5.5f \n",meanrENbias);
//            printf("bias sum %5.5f \n",meanrENbias+meantENbias);
        };
        if(tiempo > dtickshut){
                exit(1234);
            };
};

return 0;
};
