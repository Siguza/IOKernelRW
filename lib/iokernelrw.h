#ifndef LIBIOKERNELRW_H
#define LIBIOKERNELRW_H

#include <mach/mach.h>
#include <IOKit/IOKitLib.h>

static inline io_connect_t iokernelrw_open(void)
{
    io_service_t service = IOServiceGetMatchingService(kIOMainPortDefault, IOServiceMatching("IOKernelRW"));
    if(!MACH_PORT_VALID(service))
    {
        return MACH_PORT_NULL;
    }

    io_connect_t client = MACH_PORT_NULL;
    kern_return_t ret = IOServiceOpen(service, mach_task_self(), 0, &client);
    IOObjectRelease(service);
    if(ret != KERN_SUCCESS)
    {
        return MACH_PORT_NULL;
    }
    return client;
}

static inline kern_return_t iokernelrw_read(io_connect_t client, uint64_t from, void *to, uint64_t len)
{
    uint64_t in[] = { from, (uint64_t)to, len };
    return IOConnectCallScalarMethod(client, 0, in, 3, NULL, NULL);
}

static inline kern_return_t iokernelrw_write(io_connect_t client, void *from, uint64_t to, uint64_t len)
{
    uint64_t in[] = { (uint64_t)from, to, len };
    return IOConnectCallScalarMethod(client, 1, in, 3, NULL, NULL);
}

static inline kern_return_t iokernelrw_read_phys(io_connect_t client, uint64_t from, void *to, uint64_t len, uint8_t align)
{
    uint64_t in[] = { from, (uint64_t)to, len, align };
    return IOConnectCallScalarMethod(client, 2, in, 4, NULL, NULL);
}

static inline kern_return_t iokernelrw_write_phys(io_connect_t client, void *from, uint64_t to, uint64_t len, uint8_t align)
{
    uint64_t in[] = { (uint64_t)from, to, len, align };
    return IOConnectCallScalarMethod(client, 3, in, 4, NULL, NULL);
}

#endif /* LIBIOKERNELRW_H */
