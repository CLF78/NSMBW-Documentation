#pragma once
#include <common.h>
#include <dEffectBreakBase.h>

/* Settings: ((Type << 8) & FF) | (VelocityChange & 3)

Types:
- 0 = Giant Brick Block
- 1/2 = Wooden Box
- 3 = Icicle
- 4/5 = Volcano Rocks
- 6 = Poltergeist Item
- 7/8/9 = Kamek Blocks

VelocityChange = (see below) */

class dEBBM_Item {
	public:
		dEBBM_Item();   // 800929E0
		~dEBBM_Item();  // 800908B0

		float x, y, z;
		float xVel, yVel, zVel;
		u32 unk;
};

class dEffectBreakMdl_c : public dEffectBreakBase_c {
	public:
		mAllocator_c allocator;
		nw4r::g3d::ResFile *resfile;

		m3d::mdl_c models[4];
		m3d::anmClr_c anims[4];
		dEBBM_Item items[4];
		Vec3 positionsMaybe[4];

		u32 shardCount;
		u32 unk;
		u32 type;

		// Model data
		static const char* EffectBreakMdlARCList[10][];      // 803112F8
		static const char* EffectBreakMdlBRRESList[10][];    // 803113B8
		static const char* EffectBreakMdlMDLList[10][4][];   // 80311568
		static BufferOption EffectBreakMdlBufferOptions[10]; // 802F0430

		// Velocity data
		// The game writes positions and velocities in the init function in an utterly messy way...
		static bool areModelOffsetsWritten;         // 8042A1B0
		static bool areModelSpeedsWritten;          // 8042A1B1
		static float explosionMdlXYOffsets[4][2];   // 80356300 (one set of 2 for each piece)
		static float explosionMdlVelocities[4][4];  // 80356320 (uses VelocityChange flag to determine the correct index)

		virtual ~dEffectBreakMdl_c(); // 800907D0

		virtual void init();    // 8008FE30
		virtual void execute(); // 80090230
		virtual void draw();    // 800903C0
		virtual void cleanup(); // 80090430

	private:
		void loadModels();      // 80090600
		void updateModels();    // 80090440

		void runEffects();  // 80090590 (calls stuff to render some effects for shard types 4 and 5)
};
