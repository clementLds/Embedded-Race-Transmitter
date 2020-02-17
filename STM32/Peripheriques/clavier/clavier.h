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

/** Scrute le clavier en attendant qu'une touche soit press�e
 ** @note La fonction op�re une attente active
 ** @note La touche consid�r�e est la premi�re press�e seule
 ** @note La fonction retourne lorsqu'une touche a �t� press�e et que
 **       toutes les touches sont rel�ch�es ensuite
 ** @param[in] port Le num�ro (1 � 4 inclus) du port sur lequel est
 **                 branch� le clavier matriciel
 ** @return -1 si le port n'est pas dans la bonne plage de valeurs
 **         La touche press�e sous forme de caract�re imprimable sinon
 */
char clavier_scrute(void);

#endif
