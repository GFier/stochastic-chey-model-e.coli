#include "reboot.h"

extern void initializearrays(void);

extern double tiempo;
extern double dticks;
extern int globaldatacounter;
extern double meanrun;
extern double meantumble;
extern double varrun;
extern double vartumble;
extern double meanrENbias;
extern double meantENbias;
extern double meanrbias;
extern double meantbias;
extern double varrENbias;
extern double vartENbias;
extern double varrbias;
extern double vartbias;
extern double meanlig;
extern double meankin;
extern double meanmet;
extern double meanMU;
extern double meanCP;
extern double meanENCP;
extern double meanENMU;
extern double varENCP;
extern double varENMU;
extern double varlig;
extern double varkin;
extern double varmet;
extern double varMU;
extern double varCP;

void reboot(void){

dticks=0.0;
tiempo =0.0;
globaldatacounter=0;
meanrun=0.0;
meantumble=0.0;
varrun=0.0;
vartumble=0.0;
meanrENbias=0.0;
meantENbias=0.0;
meanrbias=0.0;
meantbias=0.0;
varrENbias=0.0;
vartENbias=0.0;
varrbias=0.0;
vartbias=0.0;

initializearrays();
};
