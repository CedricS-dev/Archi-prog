/********************************************************
# Nom ......... : main.c
# Rôle ........ : Contient les fonctions main et usage de l'ordinateur en papier
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 10/08/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 10, L1 informatique
# (../..)
# Compilation : gcc -Wall *.c -o ordi_papier 
# Usage : Pour exécuter : ./ordi_papier
#********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulateur.h"

// le type signed short int est redéfini en hexa
#define hexa signed short int


int main ()
{ 
  // pour mémoriser le nom du fichier donné par l'utilisateur (bootstrap.txt par défaut)
  char filename_prog[50] = "bootstrap.txt" ; 
  hexa debut_prog = 0X00 ; // adresse de début du progamme (par défaut à 0)
  // pour mémoriser la réponse de l'utilisateur sur le boot
  // si le loader s'est correctement executé 
  // si l'utilisateur veut tracer des zones mémoires
  // le nombre d'adresses à tracer (par défaut à 0)
  int réponse_boot, load, trace, nbr_trace = 0 ; 
  hexa liste_traces[nbr_trace] ;

  // charge le bootstrap dans la mémoire
  load = loader(filename_prog, debut_prog) ;

  // demande à l'utilisateur quel type de boot il souhaite exécuter
  réponse_boot = demande_boot() ;
  // si la réponse est par fichier
  if (réponse_boot == 1) 
  {
    // recupère le nom du fichier
    demande_nom_fichier(filename_prog) ;
    // recupère l'adresse de la première instruction
    debut_prog = demande_debut_programme() ;
    // et vérifie si elle est valide
    if(check_adresse(debut_prog) == 0)  ;
    load = loader(filename_prog, debut_prog) ;
  }

  // si le loader s'est bien exécuté
  if (load == 0)
  {
    // demande à l'utilisateur si il souhaite tracer des variables
    trace = demande_trace() ;
    // si oui, combien ?
    if (trace == 0) nbr_trace = combien_trace() ;
    // puis demande lui quelles adresses tracer
    memorise_trace(nbr_trace, liste_traces) ;
  } else {
    usage("Une erreur est survenue lors du chargement du fichier") ;
  }
  
  // lance l'émulateur à partir de la première instruction donnée
  // mémorise combien d'adresses tu dois tracer et leurs valeurs
  // et prend le nom du fichier
  emulateur(debut_prog, nbr_trace, liste_traces, filename_prog) ;
  return 0 ;
}


void usage(char * message)
{ 
  // si une erreur à eu lieu
  // le message doit être retourné sur la sortie d'erreur, stderr
  fprintf(stderr, "Erreur : %s, fermeture du programme.\n", message) ;                    
  exit(-1) ;
}
