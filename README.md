# War Game IA

## Description
Ce projet fait partie du premier cours d’intelligence artificielle.  
Il consiste à créer un jeu de stratégie avec des pions dotés de poids et de couleurs.

---

## Objectif du projet
Développer une IA capable de jouer au jeu à l’aide de différentes approches :
- Une fonction d’évaluation (`f_eval`)
- Une IA utilisant l’algorithme **Minimax**
- Une IA optimisée avec **Alpha–Beta pruning**

---

## Objectif du jeu
Le but est :
- d’atteindre la case de promotion avec l’un de ses pions, **ou**
- de capturer tous les pions adverses.

---

## Comment jouer
Au lancement, choisissez le mode de jeu :
1. **Humain vs IA**  
2. **Humain vs Humain**  
3. **IA vs IA**

Les déplacements se font en entrant les coordonnées de la case de départ et d’arrivée de votre pion.  
Exemple :  
A1A2
→ déplace le pion de la case **A1** vers **A2**.

---

## ⚙️ Compilation
Utilisez la commande suivante pour compiler le projet :
```bash
make
```
MinMax :
```bash
./wargame_min_max
```
AlphaBeta :
```bash
./wargame_alpha_beta
```
pour nettoyer :
```bash
make clean
```
