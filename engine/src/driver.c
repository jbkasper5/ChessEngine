#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    int data = 0;
    while(read(STDIN_FILENO, &data, sizeof(int))){
        printf("%d\n", data + 1);
        fflush(stdout);
    }
    return 0;
}