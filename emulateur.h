/********************************************************
# Nom ......... : emulateur.h
# Rôle ........ : Fichier header de l'ordinateur en papier, contient les déclarations de fonctions.
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 10/08/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 10, L1 informatique
# (../..)
# Compilation : gcc -Wall *.c -o ordi_papier 
# Usage : Pour exécuter : ./ordi_papier
#********************************************************/


#ifndef ORDI_PAP
#define ORDI_PAP

#define hexa signed short int

// fonctions de main
void usage(char * message) ;

// fonctions de emulateur.c
// fonctions principales
// charge le fichier programme dans la mémoire de l'ordinateur en papier
int loader(char * nom_fichier, hexa première_inst) ; 
// contient la logique (switch) des instructions de l'ordinateur en papier
void emulateur(int start, int nbr_adr, hexa * trace, char * filename) ;
// fonctions microcodes
// microcode 1
void adressage_imediat(FILE *mct);
// microcodes 1 13 6 7
void adressage_absolu(FILE *ft, FILE *mct) ;
// microcodes 1 13 6 7 13 6 7
void adressage_indirect(FILE *ft, FILE *mct) ;
// microcodes 13 12 
void microcode_arithm_logic(FILE *mct) ;
// microcodes 4 14 
void microcode_STORE(FILE *mct) ;
// microcodes 13 3
void microcode_LOAD(FILE *mct) ;
// microcodes 16 8 14 
void microcode_IN(FILE *mct) ;
// microcodes 13 9
void microcode_OUT(FILE *ft, FILE *mct) ;
// microcodes 1 13 2 
void microcode_branchement(FILE *ft, FILE *mct) ;
// microcodes 1 13 5 15 
void microcode_phase_1(FILE *mct) ;
// microcode 15
void microcode_phase_3(FILE *mct) ;
// empêche l'accès à la mémoire morte de l'ordinateur en papier en dehors du bootstrap
void check_memoire_morte(hexa adr, FILE *ft, FILE *mct) ;
// empêche les sauts sur place
void no_jump(FILE *ft, FILE *mct) ;


// fonctions de interface.c
// demande le type de boot du programme à l'utilisateur (bootstrap ou fichier)
int demande_boot() ;
// demande le nom du fichier contenant le programme à exécuter
void demande_nom_fichier(char * filename) ;
// demande l'adresse de la première instruction du programme
hexa demande_debut_programme() ;
// vérifie que l'adresse de la première instruction n'est pas en mémoire morte
int check_adresse(hexa adresse) ;
// demande si l'utilisateur souhaite tracer des adresses mémoires 
int demande_trace() ;
// demande combien d'adresses mémoires l'utilisateur souhaite tracer
int combien_trace() ;
// sauvegarde les adresses mémoire à tracer
void memorise_trace(int nbr_trace, hexa * liste_traces) ;
// fonction activant/désactivant le stepper selon le choix de l'utilisateur
int stepper(FILE *ft, FILE *mct) ;
// sauvegarde et formate l'entrée utilisateur
int lire(char *chaine, int longueur) ;
// vide le buffer et empèche les fuites de mémoires
void vider_buffer() ;


// fonctions de trace.c
// imprime dans le fichier trace le contenu de la mémoire sous forme de matrice 16x16
void print_memoire(FILE *trace) ;
// imprime une trace de chaque instruction exécutée lors du programme dans un fichier
void imprime_trace(FILE *trace_file, int nbr_adr, hexa * trace, int avec_stepper) ;
// imprime une description de l'action réalisée dans le fichier microcodes
void imprime_description(FILE *mct) ;
// fait le lien entre un code OP et son mnémonique correspondant
char * cherche_mnemonique() ;
// fait le lien entre un code OP et son action correspondante
char * cherche_action() ;

#endif