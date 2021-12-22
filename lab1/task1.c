#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

ssize_t processBuffer(char *buff, ssize_t size)
{
    ssize_t changedBytes = 0;
    for (ssize_t i = 0; i <= size; i++)
    {
        if (buff[i] >= 'a' && buff[i] <= 'z')
        {
            buff[i] -= 32;
            changedBytes++;
        }
    }

    return changedBytes;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("No input file in arguments\n");
        exit(1);
    }
    if (argc < 3)
    {
        printf("No output file in arguments\n");
        exit(1);
    }
    
    char *input_file = argv[1];
    char *output_file = argv[2];
    
    
    
    int fIn = open(input_file, O_RDONLY);
    if (fIn == -1)
    {
        printf("Error in input file %s.\n Error: %s\n", input_file, strerror(errno));
        exit(1);
    }

    int fOut = open(output_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fOut == -1)
    {
        printf("No in output file %s.\n Error: %s\n", output_file, strerror(errno));
        exit(1);
    }
    
    int counter = 0;
    
    while(1)
    {
        char *buffer = (char*) malloc(512 * sizeof(char));
        int bytes = read(fIn, buffer, sizeof(buffer));
        for (int i = 0; i < sizeof(buffer); i++)
        {
            if (buffer[i] >= 'a' && buffer[i] <= 'z')
            {
                buffer[i] -= 32;
                counter++;
            }
        }
        write(fOut, buffer, sizeof(buffer));
        if (bytes < sizeof(buffer))
            break;
        free(buffer);
    }

    printf("Changed %d bytes\n", counter);
    
    close(fIn);
    close(fOut);
    
    return 0;
}