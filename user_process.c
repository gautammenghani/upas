#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
        int file_desc;
        char c;
        char buffer[10];
        int my_pid = getpid();

        printf("My pid: %d\n", my_pid);
        file_desc = open("/dev/unkill", O_RDWR);
        if (file_desc < 0)
                printf("Error opening file\n");
        printf("File opened\n");
        read(file_desc, &c, my_pid);
        printf("Process is unkillable!\n");
        read(STDIN_FILENO, buffer, 10);
        printf("exiting \n");
        return 0;
}
