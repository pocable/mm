/*
 * File: z_door_spiral.c
 * Overlay: ovl_Door_Spiral
 * Description: Staircase
 */

#include "z_door_spiral.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_hakugin_obj/object_hakugin_obj.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"
#include "objects/object_ikninside_obj/object_ikninside_obj.h"
#include "objects/object_danpei_object/object_danpei_object.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DoorSpiral*)thisx)

void DoorSpiral_Init(Actor* thisx, PlayState* play);
void DoorSpiral_Destroy(Actor* thisx, PlayState* play);
void DoorSpiral_Update(Actor* thisx, PlayState* play);
void DoorSpiral_Draw(Actor* thisx, PlayState* play);

void func_809A2B60(DoorSpiral *this, DoorSpiralActionFunction function);
void func_809A2DB0(DoorSpiral* this, PlayState *play);
void func_809A3098(DoorSpiral* this, PlayState *play);
s32 func_809A2EA0(DoorSpiral *arg0, PlayState *arg1);
// u8 func_809A2BF8(PlayState *play);
s32 func_809A2B70(DoorSpiral* this, PlayState *play);
void func_809A2FF8(DoorSpiral* this, PlayState *play);

f32 func_809A2E08(PlayState *play, Actor *actor, f32 arg2, f32 arg3, f32 arg4);

/*
const ActorInit Door_Spiral_InitVars = {
    ACTOR_DOOR_SPIRAL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorSpiral),
    (ActorFunc)DoorSpiral_Init,
    (ActorFunc)DoorSpiral_Destroy,
    (ActorFunc)DoorSpiral_Update,
    (ActorFunc)DoorSpiral_Draw
};
*/

typedef struct {
    /* 0x0 */ s16 objectId;
    /* 0x2 */ u8 index1;
    /* 0x3 */ u8 index2;
} SpiralObjectInfo; // size = 0x4

extern UNK_TYPE D_809A3250;
extern UNK_TYPE D_809A3308;
extern UNK_TYPE D_809A32EC;
extern SpiralObjectInfo D_809A32D0[];

void func_809A2B60(DoorSpiral *this, DoorSpiralActionFunction function) {
    this->unk14C = function;
    this->unk14A = 0;
}

