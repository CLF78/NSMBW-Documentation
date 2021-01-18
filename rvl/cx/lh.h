#pragma once
#include <common.h>
#include <rvl/cx/cx.h>

class LHDecompressor {
	public:
		virtual bool init(void *dest, u32 unk);                 // 802B8620
		virtual int process(const void *data, u32 length);      // 802B8650
		virtual int getHeaderSize();                            // 802B8B60
		virtual int getUncompressedDataSize(const void *data);  // 802B8B70

		void *dest;
		u32 unk;
		CXUncompContextLH context;
};

class LHFile {
	public:
		virtual ~LHFile();                          // 8016B110
		virtual LHDecompressor *getDecompressor();  // 8016C450
		virtual void nullsub_8016C490();

		u8 unk; // 3 for SZS, 4 for RL, 5 for LZ, 7 for LH and 8 for LRC
		const char* fileExtension;

		static LHFile instance;  // 80377DFC
};
