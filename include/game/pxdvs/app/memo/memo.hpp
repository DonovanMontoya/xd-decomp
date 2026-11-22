#ifndef PXDVS_APP_MEMO_HPP
#define PXDVS_APP_MEMO_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct MemoEntry {
    u16 id;
    u32 trainer;
    u32 random;
};

struct Memo {
    u16 count;
    MemoEntry entry[500];
};

typedef char MemoEntrySize[sizeof(MemoEntry) == 0xC ? 1 : -1];
typedef char MemoEntriesOffset[offsetof(Memo, entry) == 4 ? 1 : -1];
typedef char MemoSize[sizeof(Memo) == 0x1774 ? 1 : -1];

#endif
