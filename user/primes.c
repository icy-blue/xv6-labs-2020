/**
 * Jingcheng Huang
 * icy2000@mail.sdu.edu.cn
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define length 4


int data[1];

void solve(int p[2], int q[2]) {
    if (fork() == 0) {
        if (read(p[0], data, length) == 0) {
            close(p[0]);
            close(q[1]);
            close(q[0]);
            exit(0);
        }
        int pr = data[0];
        printf("prime %d\n", pr);
        while (read(p[0], data, length) == length) {
            if (data[0] % pr == 0) continue;
            write(q[1], data, length);
        }
        close(q[1]);
        close(p[0]);
        pipe(p);
        solve(q, p);
    } else {
        close(p[0]);
        close(q[1]);
        close(q[0]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int p[2], q[2];
    pipe(p);
    pipe(q);
    for (data[0] = 2; data[0] <= 35; data[0]++) {
        write(p[1], data, length);
    }
    close(p[1]);
    solve(p, q);
    exit(0);
}