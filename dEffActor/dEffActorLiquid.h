#pragma once
#include <common.h>
#include <dEffActorBase.h>

/* Settings: ((Layer & 1) << 0x10) | (Type & 0xF)

Types (no idea of the differences):
0/1/2 = Water
3/4/5 = Lava
6/7 = Poison

Layer: 0 = Layer 1, 1 = Layer 2 */

class dEffActorLiquid_c : public dEffActorBase_c {
	public:
		u32 type;
		u32 layer;
		EGG::Effect effect;

		static const char* EffActorLiquidEfList[8]; // 803118C8

		virtual ~dEffActorLiquid_c(); // 80092200

		virtual void create();  // 80091F60
		virtual void execute(); // 80091FB0
		virtual void draw();    // 80092010
		virtual void cleanup(); // 80092020

	private:
		bool spawnEffect();     // 80092030
		void checkPosition();   // 80092150
};
