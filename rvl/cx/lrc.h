#pragma once
#include <common.h>
#include <rvl/cx/cx.h>

class LRCDecompressor {
	public:
		virtual bool init(void *dest, u32 unk);                 // 802B8680
		virtual int process(const void *data, u32 length);      // 802B86B0
		virtual int getHeaderSize();                            // 802B8B40
		virtual int getUncompressedDataSize(const void *data);  // 802B8B30

		void *dest;
		u32 unk;
		CXUncompContextLRC context;
};

class LRCFile {
	public:
		virtual ~LRCFile();                         // 8016B150
		virtual LRCDecompressor *getDecompressor(); // 8016C400
		virtual void nullsub_8016C440();

		u8 unk; // 3 for SZS, 4 for RL, 5 for LZ, 7 for LH and 8 for LRC
		const char* fileExtension;

		static LRCFile instance;  // 80377E08
};
