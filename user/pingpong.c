/**
 * Jingcheng Huang
 * icy2000@mail.sdu.edu.cn
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int p[2], q[2];
char data[10];

int main(int argc, char *argv[]) {
    pipe(p);
    pipe(q);
    int pid = fork();
    if (pid == 0) {
        read(q[0], data, 4);
        printf("%d: received pong\n", getpid());
        write(p[1], "ping", 4);
    } else {
        write(q[1], "pong", 4);
        read(p[0], data, 4);
        printf("%d: received ping\n", getpid());
    }
    exit(0);
}