#pragma once
#include <common.h>

// Data gently provided by Grop. Thanks man!

/*
The game uses 2 random number generators, both initialised with the same seed value:
- The first one is used for things that affect movement and gameplay
- The other one is only used for visual effects, such as tile randomisation.

The initial value for the randomness (seed) is calculated as follows (by the function at 800D9850):
- First, an array of 128 bytes is created.
- The first 8 bytes of data are the number of ticks the Wii has been powered on.
- The next 22 bytes come from somewhere deeper in the operating system internals, not sure if/to what extent they can be controlled.
- Then, 2 null bytes follow.
- Next, it goes through all 4 controllers sequentially and for each of them, it dumps:
* 12 bytes that might be the rotation of the controller in all 3 axes.
* 8 bytes that represent the X and Y coordinates the controller points to.
* 4 bytes that represent the distance between the controller and the sensor bar.
- The game then does a CRC32b checksum over the array, which will be the final seed.
*/

class dRandom_c {
	public:
		static void init(); // 800B2E70

		// NOTE: Functions marked with "_2" are identical, and are just present for completion purposes.

		//////////////////
		// Using "seed" //
		//////////////////

		static void setSeed(u32 seed);	// 800B2EB0
		static u32 getSeed();			// 800B2EC0

		static u32 getInt(u32 max);		// 800B2EE0
		static u32 getInt_2(u32 max);	// 800B2ED0

		static float getFloat();	// 800B2EF0
		static float getFloat_2();	// 800B2F00
		static float getFloat_3();	// 800B2F50

		static float getFloatMultiplier(float multiplier);			// 800B2F10
		static float getFloatMultiplierTimes16(float multiplier);	// 800B2F60

		/////////////////////
		// Using "seedAlt" //
		/////////////////////

		static void setAltSeed(u32 seed); // 801614C0

		// This one apparently doesn't exist, so i made it.
		static u32 getAltSeed() {
			return seedAlt;
		}

		// This is used for tilesets
		static u16 getAltShort(u32 max); // 801614E0

		static float getAltFloat();								// 801614D0
		static float getAltFloatMultiplier(float multiplier);	// 80161540

	private:
		static u32 generateInitialSeed(); // 800D9850

		static u32 seed;	// 8042A224
		static u32 seedAlt;	// 8042A670

		static u32 getIntWithSeed(u32 *seed, u32 max); // 801615A0

		static float getFloatWithSeed(u32 *seed);	// 801615D0
		static float getFloatWithSeed_2(u32 *seed);	// 80161620
};
