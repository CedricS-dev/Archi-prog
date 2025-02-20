# *******************************************************
# Nom ......... : hanoi_binaire
# Rôle ........ : Simule et résoud une partie des Tours de Hanoi selon le formalisme binaire
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 26/07/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 8, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 hanoi_binaire.py
#********************************************************/


######################
# VARIABLES GLOBALES #
######################

# le plateau de jeu est représenté par un dictionnaire
# les 3 tiges du jeu sont représentés sous forme de tableaux vides 
# indice 0 = disque du haut
# chaque disque sera un int, représentant sa taille, de 1 à n
game = {'start'  : [],
        'middle' : [],
        'end'    : []}

# indique l'ordre des tiges, permet de déplacer un disque en fonction de l'indice
# + 1 pour aller à droite, - 1 pour aller à gauche
# en cherchant le nom correspondant dans le dictionnaire
order = ("start", "middle", "end")

# indique si le nombre de pièces du jeu est pair ou impair
# le mouvement de la pièce 1 dépend du nombre de pièces, pair ou impair
impair = False


#############
# FONCTIONS #
#############


def lance_partie() -> bool :
  """Lance une simulation de partie des Tours de Hanoi.
  Demande à l'utilisateur le nombre de disques, puis exécute la simulation et imprime le résultat dans un fichier.

  Returns:
      bool: True la fin de la simulation, False si l'utilisateur a entré une mauvaise valeur.
  """

  # demande à l'utilisateur le nombre de disques
  nbr_disque =input("Combien de disques voulez-vous dans cette partie ?\nEntrez un nombre entier supérieur à 0 : ")
  # vérifie que l'entrée est bien un integer
  try :
    nbr_disque = int(nbr_disque)
  except :
    print("Entrez un nombre entier supérieur à 0 !")
    return False
  # et qu'il est bien supérieur à 0
  if nbr_disque <= 0:
    print("Il faut au moins un disque pour jouer !")
    return False
  
  # enregistre le résultat dans un fichier texte
  with open (f"Solution_tours_de_Hanoi_{nbr_disque}_disques.txt", "w") as f:
    resouds_hanoi(nbr_disque, f)
    # affiche le message de fin de la partie
    print("\n##############", file = f)
    print("Fin de partie.", file = f)
    print("##############", file = f)
    # indique à l'utilisateur que le fichier résultat a été créé
    print(f"Le fichier {f.name} à été créé.")

  # à la fin du traitement, retourne True
  return True


def resouds_hanoi(n: int, f: __file__) -> bool :
  """Résous une partie de Tours de Hanoi en un nombre optimal de coups

  Args:
      n (int): nombre de disques pour la partie
      f (__file__): fichier d'impression des résultats

  Returns:
      bool: True une fois la partie résolue
  """

  # import des variables globales
  global jeu
  global impair
  # si le nombre de pièces est impair, passe impair à True
  if n % 2 != 0 : 
    impair = True

  # met les disques dans la tige de départ
  jeu['départ'] = list(range(1, n + 1))
  # message de début de partie
  print("################", file = f)
  print(f"Début de partie", file = f)
  print("################\n", file = f)
  # et affiche l'état du plateau de jeu
  print(f"départ : {jeu['départ']} - centre : {jeu['centre']} - arrivée : {jeu['arrivée']}", file = f)
  
  # calcul du nombre optimal de coups nécessaires 
  nombre_mouvs = 2**n - 1
  # et lance une boucle pour éxecuter les coups l'un après l'autre
  for i in range(1, nombre_mouvs + 1) :
    # récupère le disque à déplacer à partir du nombre binaire
    disque = compare_bits_precedent(i)
    # et déplace le
    move = mouvement_disque(disque)
    # imprime le mouvement effectué et le nouvel état du plateau de jeu
    print(f"Coup {i} :\nle disque {disque} à été déplacé dans la tige {move}.\ndépart : {jeu['départ']} - centre : {jeu['centre']} - arrivée : {jeu['arrivée']}", file = f)
  
  # termine en retournant True
  return True

