#include "vma.h"
#include "riscv.h"
#include "types.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "defs.h"

struct {
  struct spinlock lock;
  struct VMA vma[NVMA];
}vma_table;

void vma_init() {
  initlock(&vma_table.lock, "vma table");
}

struct VMA *vma_alloc() {
  struct VMA *vma;
  acquire(&vma_table.lock);
  for(int i = 0; i < NVMA; i++) {
    vma = &vma_table.vma[i];
    if(vma->f == 0) {
      release(&vma_table.lock);
      // get a available vma
      return vma;
    }
  }
  release(&vma_table.lock);
  return 0;
}

void vma_free(struct VMA *vma) {
  vma->f = 0;
}