#pragma once
#include <common.h>
#include <rvl/dvd/dvd.h>

#ifdef __cplusplus
extern "C" {
#endif

void DVDClearQueue(); // 801CFBB0

bool DVDPushWaitingQueue(s32 prio, DVDCommandBlock *block); // 801CFBF0
bool DVDCheckWaitingQueue();                                // 801CFD00
bool DVDDequeueWaitingQueue(DVDCommandBlock *block);        // 801CFDD0

DVDCommandBlock* DVDPopWaitingQueue();      // 801CFC60
DVDCommandBlock* DVDGetNextWaitingQueue();  // 801CFD60

#ifdef __cplusplus
}
#endif
