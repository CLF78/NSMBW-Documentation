#pragma once
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

// Not part of CX, so not documented properly
struct UncompContextSZS {
	u8  *destp;
	s32 destCount;
	s32 forceDestCount;
	u8  unk;
	u8  unk2;
	u8  unk3;
	u8  unk4;
	u16 length;
	u8  headerSizeMaybe;
};

void InitUncompContextSZS(CXUncompContextSZS *context, void *dest);         // 802B8710
s32 ReadUncompSZS(UncompContextSZS *context, const void *data, u32 len);    // 802B8840

#ifdef __cplusplus
}
#endif

class SZSDecompressor {
	public:
		void *vtable;
		void *dest;
		u32 unk;
		UncompContextSZS context;

		virtual bool init(void *dest, u32 unk);                 // 802B8AB0
		virtual int process(const void *data, u32 length);      // 802B8AE0
		virtual int getHeaderSize();                            // 802B8B20
		virtual int getUncompressedDataSize(const void *data);  // 802B8B10

		static SZSDecompressor *instance;  // 80377E14

	private:
		static int getUncompressedDataSizeInternal(const void *data); // 802B86E0
};

class SZSFile {
	public:
		virtual ~SZSFile();                         // 8016B090
		virtual SZSDecompressor *getDecompressor(); // 8016C4F0
		virtual void nullsub_8016C530();
};
