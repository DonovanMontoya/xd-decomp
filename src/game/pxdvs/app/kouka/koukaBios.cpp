#include <global.h>
extern "C" {
struct KoukaData { u8 statusKind; u8 var; u16 status; u16 link; s16 value[2]; };
extern KoukaData kouka_data[]; extern u32 kouka_data_number;
extern u8 kouka_link_data[]; extern u32 kouka_link_data_number;
u16 koukaLinkDataBiosGetKouka(u32 id,u32 index){if(id>kouka_link_data_number||index>8)return 0;return *(u16*)(kouka_link_data+id*0x10+index*2);}
u16 koukaDataBiosGetLink(u32 id){if(id>kouka_data_number)return 0;return kouka_data[id].link;}
s16 koukaDataBiosGetValue(u32 id,u32 index){if(id>kouka_data_number||index>2)return 0;return kouka_data[id].value[index];}
u8 koukaDataBiosGetVar(u32 id){if(id>kouka_data_number)return 0;return kouka_data[id].var;}
u16 koukaDataBiosGetStatus(u32 id){if(id>kouka_data_number)return 0;return kouka_data[id].status;}
u8 koukaDataBiosGetStatusKind(u32 id){if(id>kouka_data_number)return 0;return kouka_data[id].statusKind;}
}
