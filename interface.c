/********************************************************
# Nom ......... : interface.c
# Rôle ........ : Contient les fonctions d'interface utilisateur de l'ordinateur en papier
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


int demande_boot()
{
  int reponse ;
  // demande à l'utilisateur si il souhaite commencer le programme ou quitter
  printf("Lancer le programme par :\n - chargement de fichier(0)\n - bootstrap(1)\n - quitter(2)\n - : ") ;
  // mémorise sa réponse
  //lire(reponse, 2) ;
  scanf("%d", &reponse) ;
  // le buffer est nettoyé après chaque entrée
  vider_buffer();
  //selon la réponse :
  switch (reponse)
  {
    // si l'utilisateur choisi d'entrer un ficher
    case 0 :
      return 1 ; 
      break; 
    // si c'est le bootstrap 
    case 1 :
      return 0 ;
      break ;
    // sinon quitte le programme
    case 2 :
      printf("Fermeture du programme.\n") ;
      exit(-1) ;
  // si l'utilisateur entre une autre commande, stop tout
  default:
    usage("Commande inconnue") ;
  }
  return -1 ;
}


void demande_nom_fichier(char * filename)
{
  // demande le nom du fichier et mémorise le
  printf("Entrez le nom du fichier : ") ;
  lire(filename, 50) ;
  return ;
}


hexa demande_debut_programme()
{
  hexa start ;
  // demande à l'utilisateur où commence son programme
  printf("Entrez l'adresse de la première instruction du programme.\n") ;
  printf("Attention! Cette adresse doit être supérieure à 1F (héxadécimal) : ") ;
  // et mémorise la réponse
  scanf("%hX", &start) ;
  vider_buffer();
  // puis retourne la
  return start ;
}


int check_adresse(hexa adresse)
{ 
  // si l'addresse n'est pas un hexa entre 1F et FF
  if (adresse > 0X1F && adresse <= 0XFF) return  0 ;
  else 
  {
    // stop tout
    usage("Adresse invalide") ; 
    return 1 ;
  }
}


int demande_trace()
{
  int reponse_trace ;
  // demande à l'utilisateur si il souhaite tracer des adresses mémoires
  printf("Voulez-vous tracer une adresse mémoire ?\n - Oui(0)\n - Non(1)\n - Quitter(2)\n - : ") ;
  scanf("%d", &reponse_trace) ;
  vider_buffer();
  // selon la réponse :
  switch (reponse_trace)
  {
    // continue la demande d'adresses
    case 0 : return 0 ; break ; 
    // ne demande pas d'adresses
    case 1 : return 1 ; break ; 
    // quitte le programme
    case 2 : printf("Sortie forcée par l'utilisateur.\n") ; exit(-1) ; 
    // si l'utilisateur entre une mauvaise commande, stop tout
    default :usage("Commande inconnue") ;
  }
  return -1 ;
}


int combien_trace()
{
  int nbr_trace ;
  // demande combien d'adresses tracer
  printf("Combien d'adresses mémoires voulez vous tracer ? ") ;
  scanf("%d", &nbr_trace) ;
  vider_buffer();
  // et retourne cette valeur
  return nbr_trace ;
}

void memorise_trace(int nbr_trace, hexa * liste_traces)
{
  // créé un espace mémoire pour les mémoriser
  hexa adresse ;
  // si l'utilisateur souhaite tracer des adresses
  if (nbr_trace > 0)
  {
    // pour chaque adresse à tracer
    for(int i = 0 ; i < nbr_trace ; i++)
    {
      // demande la valeur de l'adresse à tracer
      printf("Entrez l'adresse à tracer n %d (héxadécimal) : ", i + 1) ;
      scanf("%hX", &adresse) ;
      // et mémorise cette adresse
      liste_traces[i] = adresse ;
    }
  }
  return ;
}


int stepper(FILE *ft, FILE *mct)
{
  int reponse ;
  // demande à l'utilisateur si il souhaite passer en mode stepper
  printf("Continuer en mode stepper ? - Oui(0) - Non(1) - Quitter(2) : ") ;
  scanf("%d", &reponse) ;
  vider_buffer();
  // selon la réponse de l'utilisateur
  switch (reponse)
  {
    // continue en mode stepper
    case 0 : return 1 ;
    // arrête le mode stepper et va au bout de l'exécution du programme
    case 1 :  ; return 0 ;
    // arrête le programme 
    case 2 : 
    print_memoire(ft);
    // ferme les fichiers traces et microcodes
    fclose(ft) ;
    fclose(mct) ;
    printf("Sortie forcée par l'utilisateur.\n") ; exit(-1) ; break ;
    // si l'utilisateur entre une mauvaise commande
    default :
     // ferme les fichiers trace et microcode
     fclose(ft) ;
     fclose(mct) ;
     //  stop tout
     usage("Commande inconnue") ;
  }
  return 1;
}


int lire(char *chaine, int longueur)
{
  // code pour retirer les retours à la lignes des entrées utilisateur
  char *positionEntree = NULL;
  if (fgets(chaine, longueur, stdin) != NULL)
  {
    positionEntree = strchr(chaine, '\n');
    if (positionEntree != NULL) *positionEntree = '\0';
    // vide le buffer
    else vider_buffer();
    return 1;
  } else {
    vider_buffer();
    return 0;
  }
}


void vider_buffer()
{
  // code pour vider le buffer
  int c = 0;
  while (c != '\n' && c != EOF)
    c = getchar();
}