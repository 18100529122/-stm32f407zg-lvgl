#ifdef __MINGW32__
#include <stdlib.h>
#include <malloc.h>

void *_aligned_malloc(size_t size, size_t alignment)
{
    // posix_memalign returns 0 on success
    return __mingw_aligned_malloc(size, alignment);
}

void _aligned_free(void *ptr)
{
    __mingw_aligned_free(ptr);
}
#endif
