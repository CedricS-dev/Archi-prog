# *******************************************************
# Nom ......... : compare_produit_a_deux
# Rôle ........ : Compare deux nombres binaires sous forme de chaîne de caractères et renvoie le plus grand
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 15/06/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 3, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 compare_produit_a_deux.py 
#********************************************************/


# variable globale représentant le nombre de bits, à modifier pour passer à 8, 16, 32 bits...
NBR_BITS = 8



def renvoi_binaire_sup() -> str | bool:
  """Demande à l'utilisateur d'entrer deux nombres binaires et retourne le plus grand

  Returns:
      str | bool: le binaire entré le plus grand, False si les entrées sont incorrectes
  """
  # on demande à l'utilisateur d'entrer un premier nombre
  nombre1 = input(f"Enter un premier nombre binaire sur {NBR_BITS} bits :")
  # puis on le passe dans la fonction de vérification
  nombre1 = check_binaire(nombre1)
  # si le nombre n'a pas passé les tests, on arrête le traitment
  if nombre1 == False:
    return False
  # même chose pour la seconde entrée
  nombre2 = input(f"Entrer un second nombre binaire sur {NBR_BITS} bits :")
  nombre2 = check_binaire(nombre2)
  if nombre2 == False:
    return False
  # une fois les deux nombres validés, on les compare
  result = compare_binaire(nombre1, nombre2)
  # si la fonction de comparaison a retourné False, les deux nombres sont égaux
  # je suis parti du principe que n'importe quel nombre pouvait être retourné dans ce cas comme ils sont égaux, mais un code erreur serait une option valide
  if result == False:
    print("Les deux nombres sont égaux.")
    return nombre1
  # sinon, on affiche un message et on retourne le plus grand
  else:
    print(f"Entre les nombres {nombre1} et {nombre2}, le plus grand est {result}.")
    return result
 

def check_binaire(binaire:str) -> str | bool:
  """Vérifie si une chaîne de caractères correspond bien à un nombre binaire et la renvoie formatée.

  Args:
      binaire (str): le binaire à tester

  Returns:
      str | bool: résultat après test et formatage, False si la chaîne ne correspond pas
  """

  # on commence par retirer les espaces dans la chaîne
  # cela permet de rentrer les binaires par groupe de 4 -> 0000 0001
  binaire = binaire.replace(" ", "")
  # puis on vérifie si la longueur correspond au nombre de bits attendus
  if len(binaire) != NBR_BITS :
    print(f"Erreur : le nombre {binaire} n'est pas sur {NBR_BITS} bits.")
    return False
  # enfin, on vérifie si la chaîne n'est composé que de 0 et de 1
  else :
    for i in binaire :
      if i not in ('0', '1'):
        print(f"Erreur : '{binaire}' n'est pas un nombre binaire.")
        return False
  # si aucune erreur n'est relevée, le nombre binaire est au bon format, il est retourné sans espace pour être traité.
  return binaire


def compare_binaire(nombre1:str, nombre2:str) -> str | bool:
  """Compare deux nombres binaires sous forme de chaînes de caractères et renvoie le plus grand. 
      Retourne False si les deux nombres sont égaux.

  Args:
      nombre1 (str): premier binaire
      nombre2 (str): second binaire

  Returns:
      str | bool: le plus grand nombre binaire, False si les deux nombres sont égaux.
  """

  # On commence par comparer le bit de poids le plus fort pour étudier le signe du nombre
  # si nombre1 a son bit de poids le plus fort plus petit que celui de nombre2, il est positif, donc forcément plus grand
  if nombre1[0] < nombre2[0]: 
      return nombre1
  # sinon c'est nombre2 le plus grand
  elif nombre1[0] > nombre2[0]: 
      return nombre2   
  # si le bit de poids le plus fort est identique pour les deux nombres, alors ils ont le même signe
  else:
  # on boucle sur la suite des bits, en commençant à l'indice 1, l'indice 0 à déjà été traité
    i = 1
    while i <= NBR_BITS - 1 :
    # et on compare les bits, on continue jusqu'à trouver une différence
    # cette fois c'est le plus grand qui doit être retourné
      if nombre1[i] > nombre2[i]:
        return nombre1      
      elif nombre1[i] < nombre2[i]:
        return nombre2
      else:
        i += 1
  # si aucune différence n'est trouvée, c'est que l'utilisateur a entré deux fois le même nombre
  return False


# appel de la fonction
renvoi_binaire_sup()