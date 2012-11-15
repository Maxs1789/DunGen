#include <stdio.h>
#include "dungeon.h"
#include "room.h"

void dungeon_print1 (Dungeon *dun);
void dungeon_print2 (Dungeon *dun);
void dungeon_printDetail (Dungeon *dun);

int main(int argc, char**argv)
{
    Dungeon *d;
    uint w = 4, h = 4, o = 0;
    if (argc >= 4) {
        o = atoi(argv[3]);
    }
    if (argc >= 3) {
        w = atoi(argv[1]);
        h = atoi(argv[2]);
    }
    d = dungeon_new(w, h);
    dungeon_generate(d, (uint)time(NULL));
    switch (o) {
    case 1: dungeon_print1(d); break;
    case 2: dungeon_printDetail(d); break;
    default: dungeon_print2(d);
    }
    dungeon_delete(&d);
    return 0;
}

void dungeon_print1 (Dungeon *dun)
{
    uint w = dungeon_width(dun);
    uint h = dungeon_height(dun);
    Room *r;
    uint x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            r = dungeon_room(dun, x, y);
            if (room_type(r) == RT_EMPTY) {
                printf("\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508");
                printf("\033[9D\033[1B");
                printf("\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508");
                printf("\033[9D\033[1B");
                printf("\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508");
                printf("\033[9D\033[1B");
                printf("\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508");
                printf("\033[9D\033[1B");
                printf("\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508\u2508");
                printf("\033[4A");
            } else {
                switch (room_doorCount(r, UP)) {
                case 0:
                    printf("\u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510");
                    break;
                case 1:
                    printf("\u250c\u2500\u2500\u2518 \u2514\u2500\u2500\u2510");
                    break;
                case 2:
                    printf("\u250c\u2518 \u2514\u2500\u2518 \u2514\u2510");
                    break;
                }
                printf("\033[9D\033[1B");
                switch (room_doorCount(r, LEFT)) {
                case 0: printf("\u2502       "); break;
                case 1: printf("\u2518       "); break;
                case 2: printf("\u2518       "); break;
                }
                switch (room_doorCount(r, RIGHT)) {
                case 0: printf("\u2502"); break;
                case 1: printf("\u2514"); break;
                case 2: printf("\u2514"); break;
                }
                printf("\033[9D\033[1B");
                switch (room_doorCount(r, LEFT)) {
                case 0: printf("\u2502   "); break;
                case 1: printf("    "); break;
                case 2: printf("\u2578   "); break;
                }
                if (room_type(r) == RT_START) {
                    printf("S   ");
                } else {
                    printf("    ");
                }
                switch (room_doorCount(r, RIGHT)) {
                case 0: printf("\u2502"); break;
                case 1: printf(" "); break;
                case 2: printf("\u257a"); break;
                }
                printf("\033[9D\033[1B");
                switch (room_doorCount(r, LEFT)) {
                case 0: printf("\u2502       "); break;
                case 1: printf("\u2510       "); break;
                case 2: printf("\u2510       "); break;
                }
                switch (room_doorCount(r, RIGHT)) {
                case 0: printf("\u2502"); break;
                case 1: printf("\u250c"); break;
                case 2: printf("\u250c"); break;
                }
                printf("\033[9D\033[1B");
                switch (room_doorCount(r, DOWN)) {
                case 0:
                    printf("\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518");
                    break;
                case 1:
                    printf("\u2514\u2500\u2500\u2510 \u250c\u2500\u2500\u2518");
                    break;
                case 2:
                    printf("\u2514\u2510 \u250c\u2500\u2510 \u250c\u2518");
                    break;
                }
                printf("\033[4A");
            }
        }
        printf("\033[4B\n");
    }
}

void dungeon_print2 (Dungeon *dun)
{
    uint w = dungeon_width(dun);
    uint h = dungeon_height(dun);
    Room *r;
    uint x, y, i;

    for (y = 0; y < h; y++) {
        for (i = 0; i < 3; i++) {
            for (x = 0; x < w; x++) {
                r = dungeon_room(dun, x, y);
                if (room_type(r) == RT_EMPTY) {
                    printf("   ");
                } else {
                    if (i == 0) {
                        printf(" %c ", room_doorCount(r, UP) ? '|' : ' ');
                    } else if (i == 1) {
                        printf("%c:", room_doorCount(r, LEFT) ? '-' : ' ');
                        printf("%c", room_doorCount(r, RIGHT) ? '-' : ' ');
                    } else {
                        printf(" %c ", room_doorCount(r, DOWN) ? '|' : ' ');
                    }
                }
            }
            printf("\n");
        }
    }
}

void dungeon_printDetail (Dungeon *dun)
{
    uint w = dungeon_width(dun);
    uint h = dungeon_height(dun);
    Room *r;
    uint x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            r = dungeon_room(dun, x, y);
            if (room_type(r) != RT_EMPTY) {
                printf("room[%02d;%02d]\n", x, y);
                printf("-type: %d\n", room_type(r));
                printf("-doors: ");
                printf("R[%d", room_door(r, RIGHT, 0));
                printf("%d] ", room_door(r, RIGHT, 1));
                printf("D[%d", room_door(r, DOWN, 0));
                printf("%d] ", room_door(r, DOWN, 1));
                printf("L[%d", room_door(r, LEFT, 0));
                printf("%d] ", room_door(r, LEFT, 1));
                printf("U[%d", room_door(r, UP, 0));
                printf("%d]\n", room_door(r, UP, 1));
            }
        }
    }
}
