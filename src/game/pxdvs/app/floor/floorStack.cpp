#include <global.h>
extern "C" {
extern void GSthreadUnblock(void*); extern void GSthreadBlock(void*); extern void GSthreadSetGroupID(void*,u32);
void GSthreadUnblockGroup(u32);void GSthreadBlockGroup(u32);void* GSmemAlloc(u32);void GSmemFree(void*);void GSresFreeResource(u32,u32);void* memcpy(void*,const void*,u32);
void* floorDataBiosGetPtr(u32);u8 floorDataBiosGetFloorKind(void*);
extern u32 scriptCreateAppScript__Fv(void); extern void* memset(void*,int,u32);
}
enum FloorState { FloorStateNone };
class FloorStack {
public:
    u8 raw[0x224];
    FloorStack(); void clear(); void reallocPushData(); void addResource(u32,u32); void freeResource(u32,u32); void freeAllResource();
    u32 getFloorID() const; void setUpdateState(FloorState);
    void unblock(); void block(); void setGroupID(u32); void setFloorID(u32);
    s32 getObjective(); void clearFlag(); void setPopFlag(); void setPushFlag();
    s32 getScriptModule(); void makeScriptModule(); void setPushState(void*,u32);
};
class GSresID { public: u32 id, value; void set(u32,u32); void clear(); };

class FloorStackList {
public:
 FloorStack* stacks;s32 index;u32 capacity;
 FloorStackList(u32);~FloorStackList();
 FloorStack* getCurrentStack();u32 getGroupID();
 void unblock();void block();void setGroupID(u32);void setPushState(void*,u32);void setUpdateState(FloorState);
 s32 getObjective();void* getGSfloor();s32 getStateMode();FloorStack* pop();FloorStack* push(unsigned int);
};



void FloorStackList::unblock(){GSthreadUnblockGroup(getGroupID());getCurrentStack()->unblock();}

void FloorStackList::block(){GSthreadBlockGroup(getGroupID());getCurrentStack()->block();}

void FloorStackList::setGroupID(u32 id){FloorStack* stack=getCurrentStack();stack->setGroupID(id);stack->unblock();}

void FloorStackList::setPushState(void* data,u32 size){getCurrentStack()->setPushState(data,size);}

void FloorStackList::setUpdateState(FloorState state){getCurrentStack()->setUpdateState(state);}

s32 FloorStackList::getObjective(){return getCurrentStack()->getObjective();}

void* FloorStackList::getGSfloor(){return floorDataBiosGetPtr(getCurrentStack()->getFloorID());}

s32 FloorStackList::getStateMode(){u8 kind=floorDataBiosGetFloorKind(floorDataBiosGetPtr(getCurrentStack()->getFloorID()));if(kind==1)return 1;if(kind==2)return 2;return 0;}

FloorStack* FloorStackList::pop(){index--;FloorStack* stack=getCurrentStack();stack->setPopFlag();return stack;}

FloorStack* FloorStackList::push(unsigned int floor){index++;FloorStack* stack=getCurrentStack();stack->clear();stack->setPushFlag();stack->setFloorID(floor);return stack;}

FloorStackList::~FloorStackList(){if(stacks){delete stacks;stacks=0;}}

FloorStackList::FloorStackList(u32 count){stacks=new FloorStack[count];index=0;capacity=count;for(u32 i=0;i<count;i++)stacks[i].makeScriptModule();}

void FloorStack::addResource(u32 id,u32 value){
 for(GSresID* r=(GSresID*)(raw+0x20);r!=(GSresID*)(raw+0x220);r++){if(r->id==id && r->value==value){GSresFreeResource(r->id,r->value);return;}}
 for(GSresID* r=(GSresID*)(raw+0x20);r!=(GSresID*)(raw+0x220);r++){if(r->id==0){r->set(id,value);return;}}
}

void FloorStack::freeAllResource(){for(GSresID* r=(GSresID*)(raw+0x20);r!=(GSresID*)(raw+0x220);r++){if(r->id)GSresFreeResource(r->id,r->value);}memset(raw+0x20,0,0x200);}

void FloorStack::freeResource(u32 id,u32 value){for(GSresID* r=(GSresID*)(raw+0x20);r!=(GSresID*)(raw+0x220);r++){if(r->id==id && r->value==value){GSresFreeResource(r->id,r->value);r->clear();return;}}}

void FloorStack::unblock(){if(*(u32*)(raw+0x1c)!=0)GSthreadUnblock(*(void**)(raw+0x1c));}

void FloorStack::block(){if(*(u32*)(raw+0x1c)!=0)GSthreadBlock(*(void**)(raw+0x1c));}

void FloorStack::reallocPushData(){void* data=GSmemAlloc(*(u32*)(raw+0xc));if(data){memcpy(data,*(void**)(raw+8),*(u32*)(raw+0xc));GSmemFree(*(void**)(raw+8));*(void**)(raw+8)=data;}}

void FloorStack::setPushState(void* p,u32 n){*(u32*)(raw+8)=(u32)p;*(u32*)(raw+0xc)=n;}

void FloorStack::setGroupID(u32 v){*(u32*)(raw)=v;if(*(u32*)(raw+0x1c)!=0)GSthreadSetGroupID(*(void**)(raw+0x1c),v+0x2000);}

void FloorStack::setFloorID(u32 v){*(u32*)(raw+4)=v;*(u32*)raw=v+0x5001;}

s32 FloorStack::getObjective(){if(raw[0x10])return 1;if(raw[0x11])return 2;return 3;}

void FloorStack::clearFlag(){raw[0x10]=0;raw[0x11]=0;}

void FloorStack::setPopFlag(){raw[0x10]=0;raw[0x11]=1;}

void FloorStack::setPushFlag(){raw[0x10]=1;raw[0x11]=0;}

void FloorStack::clear(){*(u32*)raw=0;*(u32*)(raw+8)=0;raw[0x10]=0;raw[0x11]=0;*(u32*)(raw+0x18)=0;*(u32*)(raw+0x220)=0;*(u32*)(raw+0x1c)=0;memset(raw+0x20,0,0x200);}

s32 FloorStack::getScriptModule(){return *(s32*)(raw+0x14);}

void FloorStack::makeScriptModule(){if(*(u32*)(raw+0x14)==0)*(u32*)(raw+0x14)=scriptCreateAppScript__Fv();}

FloorStack::FloorStack(){clear();*(u32*)(raw+0x14)=0;*(u32*)(raw+0x1c)=0;}

void GSresID::set(u32 a,u32 b){id=a;value=b;}

void GSresID::clear(){id=0;value=0;}
