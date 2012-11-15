#ifndef __FIFO_H_
#define __FIFO_H_

/**
 * @file fifo.h File.
 *
 * Une file est une liste de taille dynamique dont les éléments sont placé
 * et retiré dans l'ordre. C'est à dire que le premier élément à entrer, sera
 * le premier à sortir et ainsi de suite.
 *
 * La file gère l'allocation de mémoire en fonction de ses besoins, elle fera
 * une allocation par bloc qu'il est possible de paramètrer à la création.
 */

#include "../types.h"

/**
 * @brief Construit une nouvelle file.
 *
 * @param blocSize Taille d'un bloc d'allocation.
 *
 * @return La file.
 */
Fifo *fifo_new (uint blocSize);
/**
 * @brief Détruit une file.
 *
 * @param fifo La file à détruire.
 */
void fifo_delete (Fifo **fifo);

/**
 * @brief Donne le nombre d'éléments d'une file.
 *
 * @param fifo La file.
 *
 * @return Le nombre d'éléments de la file.
 */
uint fifo_size (Fifo *fifo);

/**
 * @brief Vide une file.
 *
 * @param fifo La file.
 */
void fifo_clear (Fifo *fifo);
/**
 * @brief Ajoute un élément à une file.
 *
 * @param fifo La file.
 *
 * @param data L'élément à ajouter.
 */
void fifo_push (Fifo *fifo, void *data);
/**
 * @brief Retire un élément à une file.
 *
 * @param fifo La file.
 *
 * @return L'élément retiré.
 */
void *fifo_pop (Fifo *fifo);

/**
 * @brief Affiche une file.
 *
 * @param fifo La file.
 */
void fifo_print (Fifo *fifo);

#endif