s32 func_809A2B70(DoorSpiral* this, PlayState *play) {
    SpiralObjectInfo *z = &D_809A32D0[this->unk147];
    this->unk148 = z->index1;
    if ((this->unk148 == 7) || ((this->unk148 == 2) && (play->roomCtx.curRoom.enablePosLights != 0))) {
        if (this->unk148 == 2) {
            this->unk148 = 3;
        }
        this->actor.flags |= 0x10000000;
    }
    func_809A2B60(this, func_809A2FF8);
    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2BF8.s")
// u8 func_809A2BF8(PlayState *arg0) {
//     s16 *var_v0;
//     s32 var_v1_2;
//     u8 var_v1;

//     var_v0 = &D_809A32EC;
//     var_v1_2 = 0;
// loop_1:
//     if (*var_v0 != arg0->sceneId) {
//         var_v1_2 += 1;
//         var_v0 += 4;
//         if (var_v1_2 != 7) {
//             goto loop_1;
//         }
//     }
//     if (var_v1_2 < 7) {
//         var_v1 = var_v0->unk2;
//     } else {
//         var_v1 = 0;
//         if (Object_GetIndex(arg0 + 0x17D88, 3) >= 0) {
//             var_v1 = 1;
//         }
//     }
//     return var_v1;
// }


void DoorSpiral_Init(Actor *thisx, PlayState *play) {
    DoorSpiral *this = THIS;
    s32 transitionActorId = DOORSPIRAL_GET_FC00(thisx);
    s8 temp_v0_2;
    
    if (this->actor.room != play->doorCtx.transitionActorList[transitionActorId].sides[0].room) {
        Actor_Kill(&this->actor);
    }else{
        Actor_ProcessInitChain(&this->actor, &D_809A3308);
        this->unk145 = DOORSPIRAL_GET_SOME_FLAG(thisx);
        this->unk146 = DOORSPIRAL_GET_SOME_FLAG_2(thisx);
        this->unk147 = func_809A2BF8(play);
        temp_v0_2 = Object_GetIndex(&play->objectCtx, D_809A32D0[this->unk147].objectId);
        this->unk149 = temp_v0_2;
        if (temp_v0_2 < 0) {
            Actor_Kill(&this->actor);
        }else{
            func_809A2B60(this, func_809A2DB0);
            Actor_SetFocus(&this->actor, 60.0f);
        }
    }
}

void DoorSpiral_Destroy(Actor *thisx, PlayState *play) {
    s32 transitionActorId = DOORSPIRAL_GET_FC00(thisx);
    play->doorCtx.transitionActorList[transitionActorId].id =
        -play->doorCtx.transitionActorList[transitionActorId].id;
}

void func_809A2DB0(DoorSpiral* this, PlayState *play) {
    if (Object_IsLoaded(&play->objectCtx, this->unk149) != 0) {
        this->actor.objBankIndex = this->unk149;
        func_809A2B70(this, play);
    }
}

f32 func_809A2E08(PlayState *play, Actor *actor, f32 arg2, f32 arg3, f32 arg4) {
    Player *player = GET_PLAYER(play);
    Vec3f modpos;
    Vec3f sp1C;

    modpos.x = player->actor.world.pos.x;
    modpos.y = player->actor.world.pos.y + arg2;
    modpos.z = player->actor.world.pos.z;

    Actor_OffsetOfPointInActorCoords(actor, &sp1C, &modpos);
    if ((arg3 < fabsf(sp1C.x)) || (arg4 < fabsf(sp1C.y))) {
        return 3.4028235e+38;
    }
    return sp1C.z;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2EA0.s")
// s32 func_809A2EA0(DoorSpiral *arg0, PlayState *arg1) {
//     Actor *sp24;
//     f32 temp_fv0;
//     f32 var_ft0;
//     f32 var_ft3;
//     s16 var_v0;
//     s16 var_v1;
//     u8 temp_t0;
//     u8 temp_t1;
//     void *temp_v0;

//     sp24 = arg1->actorCtx.actorLists[2].first;
//     if (Player_InCsMode(arg1) == 0) {
//         temp_v0 = (arg0->unk148 * 0x10) + &D_809A3250;
//         temp_t0 = temp_v0->unkE;
//         var_ft0 = (f32) temp_t0;
//         if ((s32) temp_t0 < 0) {
//             var_ft0 += 4294967296.0f;
//         }
//         temp_t1 = temp_v0->unkF;
//         var_ft3 = (f32) temp_t1;
//         if ((s32) temp_t1 < 0) {
//             var_ft3 += 4294967296.0f;
//         }
//         temp_fv0 = func_809A2E08(arg1, &arg0->actor, 0.0f, var_ft0, var_ft3);
//         if (fabsf(temp_fv0) < 64.0f) {
//             var_v0 = sp24->shape.rot.y - arg0->actor.shape.rot.y;
//             if (temp_fv0 > 0.0f) {
//                 var_v0 = 0x8000 - var_v0;
//             }
//             var_v1 = var_v0;
//             if (var_v0 < 0) {
//                 var_v1 = -var_v0;
//             }
//             if (var_v1 < 0x3000) {
//                 if (temp_fv0 >= 0.0f) {
//                     return (s32) 1.0f;
//                 }
//                 return (s32) -1.0f;
//             }
//             goto block_14;
//         }
//         goto block_14;
//     }
// block_14:
//     return 0;
// }

void func_809A2FF8(DoorSpiral* this, PlayState *play) {
    Player *player;
    u32 index;

    if (this->unk144) {
        func_809A2B60(this, func_809A3098);
    }else if (func_809A2EA0(this, play) != 0) {
        player = GET_PLAYER(play);
        player->doorType = PLAYER_DOORTYPE_STAIRCASE;
        player->doorDirection = this->unk146;
        player->doorActor = &this->actor;
        index = DOORSPIRAL_GET_FC00(&this->actor);
        player->doorNext = (play->doorCtx.transitionActorList[index].params >> 0xA);
        func_80122F28(player);
    }
}

void func_809A3098(DoorSpiral* this, PlayState *play) {
    Player *player = GET_PLAYER(play);

    if (!(player->stateFlags1 & 0x20000000)) {
        func_809A2B60(this, func_809A2DB0);
        this->unk144 = 0;
    }
}

void DoorSpiral_Update(Actor *thisx, PlayState *play) {
    DoorSpiral *this = THIS;
    Player *player = GET_PLAYER(play);

    if (!(player->stateFlags1 & 0x100004C0) || (this->unk14C == func_809A2DB0)) {
        this->unk14C(this, play);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Draw.s")
// void DoorSpiral_Draw(Actor *thisx, PlayState *play) {
//     void *sp1C;
//     GraphicsContext *sp24;
//     void *sp2C;
//     GraphicsContext *temp_a0;
//     void *temp_a3;
//     void *temp_v0;
//     void *temp_v0_2;
//     DoorSpiral *this = (DoorSpiral *) thisx;

//     if (this->unk149 == this->actor.objBankIndex) {
//         temp_a3 = (this->unk148 * 0x10) + &D_809A3250;
//         if (*(temp_a3 + (this->unk146 * 4)) != 0) {
//             temp_a0 = play->state.gfxCtx;
//             sp2C = temp_a3;
//             sp24 = temp_a0;
//             func_8012C28C(temp_a0);
//             temp_v0 = sp24->polyOpa.tha.head;
//             sp24->polyOpa.tha.head = temp_v0 + 8;
//             *temp_v0 = 0xDA380003;
//             sp2C = temp_a3;
//             sp1C = temp_v0;
//             sp1C->unk4 = Matrix_NewMtx(play->state.gfxCtx);
//             temp_v0_2 = sp24->polyOpa.tha.head;
//             sp24->polyOpa.tha.head = temp_v0_2 + 8;
//             temp_v0_2->unk0 = 0xDE000000;
//             temp_v0_2->unk4 = (s32) *(temp_a3 + (this->unk146 * 4));
//         }
//     }
// }
