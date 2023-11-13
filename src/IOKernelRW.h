#ifndef IOKERNELRW_H
#define IOKERNELRW_H

#include <IOKit/IOService.h>

class IOKernelRW : public IOService
{
    OSDeclareFinalStructors(IOKernelRW);
public:
    virtual bool start(IOService *provider) override;
};

#endif
