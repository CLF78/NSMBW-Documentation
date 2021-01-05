#pragma once
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* LRC Stuff */
struct RCCompressionInfo {
	u32 *freq;      // Table for occurrence frequency: (1 << bitSize) * sizeof(u32) bytes
	u32 *low_cnt;   // Table for the LOW border value: (1 << bitSize) * sizeof(u32) bytes
	u32 total;      // Total: 4 bytes
	u8  bitSize;    // Bit size: 1 byte
	u8  padding;
};

struct RCState {
	u32 low;
	u32 range;
	u32 code;       // Only used during decompression
	u8  carry;      // Only used during compression
	u32 carry_cnt;  // Only used during compression
};

static u16 RCGetData(const u8 *src, RCCompressionInfo *info, RCState *state, u32 srcCnt, s32 *pReadCnt);    // 801D7B30
static u16 RCSearch(RCCompressionInfo *info, u32 code, u32 range, u32 low);                                 // 801D7A90
static void RCAddCount(RCCompressionInfo *info, u16 val);                                                   // 801D78A0

/* LH Stuff */
bool CXiLHVerifyTable(const void *table, u8 bit); // 801D8420

#ifdef __cplusplus
}
#endif
