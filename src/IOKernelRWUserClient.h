#ifndef IOKERNELRWUSERCLIENT_H
#define IOKERNELRWUSERCLIENT_H

#include <IOKit/IOUserClient.h>

class IOKernelRWUserClient : public IOUserClient
{
    OSDeclareFinalStructors(IOKernelRWUserClient);
public:
    virtual bool initWithTask(task_t owningTask, void *securityID, uint32_t type) override;
    virtual IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments *args, IOExternalMethodDispatch *dispatch, OSObject *target, void *reference) override;

private:
    static IOReturn readVirt(IOKernelRWUserClient *client, void *reference, IOExternalMethodArguments *args);
    static IOReturn writeVirt(IOKernelRWUserClient *client, void *reference, IOExternalMethodArguments *args);
    static IOReturn readPhys(IOKernelRWUserClient *client, void *reference, IOExternalMethodArguments *args);
    static IOReturn writePhys(IOKernelRWUserClient *client, void *reference, IOExternalMethodArguments *args);

    static IOReturn physcopy(uint64_t src, uint64_t dst, uint64_t len, uint64_t alignment, IODirection direction);
};

#endif
