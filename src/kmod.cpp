extern "C"
{

#include <mach/kmod.h>

static kern_return_t start(kmod_info_t *ki, void *data)
{
    return KERN_SUCCESS;
}

static kern_return_t stop(kmod_info_t *ki, void *data)
{
    return KERN_SUCCESS;
}

__attribute__((visibility("default"))) KMOD_EXPLICIT_DECL(net.siguza.iokernelrw, "1.0.0", start, stop);

}
