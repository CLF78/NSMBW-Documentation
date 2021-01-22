#pragma once
#include <common.h>
#include <dEffectBreakBase.h>

/* Settings: (Type << 8) | (VelocityChange & 3)

Types:
0 = Brick
1 = Stone
2 = Wood
3 = Question
4 = Used
5 = Red
6 = Used
7 = None (Unused)
8 = Final Battle

VelocityChange: (see velocities array for more details) */

class dEBT_Item1 {
	public:
		dEBT_Item1();	// 80092700
		~dEBT_Item1();	// 800910C0

		float x, y, z;
		float xVel, yVel, zVel;
		u8 _18, _19;
		u8 pad[2];
};

class dEBT_Item2 {
	public:
		dEBT_Item2();	// 80092710
		~dEBT_Item2();	// 80091040

		void *parent;
		void *child;	// Never used
};

class dEffectBreakTile_c : public dEffectBreakBase_c {
	public:
		TileRenderer renderers[4];
		dEBT_Item1 items1[4];

		u32 shardCount;
		u32 doesCycleField19;
		u32 typeMaybe;

		dEBT_Item2 items2[4];	// Used to link with the parent actor through dBaseLink

		// Values = (0x100 * Slot) + (0x10 * Row) + Column
		static u16 explosionTileNumbers[9][4]; // 802F06D8
		
		/* How it works:
		- First, the game picks a random number between 0 and 0x8000, and checks if it's odd or even
		- It then picks the float array based on that (array indexes 2 and 3 are therefore unused)
		- Then, for every block:
		* The first two floats are used as X and Y position offsets (with some other maths i cba to explain here)
		* The remaining floats are set as the shard's X and Y speed based on the VelocityChange flag in the settings
		* If the VelocityChange type is 2, 16.0 is added to the Y speed */
		static float explosionTileVelocities[4][4][10]; // 80311658

		virtual ~dEffectBreakTile_c(); // 80090F80

		virtual void init();	// 800909A0
		virtual void execute();	// 80090CF0
		virtual void draw();	// 80090ED0
		virtual void cleanup();	// 80090EE0
};
