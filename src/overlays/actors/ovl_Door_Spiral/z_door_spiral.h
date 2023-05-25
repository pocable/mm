#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include "global.h"

struct DoorSpiral;

typedef void (*DoorSpiralActionFunction)(struct DoorSpiral*, PlayState*);

#define DOORSPIRAL_GET_FC00(thisx) ((u16)(thisx)->params >> 0xA)

// TODO: Below figure out the bit mask and update to match abover
#define DOORSPIRAL_GET_SOME_FLAG(thisx) (((thisx)->params >> 8) & 3)
#define DOORSPIRAL_GET_SOME_FLAG_2(thisx) (((thisx)->params >> 7) & 1)

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ s8 unk145;
    /* 0x146 */ u8 unk146;
    /* 0x147 */ u8 unk147;
    /* 0x148 */ u8 unk148;
    /* 0x149 */ s8 unk149;
    /* 0x14A */ s8 unk14A;
    /* 0x14B */ s8 unk14B;
    /* 0x14C */ DoorSpiralActionFunction unk14C;
} DoorSpiral; // size = 0x150

#endif // Z_DOOR_SPIRAL_H
