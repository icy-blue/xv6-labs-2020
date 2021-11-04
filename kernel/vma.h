#include "types.h"

#define NVMA 16

struct VMA {
    uint64 addr;
    uint64 length;
    int prot;
    int flags;
    struct file *f;
};
