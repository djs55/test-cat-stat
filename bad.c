#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void do_echo() {
    int fd = openat(AT_FDCWD, "test1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if (fd == -1) {
        perror("openat");
    }
    int n = write(fd, "Testing\n", 8);
    if (n != 8) {
        perror("write");
    }
    if (close(fd) == -1){
        perror("close");
    }
}

void do_cat(){
    int fd = openat(AT_FDCWD, "test1.txt", O_RDONLY);
    if (fd == -1) {
        perror("openat");
    }
    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        perror("fstat");
    }
    char bytes[16];
    int n = read(fd, &bytes, sizeof(bytes));
    if (n != 8) {
        perror("read");
    }
    bytes[n] = 0;
    if (strcmp(&bytes[0], "Testing\n") != 0) {
        fprintf(stderr, "read %s\n", &bytes[0]);
        exit(1);
    }
    if (close(fd) == -1){
        perror("close");
    }
}

int do_stat(){
    struct stat buf;
    if (lstat("test1.txt", &buf) == -1) {
        perror("lstat");
    }
    printf("stat.st_mtime = %ld\n", buf.st_mtime);
    if (buf.st_mtime == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    printf("I expect a volume to be mounted on /mnt.\n");
    if (chdir("/mnt") == -1) {
        perror("chdir");
    };
    do_echo();
    do_cat();
    do_cat();
    int result = do_stat();
    if (result == 1) {
        printf("Test failed.\n");
        return 1;
    }
    printf("Test succeeded.\n");
    return 0;
}