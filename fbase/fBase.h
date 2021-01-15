#pragma once
#include <common.h>
#include <actors.h>

class fBase_c {
	public:
		u32 id;
		u32 settings;
		Actors name;

		u8 wasCreated;
		u8 wasDestroyed;
		u8 wasCreatedInstantly;
		u8 wasCreationDelayed;
		u8 baseType;            // 0 = none, 1 = scene,  2 = actor
		u8 currentProcessID;    // &1 = connect, &2 = create, &4 = execute, &8 = delete, &16 = draw

		TreeNode link_connect;
		OrderedLinkListEntry link_execute;
		OrderedLinkListEntry link_draw;
		LinkListEntry link_IDlookup;

		void *unusedStruct;  // Checked by dtor, but never used
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

		static fBase_c *createChildObject(Actors name, fBase_c *parent, int settings, char unk);    // 80162C40
		static fBase_c *createObject(Actors name, int settings, char unk);                          // 80162C60

	private:
		// Internal functions
		int processOperation(PTMF beforeState, PTMF onState, PTMF afterState); // 80161E00

		void doCreate();    // 80161F80
		void doDelete();    // 80162160
		void doExecute();   // 80162260
		void doDelete();    // 80162360
		void doConnect();   // 80162420

		// Used by the public createObject funcs
		static fBase_c *createChildUnderTree(Actors name, fBase_c *parent, int settings, char unk); // 80162BB0
		void runCreate();                                                                           // 80162A70

		// Puts the settings into global vars
		static void setNextState(Actors name, fBase_c *parent, int settings, char unk);             // 80162B90
};
