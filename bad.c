#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void test(const char *dir){
    if (chdir(dir) == -1) {
        perror("chdir");
    };
    int fd = open("test1.txt", O_WRONLY|O_CREAT, 0666);
    if (fd == -1) {
        perror("openat");
    }
    // The ftruncate causes the following fstat to return 0 mtime.
    if (ftruncate(fd, 0) == -1) {
        perror("ftruncate");
    }
    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        perror("fstat");
    }
    if (close(fd) == -1){
        perror("close");
    }
    printf("  stat.st_mtime = %ld\n", buf.st_mtime);
    if (buf.st_mtime == 0) {
        printf("  Test failed.\n");
        return;
    }
    printf("  Test succeeded.\n");
}

int main(int argc, char *argv[]) {
    printf("I expect a volume to be mounted on /mnt.\n");
    printf("in / (regular filesystem):\n");
    test("/");
    printf("in /mnt (shared volume):\n");
    test("/mnt");
}