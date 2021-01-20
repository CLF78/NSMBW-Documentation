#pragma once
#include <common.h>
#include <fbase/dbase/dBase.h>

class dControllerInformation_c : public dBase_c {
	public:
		m2d::EmbedLayout_c layout;

		bool filesLoaded;
		bool isScreenOn;    // Set to 1 once the wipe to this screen is activated
		u32 status;         // 0 = initial state, 1 = countdown in scboot started, 2/3 = enabled animation 0/1, 4 = 2 button pressed

		dControllerInformation_c();            // 80768700
		virtual ~dControllerInformation_c();   // 80767850

		virtual int onCreate();     // 807687C0
		virtual int onDelete();     // 80768A70
		virtual int onExecute();    // 80768920
		virtual int onDraw();       // 80768A30

		static dControllerInformation_c *build();  // 807686D0

	private:
		bool createLayout(); // 80768860
};
