#ifndef Z_OBJ_MAKEOSHIHIKI_H
#define Z_OBJ_MAKEOSHIHIKI_H

#include "global.h"

struct ObjMakeoshihiki;

#define OBJMAKEOSHIHIKI_GET_PATHLISTINDEX(thisx) (((thisx)->params >> 7) & 0x7F)
#define OBJMAKEOSHIHIKI_GET_SWITCHFLAG_1(thisx) ((thisx)->home.rot.z & 0x7F)
#define OBJMAKEOSHIHIKI_GET_SWITCHFLAG_2(thisx) ((thisx)->params & 0x7F)

typedef struct ObjMakeoshihiki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Vec3s* pathPoints;
    /* 0x148 */ s32 pathCount;
} ObjMakeoshihiki; // size = 0x14C

#endif // Z_OBJ_MAKEOSHIHIKI_H
