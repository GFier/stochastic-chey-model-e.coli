# C-Code developed for modeling stochastically the CheY-P molar-ity in the neighbourhood of flagella motors
Scientific background availabe in Preprint at bioRxiv [Stochastic model for the CheY-P molarity in the neighbourhood of E. coli flagella motors] (https://www.biorxiv.org/content/10.1101/831990v1.full).

## Code2 instructions

### Code files:

- `definciones.c`: File for initial setup of parameters for numerical simulations.
- `definciones.h`: File for setting number of bacteria (nbac) and number of flagella (nfla)
- `main.c` : File with code flow.
- `export.c`: File where .dat files are created for saving data.
- `RATtransition`: File where numerical simulations, flagella states and flagellar transitions are calculated.

### This branch has only one purpose:

This code is used to obtain Tumble or CW bias as a function of mu, the steady state molar concentration.

- For CW bias: \
In `definiciones.h` change:
			
			nfla=1;
			If you can run this code in differnt threads or in a cluster we recommend to use nbac=10 and perform several independent runs of the code.
			If not, we recommend using nbac=100; Although depends on your computer speed.


- For Tumble bias: 

		The  code is already set to obtain the Tumble bias for 3 flagella ---> nfla=3;
		If you  want to run the code to obtain the Tumble bias for other number of flagella just change nfla to the number you want in definiciones.h	


#### The data will be saved in `savefilesCheypBias.dat` where the columns are: 
	- First column: Mu of the first flagella of the first bacteria. 
	- Second column: bias averaged over the ensamble. 
	- Third column: mean Run time averaged over the ensamble. 
	- Fourth column: mean Tumble time averaged over the ensamble. 
	- Fifth column: Standard deviation of Run times averaged over the ensamble. 
	- Sixth column: Standard deviation of Tumble times averaged over the ensamble. 

When time reaches the value set in the variable `dtickshut`, before changing the steady state molar concentration (mu), the code saves the data and reboots changing mu with `deltaMU=0.1`. Both values can be modified to custom values in `definiciones.c` .
The code exits when mu reaches the value set in the variable `MUcut=4.0`. 
    

## For more information see `Usage_notes.pdf` 
