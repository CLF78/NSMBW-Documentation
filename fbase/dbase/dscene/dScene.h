#pragma once
#include <common.h>
#include <fbase/dbase/dBase.h>

#ifdef __cplusplus
extern "C" {
#endif

void DoSceneChange(u16 name, u32 sceneSettings, u32 unk);   // 800E1F50

// Internal functions, DO NOT USE
void SetupScene();              // 800E1EA0
int UpdateCurrentSceneObj();    // 800E1ED0

// The vars mentioned here are two u16s at 80428A48. Obviously, DO NOT USE unless necessary.
void setVar1(u16 var);              // 800E2040
void setVar2(u16 var);              // 800E2050
void setVars(u16 var1, u16 var2);   // 800E2060

#ifdef __cplusplus
}
#endif

class dScene_c : public dBase_c {
	public:
		FunctionChain *ptrToInitChain;

		dScene_c(); // 800E1AA0

		virtual int beforeCreate();     // 800E1B90
		virtual int afterCreate(int);   // 800E1BD0
		virtual int beforeDelete();     // 800E1C40
		virtual int afterDelete(int);   // 800E1C70
		virtual int beforeExecute();    // 800E1CD0
		virtual int afterExecute(int);  // 800E1E10
		virtual int beforeDraw();       // 800E1E60
		virtual int afterDraw(int);     // 800E1E90

		virtual ~dScene_c(); // 800E1B10

		void setInitChain(FunctionChain &initChain) {
			ptrToInitChain = &initChain;
		}
};
