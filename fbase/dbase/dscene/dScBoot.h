#pragma once
#include <common.h>
#include <fbase/dbase/dscene/dScene.h>
#include <fbase/dbase/dLogoScreen.h>

// dScBoot_c handles most of the actions at boot. It creates the wii strap screen and
// the controllerInformation screen, it loads the rels and starts the title screen,
// initializes dRandom_c/dRes_c/GameMgr and does many other things.

class dScBoot_c : public dScene_c {
	public:
		dStateWrapper_c<dScBoot_c> wrappers[2]; // Second wrapper is the main state

		void *yesNoWindow;
		dLogoScreen_c *wiiStrap;
		void *selectCursor;
		void *controllerInformation;

		u8 saveCreationSuccessful;  // Unused if savefile exists on NAND
		u8 fadeType;                // 0 = Fade Out, 1 = Fade In
		u8 hasCISoundBeenLoaded;    // Set to 1 when the button sfx for controllerInformation has been loaded (2 button prompt will not appear until this is 1)

		u8 doNotUseAlternateState;  // Other state will be executed if this is 0 (which seems to be always true)
		u8 unused;                  // Initialized to 0 and used in some reset states, but i haven't seen it change value yet
		u8 unused2;                 // Set to 1 at the beginning of ButtonInputWait, but never read again

		u32 maximumWaitingTime, minimumWaitingTime; // Max and min time between fade in and fade out on both wiiStrap and controllerInformation

		dScBoot_c();    // 8015C270

		// Class functions
		virtual int onCreate();         // 8015C550
		virtual int onDelete();         // 8015C600
		virtual int onExecute();        // 8015C6E0

		virtual int beforeExecute();    // 8015C6A0

		virtual int onDraw(); // 8015C760

		virtual void deleteReady(); // 8015C5F0
		virtual ~dScBoot_c();       // 8015C4B0

		// Static stuff
		static dScBoot_c *build();  // 8015BA70
		static dScBoot_c *instance; // 8042A620

		// States
		static State StateID_ResetWait;         // 80377708 (initial state 2)
		virtual void beginState_ResetWait();    // 8015C770
		virtual void executeState_ResetWait();  // 8015C7C0
		virtual void endState_ResetWait();      // 8015C840 (nullsub)

		static State StateID_ResetFadeOut;          // 80377748
		virtual void beginState_ResetFadeOut();     // 8015C850
		virtual void executeState_ResetFadeOut();   // 8015C8B0
		virtual void endState_ResetFadeOut();       // 8015CA10

		static State StateID_ResetFadeIn;           // 80377788
		virtual void beginState_ResetFadeIn();      // 8015CB90
		virtual void executeState_ResetFadeIn();    // 8015CBF0
		virtual void endState_ResetFadeIn();        // 8015CC60

		static State StateID_FadeOutWait;           // 803777C8 (initial state 1)
		virtual void beginState_FadeOutWait();      // 8015CDF0 (nullsub)
		virtual void executeState_FadeOutWait();    // 8015CE00
		virtual void endState_FadeOutWait();        // 8015CE70 (nullsub)

		static State StateID_WiiStrapKeyWait;           // 80377808
		virtual void beginState_WiiStrapKeyWait();      // 8015CE80
		virtual void executeState_WiiStrapKeyWait();    // 8015CED0
		virtual void endState_WiiStrapKeyWait();        // 8015CF10 (nullsub)

		static State StateID_WiiStrapDispEndWait;           // 80377848
		virtual void beginState_WiiStrapDispEndWait();      // 8015CF20 (nullsub)
		virtual void executeState_WiiStrapDispEndWait();    // 8015CF30
		virtual void endState_WiiStrapDispEndWait();        // 8015CFB0 (nullsub)

		static State StateID_WiiStrapFadeOut;           // 80377888
		virtual void beginState_WiiStrapFadeOut();      // 8015CFC0
		virtual void executeState_WiiStrapFadeOut();    // 8015D010
		virtual void endState_WiiStrapFadeOut();        // 8015D0A0

		static State StateID_ControllerInformationFadeIn;           // 803778C8
		virtual void beginState_ControllerInformationFadeIn();      // 8015D0B0
		virtual void executeState_ControllerInformationFadeIn();    // 8015D100
		virtual void endState_ControllerInformationFadeIn();        // 8015D170

		static State StateID_ControllerInformationSoundWait;        // 80377908
		virtual void beginState_ControllerInformationSoundWait();   // 8015D1E0
		virtual void executeState_ControllerInformationSoundWait(); // 8015D230
		virtual void endState_ControllerInformationSoundWait();     // 8015D280 (nullsub)

