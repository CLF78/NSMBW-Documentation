#pragma once
#include <common.h>
#include <rvl/cx/cx.h>

class LZDecompressor {
	public:
		virtual bool init(void *dest, u32 unk);                 // 802B8560
		virtual int process(const void *data, u32 length);      // 802B8590
		virtual int getHeaderSize();                            // 802B8BA0
		virtual int getUncompressedDataSize(const void *data);  // 802B8B90

		void *dest;
		u32 unk;
		CXUncompContextLZ context;
};

class LZFile {
	public:
		virtual ~LZFile();                          // 8016B0D0
		virtual LZDecompressor *getDecompressor();  // 8016C4A0
		virtual void nullsub_8016C4E0();

		u8 unk; // 3 for SZS, 4 for RL, 5 for LZ, 7 for LH and 8 for LRC
		const char* fileExtension;

		static LZFile instance;  // 80377DF0
};
