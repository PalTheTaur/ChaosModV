/*
    Effect by Last0xygen, modified
*/

#include <stdafx.h>

#include "Effects/Register/RegisterEffect.h"
#include "Util/Peds.h"

#define PI 3.14159265

static void OnStart()
{
	static const Hash bikerHash  = "G_M_Y_Lost_03"_hash;
	static const Hash weaponHash = "weapon_dbshotgun"_hash;
	static const Hash vehHash    = "DAEMON"_hash;

	Ped playerPed                = PLAYER_PED_ID();

	Vector3 playerPos            = GET_ENTITY_COORDS(playerPed, false);

	float heading = GET_ENTITY_HEADING(IS_PED_IN_ANY_VEHICLE(playerPed, false) ? GET_VEHICLE_PED_IS_IN(playerPed, false)
	                                                                           : playerPed);

	float x_pos   = sin((360 - heading) * PI / 180) * 10;
	float y_pos   = cos((360 - heading) * PI / 180) * 10;

	Vehicle veh   = CreatePoolVehicle(vehHash, playerPos.x - x_pos, playerPos.y - y_pos, playerPos.z, heading);
	SET_VEHICLE_ENGINE_ON(veh, true, true, false);

	Vector3 vel = GET_ENTITY_VELOCITY(playerPed);
	SET_ENTITY_VELOCITY(veh, vel.x, vel.y, vel.z);

	Ped ped = CreateHostilePed(bikerHash, weaponHash);
	CurrentEffect::SetEffectSoundPlayOptions({ .PlayType = EffectSoundPlayType::FollowEntity, .Entity = ped });

	SET_PED_INTO_VEHICLE(ped, veh, -1);
}

// clang-format off
REGISTER_EFFECT(OnStart, nullptr, nullptr, 
    {
        .Name = "Spawn Biker",
        .Id = "peds_spawn_biker",
        .EffectGroupType = EffectGroupType::SpawnEnemy
    }
);
