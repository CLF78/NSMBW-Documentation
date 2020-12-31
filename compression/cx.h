#pragma once
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Structures */
enum CXCompressionType : u8 {
    CX_COMPRESSION_LZ			= 0x10,		// LZ77
    CX_COMPRESSION_HUFFMAN		= 0x20,		// Huffman
    CX_COMPRESSION_RL			= 0x30,		// Run Length
    CX_COMPRESSION_LH			= 0x40,		// LH(LZ77+Huffman)
    CX_COMPRESSION_LRC			= 0x50,		// LRC(LZ77+RangeCoder)
    CX_COMPRESSION_DIFF 		= 0x80,		// Differential filter
    CX_COMPRESSION_TYPE_MASK	= 0xF0,
    CX_COMPRESSION_TYPE_EX_MASK = 0xFF
};

struct CXCompressionHeader {
    CXCompressionType compType; 	// Compression type
    u8 compParam;					// Compression parameter
    u8 padding[2];
    u32 destSize;					// Expanded size
};

struct CXUncompContextLH {
    u8  *destp; 						// Write-destination pointer: 4B
    s32  destCount; 					// Remaining size to write: 4B
    s32  forceDestCount;				// Forcibly set the decompression size: 4B
    u16  huffTable9[1024];				// Huffman encoding table: 2048B
    u16  huffTable12[64];				// Huffman encoding table: 128B
    u16  *nodep;						// Node during a Huffman table search: 4B
    s32  tableSize9;					// Table size during a load: 4B
    s32  tableSize12;					// Table size during a load: 4B
    u32  tableIdx;						// Index for the table load position: 4B
    u32  stream;						// Bit stream for loading: 4B
    u32  stream_len;					// Number of valid stream bits for loading: 4B
    u16  length;						// Read length for LZ compression: 2B
    s8   offset_bits;					// Bit length for offset information: 1B
    u8   headerSize;					// Size of header being read: 1B
};										// Total is 2216B

struct CXUncompContextLRC {
    u8   *destp;						// Write-destination pointer: 4B
    s32  destCount; 					// Remaining size to write: 4B
    s32  forceDestCount;				// Forcibly set the decompression size: 4B
    u32  freq9[0x200];					// Frequency table for code data: 2048B
    u32  low_cnt9[0x200];				// low_cnt table for code data: 2048B
    u32  freq12[0x1000];				// Frequency table for offset data: 16384B
    u32  low_cnt12[0x1000]; 			// low_cnt table for offset data: 16384B
    u32  total9;						// Total value for code data: 4B
    u32  total12;						// Total value for offset data: 4B
    u32  range; 						// Range state of a range coder: 4B
    u32  code;							// Code state of a range coder: 4B
    u32  low;							// Low state of a range coder: 4B
    u32  carry_cnt; 					// Number of carry digits for a range coder: 4B
    u8   carry; 						// Carry state for a range coder: 1B
    u8   codeLen;						// Code length required for a range coder: 1B
    u16  length;						// Read length for LZ compression: 2B
    u8   headerSize;					// Size of header being read: 1B
    u8   padding[3];					// 3B
};										// Total is 36908B

struct CXUncompContextRL {
    u8 *destp;							// Write-destination pointer: 4B
    s32 destCount;						// Remaining size to write: 4B
    s32 forceDestCount; 				// Forcibly set the decompression size: 4B
    u16 length; 						// Remaining size of continuous write: 2B
    u8  flags;							// Compression flag: 1B
    u8  headerSize; 					// Size of header being read: 1B
};										// Total is 16B

struct CXUncompContextLZ {
    u8 *destp;							// Write-destination pointer: 4B
    s32 destCount;  					// Remaining size to write: 4B
    s32 forceDestCount; 				// Forcibly set the decompression size: 4B
    s32 length; 						// Remaining length of continuous write: 4B
    u8  lengthFlg;						// 'length' obtained flag: 1B
    u8  flags;							// Compression flag: 1B
    u8  flagIndex;						// Current compression flag index: 1B
    u8  headerSize; 					// Size of header being read: 1B
    u8  exFormat;						// LZ77 compression extension option: 1B
    u8  padding[3]; 					// 3B
};										// Total is 24B

/* Streaming Decompression */
void CXInitUncompContextLH(CXUncompContextLH *context, void *dest); 	// 801D7060
void CXInitUncompContextLRC(CXUncompContextLRC *context, void *dest);	// 801D7C40
void CXInitUncompContextRL(CXUncompContextRL *context, void *dest); 	// 801D6990
void CXInitUncompContextLZ(CXUncompContextLZ *context, void *dest); 	// 801D69C0

s32 CXReadUncompLH(CXUncompContextLH *context, const void *data, u32 len);		// 801D70A0
s32 CXReadUncompLRC(CXUncompContextLRC *context, const void* data, u32 len);	// 801D7E90
s32 CXReadUncompRL(CXUncompContextRL *context, const void *data, u32 len);		// 801D6A00
s32 CXReadUncompLZ(CXUncompContextLZ *context, const void *data, u32 len);		// 801D6CA0

static inline bool CXIsFinishedUncompLH(const CXUncompContextLH *context) {
    return !(context->destCount > 0 || context->headerSize > 0);
}

static inline bool CXIsFinishedUncompLRC(const CXUncompContextLRC *context) {
    return !(context->destCount > 0 || context->headerSize > 0);
}

static inline bool CXIsFinishedUncompRL(const CXUncompContextRL *context) {
    return !(context->destCount > 0 || context->headerSize > 0);
}

static inline bool CXIsFinishedUncompLZ(const CXUncompContextLZ *context) {
    return !(context->destCount > 0 || context->headerSize > 0);
}

/* Normal Decompression */
u32 CXGetUncompressedSize(const void *src); 		// 801D8290
void CXUncompressLZ(const void *src, void *dest);	// 801D82D0

#ifdef __cplusplus
}
#endif
