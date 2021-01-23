#pragma once
#include <common.h>
#include <dScene.h>

class dScRestartCrsin_c : public dScene_c {
	public:
		dScRestartCrsin_c();            // 809239A0
		virtual ~dScRestartCrsin_c();   // 809239E0

		virtual int onCreate();  // 80923A40
		virtual int onDelete();  // 80923B20
		virtual int onExecute(); // 80923AE0
		virtual int onDraw();    // 80923B50

		virtual int beforeExecute(); // 80923AB0

		static dScRestartCrsin_c *build(); // 80923970
};
