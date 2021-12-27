/**
 * Jingcheng Huang
 * icy2000@mail.sdu.edu.cn
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
    if (argc < 1) return -1;
    int x = atoi(argv[1]);
    if(x < 0) return -1;
    sleep(x);
    exit(0);
}