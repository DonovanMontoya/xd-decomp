extern "C" {

extern void* _eti_init_info[];
extern int __register_fragment(void* exception_info, void* toc);
extern int __unregister_fragment(int fragment_id);

static int fragmentID = -2;

void __fini_cpp_exceptions(void) {
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

void __init_cpp_exceptions(void) {
    register void* toc;

    if (fragmentID == -2) {
        asm {
            mr toc, r2
        }
        fragmentID = __register_fragment(_eti_init_info, toc);
    }
}

__declspec(section ".ctors") void (*__init_cpp_exceptions_reference)(void) = __init_cpp_exceptions;
__declspec(section ".dtors") void (*__fini_cpp_exceptions_reference)(void) = __fini_cpp_exceptions;

}
