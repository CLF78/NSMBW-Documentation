#pragma once
#include <common.h>
#include <dvd/dvdlow.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DVD_MIN_TRANSFER_SIZE     32

// State Codes
#define DVD_STATE_FATAL_ERROR     -1
#define DVD_STATE_END             0
#define DVD_STATE_BUSY            1
#define DVD_STATE_WAITING         2
#define DVD_STATE_COVER_CLOSED    3         // Internal state, never returns
#define DVD_STATE_NO_DISK         4
#define DVD_STATE_COVER_OPEN      5
#define DVD_STATE_WRONG_DISK      6
#define DVD_STATE_MOTOR_STOPPED   7
#define DVD_STATE_PAUSING         8
#define DVD_STATE_IGNORED         9
#define DVD_STATE_CANCELED        10
#define DVD_STATE_RETRY           11
#define DVD_STATE_NO_INPUT        12

// Handle State Codes
#define DVD_FILEINFO_READY        0
#define DVD_FILEINFO_BUSY         1

// Return Codes
#define DVD_RESULT_GOOD           0
#define DVD_RESULT_FATAL_ERROR    -1
#define DVD_RESULT_IGNORED        -2
#define DVD_RESULT_CANCELED       -3

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDHandle DVDHandle;
typedef void (*DVDCallback)(s32 result, DVDHandle *handle);
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
	DVDCommandBlock* next;  // 00
	DVDCommandBlock* prev;  // 04
	u32 command;            // 08
	s32 state;              // 0C
	u32 offset;             // 10
	u32 length;             // 14
	void* addr;             // 18
	u32 currTransferSize;   // 1C
	u32 transferredSize;    // 20
	DVDDiskID* id;          // 24
	DVDCBCallback cb;       // 28
	void* userData;         // 2C
};

struct DVDHandle {
	DVDCommandBlock block;  // 00
	int address;            // 30
	int length;             // 34
	DVDCallback callback;   // 38
};

/* Main functions */
void DVDInit(); // 801CAE70

s32 DVDConvertPathToEntrynum(const char *path);     // 801CA7C0
bool DVDFastOpen(s32 entrynum, DVDHandle *handle);  // 801CAAD0
bool DVDClose(DVDHandle *handle);                   // 801CAB40

s32 DVDReadPrio(DVDHandle *handle, void *addr, s32 length, s32 offset, s32 prio);                                   // 801CAC60
bool DVDReadAsyncPrio(DVDHandle *handle, void *addr, s32 length, s32 offset, DVDCallback callback, s32 prio);       // 801CAB70
bool DVDReadAbsAsyncPrio(DVDHandle *handle, void *addr, s32 length, s32 offset, DVDCallback callback, s32 prio);    // 801CEE00

bool DVDCancelAsync(DVDCommandBlock *block, DVDCBCallback *cb); // 801CF1A0
s32 DVDCancel(DVDCommandBlock *block);                          // 801CF510

void DVDResume(); // 801CF150

bool DVDInquiryAsync(DVDCommandBlock *block, DVDDriveInfo *info, DVDCBCallback *cb); // 801CEEF0
bool DVDCheckDiscAsync(DVDHandle *handle, DVDCBCallback cb);                         // 801CF6C0
bool DVDCompareDiskID(DVDDiskID *id, DVDDiskID *id2);                                // 801D0850

s32 DVDGetCommandBlockStatus(DVDCommandBlock *block); // 801CEFD0
s32 DVDGetDriveStatus();                              // 801CF0A0
s32 DVDGetCoverStatus();                              // 801CF5F0

bool DVDSetAutoInvalidation(bool enabled); // 801CF140

void DVDPrepareResetAsync(DVDCBCallback *cb);   // 801CF900
void DVDPrepareReset();                         // 801CFA30
bool DVDTestAlarm(void *alarm);                 // 801CFB70

// These are stubbed, i think
bool DVDStopMotorAsync();   // 801CFB90
void DVDRestartMotor();     // 801CFBA0

/* Internal stuff */
void DVDFSInit();                                       // 801CA790
void StampCommand(int commandMaybe, int unk, int unk2); // 801CADA0
void defaultOptionalCommandChecker();                   // 801CAE60
int CategorizeError(int error);                         // 801CB460

/* States
s32 stateReadingFST();      // 801CAFD0
s32 stateCheckID();         // 801CC040
s32 stateCoverClosed();     // 801CD010
s32 stateDownRotation();    // 801CD420
s32 stateCoverClosed();     // 801CD730
s32 stateReady();           // 801CDB50
s32 stateBusy(void *unk);   // 801CDE70
*/

/* Callbacks
s32 cbForCancelSync();                          // 801CF5D0
s32 cbForPrepareCoverRegister();                // 801CD990
s32 cbForStateBusy(s32 result);                 // 801CE420
s32 cbForStateCheckID1(s32 result);             // 801CCCA0
s32 cbForStateCheckID2(s32 result);             // 801CCE70
s32 cbForStateCoverClosed(s32 result);          // 801CD8B0
s32 cbForStateDownRotation(s32 result);         // 801CD4F0
s32 cbForStateError(s32 result);                // 801CB2F0
s32 cbForStateGettingError();                   // 801CB630
s32 cbForStateGoToRetry(s32 result);            // 801CBE00
s32 cbForStateReadingFST(s32 result);           // 801CB150
s32 cbForStateReadingPartitionInfo(s32 result); // 801CC520
s32 cbForStateReadingTOC(s32 result);           // 801CC380
s32 cbForStateReset(s32 result);                // 801CD330
s32 cbForStoreErrorCode1();                     // 801CB400
s32 cbForStoreErrorCode2();                     // 801CB420
s32 cbForStoreErrorCode3();                     // 801CB560
s32 cbForUnrecoveredError(s32 result);          // 801CBB40
s32 cbForUnrecoveredErrorRetry(s32 result);     // 801CBD20

s32 BS2DVDLowCallback(s32 result);  // 801CF5E0
s32 CoverAlarmHandler(s32 result);  // 801CDB20
s32 ResetAlarmHandler();            // 801CD0E0
*/

#ifdef __cplusplus
}
#endif
