/**
 ** Communication avec le clavier
 **
 ** Permet de lire le clavier matriciel
 **
 ** @file        clavier.h
 ** @version     1
 ** @author      Florent TOUCHARD
 **
 */

#ifndef CLAVIER_H
#define CLAVIER_H

/** Scrute le clavier en attendant qu'une touche soit pressée
 ** @note La fonction opère une attente active
 ** @note La touche considérée est la première pressée seule
 ** @note La fonction retourne lorsqu'une touche a été pressée et que
 **       toutes les touches sont relâchées ensuite
 ** @param[in] port Le numéro (1 à 4 inclus) du port sur lequel est
 **                 branché le clavier matriciel
 ** @return -1 si le port n'est pas dans la bonne plage de valeurs
 **         La touche pressée sous forme de caractère imprimable sinon
 */
char clavier_scrute(void);

#endif
