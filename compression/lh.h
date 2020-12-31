#pragma once
#include <common.h>
#include <compression/cx.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *LHDecompClass; // 80377DFC

#ifdef __cplusplus
}
#endif

class LHDecompressor {
	public:
		void *vtable;
		void *dest;
		u32 unk;
		CXUncompContextLH context;

		virtual bool init(void *destp, u32 unk);                // 802B8620
		virtual int process(const void *data, u32 length);      // 802B8650
		virtual int getHeaderSize();                            // 802B8B60
		virtual int getUncompressedDataSize(const void *data);  // 802B8B70
};

class LHFile {
	public:
		virtual ~LHFile();                          // 8016B110
		virtual LHDecompressor *getDecompressor();  // 8016C450
		virtual void nullsub_8016C490();
};
