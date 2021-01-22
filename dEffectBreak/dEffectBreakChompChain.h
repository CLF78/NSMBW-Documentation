#pragma once
#include <common.h>
#include <dEffectBreakBase.h>

// This one is used for when the player ground pounds Chain Chomp poles. No settings here...
class dEffectBreakChompChain_c : public dEffectBreakBase_c {
	public:
		mAllocator_c allocator;
		nw4r::g3d::ResFile *resfile;

		m3d::smdl_c models[6];
		Vec3 positions[6];
		Vec3 velocities[6];
		S16Vec rotations[6];

		// Model data
		static const char* EffectBreakChainMDLList[2][]; // 80427D28

		// Velocity data
		// The game writes the speeds in the setupVelocities function (but only the ones for the X and Y axes, the Z ones are written directly in the class)
		static bool areChainSpeedsWritten;           // 8042A1C0
		static float explosionChainVelocities[6][2]; // 803563A0

		virtual ~dEffectBreakChompChain_c(); // 80091E90

		virtual void init();    // 80091860
		virtual void execute(); // 800918D0
		virtual void draw();    // 80091930
		virtual void cleanup(); // 80091990

	private:
		void loadModels();   // 800919A0
		void updateModels(); // 80091A80

		void moveShards(); // 80091D60

		void setupPositions();  // 80091BA0
		void setupVelocities(): // 80091C10
		void setupRotations();  // 80091D10
};
