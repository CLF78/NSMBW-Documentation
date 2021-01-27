#pragma once
#include <common.h>
#include <dEffActorBase.h>

/* Settings: ((Type & 3) << 4) | (SomeFlag & 1)

Types:
0/3 = Small Ice Piece
1 = Giant Ice Block Piece
2 = Big Ice Piece

SomeFlag: Uses a different set of velocities if set to 1 */

class dEffActorIce_c : public dEffActorBase_c {
	public:
		mAllocator_c allocator;
		nw4r::g3d::ResFile *resfile;

		m3d::smdl_c models[4];
		Vec3 positions[4];
		Vec3 velocities[4];
		S16Vec rotations[4];

		virtual ~dEffActorIce_c(); // 80091790

		virtual void create();  // 80091100
		virtual void execute(); // 80091170
		virtual void draw();    // 800911D0
		virtual void cleanup(); // 80091230

		// Model data
		static const char* EffActorIceARCList[4];      // 803116A0
		static const char* EffActorIceBRRESList[4];    // 803116E0
		static const char* EffActorIceMDLList[4*3];    // 80311778

		// Velocity data
		// The game writes the speeds in the setupVelocities function (but only the ones for the X and Y axes, the Z ones are written directly in the class)
		static bool areIceSpeedsWritten;                // 8042A1B8
		static float explosionIceVelocities[2*4*2];     // 80356360

	private:
		void loadModels();   // 800912A0
		void updateModels(); // 800913A0

		void moveShards(); // 80091660

		void setupPositions();  // 800914C0
		void setupVelocities(); // 80091520
		void setupRotations();  // 80091620
};
