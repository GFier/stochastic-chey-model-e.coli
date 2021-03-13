# C-Code developed for modeling stochastically the CheY-P molar-ity in the neighbourhood of flagella motors
Scientific background availabe in Preprint at bioRxiv [Stochastic model for the CheY-P molarity in the neighbourhood of E. coli flagella motors] (https://www.biorxiv.org/content/10.1101/831990v1.full).

## Code1 instructions

### Code files:

- definciones.c: File for initial setup of parameters for numerical simulations.
- definciones.h: File for setting number of bacteria (nbac) and number of flagella (nfla)
- main.c : File with code flow.
- export.c: File where .dat files are created for saving data.
- RATtransition: File where numerical simulations, flagella states and flagellar transitions are calculated.

### This branch can be used for two purposees:

- 	The code is set to obtain RTD and TTD for non unstimulated scenarios (Tumble bias=0.15). Data is saved in the savefilesTimesDist.dat file where the first column 
	saves the Runs time and the second column saves the Tumbles time.

-  Obtain steady state probability density function for molar Chey-P concentration, where the following changes must be done: \
	In definiciones.h change:  

		nfla=1; 
		nbac=1; 

	In deficiones.c change: 

		double dtickshut = 15000.0; 

	In main.c: 

		uncomment ->     if(tiempo > 100.0 && fmod(dticks,100.0)==0.0){ 
		      		  savefilesCheypDist(tmpcheyp[0][0],meancheyp/(nfla*nbac*(dticks))); 
		    		}; 

		File savefilesCheypDist.dat will have two columns separated by comma (CSV) where the first column is Chey-P values obtained from 
		numerical integration and the second one is the mean value obtained over time.
    

## For more information see Usage_notes.pdf 
