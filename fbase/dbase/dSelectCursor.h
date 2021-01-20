#pragma once
#include <common.h>
#include <fbase/dbase/dBase.h>

// dSelectCursor_c are the four corner thingies around buttons in the menus. NewerSMBW made them transparent, so they cannot normally be seen.

class SelectCursorSubclass {
	public:
		m2d::EmbedLayout_c layout;                                                  // 0x000

		nw4r::lyt::Pane *rootPane;                                                  // 0x198
		nw4r::lyt::Picture *P_cursor_00, *P_cursor_01, *P_cursor_02, *P_cursor_03;  // 0x19C
		nw4r::lyt::Pane *N_cursor_00, *N_LU_00, *N_RU_00, *N_LD_00, *N_RD_00;       // 0x1AC

		bool visible;                                                               // 0x1C0
		char paneName[0x63];                                                        // 0x1C1

		Vec2 size;                                                                  // 0x228
		float unk[2];                                                               // 0x230 (always 0 as far as i've seen, nothing changes)
		Vec2 scale;                                                                 // 0x238
		Vec2 translation;                                                           // 0x240
		float unk2[4];                                                              // 0x248 (always 0 as far as i've seen, nothing changes)

		u8 basePositionX;                                                           // 0x258 (0 = bottom, 1 = center, 2 = top)
		u8 basePositionY;                                                           // 0x259 (0 = right, 1 = center, 2 = left)
		u32 unk3;                                                                   // 0x25C (set to 0xFF by updatePane)
		u8 unk4;                                                                    // 0x260 (will hide cursor if set to anything other than 0)
		                                                                            // Total class size = 0x264
		SelectCursorSubclass();     // 8010C1D0
		~SelectCursorSubclass();    // 8010C220
};

class dSelectCursor_c : public dBase_c {
	public:
		m2d::ResAccLoader_c loader;
		SelectCursorSubclass cursors[5];
		bool filesLoaded;

		dSelectCursor_c();          // 8010C160
		virtual ~dSelectCursor_c(); // 8010C280

		virtual int onCreate();     // 8010C310
		virtual int onExecute();    // 8010C490
		virtual int onDraw();       // 8010C530
		virtual int onDelete();     // 8010C5A0

		static dSelectCursor_c *build();                                                        // 8010C130
		static dSelectCursor_c *instance;                                                       // 8042A5A8
		static void updateSelectCursor(nw4r::lyt::Pane *pane, int index, bool useSpecialDraw);  // 800B44D0

		void hideSelectCursor(int index);   // 8010C890

	private:
		void update(int index); // 8010C620 (called by onExecute)

		// updateSelectCursor calls these, so they can remain private
		void updatePane(nw4r::lyt::Pane *pane, int index, bool useSpecialDraw); // 8010C900
		void updateAlpha(nw4r::lyt::Pane *pane, int index);                     // 8010CAB0
};
