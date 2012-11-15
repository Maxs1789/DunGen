#include "dungeon.h"
#include "common.h"
#include "room.h"
#include "util/fifo.h"

void _dungeon_genBaseRoom (Dungeon *dun, Fifo *fifo);

/** @see dungeon.h */
typedef struct s_dungeon {
    uint width;     /**< Largeur du donjon. */
    uint height;    /**< Hauteur du donjon. */
    Room ***room;   /**< Tableau des salles. */
} Dungeon;

Dungeon *dungeon_new (uint width, uint height)
{
    uint x, y;
    Dungeon *dun = (Dungeon*)malloc(sizeof(Dungeon));
    dun->width = width;
    dun->height = height;
    dun->room = (Room***)malloc(sizeof(Room**) * height);
    for (y = 0; y < height; y++) {
        dun->room[y] = (Room**)malloc(sizeof(Room*) * width);
        for (x = 0; x < dun->width; x++) {
            dun->room[y][x] = room_new(dun, x, y);
        }
    }
    return dun;
}

void dungeon_delete (Dungeon **dun)
{
    uint x, y;
    for (y = 0; y < (*dun)->height; y++) {
        for (x = 0; x < (*dun)->width; x++) {
            room_delete(&(*dun)->room[y][x]);
        }
        free((*dun)->room[y]);
    }
    free((*dun)->room);
    free(*dun);
    *dun = NULL;
}

uint dungeon_width (Dungeon *dun)
{
    return dun->width;
}

uint dungeon_height (Dungeon *dun)
{
    return dun->height;
}

Room *dungeon_room (Dungeon *dun, uint x, uint y)
{
    if (x < dun->width && y < dun->height) {
        return dun->room[y][x];
    }
    return NULL;
}

uint dungeon_roomCount (Dungeon *dun)
{
    uint x, y, count = 0;
    for (y = 0; y < dun->height; y++) {
        for (x = 0; x < dun->width; x++) {
            count += room_type(dun->room[y][x]) != RT_EMPTY;
        }
    }
    return count;
}

void dungeon_clear (Dungeon *dun)
{
    uint x, y;
    for (y = 0; y < dun->height; y++) {
        for (x = 0; x < dun->width; x++) {
            room_clear(dun->room[y][x]);
        }
    }
}

void dungeon_generate (Dungeon *dun, uint seed)
{
    Fifo *fifo = fifo_new(8);
    Room *room = dun->room[dun->height-1][dun->width/2];
    uint rMin = dun->width * dun->height * 0.67;
    uint rMax = dun->width * dun->height * 0.85;
    uint nRoom;
    srand(seed);
    while (nRoom < rMin || nRoom > rMax) {
        dungeon_clear(dun);
        room_setType(room, RT_START);
        fifo_push(fifo, room);
        _dungeon_genBaseRoom (dun, fifo);
        nRoom = dungeon_roomCount(dun);
    }
    room_setDoor(room, DOWN, 0, 1);
}

void _dungeon_genBaseRoom (Dungeon *dun, Fifo *fifo)
{
    Room *room = (Room*)fifo_pop(fifo);
    if (room == NULL) {
        return;
    }
    room_generateDoor(room, fifo);
    _dungeon_genBaseRoom(dun, fifo);
}
