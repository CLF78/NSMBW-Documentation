#pragma once
#include <common.h>
#include <rvl/cx/cx.h>

class LZDecompressor {
	public:
		void *vtable;
		void *dest;
		u32 unk;
		CXUncompContextLZ context;

		virtual bool init(void *dest, u32 unk);                 // 802B8560
		virtual int process(const void *data, u32 length);      // 802B8590
		virtual int getHeaderSize();                            // 802B8BA0
		virtual int getUncompressedDataSize(const void *data);  // 802B8B90

		static LZDecompressor *instance;  // 80377DF0
};

class LZFile {
	public:
		virtual ~LZFile();                          // 8016B0D0
		virtual LZDecompressor *getDecompressor();  // 8016C4A0
		virtual void nullsub_8016C4E0();
};
