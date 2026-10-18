extern "C" {
#include <libc/stdarg.h>
#include <libc/stdio.h>
}
#include <global.h>
#include <libc/string.h>
#pragma force_active on
static char _logOutputBuf[256];
static char _logTimeStampBuf[20];
#pragma force_active reset
static char* _logBuffer;
static u16* _lenBuffer;
static u32 _logBufSize,_logLineCount,_logMaxLines,_logStampMode;
static void* _mainThread;
#pragma force_active on
static const char logDigits[]="0123456789ABCDEF";
static const char logNoBuffer[28]="GSlog: Init OK, no buffer\n";
static const char logFailed[20]="GSlog: Init FAILED\n";
static const char logInitialized[44]="GSlog: Init OK, log buffer size %d bytes\n";
static const char logStamp[23]="%d/%02d %d:%02d:%02d] ";
#pragma force_active reset
static const char* _inthexTable=logDigits;
extern "C" { void* GSmemAlloc(u32); void GSmemFree(void*); void* OSGetCurrentThread(); }
void logStrRev(char*);
void logInt2Str(int,char*);
void logHex2Str(u32,char*,bool);
void logFloat2Str(f32,char*,char*);
int logStr2Int(char*);
extern "C" {
char* GSlogGetLine(u32 line) {
    char* buffer=_logBuffer;
    if(!buffer) return 0;
    if(line>_logLineCount) return 0;
    u16* lengths=_lenBuffer;
    u32 offset=0;
    for(u32 i=0;i<line;++i) offset+=lengths[i];
    return buffer+offset;
}
u32 GSlogGetLineCount() { if(_logBuffer==0) return 0; return _logLineCount; }
// Logging output is disabled in the original release build; its variadic entry points remain.
void GSlogWritef(const char*,...) {}
void GSlogWrite(const char*,...) {}
void GSlogSetIP(u32) {}
u8 GSlogInit(u32 bytes,u32 mode) {
    const char* strings=logDigits;
    _logStampMode=mode; _logBufSize=bytes;
    if(!bytes) { GSlogWrite(strings+20); return 1; }
    _logBuffer=(char*)GSmemAlloc(bytes);
    if(!_logBuffer) { GSlogWrite(strings+48); return 0; }
    _logMaxLines=bytes>>7;
    _lenBuffer=(u16*)GSmemAlloc(_logMaxLines*2);
    if(!_lenBuffer) { GSmemFree(_logBuffer); GSlogWrite(strings+48); return 0; }
    _mainThread=OSGetCurrentThread();
    GSlogWrite(strings+68,_logBufSize);
    return 1;
}
}
extern "C" void logVsnprintf_float(char* dest,u32 capacity,const char* format,va_list args) {
    static char fmtbuf[16];
    static char cvtbuf[16];
    static char cvtbuf2[16];
    char* out=dest;
    const char* text;
    char* spec;
    u8 done=0;
    int formatting=0;
    u8 left=0;
    u8 zero=0;
    u8 converted=0;
    while(!done) {
        if((u8)formatting==0) {
            if(*format=='%') {
                if(format[1]=='%') { ++format; *out++='%'; }
                else { spec=fmtbuf; formatting=1; }
            } else { *out++=*format; }
        } else {
            switch(*format) {
            case 'c': cvtbuf[0]=va_arg(args,int); cvtbuf[1]=0; text=cvtbuf; converted=1; break;
            case 'd': logInt2Str(va_arg(args,int),cvtbuf); text=cvtbuf; converted=1; break;
            case 'f': logFloat2Str((f32)va_arg(args,double),cvtbuf,cvtbuf2); text=cvtbuf; converted=1; break;
            case 's': text=va_arg(args,char*); converted=1; break;
            case 'X': case 'x': {
                u32 value=va_arg(args,u32);
                if(*format=='X') logHex2Str(value,cvtbuf,true);
                else logHex2Str(value,cvtbuf,false);
                text=cvtbuf; converted=1; break;
            }
            default: *spec++=*format; break;
            }
            if(converted==1) {
                *spec=0;
                spec=fmtbuf;
                if(*spec=='-') { left=1; ++spec; }
                if(*spec=='0') { zero=1; ++spec; }
                formatting=logStr2Int(spec);
                int length=strlen(text);
                if(formatting>length) {
                    formatting-=length;
                    if(!left) {
                        while(formatting-- && (u32)(out-dest)<capacity) {
                            if(zero) *out++='0'; else *out++=' ';
                        }
                    }
                }
                while(*text && (u32)(out-dest)<capacity) *out++=*text++;
                if(*format=='f') {
                    text=cvtbuf2;
                    int length=strlen(text);
                    char* dot=strchr(spec,'.');
                    if(dot) {
                        formatting=logStr2Int(dot+1);
                        if(formatting>0 && length>formatting) ((char*)text)[formatting]=0;
                    }
                    *out++='.';
                    while(*text && (u32)(out-dest)<capacity) *out++=*text++;
                }
                if(left==1) {
                    while(formatting-- && (u32)(out-dest)<capacity) *out++=' ';
                }
                left=0; zero=0; formatting=0; converted=0;
            }
        }
        if(!*format || (u32)(out-dest)>=capacity) done=1;
        ++format;
    }
    *out=0;
}
void logFloat2Str(f32 value, char* integerText, char* fractionText) {
    if(value<0.0f) { value=-value; *integerText++='-'; }
    int integer=(int)value;
    logInt2Str(integer,integerText);
    value-=(f32)integer;
    f32 threshold=0.1f;
    int zeroes=0;
    for(int i=0;i<10;++i) {
        if(threshold<=value) break;
        threshold/=10.0f;
        ++zeroes;
    }
    char* out=fractionText;
    while(zeroes--) *out++='0';
    value*=1e9f;
    logInt2Str((int)value,out);
    int length=strlen(fractionText);
    out=fractionText+length;
    while(length++<10) *out++='0';
    *out=0;
}
void logHex2Str(u32 value,char* text,bool uppercase) {
    char* out=text;
    do {
        *out=_inthexTable[value&15];
        if(!uppercase && *out>='A') *out+=32;
        value>>=4; ++out;
    } while(value);
    *out=0;
    logStrRev(text);
}
void logInt2Str(int value,char* text) {
    char* out=text;
    u8 negative=0;
    if(value<0) { negative=1; value=-value; }
    do { *out++=_inthexTable[value%10]; value/=10; } while(value);
    if(negative==1) *out++='-';
    *out=0;
    logStrRev(text);
}
int logStr2Int(char* text) {
    int value=0;
    while(*text) {
        if(*text<'0' || *text>'9') break;
        value*=10;
        int digit=*text++;
        value=digit+value;
        value-=48;
    }
    return value;
}
void logStrRev(char* text) {
    u32 length=strlen(text);
    char* end=(char*)(length+(u32)text);
    --end;
    while(text<end) { *text^=*end; *end^=*text; *text^=*end--; ++text; }
}
