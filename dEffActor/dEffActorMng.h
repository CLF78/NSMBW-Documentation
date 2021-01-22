#pragma once
#include <common.h>
#include <dEffActorBase.h>

class dEffActorMng_c {
	public:
		dEffActorMng_c();    // 80092300
		~dEffActorMng_c();   // 80092310

		u16 count; // Only incremented/decremented once per class

		static dEffActorMng_c *instance; // 8042A1C8
		static LinkList effectActorList; // 8042A1D0

		void execute(); // 800923D0
		void draw();    // 80092480

		// Use the below functions to spawn shards, NOT the other classes
		// See the subclasses for more information on the settings
		bool spawnBlockShard(Vec3 *pos, u32 settings, u8 playerID);     // 800925F0
		bool spawnIceShard(Vec3 *pos, u32 settings, u8 playerID);       // 80092720
		bool spawnModelShard(Vec3 *pos, u32 settings, u8 playerID);     // 80092830
		bool spawnLiquidEffect(Vec3 *pos, u32 settings, u8 playerID);   // 80092830
		bool spawnChompShard(Vec3 *pos, u32 settings, u8 playerID);     // 80092AD0

	private:
		bool prepare(dEffActorBase_c *ef, Vec3 *pos, u32 settings, u8 playerID); // 80092370

		void cleanup();     // 800924E0
		void cleanupAll();  // 80092570
};
