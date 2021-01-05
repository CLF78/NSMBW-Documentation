#pragma once
#include <common.h>

// Level completion flags
#define COND_COIN1       0x1
#define COND_COIN2       0x2
#define COND_COIN3       0x4
#define COND_COIN_ALL    0x7
#define COND_NORMAL      0x10
#define COND_SECRET      0x20
#define COND_BOTH_EXITS  0x30
#define COND_SGNORMAL    0x80
#define COND_SGSECRET    0x100

// All of these are set by "SetWorldCompleteionBitfield" at 801028D0.
// It's called by ScStage so it doesn't depend on Nintendo maps.
#define SAVE_BIT_NEW                    0x1
#define SAVE_BIT_GAME_COMPLETE          0x2
#define SAVE_BIT_ALL_EXITS              0x4
#define SAVE_BIT_ALL_STAR_COINS         0x8
#define SAVE_BIT_ALL_STAR_COINS_W9      0x10
#define SAVE_BIT_EVERYTHING_TRULY_DONE  0x20
#define SAVE_BIT_NO_SUPER_GUIDE         0x40

#ifdef __cplusplus
extern "C" {
#endif

// Function that saves the game. USE THIS ONE WHEN SAVING.
void SaveGame(void *classDoesntMatter, bool isQuick); // 8092F5F0

// Overwrites the existing savefile instance. USE WITH CAUTION.
void CreateAllNewSavefile(); // 8015D670

// Other functions
void UpdateCompletionStats();   // 800B5450
void SaveCurrentMapLocation();  // 800FD300

#ifdef __cplusplus
}
#endif

class SaveFirstBlock {
	public:
		char titleID[4];            // 0x00
		u8 is_new;                  // 0x04 (set to 0xE if not new)
		u8 field_01;                // 0x05
		u8 current_file;            // 0x06
		u8 field_03;                // 0x07
		u16 freemode_fav[10][0x2A]; // 0x08
		u16 coinbtl_fav[10][0x2A];  // 0x350
		u16 bitfield;               // 0x698
		u16 field_69A;              // 0x69A
		u32 checksum;               // 0x69C

		// This is called during creation of the savedata struct, useful as a potential hook
		void nullsub_800CE660();

		void SetLastUsedSavefile(int block); // 800CE6E0

		bool LoadFavoriteFreeMode(int world, int level); // 800CE6F0
		void SaveFavoriteFreeMode(int world, int level); // 800CE710

		bool LoadFavoriteCoinBattle(int world, int level); // 800CE730
		void SaveFavoriteCoinBattle(int world, int level); // 800CE750

		void BitfieldSetBit(u8 bit);    // 800CE770
		bool BitfieldCheckBit(u8 bit);  // 800CE790

	private:
		void CheckFirstBlockFilledElseFill();   // 800CE7B0
		void FillNewFirstBlock();               // 800CE670
};

class SaveBlock {
	public:
		SaveBlock();  // 800CDFB0
		~SaveBlock(); // 800E0380

		u8 is_new;                  // 0x00 (set to 0xE if not new)
		u8 field_01;                // 0x01
		u8 bitfield;                // 0x02
		u8 current_world;           // 0x03
		u8 current_subworld;        // 0x04
		u8 current_path_node;       // 0x05
		u8 field_06;                // 0x06
		u8 switch_on;               // 0x07
		u8 field_08;                // 0x08
		u8 powerups_available[7];   // 0x09
		u8 toad_level_idx[10];      // 0x10
		u8 player_continues[4];     // 0x1A
		u8 player_coins[4];         // 0x1E
		u8 player_lives[4];         // 0x22
		u8 player_flags[4];         // 0x26
		u8 player_type[4];          // 0x2A
		u8 player_powerup[4];       // 0x2E
		u8 worlds_available[10];    // 0x32
		u8 ambush_countdown[10][4]; // 0x3C
		u16 field_64;               // 0x64
		u16 spentStarCoins;         // 0x66
		u16 score;                  // 0x68
		u32 completions[10][42];    // 0x6C
		u8 hint_movie_bought[70];   // 0x6FC
		u8 toad_location[10];       // 0x742
		u8 field_74C[10][4];        // 0x74C
		u8 field_774[10][4];        // 0x774 (each field defaults to -1)
		u8 field_79C[10][4];        // 0x79C (each field defaults to 2)
		u8 death_counts[10][42];    // 0x7C4
		u8 death_count_3_4_switch;  // 0x968
		u8 pad[0x13];               // 0x969
		u32 checksum;               // 0x97C

		void SetCharacterForPlayer(int playerID, int character); // 800CE150
		u8 GetCharacterForPlayer(int playerID);                  // 800CE160

		void SetPowerupForPlayer(int playerID, int powerup); // 800CE170
		u8 GetPowerupForPlayer(int playerID);                // 800CE180

