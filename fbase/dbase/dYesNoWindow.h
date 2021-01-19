#pragma once
#include <common.h>
#include <fbase/dbase/dBase.h>

// dYesNoWindow is a simple window you can use to ask a Yes/No question, but despite the name it can also be used as a confirmation prompt (OK button)

/* List of Message Types:
- 0 = New Super Mario Bros Wii save data has been created.
- 1 = Save?
- 2 = Progress saved.
- 3 = Are you sure you want to exit Free Mode and return to the File Selection Screen?
- 4 = Watch this Hint Movie?
- 5 = Are you sure you want to skip this course and move on to the next one?
- 6 = Are you sure you want to skip past the final challenge and see the ending? (hardcoded to stage 8-24, will show "Watch this Hint Movie?" otherwise)
- 7 = You got all the Star Coins in World X!
- 8 = You got all the Star Coins in World X! You can now play a new course in World 9!
- 9 = (Bowser Jr letter, unused i think?)
- 10 = Are you sure you want to return to the title screen? [...]
- 11 = (Bowser Jr letter single player version, unused i think?)
- 12 = Are you sure you want to exit and go back to the map?
- 13 = Are you sure you want to go back to the course selection screen?
- 14 = You got all the Star Coins in World X! You've now collected all the Star Coins in every world!
- 15 = Quit and go back to the title screen? Your progress will be saved, but you can only continue from this quick save once.
- 16 = Progress saved. Returning to the title screen.
- 17 = All the Toad houses have popped back up! [...]
- 18 = Press X on the map to access your items! [...]
- 19 = Now that you cleared this course with Super Guide, do you want to give it another try without?
- 20 = Are you sure you want to skip this course and move on to the next one? (dupe?)
- 21 = You've completed everything in New Super Mario Bros. Wii!
- 22 = Progress saved. You will now return to the title screen. Now you can save at anytime from the Map Menu.
- 23 = (World 3 switch activated)
- 24 = (World 3 switch deactivated)
- 25 = Are you sure you want to exit Coin Battle and return to the File Selection Screen?
- 26 = Are you sure you want to exit and go back to the map? (dupe?)
- 27 = Don't forget to stop by Peach's Castle once in a while to watch Hint Movies. [...]
- 28 = Spend your Star Coins at Peach's Castle in World 1 to watch Hint Movies. [...]

List of prompts for each type (to change these you'll need to edit the createLayout function):
- 1 = Save / Don't Save
- 15 = Quick Save / Don't Save
- 19 = OK, I'll try it! / No, skip it
- 20 = Yes, I'm sure / No, wait! (first text hardcoded to "Watch Ending" on 8-24)
- All other options = OK! / Cancel

Finally, types 12, 13 and 26 mute all other sound effects.
*/

class dYesNoWindow_c : public dBase_c {
	public:
		m2d::EmbedLayout_c layout;
		dStateWrapper_c<dYesNoWindow_c> state;

		nw4r::lyt::Pane *rootPane;

		nw4r::lyt::Picture *P_yesBase_00, *P_noBase_00, *P_centerBase_00;

		nw4r::lyt::TextBox
			*T_questionS_00, *T_question_00,
			*T_otehonTextS_01, *T_otehonText_01,
			*T_needCoinX_00, *T_needcoin_00,
			*T_yes_00, *T_yes_01,
			*T_no_00, *T_no_01;

		nw4r::lyt::Pane *N_otehonText_00, *N_saveIcon_00;

		int current, previous, type, starCoinRequiredCount;
		bool layoutLoaded, visible, close, animationActive, keepOpen, cancelled, hasBG;

		// Class functions
		dYesNoWindow_c();           // 80768AB0
		virtual ~dYesNoWindow_c();  // 80768DF0

		virtual int onCreate();     // 80768E80
		virtual int onDelete();     // 80769120
		virtual int onExecute();    // 80769010
		virtual int onDraw();       // 807690C0

		// Static stuff
		static dYesNoWindow_c *build(); // 80768A80

		enum DefaultChoice {
			YES = 0,
			NO = 1,
			OK = 2,
		};

		static u32 messageIDs[29];                  // 8076A5F8 (see list at the beginning of the file)
		static DefaultChoice defaultChoices[29];    // 8076A6C4
		static bool buttonVisible[29][3];           // 8076A66C (first entry is Yes button, second entry is No button, third entry is OK button)

		// States
		static State StateID_InitWait;         // 8076D478 (initial state)
		virtual void beginState_InitWait();    // 807694A0
		virtual void executeState_InitWait();  // 807694C0
		virtual void endState_InitWait();      // 80769500 (nullsub)

		static State StateID_OpenAnimeEndWait;          // 8076D4B8
		virtual void beginState_OpenAnimeEndWait();     // 80769510
		virtual void executeState_OpenAnimeEndWait();   // 80769620
		virtual void endState_OpenAnimeEndWait();       // 80769680

		static State StateID_ButtonOnStageAnimeEndWait;           // 8076D4F8
		virtual void beginState_ButtonOnStageAnimeEndWait();      // 80769690
		virtual void executeState_ButtonOnStageAnimeEndWait();    // 807696F0
		virtual void endState_ButtonOnStageAnimeEndWait();        // 80769750

		static State StateID_ButtonChangeAnimeEndWait;           // 8076D538
		virtual void beginState_ButtonChangeAnimeEndWait();      // 80769770
		virtual void executeState_ButtonChangeAnimeEndWait();    // 807697E0
		virtual void endState_ButtonChangeAnimeEndWait();        // 80769840

		static State StateID_SelectWait;           // 8076D578
		virtual void beginState_SelectWait();      // 80769850
		virtual void executeState_SelectWait();    // 807698C0
		virtual void endState_SelectWait();        // 807699E0

		static State StateID_HitAnimeEndWait;           // 8076D5B8
		virtual void beginState_HitAnimeEndWait();      // 807699F0
		virtual void executeState_HitAnimeEndWait();    // 80769A80
		virtual void endState_HitAnimeEndWait();        // 80769B10

		static State StateID_ClouseAnimeEndWait;           // 8076D5F8 (not a typo)
		virtual void beginState_ClouseAnimeEndWait();      // 80769B20
		virtual void executeState_ClouseAnimeEndWait();    // 80769BC0
		virtual void endState_ClouseAnimeEndWait();        // 80769C20

		static State StateID_HitAnimeAfterWait;           // 8077D638
		virtual void beginState_HitAnimeAfterWait();      // 80769C30
		virtual void executeState_HitAnimeAfterWait();    // 80769C40 (nullsub)
		virtual void endState_HitAnimeAfterWait();        // 80769C50 (nullsub)

	private:
		void createLayout(); // 80769130
};
