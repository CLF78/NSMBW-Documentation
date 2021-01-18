#pragma once
#include <common.h>
#include <save/save.h>

// SaveHandler state values
#define SAVEHANDLER_STATE_PERMCHECK     1
#define SAVEHANDLER_STATE_SPACECHECK    2
#define SAVEHANDLER_STATE_DELETE        3
#define SAVEHANDLER_STATE_WRITE         4
#define SAVEHANDLER_STATE_LOAD          5
#define SAVEHANDLER_STATE_RETURN        6

class SaveHandler : public EGG::Thread {
	public:
		SaveHandler(OSPriority prio, EGG::Heap *heap);  // 800CED00
		virtual ~SaveHandler();                         // 800CEEA0

		u8 unknown[0x10];       // 0x40 (could be an instance of nw4r::ut:Link)
		void *vtable2;          // 0x50
		OSMutex mutex;          // 0x54
		OSThreadQueue queue;    // 0x6C
		u32 CurrentState;       // 0x74
		u32 CurrentError;       // 0x78
		u32 DoesSaveFileExist;  // 0x7C

		static void createOnHeap(EGG::Heap *heap);  // 800CFBA0
		static SaveHandler *instance;               // 8042A298

		virtual void run(); // 800CFAC0

		// These do stuff with mutex, they're almost identical
		bool sub_800CEF10();
		bool sub_800CF170(SaveFile *savefile);
		bool sub_800CF9E0();

	private:
		void ErrorHandling(int errorCode); // 800CFC20

		/* All called by the run function. THESE MESS WITH NAND, SO AVOID USING THEM. */
		void CheckIfSaveFileExistsOnNAND(); // 800CEF80

		void CheckNANDSpace(); // 800CF0D0

		int WriteSaveToNAND(); // 800CF200

		bool DoBannerStuff();                       // 800CF380
		void CreateBannerFile(NandHandle *handle);  // 800CF500

		bool LoadSaveFromNAND();        // 800CF680
		bool DoesSaveMatchChecksum();   // 800CF910

		void DeleteSaveFromNAND(); // 800CFA50

		// Different buffer than the SaveFile instance
		SaveFile *returnSaveFileBuffer(); // 800CFCA0
};

// Convenience functions
inline SaveHandler *GetSaveHandler() {
	return SaveHandler::instance;
}
