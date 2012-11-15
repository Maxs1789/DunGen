#ifndef __ROOM_H__
#define __ROOM_H__

/** @file room.h */

#include "types.h"

/**
 * @brief Construit une nouvelle salle.
 *
 * @param dungeon Le donjon de la salle.
 * @param x       La position en x de la salle.
 * @param y       La position en y de la salle.
 *
 * @return La salle.
 */
Room *room_new (Dungeon *dungeon, uint x, uint y);
/**
 * @brief Détruit une salle.
 *
 * @param room La salle à détruire.
 */
void room_delete (Room **room);

/**
 * @brief Donne la position en x d'une salle.
 *
 * @param room La salle.
 *
 * @return La position en x.
 */
uint room_x (Room *room);
/**
 * @brief Donne la position en y d'une salle.
 *
 * @param room La salle.
 *
 * @return La position en y.
 */
uint room_y (Room *room);
/**
 * @brief Donne la zone d'une porte de salle.
 *
 * @param room La salle.
 * @param dir  La direction de la porte.
 * @param door Le numéro de porte (0 ou 1).
 *
 * @return Le numéro de zone de la porte ou 0 si la porte n'existe pas.
 */
uint room_door (Room *room, Direction dir, uint door);
/**
 * @brief Donne le nombre de porte dans une direction d'une salle.
 *
 * @param room La salle.
 * @param dir  La direction.
 *
 * @return Le nombre de porte
 */
uint room_doorCount (Room *room, Direction dir);
/**
 * @brief Donne le donjon d'une salle.
 *
 * @param room La salle.
 *
 * @return Le donjon.
 */
Dungeon *room_dungeon (Room *room);
/**
 * @brief Donne le type d'une salle.
 * @param room La salle.
 * @return Le type.
 */
RoomType room_type (Room *room);
/**
 * @brief Donne l'une des salles voisine à un salle.
 * @param room La salle.
 * @param dir  La direction de la salle voisine.
 * @return La salle voisine ou NULL si elle n'existe pas.
 */
Room *room_next (Room *room, Direction dir);

/**
 * @brief Retire une porte de salle ou change son numéro de zone.
 *
 * @param room  La salle.
 * @param dir   La direction.
 * @param door  Le numéro de porte (0 ou 1).
 * @param zone  Le numéro de zone de la porte, ou 0 pour la retirer.
 */
void room_setDoor (Room *room, Direction dir, uint door, uint zone);
/**
 * @brief Change le type d'une salle.
 *
 * @param room La salle.
 * @param type Le type.
 */
void room_setType (Room *room, RoomType type);
/**
 * @brief Vide une salle et enlève ses portes
 *
 * @param room La salle.
 */
void room_clear (Room *room);

/**
 * @brief Génère les portes d'une salle en s'adaptant aux salles voisines
 *        et pousse dans la pile les salles devant être générée ensuite.
 *
 * @param room La salle.
 * @param fifo La pile.
 */
void room_generateDoor (Room *room, Fifo *fifo);

#endif
