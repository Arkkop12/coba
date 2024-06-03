#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define INPUT_FILE "dmesg.log"
#define OUTPUT_DIR "wlan_log"
#define BUFFER_SIZE 1024

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int main() {
    FILE *infile;
    char buffer[BUFFER_SIZE];
    int line_counter = 1;

    // Ensure the output directory exists
    ensure_directory_exists(OUTPUT_DIR);

    // Open the input file
    infile = fopen(INPUT_FILE, "r");
    if (infile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Read the input file and process each line
    while (fgets(buffer, BUFFER_SIZE, infile) != NULL) {
        if (strstr(buffer, "wlan0") != NULL) {
            // Define the output file name
            char output_file[BUFFER_SIZE];
            snprintf(output_file, sizeof(output_file), "%s/wlan0.log.%d", OUTPUT_DIR, line_counter);

            // Open the output file
            FILE *outfile = fopen(output_file, "w");
            if (outfile == NULL) {
                perror("Error opening output file");
                fclose(infile);
                return EXIT_FAILURE;
            }

            // Write the line to the output file
            fputs(buffer, outfile);
            fclose(outfile);

            // Increment the line counter
            line_counter++;
        }
    }

    fclose(infile);

    printf("Processed %d lines containing 'wlan0'.\n", line_counter - 1);

    return EXIT_SUCCESS;
}
