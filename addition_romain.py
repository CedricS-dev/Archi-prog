# *******************************************************
# Nom ......... : addition_romain
# Rôle ........ : Additionne deux nombres romains entrés par l'utilisateur
# Auteur ...... : Cedric SAGHI
# Version ..... : V0.1 du 10/06/2024
# Licence ..... : Réalisé dans le cadre du cours d'architecture des ordinateurs, chapitre 2, L1 informatique
# (../..)
# Compilation : aucune
# Usage : Pour exécuter : python3 addition_romain.py 
#********************************************************/

# variable globale contenant les différents symboles des nombres romains dans l'ordre décroissant
TABLE_ORDRE_ROMAIN = ["M", "D", "C", "L", "X", "V", "I"]

# variable globale servant de table de conversion des groupes soustractifs vers additifs
TABLE_SOUSTRACTIF_ROMAIN = {
    'CM': 'DCCCC',
    'CD': 'CCCC',
    'XC': 'LXXXX',
    'XL': 'XXXX',
    'IX': 'VIIII',
    'IV': 'IIII'
} 

# variable globale servant de table de conversion pour les combinaisons de symboles
# les valeurs associées aux clés sont à l'envers comme le traitement se fait sur une chaîne inversée
TABLE_COMBINAISON_ROMAIN = {
    'IIIIIIIII' : 'IIIIV', 'IIIIIIII' : 'IIIV', 'IIIIIII' : 'IIV', 'IIIIII' : 'IV', 'IIIII' : 'V',
    'VVVVVVV' : 'VXXX', 'VVVVV' : 'VXX', 'VVV' : 'VX', 'VV' : 'X', 
    'XXXXXXXXX' : 'XXXXL', 'XXXXXXXX' : 'XXXL', 'XXXXXXX' : 'XXL', 'XXXXXX' : 'XL', 'XXXXX' : 'L',
    'LLLLLLLLL' : 'LCCCC', 'LLLLLLL' : 'LCCC', 'LLLLL' : 'LCC', 'LLL' : 'LC', 'LL' : 'C',
    'CCCCCCCCC' : 'CCCCD', 'CCCCCCCC' : 'CCCD', 'CCCCCCC' : 'CCD', 'CCCCCC' : 'CD', 'CCCCC' : 'D',
    'DDDDDDD' : 'DMMM', 'DDDDD' : 'DMM', 'DDD' : 'DM', 'DD' : 'M'
}


def additif_en_soustractif(nombre_romain:str) -> str: 
    """Fonction pour convertir les groupes de symboles additifs d'un nombre romain en groupes soustractifs
        exemple : IIII -> IV
    
    Args:
        nombre_romain (str): le nombre dans sa forme additive

    Returns:
        str: résultat après conversion
    """

    # boucle cherchant des correspondances entre la valeur entrée et les clés du dictionnaire TABLE_SOUSTRACTIF_ROMAIN
    # si des correspondances sont trouvées, les symboles de la valeur entrée sont remplacés par les valeurs associées aux clés
    for key, value in TABLE_SOUSTRACTIF_ROMAIN.items():   
        if key in nombre_romain:            
            nombre_romain = nombre_romain.replace(key, value)         
    return nombre_romain 


def soustractif_en_additif(nombre_romain:str) -> str:
    """Fonction pour convertir les groupes de symboles soustractifs d'un nombre romain en groupes additifs
        exemple : IV -> IIII

    Args:
        nombre_romain (str): le nombre dans sa forme soustractive

    Returns:
        str: résultat après conversion
    """

    # boucle cherchant des correspondances entre la valeur entrée et les valeurs du dictionnaire TABLE_SOUSTRACTIF_ROMAIN
    # si des correspondances sont trouvées, les symboles de la valeur entrée sont remplacés par les clé associées
    for key, value in TABLE_SOUSTRACTIF_ROMAIN.items():   
        if value in nombre_romain:            
            nombre_romain = nombre_romain.replace(value, key)       
    return nombre_romain 


def ordonne_nombre_romain(nombre_romain:str) -> str:  
    """Fonction servant à mettre dans l'ordre décroissant les symboles des nombres romains
        exemple : VXIC -> CXVI
    
    Args:
        nombre_romain (str): nombre romain désordonné

    Returns:
        str: nombre romain mis dans l'ordre décroissant
    """
    
    # variable qui contiendra le résultat après traitement
    result = ""
    # boucle comparant la valeur entrée avec le tableau contenant les symboles dans l'ordre décroissant
    # si une correspondance est trouvée, la valeur est ajoutée au contenu de result    
    for row in TABLE_ORDRE_ROMAIN: 
        for digit in nombre_romain:
            if row == digit:
                result = result + digit          
    return result    

def combine_nombres_romains(nombre_romain:str) -> str:  
    """Fonction qui combine les symboles d'un nombre romain vers leurs formes correctes
        exemple : IIIII -> V

    Args:
        nombre_romain (str): nombre romain à simplifier

    Returns:
        str: résultat après simplification
    """
    # inversion du nombre romain pour commencer la simplification par les plus petits symboles
    nombre_romain = "".join(reversed(nombre_romain))

    # boucle cherchant des éléments communs entre la globale TABLE_COMBINAISON_ROMAIN et la valeur entrée
    # si des éléments sont trouvés, ils sont remplacés par la valeur associée dans la table
    for key, value in TABLE_COMBINAISON_ROMAIN.items():
        if key in nombre_romain:
            nombre_romain = nombre_romain.replace(key, value)
            #print(nombre_romain)

    # renvoi le résultat après l'avoir de nouveau inversé             
    return "".join(reversed(nombre_romain))


def additionne_nombres_romains() -> str:
    """Fonction qui demande à l'utilisateur deux nombres romains et retourne la somme de ces deux nombres
        exemple : IV + V ->  IX

    Returns:
        str: résultat de l'addition
    """

    # tests sur les entrées utilisateurs
    # si un symbole ne fait pas partit de la liste des symboles de la globale TABLE_ORDRE_ROMAIN
    # alors ce symbole n'est pas un chiffre romain 
    nombre_romain1 = input("Entrez un premier nombre romain : ")
    for symbol in nombre_romain1:
        if not symbol in TABLE_ORDRE_ROMAIN:
            print(f"Le nombre {nombre_romain1} n'est pas un nombre valide.")
            return
        
    nombre_romain2 = input("Entrez un second nombre romain : ")
    for symbol in nombre_romain2:
        if not symbol in TABLE_ORDRE_ROMAIN:
            print(f"Le nombre {nombre_romain2} n'est pas un nombre valide.")
            return

    # conversion des entrées utilisateurs en forme soustractive     
    nombre_romain1 = additif_en_soustractif(nombre_romain1)
    nombre_romain2 = additif_en_soustractif(nombre_romain2)
    # concaténation des entrées (addition)
    result = nombre_romain1 + nombre_romain2
    # mise en ordre des symboles
    result = ordonne_nombre_romain(result)
    # combinaison des groupes de symboles
    result = combine_nombres_romains(result)
    # transformation du résultat en forme soustractive    
    result = soustractif_en_additif(result)
    print(f"Résultat de l'addition : {result}")
    return result

# appel de la fonction
additionne_nombres_romains()
