#pragma once
#include <common.h>
#include <fbase/dbase/dBase.h>

// More commonly known as the "strap screen"
class dLogoScreen_c : public dBase_c {
	public:
		m2d::EmbedLayout_c layout;
		u8 filesLoaded, filesLoadedDupe; // Both set to 1 if the layouts were loaded successfully

		dLogoScreen_c();			// 8010F0B0
		virtual ~dLogoScreen_c();	// 8010F100

		virtual int beforeExecute(); // 8010F380

		virtual int onCreate();		// 8010F170
		virtual int onDelete();		// 8010F520
		virtual int onExecute();	// 8010F480
		virtual int onDraw();		// 8010F4E0

		bool createLayout();			// 8010F1D0
		static dLogoScreen_c *build();	// 8010F080
};
