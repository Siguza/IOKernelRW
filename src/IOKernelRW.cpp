#include <IOKit/IOService.h>
#include "IOKernelRW.h"

#define super IOService
OSDefineMetaClassAndFinalStructors(IOKernelRW, IOService)

bool IOKernelRW::start(IOService *provider)
{
    if(!super::start(provider))
    {
        return false;
    }

    registerService();

    return true;
}
