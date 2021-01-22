#pragma once
#include <common.h>
#include <dEffectBreakBase.h>

class dEffectBreakMgr_c {
	public:
		dEffectBreakMgr_c();    // 80092300
		~dEffectBreakMgr_c();   // 80092310

		u16 count; // Only incremented/decremented once per class

		static dEffectBreakMgr_c *instance; // 8042A1C8
		static LinkList effectBreakList;    // 8042A1D0

		void execute(); // 800923D0
		void draw();    // 80092480

		// Use the below functions to spawn shards, NOT the other classes
		// See the subclasses for more information on the settings
		bool spawnBlockShard(Vec3 *pos, u32 settings, u8 playerID);     // 800925F0
		bool spawnIceShard(Vec3 *pos, u32 settings, u8 playerID);       // 80092720
		bool spawnModeledShard(Vec3 *pos, u32 settings, u8 playerID);   // 80092830
		bool spawnLiquidEffect(Vec3 *pos, u32 settings, u8 playerID);   // 80092830
		bool spawnChompShard(Vec3 *pos, u32 settings, u8 playerID);     // 80092AD0

	private:
		bool prepare(dEffectBreakBase_c *ef, Vec3 *pos, u32 settings, u8 playerID); // 80092370

		void cleanup();     // 800924E0
		void cleanupAll();  // 80092570
};
