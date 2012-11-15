#ifndef __TYPES_H__
#define __TYPES_H__

/** @file types.h */

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct s_fifo Fifo;
typedef struct s_dungeon Dungeon;
typedef struct s_room Room;

/**
 * @brief Type de salle.
 */
typedef enum e_room_type {
    RT_EMPTY,   /**< Salle vide. */
    RT_SIMPLE,  /**< Salle simple. */
    RT_START,   /**< Salle de départ. */
    RT_BOSS     /**< Salle du boss. */
} RoomType;

/**
 * @brief Direction.
 **/
typedef enum e_direction {
    RIGHT = 0,  /**< Droite. */
    DOWN  = 1,  /**< Base. */
    LEFT  = 2,  /**< Gauche. */
    UP    = 3   /**< Haut. */
} Direction;

#define opDir(dir) ((dir + 2) % 4)

#endif
