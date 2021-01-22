#pragma once
#include <fbase/fBase.h>

// Some sort of group controller, perhaps? According to Treeki it's used primarily by BgGm
class dBaseLink {

	void link(void *child, void *parent);   // 80161890
	void unlink(void *child, void *parent); // 80161940

	void clear(); // 80161A00

	void sub_80161880(); // Nullsub, useful as a potential hook
};

class dBase_c : public fBase_c {
	public:
		dBaseLink *firstLinkedNode;
		const char *explanation_string;
		const char *name_string;

		dBase_c(); // 8006C420

		virtual int beforeCreate();     // 8006C540
		virtual int afterCreate(int);   // 8006C570
		virtual int beforeDelete();     // 8006C580
		virtual int afterDelete(int);   // 8006C5B0
		virtual int beforeExecute();    // 8006C5C0
		virtual int afterExecute(int);  // 8006C600
		virtual int beforeDraw();       // 8006C610
		virtual int afterDraw(int);     // 8006C650

		virtual ~dBase_c(); // 8006C490

		virtual const char *getExplanationString(); // 8006C660

	private:
		// Called when the EGGSystem class is created, stores the addresses of two nullsubs
		static void initLoader(); // 8006C690
};
