/**
 * Jingcheng Huang
 * icy2000@mail.sdu.edu.cn
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[]) {
    char input[50];
    char *args[50];
    char charset[500];
    memset(args, 0, sizeof(args));
    memset(input, 0, sizeof(input));
    memset(charset, 0, sizeof(charset));
    int arg = argc - 1, chars;
    char *index = charset;
    args[argc - 1] = charset;
    for (int j = 1; j < argc; j++) {
        args[j - 1] = argv[j];
    }
    while ((chars = read(0, input, sizeof(input))) > 0) {
        for (int i = 0; i < chars; i++) {
            switch (input[i]) {
                case ' ': {
                    *index++ = '\0';
                    args[++arg] = index;
                    break;
                }
                case '\n': {
                    *index++ = '\0';
                    if (fork() == 0) {
                        exec(args[0], args);
                    } else {
                        wait(0);
                        memset(args, 0, sizeof(args));
                        memset(charset, 0, sizeof(charset));
                        arg = argc - 1, index = charset;
                        for (int j = 1; j < argc; j++) {
                            args[j - 1] = argv[j];
                        }
                        args[argc - 1] = charset;
                    }
                    break;
                }
                default: {
                    *index++ = input[i];
                }
            }
        }
    }
//    printf("hello\nhello\nhello\n");
    exit(0);
}
