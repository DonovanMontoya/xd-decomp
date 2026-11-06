#include <dolphin/types.h>

/* koukaLinkDataBiosGetKouka selects one of eight u16 effect IDs. */
typedef struct KoukaLinkDataRecord { u16 kouka[8]; } KoukaLinkDataRecord;
KoukaLinkDataRecord kouka_link_data[] = {
    { { 0, 0, 0, 0, 0, 0, 0, 0 } },
};

u32 kouka_link_data_number = sizeof(kouka_link_data) / sizeof(kouka_link_data[0]);