def decimal_en_binaire_inverse(n : int) -> str :
  """Convertit un nombre décimal en nombre binaire inversé

  Args:
      n (int): décimal à convertir

  Returns:
      str: binaire inversé après conversion
  """

  # intitialisation du résultat sous forme de chaîne vide
  result = ""
  # tant que nombre est différent de 0
  while n != 0 :
    # modulo par 2 sur le nombre et conversion en chaîne
    # puis concaténation avec le résultat
    result += str(n % 2)
    # division du nombre en ne gardant que la partie entière 
    n = n // 2
  # retourne le résultat (inversé)
  return result


def compare_bits_precedent(n : int) -> int :
  """Convertit deux nombres décimaux : n en argument et n-1 sous forme de binaire inversé.
  Puis compare et retourne l'indice + 1 du premier bit de n plus grand que le bit de n-1 à la même position

  Args:
      n (int): décimal à convertir et comparer aver n-1

  Returns:
      int: l'indice + 1 du premier bit de n plus grand que le bit de n-1 à la même position
  """

  # convertit le nombre n en binaire inversé
  courant = decimal_en_binaire_inverse(n)
  # et fairt de même avec n-1
  précédent = decimal_en_binaire_inverse(n - 1)
  # si n est plus long que n-1, retourne sa longueur
  if len(courant) > len(précédent) :
    return len(courant)
  # sinon, compare bit par bit
  else :
    i = 0
    # retourne l'indice + 1 du premier bit de n
    # qui est strictment plus grand que le bit de n-1 à la même position
    while i < len(courant) :
      if courant[i] > précédent[i] :
        return i + 1
      else :
        i = i + 1


def mouvement_disque(disque: int) -> str :
  """Cherche puis réalise le mouvement à effectuer selon le disque donné en argument

  Args:
      disque (int): le numéro du disque à traiter

  Returns:
      str: le nom de la tige où le disque a été déplacé
  """

  # import des variables globales
  global jeu
  global ordre
  global impair
  # variables pour contrôler la boulce
  cherche = True
  i = 0
  # commence la recherche du disque
  while (cherche == True):
    # récupère le nom de la tige à l'indice i
    nom_tige = ordre[i]
    # cherche le disque dans la la tige du jeu ayant le même nom
    if disque in jeu[nom_tige] :
      # arrête la recherche
      cherche = False
      # si tu trouves un disque retire-le
      jeu[nom_tige].remove(disque)    
      # et cherche dans quelle tige le déplacer
      mouv = deplace_disque(disque, nom_tige)
      return mouv
    
    else :
     # sinon, passe sur la tige de droite
      i = i + 1
      # si cette tige n'existe pas, va à la première tige
      if i == 3 : i = 0
    

def deplace_disque(disque : int, nom_tige : str) -> str :
  """Déplace le disque désigné vers la bonne tige
     (application des graphes de l'automate)

    Args:
      disque (int): le numéro du disque à traiter
      nom_tige (str): le nom de la tige d'origine

  Returns:
      str: nom de la tige de destination
  """
  # import variabe globale
  global impair
  # fait un de ces mouvements si :
  # le nombre total de disques est pair et le disque est impair
  # ou le nombre total de disques est impair et le disque est pair
  if (disque % 2 == 1 and impair == False) or (disque % 2 == 0 and impair == True) :
    if nom_tige == "départ" :
      jeu["centre"].insert(0, disque)
      return "centre"
    elif nom_tige == "centre" :
      jeu["arrivée"].insert(0, disque)
      return "arrivée"
    else :
      jeu["départ"].insert(0, disque)
      return "départ"
  # fait un de ces mouvements si :
  # le nombre total de disques est pair et le disque est pair
  # ou le nombre total de disques est impair et le disque est impair
  elif (disque % 2 == 0 and impair == False) or (disque % 2 == 1 and impair == True):
    if nom_tige == "départ" :
      jeu["arrivée"].insert(0, disque)
      return "arrivée"
    elif nom_tige == "centre" :
      jeu["départ"].insert(0, disque)
      return "départ"
    else :
      jeu["centre"].insert(0, disque)
      return "centre"


# lance la partie
lance_partie()
