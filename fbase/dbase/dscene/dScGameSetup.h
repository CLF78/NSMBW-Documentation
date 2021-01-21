#pragma once
#include <common.h>
#include <fbase/dbase/dscene/dScene.h>
#include <fbase/dbase/dSelectCursor.h>

// dScGameSetup handles many background tasks in the file select and character select screens.
class dScGameSetup_c : public dScene_c {
	public:
		dStateWrapper_c<dScGameSetup_c> wrapper;
		FunctionChain setupChain;

		void *npChange;
		dSelectCursor_c *selectCursor;
		void *wm2DPlayer[4];
		void *selectPlayer;
		void *easyPairing;
		void *sequenceBG;
		void *dateFile[3];
		void *fileSelect;
		void *infoWindow;

		u32 _F0, _F4;   // Should be unused
		u32 playerCount;
		u32 _FC, _100;  // Should also be unused

		u32 lastUsedSaveFile;   // Copied from SaveFile instance
		bool isInPlayerSelect;

		EGG::ProjectOrtho ortho;
		EGG::LookAtCamera camera;
		EGG::SimpleViewport viewport;

		// Class functions
		dScGameSetup_c();   // 80918020

		virtual int onCreate();     // 80918330
		virtual int onDelete();     // 80919270
		virtual int onExecute();    // 809183F0
		virtual int onDraw();       // 80919240

		virtual int beforeExecute();    // 809183B0

		virtual void deleteReady(); // 80919250
		virtual ~dScGameSetup_c();  // 809182A0

		// Static stuff
		static dScGameSetup_c *build();     // 80917960
		static dScGameSetup_c *instance;    // 809A14D0

		// States
		static State StateID_FadeInEndWait;         // 809A14E0
		virtual void beginState_FadeInEndWait();    // 80918680 (nullsub)
		virtual void executeState_FadeInEndWait();  // 80918690
		virtual void endState_FadeInEndWait();      // 80918710 (nullsub)

		static State StateID_FileSelect;        // 809A1520
		virtual void beginState_FileSelect();   // 80918720
		virtual void executeState_FileSelect(); // 80918780
		virtual void endState_FileSelect();     // 809188E0

		static State StateID_FadeOut;           // 809A1560
		virtual void beginState_FadeOut();      // 80918910
		virtual void executeState_FadeOut();    // 80918950
		virtual void endState_FadeOut();        // 809189C0

		static State StateID_FadeIn;        // 809A15A0
		virtual void beginState_FadeIn();   // 809189F0
		virtual void executeState_FadeIn(); // 80918A20
		virtual void endState_FadeIn();     // 80918AC0

		static State StateID_StartMember;           // 809A15E0
		virtual void beginState_StartMember();      // 80918AD0
		virtual void executeState_StartMember();    // 80918B00
		virtual void endState_StartMember();        // 80918C00 (nullsub)

		static State StateID_ConnectionCheck;           // 809A1620
		virtual void beginState_ConnectionCheck();      // 80918C10
		virtual void executeState_ConnectionCheck();    // 80918D10
		virtual void endState_ConnectionCheck();        // 80918DB0 (nullsub)

		static State StateID_EasyPairingWait;           // 809A1660
		virtual void beginState_EasyPairingWait();      // 80918DC0
		virtual void executeState_EasyPairingWait();    // 80918E40
		virtual void endState_EasyPairingWait();        // 80918E70

		static State StateID_LowBatteryCheck;           // 809A16A0
		virtual void beginState_LowBatteryCheck();      // 80918EE0
		virtual void executeState_LowBatteryCheck();    // 80918EF0
		virtual void endState_LowBatteryCheck();        // 80918F80

		static State StateID_NandAccess;        // 809A16E0
		virtual void beginState_NandAccess();   // 80918FF0
		virtual void executeState_NandAccess(); // 80919050
		virtual void endState_NandAccess();     // 809190E0

		static State StateID_VoiceEndWait;          // 809A1720
		virtual void beginState_VoiceEndWait();     // 80919120 (nullsub)
		virtual void executeState_VoiceEndWait();   // 80919130
		virtual void endState_VoiceEndWait();       // 80919190

		static State StateID_NextSceneWait;         // 809A1760
		virtual void beginState_NextSceneWait();    // 80919210 (nullsub)
		virtual void executeState_NextSceneWait();  // 80919220 (nullsub)
		virtual void endState_NextSceneWait();      // 80919230 (nullsub)

	private:
		// Called by onCreate
		void allocateScene();           // 80919560
		void loadScene(int id);         // 809194A0
		void loadLayout3DScene(int id); // 809193E0

		// Called by onExecute
		void updateCamera();    // 809195D0
		void checkWiimotes();   // 809185C0

		// Called by onDelete
		void freeScene(int id); // 809195C0

		// Called by FileSelect state
		void positionDateFiles(); // 80918450

		// Called by LowBatteryCheck state
		static void sub_80918500(); // Updates stuff in GameMgr
};