		void SetLivesForPlayer(int playerID, int lives); // 800CE190
		u8 GetLivesForPlayer(int playerID);              // 800CE1A0

		void SetStarFlagForPlayer(int playerID, int playerFlag); // 800CE1B0
		bool GetStarFlagForPlayer(int playerID);                 // 800CE1C0

		void SetCoinsForPlayer(int playerID, int coins); // 800CE1D0
		u8 GetCoinsForPlayer(int playerID);              // 800CE1E0

		void SetScore(u32 score); // 800CE1F0
		u32 GetScore();           // 800CE200

		void SetCreditsHighscore(u16 score); // 800CE210
		u16 GetCreditsHighscore();           // 800CE230

		void SetHintMovieBought(int movieID);   // 800CE240
		bool CheckHintMovieBought(int movieID); // 800CE250

		void SetSpecificStarCoinCollected(int world, int level, int starCoin);  // 800CE270
		int GetStarCoinsInWorld(int world);                                     // 800CE280
		bool CheckCoinCollected(int world, int level, int num);                 // 800CE300

		void SetToadByte(int world, int flag);  // 800CE330
		u8 GetToadByte(int world);              // 800CE340

		void SetSuperGuideDeathCount(int world, int level, bool is34SwitchOn, u8 deathcount); // 800CE350
		u8 GetSuperGuideDeathCount(int world, int level, bool is34SwitchOn);                  // 800CE3B0

		void SetContinuesUsed(int playerID, int continues); // 800CE400
		u8 GetContinuesUsed(int playerID);                  // 800CE410

		void SetPowerupCount(int powerup, int count); // 800CE420

		bool CheckWorldAvailability(int world, bool isAvailable);   // 800CE450
		void SetWorldAvailability(int world, bool isAvailable);     // 800CE460
		void UnsetWorldAvailability(int world, bool isAvailable);   // 800CE470

		u32 GetLevelCondition(int world, int level);                // 800CE490
		bool CheckLevelCondition(int world, int level, int cond);   // 800CE4B0
		void SetLevelCondition(int world, int level, int cond);     // 800CE4B0
		void UnsetLevelCondition(int world, int level, int cond);   // 800CE500

		void SetAmbushCountdown(int world, int enemyMaybe, int countdown);  // 800CE520
		u8 GetAmbushCountdown(int world, int enemyMaybe);                   // 800CE540

		void SetByteInArray74C(int world, int enemyMaybe, int value); // 800CE560
		u8 GetByteInArray74C(int world, int enemyMaybe);              // 800CE580

		void SetByteInArray774(int world, int enemyMaybe, int value); // 800CE5A0
		u8 GetByteInArray774(int world, int enemyMaybe);              // 800CE5C0

		void SetByteInArray79C(int world, int enemyMaybe, int value); // 800CE5E0
		u8 GetByteInArray79C(int world, int enemyMaybe);              // 800CE600

		void SetToadLocation(int world, int level); // 800CE620
		u8 GetToadLocation(int world);              // 800CE630

		void SetField6(int value);  // 800CE640
		u8 GetField6();             // 800CE650

	private:
		void CheckBlockFilledElseFill();    // 800CE110
		void FillNewBlock();                // 800CDFC0
};

class SaveFile {
	public:
		SaveFile(); // 800E02C0
		u32 field_00;
		u32 field_04;
		u32 field_08;
		u32 field_0C;
		u32 field_10;
		u32 field_14;
		u32 field_18;
		u32 field_1C;

		// Real savefile starts here
		SaveFirstBlock header;
		SaveBlock blocks[3];
		SaveBlock quickSave[3];

		SaveBlock *GetBlock(int id);    // 800E0470
		SaveBlock *GetQSBlock(int id);  // 800E04A0

		static SaveFile *instance;  // 8042A298
		bool CheckIfWriting();      // 800E0540

	private:
		// Checksum updaters
		void UpdateFirstBlockChecksum(); // 800E0560
		void UpdateSaveChecksums();      // 800E05A0

		// Copies to the buffer and initializes empty save blocks by calling the CheckIfFilled function for each block.
		void SaveGame_Init(); // 800E03C0

		int WriteSaveToBuffer();        // 800E0630
		int WriteQuickSaveToBuffer();   // 800E0E10
		int WriteFirstBlockToBuffer();  // 800E0D10

		void CopyQuickSaveToNormalSave(int block); // 800E1A30

		// Called by the SaveGame function mentioned earlier in the file.
		void SaveGame_Internal(); // 800E1780

		// Called after GameOver and some other places
		void ReloadValuesFromSave(int block); // 800E1930

		// Not sure about these ones...
		void CopyBlockMaybe(u8 src, u8 dest);   // 800E04D0
		int SomethingWithNANDAccess();          // 800E12C0
};

// Convenience functions
inline SaveFile *GetSaveFile() {
	return SaveFile::instance;
}
