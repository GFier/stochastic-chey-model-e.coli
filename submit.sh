#!/bin/bash

### Las líneas #SBATCH configuran los recursos de la tarea
### (aunque parezcan estar comentadas)

### Nombre de la tarea
#SBATCH --job-name=Skynet

### Cola de trabajos a usar
### Las particiones posibles son FISESTA,IFIMAR,CLUSTER
#SBATCH --partition=FLASH,IFIMAR

### Procesos a largar.
### Es OpenMP, o sea que un proceso en un nodo y muchos hilos.
#SBATCH --ntasks=1

### Hilos por proceso
### Poner el mismo valor acá que en OMP_NUM_THREADS/MKL_NUM_THREADS
#SBATCH --cpus-per-task=1

### Tiempo de ejecucion. Formato dias-horas:minutos. Maximo una semana.
### Traten de acotarlo.
#SBATCH --time 7-0:00

# SBATCH --exclude=flash-10-9

### Script que se ejecuta al arrancar el trabajo

### Cargar el entorno del usuario incluyendo la funcionalidad de modules
### No tocar
source /etc/profile

### Configurar OpenMP/MKL/etc con la cantidad de cores detectada.
#export OMP_NUM_THREADS=8

### Cargar los módulos para la tarea
# FALTA: Agregar los módulos necesarios
module load gnu

### Largar el programa
# FALTA: Poner el nombre del programa
srun ./Skynet
