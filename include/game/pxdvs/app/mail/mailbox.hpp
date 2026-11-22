#ifndef PXDVS_APP_MAILBOX_HPP
#define PXDVS_APP_MAILBOX_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct Mailbox {
    u16 ids[32];
    u16 count;
    u8 flags[4];
    u8 sort;
    u8 unk47;
    u16 sent;
};

typedef char MailboxFlagsOffset[offsetof(Mailbox, flags) == 0x42 ? 1 : -1];
typedef char MailboxSentOffset[offsetof(Mailbox, sent) == 0x48 ? 1 : -1];
typedef char MailboxSize[sizeof(Mailbox) == 0x4A ? 1 : -1];

#endif
