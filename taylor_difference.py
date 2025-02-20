# *******************************************************
# Nom ......... : taylor_difference
# Rôle ........ : Calcul de l'erreur d'approximantion de la fonction exponentielle selon la formule de Taylor
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 24/06/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 4, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 taylor_difference.py 
#********************************************************/


# import du module math de python pour le calcul de la factorielle et de l'exponentielle
import math 

def Taylor_function_difference() -> float | bool:
  """ Calcule la formule de Taylor en demandant à l'utilisateur les nombres x (valeur de l'exponentielle) et n (nombre de termes) et affiche l'écart d'approximantion, imprime l'évolution du résultat dans un fichier
 

  Returns:
      float | bool: approximation après le calcul sur n termes, ou False si l'utilisateur n'a pas entrer des nombres cohérents
  """

  print("Calcul de l'erreur d'approximantion de la fonction exponentielle selon la formule de Taylor")
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
  
  e = 0
  exponentielle = math.exp(x)

  # boucle le calcul de la formule
  # le premier tour avec i = 0 est égal à 1
  # le second avec i = 1 est égal à x, la formule est complète
  # le résultat peut être sur un grand nombres de lignes, il est donc sauvegardé dans un fichier
  with open (f"resultat_exp_{x}.txt", "w") as f:
    # la première ligne du fichier présente le résultat de la fonciton exponentielle  
    print(f"Calcul de e exp{x} : {exponentielle}", file=f)
    for i in range(n):
      e += x**i / math.factorial(i)
      # le résultat de la soustraction de l'exponentielle par la formule de Taylor nous donne la marge d'erreur
      approx = exponentielle  - e
      # affiche l'évolution du calcul à chaque tour
      # le numéro du tour est sur la première ligne
      # le résultat sur la deuxième
      # l'ecart est affiché sur la troisième 
      print(f"Tour {i + 1} \nRésultat\t\t\t: {e} \nApproximation\t: {approx}", file=f)

    # un message est affiché dans la console à la fin du traitement
    print(f"Le fichier resultat_exp_{x}.txt a été créé." )

  # l'approximation est retournée
  return approx

# appel de la fonction
Taylor_function_difference()
