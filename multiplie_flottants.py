# *******************************************************
# Nom ......... : multiplie_flottants
# Rôle ........ : Multiplie deux nombres représentés en base 10 en virgule flottante
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 22/06/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 4, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 multiplie_flottants.py 
#********************************************************/


def multiplie_flottants() -> str | bool:
  """Demande à l'utilisateur d'entrer deux nombres et les multiplie

  Returns:
      str | bool: le résultat de la multplicaton en virgule flottante, False si erreur
  """

  # demande à l'utilisateur d'entrer un nombre
  # puis ce nombre est passé dans la fonction extrait_mantisse_exposant
  nombre1 = input("Entrer un premier nombre en base 10 (entier ou virgule flottante) :")
  nombre1 = extrait_mantisse_exposant(nombre1)
  # si la fonction a retourné False, alors l'entrée n'était pas un nombre ou était égale à 0
  # la fonction s'arrète et retourne False
  if nombre1 == False:
    return False
  # même chose pour la seconde entrée
  nombre2 = input("Entrer un second nombre en base 10 (entier ou virgule flottante) : ")
  nombre2 = extrait_mantisse_exposant(nombre2)
  if nombre2 == False:
    return False
  
  # le calcul est effectué quand les deux nombres ont passé les tests
  # les mantisses sont multipliées (avec un arrondi sur cinq chiffres)
  # les exposants sont additionnés
  result = (round(nombre1[0] * nombre2[0], 5), nombre1[1] + nombre2[1])
  # le tuple est alors passé à la fonction format_flottant()
  result = format_flottant(result)
  # le résultat obtenu est imprimé à l'écran et retourné
  print(f"Résultat de la multiplication : {result}")
  return result


def extrait_mantisse_exposant(flottant:str) -> tuple | bool: 
  """Reçoit un nombre sous forme de chaîne de caractères et le sépare en un tuple au format (mantisse, exposant)
  Retourne une erreur si la conversion échoue, ou un message si le nombre est égal à 0

  Args:
      flottant (str): nombre flottant sous forme de chaîne de caractères

  Returns:
      tuple | bool: tuple au format (mantisse, exposant), False si la conversion échoue ou si le nombre est égal à 0
  """

  # tentative de conversion de la valeur en float
  try:
    mantisse = float(flottant)
  except:
    # si ce n'est pas possible, la chaîne est formatée pour préparer le split
    # les espaces sont supprimés, les caractères en majuscule passent en minuscule, la virgule par un point et le "^" est remplacé par "e",
    flottant = flottant.replace(" ", "").replace(",", ".").replace("^", "e")
    flottant = flottant.lower()
  else:
    # si la conversion en float est passée, l'entrée est testée pour savoir si elle est égale à 0
    # si c'est le cas, pas besoin d'aller plus loin, le résultat sera toujours égal à 0
    if mantisse == 0:
      print("Toute multiplication par 0 a pour résultat 0.")
      return False
    # sinon, l'exposant est mis à 0 et les valeurs sont retournées sous forme de tuples
    exposant = 0
    return (mantisse, exposant)


  # le traitement continue si la conversion a raté
  # il faut maintenant savoir si la chaîne de caractères est au format (float)x10e(int)
  # en commencant par un split de la chaîne
  mantisse_exp = flottant.split("x10e")

  # tentative de conversion en float de la première donnée récupérée après le split
  # et en int de la seconde
  # si une erreur est levée, c'est que l'une des entrées n'est pas un nombre, une erreur est affichée, la fonction retourne False
  try:
    mantisse = float(mantisse_exp[0])
    exposant = int(mantisse_exp[1])
  except:
    print("Erreur : la valeur entrée n'est pas un nombre.")
    return False

  # sinon, un test est une nouvelle fois lancé sur la mantisse pour le 0
  if mantisse == 0:
    print("Toute multiplication par 0 a pour résultat 0.")
    return False
  
  # si la chaîne a passé tous les tests, le tuple est retourné
  return (mantisse, exposant)


def format_flottant(nombre_tuple:tuple) -> str:
  """Récupère un tuple au format (mantisse, exposant) et le transforme en notation scientifique

  Args:
      nombre_tuple (tuple): tuple au format (mantisse, exposant)

  Returns:
      str: nombre en notation scientifique
  """

  # le tuple est séparé en deux variables
  mantisse = nombre_tuple[0]
  exposant = nombre_tuple [1]
  
  # une mantisse ne peut avoir qu'un seul chiffre avant la virgule
  # si la mantisse est supérieure ou égale à 10 ou inférieure ou égale à -10
  # la mantisse est divisée par 10
  # et l'exposant incrémenté de 1
  while mantisse >= 10 or mantisse <= -10:
    mantisse /= 10
    exposant += 1

  # si la mantisse est entre 0 et 1, ou entre 0 et -1
  # la mantisse est multipliée par 10
  # et l'exposant décrémenté de 1
  while (mantisse > 0 and mantisse < 1) or (mantisse < 0 and mantisse > -1):
    mantisse *= 10
    exposant -= 1

  # si l'exposant est égal à 0, ce n'est pas nécessaire de le renvoyer
  if exposant == 0:
    return str(mantisse)
  # sinon, la chaîne est reconstruite et retournée
  else:
    return str(mantisse) + "x10e" + str(exposant)
  

# appel de la fonction
multiplie_flottants()