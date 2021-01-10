#pragma once
#include <common.h>
#include <rvl/cx/cx.h>

class RLDecompressor {
	public:
		virtual bool init(void *dest, u32 unk);                 // 802B85C0
		virtual int process(const void *data, u32 length);      // 802B85F0
		virtual int getHeaderSize();                            // 802B8B80
		virtual int getUncompressedDataSize(const void *data);  // 802B8B70

		void *dest;
		u32 unk;
		CXUncompContextRL context;
};

class RLFile {
	public:
		virtual ~RLFile();                          // 8016B190
		virtual RLDecompressor *getDecompressor();  // 8016C3B0
		virtual void nullsub_8016C3F0();

		u8 unk; // 3 for SZS, 4 for RL, 5 for LZ, 7 for LH and 8 for LRC
		u8 pad[3];
		const char* fileExtension[];

		static RLFile instance;  // 80377E14
};
