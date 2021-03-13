#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include "definiciones.h"

//Funciones
//Variables Globales
extern double cheyp[nbac][nfla];
extern double ddt;
extern double MU[nbac][nfla];
extern double THETA;
extern double QCH;
extern double tmpcheyp[nbac][nfla];
extern double CRT;
extern double CTR;
extern int shift[nbac][nfla];
extern int ticks;
extern int doingshift[nbac][nfla];
extern double PI;
extern double TPI;
extern double etta;
extern double meanrun;
extern double meantumble;
extern double varrun;
extern double vartumble;
extern double tiempo;
extern double lmax;
extern double LigInit;
extern double lcero;
extern double amp;
extern double frec;
extern double frecVA;
extern double meanrENbias;
extern double meantENbias;
extern double meanrbias;
extern double meantbias;
extern double varrENbias;
extern double vartENbias;
extern double varrbias;
extern double vartbias;
extern double tmpbiast[nbac];
extern double tmpbiasr[nbac];
extern double meancheyp;

//Calcula el <V.A.> sin dividir por el total
double medio(double tmpmedio,double var){

    tmpmedio = tmpmedio + var;
    return  tmpmedio;
};

//Random Variate with Normal Distribution (0,1)
double generateGaussianNoise(double mu, double sigma){ //Box MIller Method
	static const double epsilon = DBL_MIN;//std::numeric_limits<double>::min();
	double z1=0.0;

	bool generate;
	generate = !generate;

	if (!generate)
	   return z1 * sigma + mu;

	double u1, u2;
	do
	 {
	   u1 = rand() * (1.0 / RAND_MAX);
	   u2 = rand() * (1.0 / RAND_MAX);
	 }
	while ( u1 <= epsilon );

	double z0;
	z0 = sqrt(-2.0 * log(u1)) * cos(TPI * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(TPI * u2);
	//printf("gass: %3.3f \n",z0 * sigma + mu);

	etta=z0 * sigma + mu;
	return etta;
};

//Langevin Equation for each flagella , numerical integration following Risken.
void cheypsolver(double initcond,int idn,int idf){
double temcheyp=0.0;

    temcheyp=initcond;

    // Equation 1 in the paper:
    cheyp[idn][idf]=temcheyp + ddt*THETA*(MU[idn][idf]-temcheyp)*temcheyp+ sqrt(2.0f*QCH*ddt)*generateGaussianNoise(0.0, 1.0);

    tmpcheyp[idn][idf] = cheyp[idn][idf];

    if(tmpcheyp[idn][idf] < 0.0){cheyp[idn][idf]=-cheyp[idn][idf];tmpcheyp[idn][idf] = -tmpcheyp[idn][idf];};
    if(cheyp[idn][idf] < 0.0){printf("cheyp error: %3.3f \n",cheyp[idn][idf]);exit(5);};

    meancheyp=medio(meancheyp,tmpcheyp[idn][idf]);
};

void transicionRT(double cheypvalue,int idn,int idf){

    if(shift[idn][idf]==1 && cheypvalue < CRT){ //Run Motion
        shift[idn][idf]=1;
    }
    else if(shift[idn][idf]==1 && cheypvalue >= CRT){ // Transition from Run to Tumble
        doingshift[idn][idf]=1;
        shift[idn][idf]=0;
    }
    else if(shift[idn][idf]==0 && cheypvalue > CTR){ // Tumble Motion
        shift[idn][idf]=0;
    }
    else if(shift[idn][idf]==0 && cheypvalue <= CTR){ // Transition from Tumble to Run
        doingshift[idn][idf]=2;
        shift[idn][idf]=1;
    };
};

void statistical(double runtime,double tumbletime,int count){
double tmpmeanrun=0.0;
double tmpmeantumble=0.0;

        meanrun = meanrun + runtime;
        meantumble = meantumble + tumbletime;

        tmpmeanrun=meanrun/(double)count;
        tmpmeantumble=meantumble/(double)count;

        varrun =varrun + (tmpmeanrun - runtime)*(tmpmeanrun - runtime);
        vartumble =vartumble + (tmpmeantumble - tumbletime)*(tmpmeantumble - tumbletime);
};

//Mean ensamble with time dependence
void meanbias(void){
double tmpmeanbiasR=0.0;double tmpmeanbiasT=0.0;double tmpvarbiasR=0.0;double tmpvarbiasT=0.0;

    for(int k=0;k < nbac;k++){
        tmpmeanbiasR=tmpmeanbiasR+tmpbiasr[k];
        tmpmeanbiasT=tmpmeanbiasT+tmpbiast[k];

    };
    meanrENbias=tmpmeanbiasR/(double)nbac;
    meantENbias=tmpmeanbiasT/(double)nbac;

    for(int k=0;k < nbac;k++){
        tmpvarbiasR=tmpvarbiasR+(tmpbiasr[k]-meanrENbias)*(tmpbiasr[k]-meanrENbias);
        tmpvarbiasT=tmpvarbiasT+(tmpbiast[k]-meantENbias)*(tmpbiast[k]-meantENbias);
    };
    varrENbias=tmpmeanbiasR/(double)nbac;
    vartENbias=tmpmeanbiasT/(double)nbac;
};
