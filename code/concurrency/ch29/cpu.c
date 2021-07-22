#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // logical CPUs
    printf("Number of logical CPUs: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
    return 0;
}