#include <stdlib.h>
#include <stdio.h>

void echo() {
    open("test1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) 
    write(1, "Testing\n", 8)
    close(3) 
}

void cat(){
    open("test1.txt", O_RDONLY) 
    sendfile(1, 3, NULL, 16777216) 
    close(3)  
}

void stat(){
    lstat("test1.txt", {st_mode=S_IFREG|0755, st_size=8, ...})
}

int main(int argc, char *argv[]) {
    echo()
    cat()
    cat()
    stat()
    return 0;
}