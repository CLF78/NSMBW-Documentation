#pragma once
#include <common.h>
#include <rvl/cx/cx.h>

class LHDecompressor {
	public:
		void *vtable;
		void *dest;
		u32 unk;
		CXUncompContextLH context;

		virtual bool init(void *dest, u32 unk);                 // 802B8620
		virtual int process(const void *data, u32 length);      // 802B8650
		virtual int getHeaderSize();                            // 802B8B60
		virtual int getUncompressedDataSize(const void *data);  // 802B8B70

		static LHDecompressor *instance;  // 80377DFC
};

class LHFile {
	public:
		virtual ~LHFile();                          // 8016B110
		virtual LHDecompressor *getDecompressor();  // 8016C450
		virtual void nullsub_8016C490();
};
