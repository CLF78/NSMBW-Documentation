#pragma once
#include <common.h>
#include <compression/cx.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *RLDecompClass; // 80377E14

#ifdef __cplusplus
}
#endif

class RLDecompressor {
	public:
		void *vtable;
		void *dest;
		u32 unk;
		CXUncompContextRL context;

		virtual bool init(void *dest, u32 unk);                 // 802B85C0
		virtual int process(const void *data, u32 length);      // 802B85F0
		virtual int getHeaderSize();                            // 802B8B80
		virtual int getUncompressedDataSize(const void *data);  // 802B8B70
};

class RLFile {
	public:
		virtual ~RLFile();                          // 8016B190
		virtual RLDecompressor *getDecompressor();  // 8016C3B0
		virtual void nullsub_8016C3F0();
};
