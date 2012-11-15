#include "room.h"
#include "common.h"
#include "dungeon.h"
#include "util/fifo.h"

void _room_attach (Room *room, Room *nextRoom, Direction dir);

/** @see room.h*/
typedef struct s_room {
    uint x;             /**< Position en x de la salle. */
    uint y;             /**< Position en y de la salle. */
    RoomType type;      /**< Type de la salle. */
    uint door[8];       /**< Zones des portes de la salle. */
    Dungeon *dungeon;   /**< Donjon de la salle. */
} Room;

Room *room_new (Dungeon *dungeon, uint x, uint y)
{
    Room *room = (Room*)malloc(sizeof(Room));
    room->x = x;
    room->y = y;
    room->dungeon = dungeon;
    room_clear(room);
    return room;
}

void room_delete (Room **room)
{
    free(*room);
    *room = NULL;
}

uint room_x (Room *room)
{
    return room->x;
}

uint room_y (Room *room)
{
    return room->y;
}

uint room_door (Room *room, Direction dir, uint door)
{
    if (door < 2) {
        return room->door[(dir * 2) + door];
    }
    return 0;
}

uint room_doorCount (Room *room, Direction dir)
{
    dir *= 2;
    return (room->door[dir] > 0) + (room->door[dir+1] > 0);
}

Dungeon *room_dungeon (Room *room)
{
    return room->dungeon;
}

RoomType room_type (Room *room)
{
    return room->type;
}

Room *room_next (Room *room, Direction dir)
{
    uint x = room->x, y = room->y;
    if (dir == LEFT) {
        if (x == 0) {
            return NULL;
        }
        x--;
    } else if (dir == UP) {
        if (y == 0) {
            return NULL;
        }
        y--;
    } else if (dir == RIGHT) {
        x++;
    } else {
        y++;
    }
    return dungeon_room(room->dungeon, x, y);
}

void room_setDoor (Room *room, Direction dir, uint door, uint zone)
{
    if (door < 2) {
        room->door[(dir * 2) + door] = zone;
    }
}

void room_setType (Room *room, RoomType type)
{
    room->type = type;
}

void room_clear (Room *room)
{
    uint i;
    room->type = RT_EMPTY;
    for (i = 0; i < 8; i++) {
        room->door[i] = 0;
    }
}

void room_generateDoor (Room *room, Fifo *fifo)
{
    Room *nextRoom;
    Direction dir, opDir;
    for (dir = RIGHT; dir <= UP; dir++) {
        nextRoom = room_next(room, dir);
        if (nextRoom == NULL) {
            _room_attach(room, NULL, dir);
        } else {
            room->door[dir*2] = rand() % 3 == 0;/* chance porte1 */
            room->door[(dir*2)+1] = rand() % 5 == 0;   /* porte2 */
            if (nextRoom->type == RT_EMPTY) {
                if (room_doorCount(room, dir)) {
                    fifo_push(fifo, nextRoom);
                    nextRoom->type = RT_SIMPLE;
                }
            } else {
                opDir = opDir(dir);        /* chances de boucler */
                if (room_doorCount(nextRoom, opDir) || rand() % 4 == 0) {
                    _room_attach(room, nextRoom, dir);
                } else {
                    _room_attach(nextRoom, room, opDir);
                }
            }
        }
    }
}

void _room_attach (Room *room, Room *nextRoom, Direction dir)
{
    if (nextRoom == NULL || nextRoom->type == RT_EMPTY) {
        room->door[dir*2]     = 0;
        room->door[(dir*2)+1] = 0;
    } else {
        Direction opDir = opDir(dir);
        room->door[dir*2] = nextRoom->door[(opDir*2)+1];
        room->door[(dir*2)+1] = nextRoom->door[opDir*2];
    }
}
