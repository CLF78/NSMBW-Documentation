#pragma once
#include <fbase/dbase/dscene/dScene.h>

// Possibly the most useless class i've seen so far
class dScAutoSelect_c : public dScene_c {
	public:
		virtual ~dScAutoSelect_c();         // 8091EBB0

		static dScAutoSelect_c *build();    // 8091EB60 (constructor is inlined)
};
