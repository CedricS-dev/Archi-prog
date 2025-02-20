# *******************************************************
# Nom ......... : taylor
# Rôle ........ : Calcul de la fonction exponentielle selon la formule de Taylor
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 24/06/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 4, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 taylor.py 
#********************************************************/


# import du module math de python pour le calcul de la factorielle
import math 

def Taylor_function() -> float | bool:
  """Calcule la formule de Taylor en demandant à l'utilisateur les nombres x (valeur de l'exponentielle) et n (nombre de termes)

  Returns:
      float | bool: résultat après le calcul sur n termes, ou False si l'utilisateur n'a pas entrer des nombres cohérents
  """

  print("Calcul de la fonction exponentielle selon la formule de Taylor")
  # demande à l'utilisateur d'entrer le nombre x
  x = input("Entrez le nombre x (supérieur ou égal à 0) : ")
  # test de conversion de x en integer, retourne un message d'erreur si échoue
  try:
    x = (int(x))
  except:
    print(f"Erreur : {x} n'est pas un nombre.")
    return False
  # x ne peut pas être un nombre négatif
  if x < 0 :
    print(f"Erreur : x doit être supérieur ou égal à 0.")

  # même chose pour n...
  n = input("Entrez le nombre n (supérieur ou égal à 0) : ")
  try:
    n = (int(n))
  except:
    print(f"Erreur : {n} n'est pas un nombre.")
    return False
  
  # ...avec un test suplémentaire pour vérifier si n est égal à 0
  # dans ce cas le résultat est égal à 1
  # cette étape est obligatoire, si n est égal à 0, la boucle suivante ne se lance pas et la fonction retourne 0
  if n == 0 :
    print("Résultat : 1")  
    return 1
  # n ne peut pas être un nombre négatif
  elif n < 0 :
    print("Erreur : le nombre n doit être supérieur ou égal à 0.")  
    return False
  
  # boucle pour le calcul de la formule
  # le premier tour avec i = 0 est égal à 1
  # le second avec i = 1 est égal à x, la formule est complète
  e = 0
  for i in range(n):
    e += x**i / math.factorial(i)
 
  # affichage et renvoie du résultat
  print(f"Résultat : {e}.")
  return e

# appel de la fonction
Taylor_function()

