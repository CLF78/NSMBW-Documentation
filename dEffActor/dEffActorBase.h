#pragma once
#include <common.h>

class dEffActorBase_c {
	public:
		// Constructor is inlined, use dEffActorMng to spawn any subclass
		virtual ~dEffActorBase_c(); // 800908F0

		virtual void cleanup(); // 80090960
		virtual void draw();    // 80090970
		virtual void execute(); // 80090980
		virtual void create();    // 80090990

		float x, y, z;
		float xVel, yVel, zVel;
		float xMaxVel, yMaxVel, zMaxVel;
		float xScale, yScale, zScale;

		s16 xRot, yRot, zRot;

		float yAccel;

		u32 _40;
		u32 settings;
		u32 countdownUntilDeletion;
		u8 associatedPlayer; // -1 if not associated to a player

		u32 willBeDeleted;
		LinkListEntry link;

	private:
		void addVectorToPosition(Vec3 *vec);    // 80092290
		void updateYVelocity();                 // 800922D0
};
