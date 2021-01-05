#pragma once
#include <common.h>
#include <dvd/dvdlow.h>

#ifdef __cplusplus
extern "C" {
#endif

bool DVDCheckDevice(); // 801D0AC0

void DVDStoreErrorCode(int error, DVDLowCallback callback); // 801D07E0

void DVDShowFatalMessage();     // 801D0940
void DVDPrintFatalMessage();    // 801D0A90

bool DVDSetAutoFatalMessaging(bool enabled);    // 801D0A10
bool DVDGetAutoFatalMessaging();                // 801D0A70

/* Callbacks
void cbForNandClose(s32 result);                // 801CFE30
void cbForNandWrite();                          // 801CFE60
void cbForNandSeek(s32 result);                 // 801CFEC0
void cbForNandWrite0(s32 result);               // 801CFFC0
void cbForNandSeek2(s32 result);                // 801D0120
void cbForNandRead(s32 result);                 // 801D01E0
void cbForNandSeek0(s32 result);                // 801D02D0
void cbForNandSeek1(s32 result);                // 801D0370
void cbForNandOpen(s32 result);                 // 801D0470
void cbForNandCreate(s32 result);               // 801D0590
void cbForNandCreateDir(s32 result);            // 801D0640
void cbForPrepareControlRegister(s32 result);   // 801D06D0
void cbForPrepareStatusRegister(s32 result);    // 801D0760
*/

#ifdef __cplusplus
}
#endif
