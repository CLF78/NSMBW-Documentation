#pragma once
#include <fbase/dbase/dscene/dScene.h>

// Possibly the most useless class i've seen so far
class dScSelect_c : public dScene_c {
	public:
		virtual ~dScSelect_c();         // 80923BB0

		static dScSelect_c *build();    // 80923B60 (constructor is inlined)
};
