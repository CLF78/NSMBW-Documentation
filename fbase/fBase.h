#pragma once
#include <common.h>
#include <actors.h>

// Forward declaration
class fBase_c;

#ifdef __cplusplus
extern "C" {
#endif

fBase_c *createChildObject(Actors name, fBase_c *parent, int settings, char unk);    // 80162C40
fBase_c *createObject(Actors name, int settings, char unk);                          // 80162C60

// Used by the above two. DO NOT USE.
fBase_c *createChildUnderTree(Actors name, fBase_c *parent, int settings, char unk); // 80162BB0

#ifdef __cplusplus
}
#endif

class fBase_c {
	public:

		enum Basetype : u8 {
			NONE = 0,
			SCENE = 1,
			ACTOR = 2,
		};

		u32 id;
		u32 settings;
		Actors name;

		u8 wasCreated;
		u8 wasDestroyed;
		u8 wasCreatedInstantly;
		u8 wasCreationDelayed;
		Basetype type;
		u8 currentProcessID; // &1 = connect, &2 = create, &4 = execute, &8 = delete, &16 = draw

		TreeNode link_connect;
		OrderedLinkListEntry link_execute;
		OrderedLinkListEntry link_draw;
		LinkListEntry link_IDlookup;

		void *unusedStruct;  // Checked by dtor and afterDelete, but never used
		void *unusedStruct2; // Checked by beforeDelete, but never used
		u32 unk;
		void *heap;

		fBase_c(); // 80161C10

		virtual int onCreate();         // 80161EC0
		virtual int beforeCreate();     // 80161ED0
		virtual int afterCreate(int);   // 80161EE0

		virtual int onDelete();         // 80161F70
		virtual int beforeDelete();     // 80162030
		virtual int afterDelete(int);   // 801620A0

		virtual int onExecute();        // 80162210
		virtual int beforeExecute();    // 80162220
		virtual int afterExecute(int);  // 80162250

		virtual int onDraw();       // 80162310
		virtual int beforeDraw();   // 80162320
		virtual int afterDraw(int); // 80162350

		virtual void deleteReady(); // 80162410

		virtual bool moreHeapStuff(u32 size, void *parentHeap); // 80162730
		virtual bool createHeap(u32 size, void *parentHeap);    // 80162930
		virtual void heapCreated();                             // 801629F0

		virtual ~fBase_c(); // 80161D80

		void destroy(); // 80162650

		fBase_c *GetParent();   // 801626D0
		fBase_c *GetChild();    // 801626F0
		fBase_c *GetNext();     // 80162710

		bool hasUninitialisedProcesses();           // 80162B60
		fBase_c *findNextUninitialisedProcess();    // 80162AF0

	private:
		// Internal functions
		int processOperation(PTMF beforeState, PTMF onState, PTMF afterState); // 80161E00

		void doCreate();    // 80161F80
		void doDelete();    // 80162160
		void doExecute();   // 80162260
		void doDraw();      // 80162360
		void doConnect();   // 80162420

		// Used by the createObject funcs
		void runCreate(); // 80162A70

		// Puts the settings into global vars
		static void setNextState(Actors name, fBase_c *parent, int settings, char unk); // 80162B90
};
