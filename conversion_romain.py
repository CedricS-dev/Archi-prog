# *******************************************************
# Nom ......... : conversion_romain
# Rôle ........ : Convertit un nombre décimal en nombre romain
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 10/06/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 2, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 conversion_romain.py 
#********************************************************/



def conversion_romain() -> str :
  """Demande à l'utilisateur d'entrer un nombre entre 1 et 3999 puis le convertit en nombres romains.

  Returns:
      str: Résultat sous forme de chaîne de caractères.
  """
  nombre_decimal = input("Entrez un nombre entre 1 et 3999 : ")
  
  # test sur l'entrée utilisateur
  # vérifie si la valeur entrée est bien un nombre
  try:
    nombre_decimal = int(nombre_decimal)
  except:
    print("Erreur : entrez un nombre.")
    return

  # tests sur les limites de la valeur entrée
  if nombre_decimal == 0:
    print("Impossible, le 0 n'existe pas en chiffres romains.")
    return 
  elif nombre_decimal < 0:
    print("Erreur : ce programme ne traite pas les nombres négatifs.")
    return 
  elif nombre_decimal >= 4000:
    print("Erreur : le nombre est trop grand.")
    return 
  
  # le traitement se fait sur une copie de la valeur entrée, pour la renvoyer dans un message final
  nombre = nombre_decimal
  # variable pour stocker le résultat de l'algorithme
  romain = []
  # tableau de tuples servant de table de conversion pour les nombres romains
  dico_romain = [
    (1000, "M"), (900, "CM"), (500, "D"), (400, "CD"), (100, "C"), (90, "XC"), (50, "L"), (40, "XL"), (10, "X"), (9, "IX"), (5, "V"), (4, "IV"), (1, "I")
  ]

  # boucle de traitement
  # vérifie si la valeur entrée est plus grande que la première valeur du tuple en cour dans le tableau de conversion
  # si non, passe au tuple suivant
  # si oui, ajoute le nombre romain associé dans la variable "romain" et soustrait la première valeur du tuple à la valeur entrée
  # quand la valeur entrée est égale à 0, la boucle s'arrête
  for num, rom_num in dico_romain:
    while nombre >= num:
      nombre -= num
      romain.append(rom_num)

  # le résultat est converti en chaîne de caractères et retourné à l'utilisateur  
  result = "".join(romain)
  print(f"Le nombre {nombre_decimal} équivaut à {result} en chiffres romains.")
  return(result)

# appel de la fonction
conversion_romain()
