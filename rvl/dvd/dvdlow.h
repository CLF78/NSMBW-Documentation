#pragma once
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

// Low-level callback results
#define DVDLOW_RESULT_TRANSFER       0x01    // DMA Transfer complete
#define DVDLOW_RESULT_ERROR          0x02    // Disk Error
#define DVDLOW_RESULT_RESET_COVER    0x04    // Cover signal status reset
#define DVDLOW_RESULT_BREAK          0x08    // Break request
#define DVDLOW_RESULT_TIMEOUT        0x10    // Operation timeout

// Callback for low-level operations
typedef void (*DVDLowCallback)(s32 result);

typedef struct DVDDiskID {
	char name[0x04];
	char company[0x02];
	u8 diskNum;
	u8 version;
	u8 streaming;
	u8 streamBufferSize; // 0 = default
	u8 pad[14];
	u32 rvlMagic;
	u32 gcMagic;
};

// Credits to arookas
typedef struct DVDDriveInfo {
	u16 revisionLevel;
	u16 deviceCode;
	u16 releaseDate;
	u8 pad[0x18];
};

/* Main functions */
bool DVDLowInit(); // 801D1370

bool DVDLowRead(void *buffer, u32 length, u32 offset, DVDLowCallback callback);             // 801D3060
bool DVDLowReadDiskBca(void *buffer, DVDLowCallback callback);                              // 801D2D60
bool DVDLowReadDiskID(DVDDiskID *diskID, DVDLowCallback callback);                          // 801D15E0
bool DVDLowUnencryptedRead(void *buffer, u32 length, u32 offset, DVDLowCallback callback);  // 801D2270

bool DVDLowSeek(u32 offset, DVDLowCallback callback); // 801D3210

bool DVDLowAudioBufferConfig(u32 length, u32 offset, DVDLowCallback callback);          // 801D2A20
bool DVDLowInquiry(DVDDriveInfo *info, DVDLowCallback callback);                        // 801D25B0
bool DVDLowReportKey(void *buffer, u32 length, u32 offset, DVDLowCallback callback);    // 801D2BC0

bool DVDLowSetSpinupFlag(int flag);                                 // 801D2890
bool DVDLowSetMaximumRotation(u32 length, DVDLowCallback callback); // 801D2ED0

bool DVDLowStopMotor(DVDLowCallback callback);      // 801D2410
bool DVDLowRequestError(DVDLowCallback callback);   // 801D2720
void DVDLowReset(DVDLowCallback callback);          // 801D28A0

bool DVDLowClosePartition(DVDLowCallback callback); // 801D2100
bool DVDLowFinalize();                              // 801D1320

int DVDLowGetCoverRegister();       // 801D3390
int DVDLowGetStatusRegister();      // 801D33A0
int DVDLowGetControlRegister();     // 801D33B0
int DVDLowGetImmBufferRegister();   // 801D3810

bool DVDLowPrepareCoverRegister(DVDLowCallback callback);   // 801D33C0
bool DVDLowPrepareStatusRegister(DVDLowCallback callback);  // 801D3530
bool DVDLowPrepareControlRegister(DVDLowCallback callback); // 801D36A0

bool DVDLowMaskCoverInterrupt();                            // 801D3830
bool DVDLowClearCoverInterrupt(DVDLowCallback callback);    // 801D3840
bool DVDLowUnmaskStatusInterrupts();                        // 801D3820

// Unsure about the arguments of these
bool DVDLowOpenPartition(u32 length, void *eTicket, u32 cert_len, void *cert_in, void *cert_out, DVDLowCallback callback);                                          // 801D1770
bool DVDLowOpenPartitionWithTmdAndTicketView(u32 length, void *eTicket, u32 cert_in_len, void *cert_in, u32 cert_out_len, void *cert_out, DVDLowCallback callback); // 801D19E0

bool DVDLowGetNoDiscBufferSizes(u32 length, u32 cert_len, void *cert, DVDLowCallback callback);                                                                             // 801D1C50
bool DVDLowGetNoDiscOpenPartitionParams(u32 length, void *unk, u32 *cert_in_len, void *cert_in, u32 *cert_out_len, void *cert_out, void *unk2, DVDLowCallback callback);    // 801D1E60

// This is stubbed out
void DVDLowTestAlarm(); // 801D39B0

/* Callbacks
s32 doTransactionCallback(s32 result, void *userdata);          // 801D11A0
s32 doPrepareCoverRegisterCallback(s32 result, void *userdata); // 801D1260
*/

#ifdef __cplusplus
}
#endif
