#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define LOG_DIR "wlan_log"
#define INPUT_FILE "dmesg.log"
#define BUFFER_SIZE 1024

void create_log_directory() {
    struct stat st = {0};

    // Buat direktori jika belum ada
    if (stat(LOG_DIR, &st) == -1) {
        mkdir(LOG_DIR, 0700);
    }
}

void process_log_file() {
    FILE *input_file = fopen(INPUT_FILE, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int file_counter = 1;

    while (fgets(buffer, BUFFER_SIZE, input_file)) {
        // Cari string "wlan0" di setiap baris
        if (strstr(buffer, "wlan0") != NULL) {
            char output_file_path[BUFFER_SIZE];
            snprintf(output_file_path, BUFFER_SIZE, "%s/wlan0.log.%d", LOG_DIR, file_counter);

            FILE *output_file = fopen(output_file_path, "w");
            if (output_file == NULL) {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }

            // Tulis baris ke file output
            fputs(buffer, output_file);
            fclose(output_file);

            file_counter++;
        }
    }

    fclose(input_file);
}

int main() {
    create_log_directory();
    process_log_file();
    return 0;
}
