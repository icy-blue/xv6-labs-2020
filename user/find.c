/**
 * Jingcheng Huang
 * icy2000@mail.sdu.edu.cn
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *name) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path); // 2: stderr
        return;
    }

    if (fstat(fd, &st) < 0 || st.type != T_DIR) {
        fprintf(2, "find: cannot open DIR %s\n", path);
        close(fd);
        return;
    }

    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        if (de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        switch (st.type) {
            case T_FILE: {
                if (strcmp(de.name, name) == 0) {
                    printf("%s\n", buf);
                }
                break;
            }

            case T_DIR: {
                if (de.name[0] != '.') {
                    find(buf, name);
                    break;
                }
                break;
            }
        }
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}
