---
layout: default
title: Le Jeu de la Vie de John Conway
subtitle: Automate Cellulaire et Vie Artificielle
---

# Présentation du tuto

Je vous propose ici une petite récréation mathématique, à défaut d'un véritable *jeu* au sens classique du terme, pour la Gamebuino META : le célèbre Jeu de la Vie, imaginé par John Conway dans les années 1970. Vous allez voir que c'est un petit exercice formidable, qui va nous permettre d'aborder de nombreux concepts et techniques de programmation. L'idée maîtresse qui m'a guidé tout au long de la rédaction de ce tutoriel était de proposer un exercice à la fois simple et riche en possibilités, que nous allions pouvoir traiter de manière différente, au travers d'une approche graduelle dans la complexité de la programmation, pour aboutir à une application finalisée avec une architecture maîtrisée.

# Quels sont les prérequis ?

|                  | Débutant |         Intermédiaire        |  Confirmé | Expert |
|-----------------:|:--------:|:----------------------------:|:---------:|:------:|
|**Niveau requis** |          | <i class="fas fa-check"></i> |           |        |

Pour pouvoir suivre ce tutoriel dans les meilleures conditions, vous devez :

- maîtriser les notions de base du langage C (ou C++),
- avoir suivi avec succès tous les ateliers de l'[Académie](https://gamebuino.com/academy).

Posséder une Gamebuino META n'est pas indispensable : vous pouvez tester votre code sur l'excellent [émulateur](http://games.aoneill.com/meta-emulator/) grâcieusement développé par [Andy O'Neill](https://gamebuino.com/@aoneill), talentueux contributeur au projet Gamebuino.

# Ce que vous allez apprendre ici

Dans les grande lignes, vous aller apprendre à :

- programmer un automate cellulaire,
- optimiser votre code pour :
    - accélérer la vitesse d'exécution,
    - économiser l'espace mémoire,
- mieux organiser votre code avec la Programmation Orientée Objet,
- concevoir vos applications avec une architecture Model View Controller,
- intercepter les événements lorsque l'utilisateur appuie sur les boutons,
- gérer des menus dans vos application,
- programmer un gestionnaire des LEDs de la console,
- programmer un gestionnaire d'effets sonores.

Vous ne trouverez pas ici un cours complet sur la Programmation Orientée Objet, ni sur l'architecture Model View Controller. Mais j'espère néanmoins avoir su semer quelques graines qui vous permettront d'en comprendre les fondements et vous aideront à améliorer la conception de vos applications.

Pour compléter vos connaissances dans ce domaine ou consulter d'autres exemples d'applications construites à l'aide de ces modèles de programmation, vous pouvez aussi examiner les créations de [chris-scientist](https://gamebuino.com/@chris-scientist), contributeur très actif dans la commnunauté.
