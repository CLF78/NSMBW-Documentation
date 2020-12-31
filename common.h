#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Common Number Types */
typedef signed long long s64;
typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef float f32;
typedef double f64;

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef unsigned long size_t;

/* Common Structures */
typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];
typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];
typedef f32 ROMtx[4][3];
typedef f32 (*ROMtxPtr)[3];

typedef struct {f32 x, y;} Vec2, *Vec2Ptr;
typedef struct {f32 x, y, z;} Vec3, *Vec3Ptr;
typedef struct {s16 x, y, z;} S16Vec, *S16VecPtr;
typedef struct {f32 x, y, z, w;} Quat, *QuatPtr;

typedef struct {f32 frame, value, slope;} HermiteKey;

struct PTMF {
	u32 classOffset, vtableOffset;
	void *funcOrVtableLocation;
};

struct TreeNode {
	TreeNode *parent, *child, *prev_sibling, *next_sibling;
	void *obj;
};

struct Tree {
	TreeNode *node;
	PTMF walkFunc;
};

struct LinkListEntry {
	LinkListEntry *prev, *next;
	void *obj;
};

struct OrderedLinkListEntry : LinkListEntry {
	u16 order;
	u16 padding;
};

struct LinkList {
	LinkListEntry *firstEntry, *lastEntry;
	PTMF walkFunc;
};


#ifdef __cplusplus
}
#endif

/* Common Classes */
typedef bool (*ChainedFunc)(void*);

class FunctionChain {
	public:
		ChainedFunc *functions;
		u16 count;
		u16 current;

		void setup(ChainedFunc *functions, u16 count);  // 8015F740
		void process(u16 startIndex);                   // 8015F760
};

#ifdef __cplusplus
extern "C" {
#endif

/* Common Functions */
void OSReport(const char *format, ...); // 8015F870

int memcmp(const void *ptr1, const void *ptr2, size_t num);         // 802DF388
void *memchr(void *ptr, int value, size_t num);                     // 802DF330
void *memcpy(void *dest, const void *src, size_t count);            // 80004364
void *memmove(void *destination, const void *source, size_t num);   // 802DF264
void *memset(void *ptr, int value, size_t num);                     // 800046B4

wchar_t *wmemchr(const wchar_t *ptr, wchar_t wc, size_t num);               // 802E24C4
wchar_t *wmemcpy(wchar_t *destination, const wchar_t *source, size_t num);  // 802E24BC

int snprintf(char *buffer, size_t buff_size, const char *format, ...);  // 802E19D8
int sprintf(char *buffer, const char *format, ...);                     // 802E1ACC

char *strcat(char *dest, const char *src);          // 802E1D2C
char *strcpy(char *dest, const char *src);          // 802E1C28
char *strstr(const char *str1, const char *str2);   // 802E1F78
const char *strchr(const char *str, int character); // 802E1F00
int strcmp(const char *str1, const char *str2);     // 802E1DA4
int stricmp(const char *str1, const char *str2);    // 802E8B5C
int strlen(const char *str);                        // 802DC98C

char *strncat(char *destination, const char *source, size_t num);   // 802E1D58
char *strncpy(char *dest, const char *src, int num);                // 802E1CE8
const char *strrchr(const char *str, int character);                // 802E1F30
int strncmp(const char *str1, const char *str2, int num);           // 802E1EC0
int strnlen(const char *str, size_t max_len);                       // 802244D0

int wcscmp(const wchar_t *wcs1, const wchar_t *wcs2);               // 802E4788
int wcslen(const wchar_t *str);                                     // 802E470C
wchar_t *wcschr(const wchar_t *ws, wchar_t wc);                     // 802E47BC
wchar_t *wcscpy(wchar_t *dest, const wchar_t *src);                 // 802E4728
wchar_t *wcsncpy(wchar_t *dest, const wchar_t *src, size_t num);    // 802E4744

int mbstowcs(wchar_t *dest, const char *src, size_t max); // 802DF0EC
int wcstombs(char *dest, const wchar_t *src, size_t max); // 802DF1AC

int vprintf(const char *format, ...);                               // 802E1850
int vsnprintf(char *s, size_t n, const char *format, ...);          // 802E18CC
int vswprintf(wchar_t *ws, size_t len, const wchar_t *format, ...); // 802E4680

int atoi(const char *str); // 802E23F8
// char *itoa(int value, wchar_t *buffer, int base, size_t size, bool unk); // 800CDD60 (unsure about the arguments, so it's staying ruled out for now)

void bdcmp(const char *bdsrc, const char *bdest); // 801FA4E4
void bdcpy(const char *bdsrc, const char *bdest); // 801FA518

/* Math Functions */
float asin(float x);            // 802E88FC
float acos(float x);            // 802E88F8
float atan(float x);            // 802E7F04
float atan2(float y, float x);  // 802E8900

float cos(float x);     // 802E82AC
float sin(float x);     // 802E87B4
float tan(float x);     // 802E8880
float ceil(float x);    // 802E8134
float floor(float x);   // 802E8374

float sqrt(float x);         // 802E8B58
float pow(float x, float y); // 802E5894

float log10(float x);   // 802E5780
float log(float x);     // 802E54CC

float GetHermiteCurveValue(float currentFrame, HermiteKey* keys, u32 keyCount); // 8017D660

int abs(int n);  // 802DE804
int labs(int n); // 802DE814

/* ASM Helpers */

// Yes i know this sucks.
// Not doing the GPR ones, just use stmw/lmw
// Put r1 + (STACK SPACE) in r11 for these to work

void store_fpr31(); // 802DD028 and upwards
void store_fpr30();
void store_fpr29();
void store_fpr28();
void store_fpr27();
void store_fpr26();
void store_fpr25();
void store_fpr24();
void store_fpr23();
void store_fpr22();
void store_fpr21();
void store_fpr20();
void store_fpr19();
void store_fpr18();
void store_fpr17();
void store_fpr16();
void store_fpr15();
void store_fpr14();

void load_fpr31(); // 802DCFDC and upwards
void load_fpr30();
void load_fpr29();
void load_fpr28();
void load_fpr27();
void load_fpr26();
void load_fpr25();
void load_fpr24();
void load_fpr23();
void load_fpr22();
void load_fpr21();
void load_fpr20();
void load_fpr19();
void load_fpr18();
void load_fpr17();
void load_fpr16();
void load_fpr15();
void load_fpr14();

#ifdef __cplusplus
}
#endif
