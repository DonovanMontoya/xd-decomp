#include <game/maximum/GSAPI/baselib/hash.h>

extern void __assert(const char*, int, const char*);

static inline HSD_HashEntry* hashFindEntry(HSD_Hash* hash, unsigned int index, void* key)
{
    HSD_HashEntry* entry = hash->table[index];
    if (entry == 0) {
        return 0;
    }
    while (entry != 0) {
        if (hash->class_info->keycheck(hash, entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return 0;
}

void* HSD_HashSearch(HSD_Hash* hash, void* key, int* success)
{
    unsigned int index = hash->class_info->getidx(hash, key);
    HSD_HashEntry* entry;

    if (index >= hash->table_size) {
        __assert("hash.c", 0x71, "idx < hash->table_size");
    }
    entry = hashFindEntry(hash, index, key);
    if (success != 0) {
        *success = entry != 0;
    }
    return entry != 0 ? entry->value : 0;
}
