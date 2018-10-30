---
layout: default
title: Le Jeu de la Vie de John Conway
subtitle: Automate Cellulaire et Vie Artificielle
---

# Programmation Orientée Objet

La Programmation Orientée Objet (POO) est un *paradigme*, c'est-à-dire une représentation du monde, une manière de voir les choses, un modèle cohérent du monde tangible et concret qui repose sur un fondement défini et universellement reconnu par la communauté des informaticiens. Ce modèle de programmation a été élaboré au début des années 1960 par les norvégiens [Ole-Johan Dahl](https://fr.wikipedia.org/wiki/Ole-Johan_Dahl) et [Kristen Nygaard](https://fr.wikipedia.org/wiki/Kristen_Nygaard), puis approfondi par l'américain [Alan Kay](https://fr.wikipedia.org/wiki/Alan_Kay) dans les années 1970, alors qu'il travaillait sur le langage [Smalltalk](https://fr.wikipedia.org/wiki/Smalltalk) au Xeros PARC.

Pour mieux comprendre ce qu'est la POO et ce qu'elle nous a apporté, revenons un peu sur les paradigmes « classiques » de programmation qui l'ont précédée.

**La programmation séquentielle**

Dans ce modèle, l'ordinateur déroule une liste d'instructions et les exécute pas à pas. C'est typiquement ce que l'on fait lorsqu'on programme en assembleur. On peut tout à fait faire de la programmation séquentielle en C ou en C++, mais ce serait laborieux. En effet, *réutiliser* une portion de code reviendrait à faire du copier-coller des instructions concernées et d'en changer éventuellement les paramètres. Imaginez un peu programmer le Jeu de la vie de cette manière... vous y serez encore la semaine prochaine !

**La programmation procédurale**

Dans ce modèle, on va justement chercher à construire une abstraction de certaines portions du code pour en faire des *procédures* que l'on pourra ensuite réutiliser en appelant ces procédures par des enchaînements contrôlés dans le code. C'est exactement ce que l'on a fait dans les chapitres précédents, en écrivant des *fonctions* que nous avons appelées et rappelées. Certaines fonctions appelaient même d'autres fonctions à leur tour. Et c'est l'ordonnancement de toutes ces tâches qui nous a permis d'obtenir un simulateur du Jeu de la Vie parfaitement fonctionnel (sans jeu de mots).

En suivant cette approche, nous avons défini un certain nombre de variables (des booléens, des entiers, des tableaux, etc.) que nous avons ensuite manipulées avec des procédures (nos fonctions). Mais à aucun moment nous n'avons véritablement associé explicitement ces variables aux procédures qui les manipulaient. Intrinsèquement, cela veut dire que les données et les procédures sont traitées indépendamment les unes des autres, sans tenir compte des relations étroites qui les unissent. C'est précisément ce que va nous permettre l'approche orientée objet.

**La programmation orientée objet**

Dans ce paradigme, nous allons associer les données et les procédures qui sont « faîtes pour aller ensemble » au sein d'une même entité : un **objet**. Les données vont permettre de définir la *structure* de l'objet (de quoi est-il fait). Ce sont elles qui vont caractériser son *état*. Tandis que les procédures vont permettre de définir le *comportement* de l'objet (quelles sont ses capacités à agir), c'est-à-dire son aptitude à entrer en *interaction* avec les autres objets du monde, ou avec lui-même. La notion de « monde » doit ici être comprise comme une nouvelle manière d'organiser notre programme.


# Application au Jeu de la Vie

Voyons maintenant comment appliquer ce paradigme à notre programme pour le réorganiser sous la forme d'une collection d'objets en interaction. L'objet *central* de notre code est évidemment l'automate cellulaire lui-même. Nous allons devoir ici en expliciter sa structure et son comportement. En d'autres termes, sa *nature*, c'est-à-dire ses *propriétés*. Les propriétés structurelles et comportementales d'un objet doivent être définies selon un modèle *abstrait* de cet objet, que l'on appelle une **classe**.

En C++, une règle de « bonne pratique » consiste à séparer la partie *déclarative* de la classe, de sa *définition*. Nous allons décrire le modèle de notre automate cellulaire par une classe que nous baptiserons `Automaton` (la convention veut que le nom d'une classe commence par une majuscule). Pour cela, nous allons créer deux fichiers :

- `Automaton.h` qui va contenir la déclaration de la classe,
- `Automaton.cpp` qui va contenir la définition de la classe.


## Déclaration d'une classe

**La déclaration de la classe** va nous permettre de décrire :

- les **attributs** : les propriétés structurelles de ses instances,
- les ***méthodes*** : les propriétés comportementales de ses instances.

Elle figure dans un fichier d'en-tête, aussi appelé « header » (d'où l'extension `.h`) :

<div class="filename">Automaton.h</div>
```c++
class Automaton
{
    private:

        // attribut
        uint8_t grid[W+2][H+2];

        // méthodes
        uint8_t duplicate(uint8_t g);
        uint8_t neighbours(size_t x, size_t y);
        void bufferize();
        void applyRules();

    public:

        // constructeur
        Automaton();

        // méthodes
        void randomize();
        void step();
        void draw();
};
```

Au premier coup d'oeil, vous remarquez la présence des mots-clefs `private` et `public`. Ils sont là pour définir ce que l'on appelle l'**encapsulation**, c'est-à-dire les contrôles d'accès aux propriétés de la classe.

Rappelez-vous que la classe est une entité abstraite qui décrit un modèle. On pourrait l'assimiler à un plan de construction, ou un *patron*. Ce modèle va nous permettre de construire des **objets** à son image. Ces objets seront en quelque sorte des concrétisations de ce modèle. Tous les objets construits à l'image de leur classe sont nommés les **instances** de la classe. Par analogie à la métaphore architecturale que j'ai employée, les instances seraient toutes les maisons bâties selon le même plan de construction.

Pour revenir à la notion d'encapsulation, tout ce qui est déclaré sous le mot-clef `private` ne sera accessible qu'aux instances de cette classe, mais de manière individuelle. Cela veut dire qu'une instance aura accès à ses propriétés privées, mais pas les autres instances issues de la même classe, et encore moins le reste du monde. Chaque instance a accès à ses propres attributs et méthodes, mais elle seule y a accès si ses propriétés sont privées. En revanche, toutes les propriétés déclarées sous le mot-clef `public` seront exposées au monde entier.

Prenons l'exemple de la méthode `bufferize()` : elle est déclarée comme `private` parce-qu'elle correspond à un mécanisme *interne* à l'objet. Le reste du monde n'a pas à connaître l'existence de cette méthode et ne doit pas pouvoir, *a fortiori*, l'invoquer (c'est-à-dire l'appeler... comme on appelle une fonction).

En revanche la méthode `draw()` est déclarée comme `public`, justement parce-que l'on souhaite exposer ce comportement au reste du monde. En effet, lorsque le programme principal `GameOfLife.ino` entrera dans sa boucle `loop()` il aura besoin d'invoquer cette méthode, pour demander à l'automate de se dessiner à l'écran, à chaque cycle de la simulation. Dans la terminologie objet, on dira que le programme principal enverra le **message** `draw()` à l'automate. Et oui, les objets communiquent par envois de messages.

Vous avez aussi sans doute remarqué que la classe `Automaton` expose une fonction un peu particulière, dont le nom est le même que la classe elle-même (avec sa majuscule) : je veux parler de la fonction `Automaton()`. Cette fonction est en fait une méthode un peu particulière que l'on appelle un **constructeur**. C'est précisément par le biais de ce constructeur que l'on va pouvoir créer des instances de la classe `Automaton`. Comme toute fonction, le constructeur peut accepter des arguments. Ça n'est pas le cas ici, mais c'est tout à fait possible.

De manière générale vous pouvez aussi constater que les méthodes de la classe sont simplement déclarées par ce que l'on appelle des **prototypes**. Ces prototypes définissent ce que chaque méthode accepte comme arguments (avec leurs types) et ce qu'elle renvoie à son tour. Aucun code n'explicite ce que *fait* réellement la méthode (quelles instructions elle exécute). C'est pour cela que nous allons devoir maintenant *définir* chacune de ces méthodes.


## Définition d'une classe

**La définition de la classe** va nous permettre d'expliciter l'implémentation de chaque méthode déclarée.

<div class="filename">Automaton.cpp</div>
```c++
#include "Automaton.h"

// le constructeur
Automaton::Automaton() {

}

void Automaton::randomize() {
    size_t x,y;
    size_t xsup = W+1; // borne supérieure de x
    size_t ysup = H+1; // borne supérieure de y
    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            this->grid[x][y] = random(0,2) == 0 ? random(1, 4) : 0;
        }
    }
}

uint8_t Automaton::duplicate(uint8_t g) {
    return (g << 4) | (g & 0xF);
}

uint8_t Automaton::neighbours(size_t x, size_t y) {
    uint8_t n = 0;
    size_t x1 = x-1;
    size_t x2 = x+1;
    size_t y1 = y-1;
    size_t y2 = y+1;

    if (this->grid[x1][y1] & 0xF0) { n++; }
    if (this->grid[x][y1]  & 0xF0) { n++; }
    if (this->grid[x2][y1] & 0xF0) { n++; }
    if (this->grid[x1][y]  & 0xF0) { n++; }
    if (this->grid[x2][y]  & 0xF0) { n++; }
    if (this->grid[x1][y2] & 0xF0) { n++; }
    if (this->grid[x][y2]  & 0xF0) { n++; }
    if (this->grid[x2][y2] & 0xF0) { n++; }
    
    return n;
}

void Automaton::bufferize() {
    size_t x,y;
    size_t w = W+1;
    size_t h = H+1;
    size_t xsup = W+2;
    size_t ysup = H+2;

    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            // recopie de la partie visible de la grille
            this->grid[x][y] = this->duplicate(grid[x][y]);
        }
        // recopie vers la frange de gauche
        this->grid[0][y] = this->duplicate(grid[W][y]);
        // recopie vers la frange de droite
        this->grid[w][y] = this->duplicate(grid[1][y]);
    }

    for (x=1; x<xsup; x++) {
        // recopie vers la frange du haut
        this->grid[x][0] = this->duplicate(grid[x][H]);
        // recopie vers la frange du bas
        this->grid[x][h] = this->duplicate(grid[x][1]);
    }

    // recopie des coins
    this->grid[0][0] = this->duplicate(grid[W][H]);
    this->grid[w][0] = this->duplicate(grid[1][H]);
    this->grid[0][h] = this->duplicate(grid[W][1]);
    this->grid[w][h] = this->duplicate(grid[1][1]);
}

void Automaton::applyRules() {
    uint8_t n,g,b;
    size_t x,y;
    size_t xsup = W+1;
    size_t ysup = H+1;

    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            n = this->neighbours(x,y);
            // l'état courant de la cellule
            g = this->grid[x][y] & 0xF;
            // l'état de la cellule à la génération précédente
            b = this->grid[x][y] & 0xF0;
            if (g == 0) { // si la cellule est morte
                if (n == 3) {
                    g = 1;
                }
            } else { // sinon c'est qu'elle est vivante
                if (n == 2 || n == 3) {
                    if (g != 15) {
                        g++;
                    }
                } else {
                    g = 0;
                }
            }
            // on n'oublie pas de conserver l'état de la cellule
            // à la génération précédente, puisque la grille n'a
            // pas encore été totalement parcourue !
            this->grid[x][y] = b | g;
        }
    }
}

void Automaton::step() {
    this->bufferize();
    this->applyRules();
}

void Automaton::draw() {
    uint8_t i,j,y,g;
    gb.display.clear();
    for (i=0; i<H; i++) {
        y = i+1;
        for (j=0; j<W; j++) {
            g = grid[j+1][y] & 0xF;
            if (g) {
                gb.display.setColor(PALETTE[g]);
                gb.display.drawPixel(j,i);
            }
        }
    }
}
```

En ce qui concerne le corps des méthodes, rien de nouveau, nous avons déjà explicité en détail ce que font toutes ces fonctions dans le chapitre précédent. Nous les avons simplement réécrites ici avec une syntaxe propre à la POO.

Vous voyez que le nom de chaque méthode doit être préfixé par le nom de la classe. Par exemple la méthode `randomize()` que nous avons déclarée dans le fichier `Automaton.h` est définie de la manière suivante : `void Automaton::randomize()`. En particulier, le constructeur respecte la même règle : `Automaton::Automaton()`.

En y regardant d'un peu plus près, vous aurez probablement remarqué la présence du mot-clef `this` et de la curieuse notation `this->`. Rien de méchant... en réalité, `this` est un pointeur vers l'objet lui-même. C'est une sorte d'auto-référence. Et l'usage veut que l'on utilise cette référence lorsque l'objet a besoin de faire référence à l'une de ses propriétés. Par exemple, s'il souhaite accéder à la cellule de coordonnées `(x,y)` de sa propre grille, on écrira : `this->grid[x][y]`. S'il souhaite invoquer sa propre méthode `bufferize()`, on écrira : `this->bufferize()`. Cette forme d'écriture n'est pas obligatoire, mais elle est recommandée. `this` permet à l'objet de faire référence à lui-même. Cela peut s'avérer nécessaire lorsqu'il doit communiquer cette référence à un autre objet (comme argument d'un message par exemple).


## Les directives de pré-compilation

Vous remarquerez également qu'au début du fichier `Automaton.cpp` est inscrite une directive de pré-compilation :

```c++
#include "Automaton.h"
```

Cette directive indique au préprocesseur de traiter le contenu de ce fichier comme s'il figurait dans le code source à l'emplacement où figure la directive. Cela permet de charger la déclaration de la classe avant sa définition. Les deux seront nécessaires lors de la compilation. Cette directive sera également nécessaire dans le code du programme principal puisque nous aurons besoin de la déclaration de la classe `Automaton` pour pouvoir la désigner. Il peut arriver que l'on ait besoin d'inclure le même fichier d'en-tête à plusieurs endroits dans notre code. Aussi, pour indiquer au préprocesseur de ne pas redéclarer ce qui l'a déjà été et empêcher les inclusions multiples, on utilisera des garde-fous, que l'on appelle aussi des *`#define` Guards* :

<div class="filename">Automaton.h</div>
```c++
// garde-fou
#ifndef GAME_OF_LIFE_AUTOMATON_H_
#define GAME_OF_LIFE_AUTOMATON_H_

class Automaton
{
    // ... je ne réécris pas ici toutes les déclarations
};

#endif
```

L'étiquette d'un garde-fou doit être unique, aussi il est important de veiller à bien les nommer pour limiter le risque de redéfinir une étiquette qui existerait déjà. Les conventions de nommage des garde-fous diffèrent selon les *paroisses*... Mais nous pouvons, par exemple, nous inspirer du [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#The__define_Guard) qui préconise l'usage du format suivant : `<PROJECT>_<PATH>_<FILE>_H_`. À la différence près que, dans notre cas, tous les fichiers sont dans le même dossier, donc on peut ignorer le segment `<PATH>_`.

Il nous faudra également réunir la déclaration des constantes globales dans un fichier d'en-tête qui pourra ensuite être chargé partout où ce sera nécessaire. Pour cela, nous allons simplement créer le *header* `bootstrap.h` :

<div class="filename">bootstrap.h</div>
```c++
#ifndef GAME_OF_LIFE_BOOTSTRAP_H_
#define GAME_OF_LIFE_BOOTSTRAP_H_

// On charge ici le header de la bibliothèque Gamebuino-Meta
// qui définit la plupart des types et des constantes ci-dessous
#include <Gamebuino-Meta.h>

// on préfèrera ici définir `W` et `H` comme des constantes
// plutôt que d'utiliser des #define comme nous le faisions
// dans les versions précédentes
// 👁 https://goo.gl/NezfyR pour la comparaison
const uint8_t W = 80;
const uint8_t H = 64;

const Color PALETTE[] = {BLACK, GREEN, LIGHTGREEN, WHITE, YELLOW, BEIGE, BROWN, ORANGE, RED, PINK, PURPLE, DARKBLUE, BLUE, LIGHTBLUE, GRAY, DARKGRAY};

#endif
```

Et, en particulier, ce fichier sera nécessaire dans la déclaration de la classe `Automaton` qui utilise ces constantes globales, donc il ne faut pas oublier d'y ajouter la directive d'inclusion correspondante :

<div class="filename">Automaton.h</div>
```c++
#ifndef GAME_OF_LIFE_AUTOMATON_H_
#define GAME_OF_LIFE_AUTOMATON_H_

#include "bootstrap.h"

class Automaton
{
    // ... je ne réécris pas ici toutes les déclarations
};

#endif
```

## Retour au programme principal

Il ne nous reste plus qu'à réécrire le programme principal de façon à ce qu'il soit capable de traiter tout ce que nous venons de réécrire en POO :

<div class="filename">GameOfLife.ino</div>
```c++
#include "bootstrap.h"
#include "Automaton.h"

// on déclare un pointeur sur un Automaton
Automaton* automaton;

void setup() {
    gb.begin();

    // instanciation de l'automate
    automaton = new Automaton();
    // l'opérateur `new` renvoie un pointeur sur un Automaton

    automaton->randomize();
}

void loop() {
    
    while (!gb.update());

    if (gb.buttons.pressed(BUTTON_A)) {
        automaton->randomize();
    }

    automaton->step();
    automaton->draw();
}
```

La ligne sur laquelle vous devez porter votre attention avant tout est la suivante :

```c++
automaton = new Automaton();
```

C'est précisément cette instruction qui va permettre d'instancier la classe `Automaton` pour obtenir un objet (une instance) construit d'après le modèle décrit par cette classe. L'opérateur `new` est donc un opérateur de *construction* qui renverra un pointeur sur l'objet qu'il a généré. D'où la déclaration en amont :

```c++
Automaton* automaton;
```

Il suffira ensuite d'utiliser la notation `->` pour envoyer un message à cet objet et ainsi invoquer l'une de ses méthodes publiques. Par exemple :

```c++
// pour envoyer le message `randomize` à l'instance d'Automaton :
automaton->randomize();
```

Il vous sera par contre impossible d'invoquer une méthode privée (vous obtiendrez une erreur à la compilation) :

```c++
// ATTENTION ! L'encapsulation interdit l'envoi de ce message :
automaton->bufferize();
```

Voilà, nous en avons terminé avec cette petite introduction à la programmation orientée objet. Le code source complet de cette troisième version est [disponible ici]({{ site.github.repository_url | append: '/blob/master/sources/v3/GameOfLife/' }}).

> **N.B.** Nous aurions pu pousser le vice plus loin et appliquer le paradigme de la POO à chaque cellule de la grille... en effet, nous aurions pu créer une classe `Cell` chargée de maintenir l'état d'une cellule. Chaque cellule aurait pu être *connectée* à 8 autres cellules (des instances construites sur le même modèle) pour constituer son voisinage, etc. Mais quand on y réfléchit, actuellement, `1 octet` suffit à coder l'état de chacune de nos cellules et la structure du voisinage est parfaitement intégrée dans un tableau à 2 dimensions. Par conséquent, dans ce cas précis, une telle modélisation alourdirait notre code inutilement, et surtout nous ferait perdre tout le bénéfice des optimisations que nous avons appliquées dans la `v2`. Les performances de calcul s'effondreraient et l'occupation mémoire exploserait. Un tel choix ne serait donc pas très judicieux. Ne tombez pas dans l'extrémisme à vouloir faire du **tout objet**. Ça n'est pas toujours la meilleure des solutions.

D'ailleurs, jetons un oeil sur les nouvelles mesures de performances :

|    code    | cycle  | fréquence | RAM libre  |  technique  |
|:----------:|-------:|----------:|-----------:|:-----------:|
|   **v1**   | 109 ms |     9 fps | 4907 bytes | procédurale |
|   **v2**   |  35 ms |    28 fps | 9723 bytes | procédurale |
|   **v3**   |  36 ms |    27 fps | 9719 bytes |     POO     |
| **sautax** |  49 ms |    20 fps | 4779 bytes | procédurale |

On obtient sensiblement les mêmes résultats qu'avec la `v2`. Bonne nouvelle ! <i class="far fa-smile-wink"></i>