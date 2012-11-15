#ifndef __DUNGEON_H__
#define __DUNGEON_H__

/** @file dungeon.h */

#include "types.h"

/**
 * @brief Construit un nouveau donjon.
 *
 * @param width  Largeur du donjon.
 * @param height Hauteur du donjon.
 *
 * @return Le donjon.
 */
Dungeon *dungeon_new (uint width, uint height);
/**
 * @brief Détruit un donjon.
 *
 * @param dun Le donjon à détruire.
 */
void dungeon_delete (Dungeon **dun);

/**
 * @brief Donne la largeur d'un donjon.
 *
 * @param dun Le donjon.
 *
 * @return La largeur du donjon.
 */
uint dungeon_width (Dungeon *dun);
/**
 * @brief Donne la hauteur d'un donjon.
 *
 * @param dun Le donjon.
 *
 * @return La hauteur du donjon.
 */
uint dungeon_height (Dungeon *dun);
/**
 * @brief Donne une salle d'un donjon.
 *
 * @param dun Le donjon.
 * @param x   La position en x de la salle.
 * @param y   La position en y de la salle.
 *
 * @return Pointeur vers la salle ou NULL si elle n'existe pas.
 */
Room *dungeon_room (Dungeon *dun, uint x, uint y);
/**
 * @brief Donne le nombre de salle d'un donjon.
 *
 * @param dun Le donjon.
 *
 * @return Le nombre de salle.
 */
uint dungeon_roomCount (Dungeon *dun);

/**
 * @brief Vide complètement un donjon.
 *
 * @param dun Le donjon à vider.
 */
void dungeon_clear (Dungeon *dun);

/**
 * @brief Génère un donjon.
 *
 * @param dun  Le donjon à générer.
 * @param seed La "graine" de génération.
 */
void dungeon_generate (Dungeon *dun, uint seed);

#endif
