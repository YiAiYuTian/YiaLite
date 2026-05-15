#include "../../utils/memory/allocator.h"

void* yialiteStbMalloc(size_t size)
{
   return ALLOCATE_SIZED(size);
}

void* yialiteStbRealloc(void* ptr, size_t size)
{
   return REALLOCATE_SIZED(ptr, size);
}

void yialiteStbFree(void* ptr)
{
   DEALLOCATE(ptr);
}

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(sz)           yialiteStbMalloc(sz)
#define STBI_REALLOC(p,newsz)     yialiteStbRealloc(p,newsz)
#define STBI_FREE(p)              yialiteStbFree(p)
#include "stb_image.h"