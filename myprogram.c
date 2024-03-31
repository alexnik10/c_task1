#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>

#define DEFAULT_BLOCK_SIZE 4096

void process_file(int input, int output, int block_size) {
    char buffer[block_size];
    ssize_t bytes_read;
    off_t offset = 0;

    while ((bytes_read = read(input, buffer, block_size)) > 0) {
        int is_zero_block = 1;
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] != 0) {
                is_zero_block = 0;
                break;
            }
        }

        if (is_zero_block) {
            offset += bytes_read;
        } else {
            lseek(output, offset, SEEK_CUR);
            write(output, buffer, bytes_read);
            offset = 0;
        }
    }

    ftruncate(output, lseek(output, 0, SEEK_CUR));
}

int main(int argc, char *argv[]) {
    int opt;
    int block_size = DEFAULT_BLOCK_SIZE;

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
            case 'b':
                block_size = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-b block_size] [input_file] output_file\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    int input = STDIN_FILENO;
    int output;

    if (optind < argc - 1) {
        input = open(argv[optind], O_RDONLY);
        if (input == -1) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        optind++;
    }

    output = open(argv[optind], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output == -1) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    process_file(input, output, block_size);

    close(input);
    close(output);

    return 0;
}