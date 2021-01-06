#include <common.h>

// Class RE'd by Grop

class TimeKeeper {
	public:
		void *vtable; // 8031B358

		u32 timePlusFFFTimes40000;
		u16 startingTime;
		u8 isAmbush;
		u8 isTimeLessThan100;
		u8 isPaused;

		static TimeKeeper* instance; // 8042A350

		TimeKeeper(u32 *buffer, u32 initialTime);	// 800E38E0
		virtual ~TimeKeeper();						// 800E3910

		void setTime(u32 time);	// 800E3A00 - Updates the u32. Maybe you need to manually set isTimeLessThan100...
		void tick();			// 800E3A20 - Updates the display and speeds up the music if needed.

		void handleTimeUp(); // 800E3B50
};
