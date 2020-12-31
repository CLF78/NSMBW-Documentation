#pragma once
#include <common.h>
#include <compression/cx.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *LRCDecompClass; // 80377E08

#ifdef __cplusplus
}
#endif

class LRCDecompressor {
	public:
		void *vtable;
		void *dest;
		u32 unk;
		CXUncompContextLRC context;

		virtual bool init(void *destp, u32 unk);				// 802B8680
		virtual int process(const void *data, u32 length);		// 802B86B0
		virtual int getHeaderSize();							// 802B8B40
		virtual int getUncompressedDataSize(const void *data);	// 802B8B30
};

class LRCFile {
	public:
		virtual ~LRCFile();							// 8016B150
		virtual LRCDecompressor *getDecompressor();	// 8016C400
		virtual void nullsub_8016C440();
};