		static State StateID_ControllerInformationKeyWait;          // 80377948
		virtual void beginState_ControllerInformationKeyWait();     // 8015D290 (nullsub)
		virtual void executeState_ControllerInformationKeyWait();   // 8015D2A0
		virtual void endState_ControllerInformationKeyWait();       // 8015D2F0 (nullsub)

		static State StateID_ControllerInformationDispEndWait;          // 80377988
		virtual void beginState_ControllerInformationDispEndWait();     // 8015D300 (nullsub)
		virtual void executeState_ControllerInformationDispEndWait();   // 8015D310
		virtual void endState_ControllerInformationDispEndWait();       // 8015D3C0 (nullsub)

		static State StateID_NandCommandEndWait;        // 803779C8
		virtual void beginState_NandCommandEndWait();   // 8015D3D0 (nullsub)
		virtual void executeState_NandCommandEndWait(); // 8015D3E0
		virtual void endState_NandCommandEndWait();     // 8015D460 (nullsub)

		static State StateID_ExistFileCheck;        // 80377A08
		virtual void beginState_ExistFileCheck();   // 8015D470
		virtual void executeState_ExistFileCheck(); // 8015D4E0
		virtual void endState_ExistFileCheck();     // 8015D4D0 (nullsub)

		static State StateID_NandSpaceCheck;        // 80377A48
		virtual void beginState_NandSpaceCheck();   // 8015D5A0
		virtual void executeState_NandSpaceCheck(); // 8015D5C0
		virtual void endState_NandSpaceCheck();     // 8015D5B0 (nullsub)

		static State StateID_CreateFile;        // 80377A88
		virtual void beginState_CreateFile();   // 8015D670
		virtual void executeState_CreateFile(); // 8015D6F0
		virtual void endState_CreateFile();     // 8015D770 (nullsub)

		static State StateID_Load;          // 80377AC8
		virtual void beginState_Load();     // 8015D780
		virtual void executeState_Load();   // 8015D790
		virtual void endState_Load();       // 8015D830 (nullsub)

		static State StateID_GoToErrorFadeOut;          // 80377B08
		virtual void beginState_GoToErrorFadeOut();     // 8015DA30
		virtual void executeState_GoToErrorFadeOut();   // 8015DA70
		virtual void endState_GoToErrorFadeOut();       // 8015DAF0 (nullsub)

		static State StateID_GoToErrorFadeIn;           // 80377B48
		virtual void beginState_GoToErrorFadeIn();      // 8015DB00
		virtual void executeState_GoToErrorFadeIn();    // 8015DB30
		virtual void endState_GoToErrorFadeIn();        // 8015DBE0

		static State StateID_NewSaveFileDisp;           // 80377B88
		virtual void beginState_NewSaveFileDisp();      // 8015D870
		virtual void executeState_NewSaveFileDisp();    // 8015D890
		virtual void endState_NewSaveFileDisp();        // 8015D8C0

		static State StateID_ButtonInputWait;           // 80377BC8
		virtual void beginState_ButtonInputWait();      // 8015D8F0
		virtual void executeState_ButtonInputWait();    // 8015D900
		virtual void endState_ButtonInputWait();        // 8015D980 (nullsub)

		static State StateID_WindowExitWait;        // 80377C08
		virtual void beginState_WindowExitWait();   // 8015D990
		virtual void executeState_WindowExitWait(); // 8015D9A0
		virtual void endState_WindowExitWait();     // 8015DA20 (nullsub)

		static State StateID_ProcEnd;           // 80377C48
		virtual void beginState_ProcEnd();      // 8015D840 (nullsub)
		virtual void executeState_ProcEnd();    // 8015D850
		virtual void endState_ProcEnd();        // 8015D860 (nullsub)

		static State StateID_ErrorWindowOnStageWait;        // 80377C88
		virtual void beginState_ErrorWindowOnStageWait();   // 8015DC10
		virtual void executeState_ErrorWindowOnStageWait(); // 8015DC30
		virtual void endState_ErrorWindowOnStageWait();     // 8015DD10 (nullsub)

		static State StateID_ErrorInfinityDisp;         // 80377CC8
		virtual void beginState_ErrorInfinityDisp();    // 8015DD20 (nullsub)
		virtual void executeState_ErrorInfinityDisp();  // 8015DD30 (nullsub)
		virtual void endState_ErrorInfinityDisp();      // 8015DD40 (nullsub)

	private:
		static FunctionChain BootInitTable; // 8042A628 - processed during beforeExecute
		static FunctionChain GameInitTable; // 8042A638 - processed during onExecute and destroyed in deleteReady
};
