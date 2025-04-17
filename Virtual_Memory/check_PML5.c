
#include <stdio.h>
#include <cpuid.h>

int main() {
    unsigned int eax, ebx, ecx, edx;
    __cpuid_count(7, 0, eax, ebx, ecx, edx);

    if (ecx & (1 << 16)) {
        printf("PML5 is supported!\n");
    } else {
        printf("PML5 is NOT supported.\n");
    }

    return 0;
}
