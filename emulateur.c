/********************************************************
# Nom ......... : emulateur.c
# Rôle ........ : Contient les fonctions d'émulation de l'ordinateur en papier
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


#define hexa signed short int


// variables globales
// accumulateur A et les registres RM, AD, OP et RS
hexa A, RM, AD, OP, RS ; 
// mémoire de 256 cases/octets (255 + 1 pour l'indice 0)
hexa MEMORY[255] ;
// registre Program Counter
int PC ;
// Unité  Arithmétique et Logique
char UAL[5];



int loader(char * nom_fichier, hexa première_inst)
{
  hexa code ;
  FILE * fprog ;
  // lecture du fichier programme
  fprog = fopen(nom_fichier, "rb") ;
  // si le nom du fichier ne va pas, stop tout
  if (!fprog)
  {
    fprintf(stderr, "Erreur : Le fichier %s n'est pas lisible.\n", nom_fichier) ;
    exit(-1) ;
  } 
  
  // parcours chaque code du fichier
  // en commançant à l'instruction donnée
  int lecture = 0, inst ;
  for (inst = première_inst ; inst < 256 && lecture != EOF ; inst++)
  {
    int lecture = fscanf(fprog, "%02hX", &code) ; 
    // si le fichier s'arrête avant la fin de la mémoire
    // arrête toi
    if (lecture == EOF) break ;
    // sinon mémorise ce mot dans la mémoire
    MEMORY[inst] = code ;
  }
  // ferme le fichier une fois la mise en mémoire terminée
  // si la fermeture échoue, stop tout
  if (fclose(fprog) == EOF) 
  {
    usage("Un problème est survenu lors de la mise en mémoire") ;
    return -1 ;
  }
  else return 0 ;
  
}


void emulateur(int start, int nbr_adr, hexa * trace, char * filename)
{
  int avec_stepper = 1 ;
  
  char filename_trace[128], filename_microcode[128] ;
  sprintf(filename_trace, "trace_%s", filename) ;
  sprintf(filename_microcode, "trace_microcode_%s", filename) ;
  FILE *ft, *mct ;
  // ouvre un fichier trace en mode écriture
  ft = fopen(filename_trace, "w") ;
  // ouvre un fichier trace pour les microcodes en mode écriture
  mct = fopen(filename_microcode, "w") ;
  // imprime l'état de la mémoire avant le lancement du programme dans le fichier trace
  fprintf(ft, "Mémoire de l'émulateur avant exécution du programme\n\n") ;
  print_memoire(ft) ;
  // indique à l'utilisateur le nom du fichier qui est traité sur le terminal
  printf("Lancement de l'émulateur sur le fichier %s\n", filename) ;
  // et dans le fichier trace
  fprintf(ft,"Lancement de l'émulateur sur le fichier %s\n\n", filename) ;
  
  // commence le programme à l'adresse donnée
  PC = start;
  // lance les instructions une à une
  while (PC <= 256)
  { 
    // DÉBUT PHASE 1
    microcode_phase_1(mct) ;
    // tant que le stepper est activé, relance le
    if (avec_stepper == 1)  avec_stepper = stepper(ft, mct) ;
    // imprime les traces
    imprime_trace(ft, nbr_adr, trace, avec_stepper) ;

    // DÉBUT PHASE 2
    // pour chaque code OP
    // si le code OP correspond à l'un de ces cas
    // alors exécute les actions correspondantes
    switch (OP) 
    { 
      //######## ARITHMÉTIQUE ########
      // instruction ADD # : A <- A + V
      case 0X20 :
        imprime_description(mct) ;
        // microcode 10
        strcpy(UAL, "+") ;
        fprintf(mct, "MC 10 : \nÉcrire + dans UAL | UAL : %s\n", UAL) ;
        adressage_imediat(mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction ADD @ : A <- A + (@)
      case 0X60 :
        imprime_description(mct) ;
        // microcode 10
        strcpy(UAL, "+") ;
        fprintf(mct, "MC 10 : \nÉcrire + dans UAL | UAL : %s\n", UAL) ;
        adressage_absolu(ft, mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction ADD *@ : A <- A + (@)
      case 0XE0 :
        imprime_description(mct) ;
        // microcode 10
        strcpy(UAL, "+") ;
        fprintf(mct, "MC 10 : \nÉcrire + dans UAL | UAL : %s\n", UAL) ;
         adressage_indirect(ft, mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction SUB # : A <- A - V
      case 0X21 : 
        imprime_description(mct) ;
        // microcode 11
        strcpy(UAL, "-") ;
        fprintf(mct, "intstruction 21\n") ;
        fprintf(mct, "MC 11 : \nÉcrire - dans UAL | UAL : %s\n", UAL) ;
        adressage_imediat(mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction SUB @ : A <- A - (@)
      case 0X61 : 
        imprime_description(mct) ;
        // microcode 11
        strcpy(UAL, "-") ;
        fprintf(mct, "MC 11 : \nÉcrire - dans UAL | UAL : %s\n", UAL) ;
        adressage_absolu(ft, mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction SUB *@ : A <- A - *(@)
      case 0XE1 :
        imprime_description(mct) ;
        // microcode 11
        strcpy(UAL, "-") ;
        fprintf(mct, "MC 11 : \nÉcrire - dans UAL | UAL : %s\n", UAL) ;
         adressage_indirect(ft, mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      //######## LOGIQUE ########
      // instruction NAND # : A <- ![A & V]
      case 0X22 :
        imprime_description(mct) ;
        // microcode 17
        strcpy(UAL, "NAND") ;
        printf("MC 11 : \nÉcrire NAND dans UAL | UAL : %s\n", UAL) ;
        adressage_imediat(mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction NAND @ : A <- ![A & (@)]
      case 0X62 : 
        imprime_description(mct) ;
        // microcode 17
        strcpy(UAL, "NAND") ;
        fprintf(mct, "MC 11 : \nÉcrire NAND dans UAL | UAL : %s\n", UAL) ;
        adressage_absolu(ft, mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      // instruction NAND *@ : A <- ![A & *(@)]
      case 0XE2 : 
        imprime_description(mct) ;
        // microcode 17
        strcpy(UAL, "NAND") ;
        fprintf(mct, "MC 11 : \nÉcrire NAND dans UAL | UAL : %s\n", UAL) ;
         adressage_indirect(ft, mct) ;
        microcode_arithm_logic(mct) ;
        break ;
      //######## TRANSFERTS ########
      // instruction LOAD # : A <- V
      case 0X00 : 
        imprime_description(mct) ; 
        adressage_imediat(mct) ;
        microcode_LOAD(mct) ;
        break ;
      // instruction LOAD @ : A <- (@) 
      case 0X40 : 
        imprime_description(mct) ;
        adressage_absolu(ft, mct) ;
        microcode_LOAD(mct) ;
        break ;
      // instruction LOAD *@ : A <- *(@)
      case 0XC0 : 
        imprime_description(mct) ;
         adressage_indirect(ft, mct) ;
        microcode_LOAD(mct) ;
        break ;
      // instruction STORE  : (@) <- A   
      case 0X48 :
        imprime_description(mct) ;
        adressage_absolu(ft, mct) ;
        microcode_STORE(mct) ;
        //check_memoire_morte(RS) ;
        break ;
      // instruction STORE  : *(@) <- A   
      case 0XC8 :
        imprime_description(mct) ;
         adressage_indirect(ft, mct) ;
        microcode_STORE(mct) ;
        //check_memoire_morte(RS) ;
        break ;
      //######## ENTRÉE / SORTIE ########  
      // instruction IN @ : @ <- Entrée
      case 0X49 : 
        imprime_description(mct) ;
        adressage_absolu(ft, mct) ;
        microcode_IN(mct) ;
        break ;
      // instruction IN *@ : *(@) <- Entrée
      case 0XC9 : 
        imprime_description(mct) ;
         adressage_indirect(ft, mct) ;
        microcode_IN(mct) ;
        break ;     
    // instruction OUT @ : Entrée <- @
      case 0X41 : 
        imprime_description(mct) ;
        adressage_absolu(ft, mct) ;
        microcode_OUT(ft, mct) ;
        break ;
      // instruction OUT *@ : Entrée <- *(@)
      case 0XC1 : 
        imprime_description(mct) ;
         adressage_indirect(ft, mct) ;
        microcode_OUT(ft, mct) ;
        break ;
      //######## BRANCHEMENTS ########
      // instruction JUMP @ : PC <- @
      case 0X10 :
        imprime_description(mct) ;
        microcode_branchement(ft, mct) ;
        break ;
      // instruction BRN @ : si A = 0 alors PC <- @
      case 0X11 :
      if (A < 0) 
      {
        imprime_description(mct) ;
        microcode_branchement(ft, mct) ;
        break ;
      } else  microcode_phase_3(mct) ; break  ;
      // instruction BRZ @ : si A = 0 alors PC <- @
      case 0X12 :
      if (A == 0) 
      {
        imprime_description(mct) ;
        microcode_branchement(ft, mct) ;
        break ;
      } else  microcode_phase_3(mct) ; break ;
      default : break ;
    }    
    
    // si le code OP est un des branchements, ne lance pas la phase 3
    if (OP != 0X10 && OP != 0X11 && OP != 0X12)
      // DÉBUT PHASE 3
      microcode_phase_3(mct) ;
    
  } // FIN DE LA BOUCLE
  

  fprintf(ft,"\n") ;
  // imprime dans la trace la mémoire après l'exécution
  fprintf(ft, "Mémoire de l'émulateur après exécution du programme\n\n") ;
  print_memoire(ft) ;
  // ferme le fichier trace
  fclose(ft) ;
  // ferme le fichier microcodes
  fclose(mct) ;
  return ;
}


void adressage_imediat(FILE *mct)
{
  // microcode 1
  RS = PC ;
  fprintf(mct ,"MC  1 : \nRS <- PC | RS : %02hhX | PC : %02hhX\n", RS, PC) ;
  return ;
}

void adressage_absolu(FILE *ft, FILE *mct)
{
  // microcode 1
  RS = PC ;
  fprintf(mct ,"MC  1 : \nRS <- PC | RS : %02hhX | PC : %02hhX\n", RS, PC) ;
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct ,"MC 13 : \nLecture mémoire : RM <- RS | RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 6
  AD = RM ;
   check_memoire_morte(AD, ft, mct) ;
  fprintf(mct ,"MC  6 : \nAD <- RM | AD : %02hhX | RM : %02hhX\n", AD, RM) ;
  // microcode 7
  RS = AD ;
  fprintf(mct ,"MC  7 : \nRS <- AD | RS : %02hhX | AD : %02hhX\n", RS, AD) ;
  return ;
}

void adressage_indirect(FILE *ft, FILE *mct)
{
  // microcode 1
  RS = PC ;
  fprintf(mct ,"MC  1 : \nRS <- PC | RS : %02hhX | PC : %02hhX\n", RS, PC) ;
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct ,"MC 13 : \nLecture mémoire : RM <- RS | RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 6
  AD = RM ;
  fprintf(mct ,"MC  6 : \nAD <- RM | AD : %02hhX | RM : %02hhX\n", AD, RM) ;
  // microcode 7
  RS = AD ;
  fprintf(mct ,"MC  7 : \nRS <- AD | RS : %02hhX | AD : %02hhX\n", RS, AD) ;
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct ,"MC 13 : \nLecture mémoire : RM <- RS | RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 6
  AD = RM ;
  check_memoire_morte(AD, ft, mct) ;
  fprintf(mct ,"MC  6 : \nAD <- RM | AD : %02hhX | RM : %02hhX\n", AD, RM) ;
  // microcode 7
  RS = AD ;
  fprintf(mct ,"MC  7 : \nRS <- AD | RS : %02hhX | AD : %02hhX\n", RS, AD) ;
  return ;
}

void microcode_arithm_logic(FILE *mct)
{
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct, "MC 13 : \nRM <- RS | RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 12
  switch (UAL[0])
  {
    case '+' :
      A = A + RM ;
      break ;
    case '-' :
      A = A - RM ;
      break ;
    case 'N' :
       A = ~(A & RM);
       break ;
    default :
      usage("Un erreur est survenue") ;
  }
  fprintf(mct, "MC 12 : \nA <- A %s RM | A : %02hhX | RM : %02hhX\n", UAL, A, RM) ;
  return ;
}

void microcode_STORE(FILE *mct)
{
  // microcode 4
  RM = A ;
  fprintf(mct, "MC  4 : \nRM <- A  | RM : %02hhX| A : %02hhX\n", RM, A) ;
  // microcode 14
  MEMORY[RS] = RM ;
  fprintf(mct, "MC 14 : \nÉcriture mémoire : RS <- RM | RS : %02hhX | RM : %02hhX\n", RS, RM) ;
  return ;
}

void microcode_LOAD(FILE *mct)
{
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct, "MC 13 : \nRM <- RS - RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 3
  A = RM ;
  fprintf(mct, "MC  3 : \nA <- RM | A : %02hhX| RM : %02hhX\n",A, RM) ; 
  return ;
}

void microcode_IN(FILE *mct)
{
  // microcode 16
  printf("Entrez une valeur : ") ;
  fprintf(mct, "MC 16 : \nAttendre qu'une valeur soit écrite dans l'Entrée \n") ;
  // microcode 8
  scanf("%02hX", &RM) ;
  fprintf(mct, "MC  8 : \nRM <- Entrée | RM : %02hhX\n", RM) ;
  // microcode 14
  MEMORY[RS] = RM ;
  fprintf(mct, "MC 14 : \nÉcriture mémoire : RS <- RM | RS : %02hhX | RM : %02hhX\n", RS, RM) ;
  return ;
}

void microcode_OUT(FILE *ft, FILE *mct)
{
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct, "MC 13 : \nRM <- RS - RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 9
  printf("%02hhX\n", RM) ;
  fprintf(mct, "MC  8 : \nSortie <- RM | RM : %02hhX\n", RM) ; 
  // imprime aussi dans le fichier trace
  fprintf(ft,"%02hhX\n", RM) ;
  return ;
}

void microcode_branchement(FILE *ft, FILE *mct)
{
  // microcode 1
  RS = PC ;
  fprintf(mct ,"MC  1 : \nRS <- PC | RS : %02hhX | PC : %02hhX\n", RS, PC) ;
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct ,"MC 13 : \nLecture mémoire : RM <- RS | RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 2
  no_jump(ft, mct) ;
  check_memoire_morte(RM, ft, mct) ;
  PC = RM ;
  fprintf(mct, "MC  2 : \nPC <- RM | PC : %02hhX | RM : %02hhX\n", PC, RM) ;
  return ;
}

void microcode_phase_1(FILE *mct)
{
  fprintf(mct, "DÉBUT PHASE 1\n") ;
  // microcode 1
  RS = PC ;
  fprintf(mct,"MC  1 : \nRS <- PC | RS : %02hhX | PC : %02hhX\n", RS, PC) ;
  // microcode 13
  RM = MEMORY[RS] ;
  fprintf(mct,"MC 13 : \nRM <- RS | RM : %02hhX | RS : %02hhX\n", RM, RS) ;
  // microcode 5
  OP = RM ;
  fprintf(mct,"MC  5 : \nOP <- RM | OP : %02hhX | RM : %02hhX\n", RM, OP) ;
  // microcode 15
  ++PC ;
  fprintf(mct,"MC 15 : \nIncrémenter le contenu de PC | PC : %02hhX\n", PC) ;
  fprintf(mct,"DÉBUT PHASE 2\n") ;
  return ;
}

void microcode_phase_3(FILE *mct)
{
  fprintf(mct, "DÉBUT PHASE 3\n") ;
  // microcode 15
  ++PC ;
  fprintf(mct, "MC 15 : \nIncrémenter le contenu de PC\n") ;
}

void check_memoire_morte(hexa adr, FILE *ft, FILE *mct)
{
  // si tu essaies d'accéder à une adresse <= 1F en dehors du bootstrap
  if (adr <= 0X1F && PC > 0X1F)
  {
     // ferme les fichiers traces et microcodes
    fclose(ft) ;
    fclose(mct) ;
    // et stop tout
    usage("Le programme essaie d'accéder à une adresse mémoire interdite") ;
  }  
  // sinon, retourne la valeur
  return ;
}

void no_jump(FILE *ft, FILE *mct)
{
  // si l'opérande du saut a la même valeur que l'adresse de l'instruction du saut 
  if (RM == PC - 1)
  {
     // ferme les fichiers traces et microcodes
    fclose(ft) ;
    fclose(mct) ;
    //  et stop tout
    usage("Le programme réalise des sauts sur place") ;
  }
  return ;
}