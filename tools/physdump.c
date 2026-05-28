#include "../lib/iokernelrw.h"

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv)
{
    if(argc != 4)
    {
        fprintf(stderr, "Usage: %s addr size alignment\n", argv[0]);
        return -1;
    }

    char *end = NULL;
    unsigned long long addr = strtoull(argv[1], &end, 0);
    if(*end != '\0' || argv[1][0] == '\0')
    {
        fprintf(stderr, "Invalid addr: %s\n", argv[1]);
        return -1;
    }

    end = NULL;
    unsigned long long len = strtoull(argv[2], &end, 0);
    if(*end != '\0' || argv[1][0] == '\0')
    {
        fprintf(stderr, "Invalid len: %s\n", argv[2]);
        return -1;
    }

    end = NULL;
    unsigned long long alignment = strtoull(argv[3], &end, 0);
    if(*end != '\0' || argv[1][0] == '\0' || alignment > 0xff)
    {
        fprintf(stderr, "Invalid alignment: %s\n", argv[3]);
        return -1;
    }

    void *buf = malloc(len);
    if(!buf)
    {
        fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno));
        return -1;
    }

    io_connect_t client = iokernelrw_open();
    fprintf(stderr, "client: %x\n", client);
    if(!MACH_PORT_VALID(client))
    {
        return -1;
    }

    kern_return_t ret = iokernelrw_read_phys(client, addr, buf, len, (uint8_t)alignment);
    fprintf(stderr, "read: %x, %s\n", ret, mach_error_string(ret));
    if(ret != KERN_SUCCESS)
    {
        return -1;
    }

    write(1, buf, len);

    free(buf);
    IOServiceClose(client);
    return 0;
}
