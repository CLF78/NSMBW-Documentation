#pragma once
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

void BCACheck();                                // 801D0E30
void TriggerErrorMessage();                     // 801D1060
int CheckImmBufferRegister(int immbufferreg);   // 801D0D70

/* Callbacks
void BCACallback1();        // 801D0D40
void BCACallback3();        // 801D0D60
s32 BCACallback2(s32 unk);  // 801D0D50
*/

#ifdef __cplusplus
}
#endif
