/********************************************************
# Nom ......... : trace.c
# Rôle ........ : Contient les fonctions d'impression de traces de l'ordinateur en papier
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 10/08/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 10, L1 informatique
# (../..)
# Compilation : gcc -Wall *.c -o ordi_papier 
# Usage : Pour exécuter : ./ordi_papier
#********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "emulateur.h"


#define NBR_INST 21
#define SIZE_INST 10


// tableaux listant les codes héxadécimaux des instructions du progamme ...
hexa code_OP[NBR_INST] = {
  0X20, 0X60, 0XE0, 0X21,
  0X61, 0XE1, 0X22, 0X62,
  0XE2, 0X00, 0X40, 0XC0,
  0X48, 0XC8, 0X49, 0XC9,
  0X41, 0XC1, 0X10, 0X11,
  0X12} ;

// ... et les mnémoniques correspondants ...
char mnémoniques[NBR_INST][SIZE_INST] = {
  {"ADD #"},  {"ADD @"},   {"ADD *@"},{"SUB #"},
  {"SUB @"},  {"SUB *@"},  {"NAND #"},{"NAND @"},
  {"NAND *@"},{"LOAD #"},  {"LOAD @"},{"LOAD *@"},
  {"STORE @"},{"STORE *@"},{"IN @"},  {"IN *@"},
  {"OUT @"},  {"OUT *@"},  {"JUMP @"},{"BRN @"},
  {"BRZ @"} } ;

// .. ainsi que les actions correspondantes
char actions[NBR_INST][25] = {
  {"A <- A + V"},      {"A <- A + (@)"},  {"A <- A + *(@)"},  {"A <- A - V"},
  {"A <- A - (@)"},    {"A <- A - *(@)"}, {"A <- ~[A & V]"},  {"A <- ~[A & (@)]"}, 
  {"A <- ~[A & (@)]"}, {"A <- V"},        {"A <- (@)"},       {"A <- *(@)"},
  {"(@) <- A"},        {"*(@) <- A"},     {"(@) <- Entrée"},  {"*(@) <- Entrée"},
  {"Sortie <- (@)"},   {"Sortie <- *(@)"},{"PC <- @"},        {"si A < 0 alors PC <- @"},
  {"si A = 0 alors PC <- @"} } ; 

extern hexa MEMORY[], OP, A, AD ;
extern int  PC ;


void print_memoire(FILE * trace)
{
  // logique pour imprimer la mémoire sous forme de matrice de 16 x 16
  int j = 0;
  // en-tête de la matrice
  fprintf(trace,"   | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n") ;
  fprintf(trace,"---+------------------------------------------------\n") ;
  // pour chaque case mémoire
  while (j < 256)
  {
    // imprime en héxa la colonne de gauche
    fprintf(trace, "%02hhX | ",j/16) ;
    int i ;
    // pour chaque ligne de 16 cases
    for (i = 0; i < 16 ; i++)
    // imprime la case mémoire correspondant à la ligne(i) et à la colonne(j)
      fprintf(trace,"%02hhX ", MEMORY[i + j]) ;
    fprintf(trace,"\t") ;
    int k ;
    
    // à la fin de chaque lignes, imprime le caractère correspondant
    for (k = 0; k < 16 ; k++)
    {
      // si le caractère n'est pas imprimable, met un "."
      if (MEMORY[k + j] > 31 && MEMORY[k + j] < 127) 
      {
        fprintf(trace,"%c", MEMORY[k + j]) ;
      }
      else {fprintf(trace,".") ;}
    }
    fprintf(trace,"\n") ;
    // incrémente j de 16 (passe à la ligne)
    j = j + 16 ;
  }
  fprintf(trace,"\n") ;
  return ;
}


void imprime_trace(FILE *trace_file, int nbr_adr, hexa * trace, int avec_stepper)
{
  // imprime une trace de l'adresse de l'instruction, 
  // de A, du code opératoire, du mnémonique correspondant,
  // et de l'opérande
  fprintf(trace_file, "Instruction : %02hhX %-8s %02hhX %02hhX | PC : %02hhX | A : %02hhX", PC - 1, cherche_mnemonique(), OP, MEMORY[PC], PC, A) ;
  // si le programme est en mode stepper, imprime aussi la trace dans le terminal
  if (avec_stepper == 1) printf("Instruction : %02hhX %-8s %02hhX %02hhX | PC : %02hhX | A : %02hhX", PC - 1, cherche_mnemonique(), OP, MEMORY[PC], PC, A) ;
  
  // si l'utilisateur a choisi de tracer des adresses mémoires
  for (int i = 0 ; i < nbr_adr ; i++)
  {
    // ajoute ces adresses à la trace
    fprintf(trace_file," | ADR %02hhX : %02hhX", trace[i], MEMORY[trace[i]]) ;
    // si le programme est en mode stepper, imprime aussi la trace dans le terminal
    if (avec_stepper == 1) printf(" | ADM %02hhX : %02hhX", trace[i], MEMORY[trace[i]]) ;
  }
  fprintf(trace_file,"\n") ;
  if (avec_stepper == 1) printf("\n") ;
  return ;
}

void imprime_description(FILE *mct)
{
  // imprime une description de l'opération avant de lister les microcodes
  fprintf(mct ,"## %s %02hhX %02hhX | %s ##\n", cherche_mnemonique(), OP, MEMORY[PC], cherche_action()) ;
}

char * cherche_mnemonique()
{
  // cherche l'indice de l'instruction dans la table code_OP
  // et retourne le mnémonique correspondant au même indice
  for (int i = 0 ; i < NBR_INST ; i++)
    if (OP == code_OP[i]) return mnémoniques[i] ;
  // sinon, retourne une chaine vide
  return " ";
}

char * cherche_action()
{
  // cherche l'indice de l'instruction dans la table code_OP
  // et retourne l'action correspondant au même indice
  for (int i = 0 ; i < NBR_INST ; i++)
    if (OP == code_OP[i]) return actions[i] ;
  // sinon, retourne une chaine vide
  return " ";
}
