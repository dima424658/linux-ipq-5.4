/* SPDX-License-Identifier: GPL-2.0 */
#ifndef DMA_H
#define DMA_H

#include <asm/glue-cache.h>

#ifndef MULTI_CACHE

/*
 * These are private to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to system memory is
 * visible to the CPU.
 */

/* These turn into function declarations for each per-CPU glue function */
void __glue(_CACHE,_dma_map_area)(const void *, size_t, int);
void __glue(_CACHE,_dma_unmap_area)(const void *, size_t, int);

static inline void __nocfi dmac_map_area(const void *start, size_t sz, int flags)
{
	__glue(_CACHE,_dma_map_area)(start, sz, flags);
}

static inline void __nocfi dmac_unmap_area(const void *start, size_t sz, int flags)
{
	__glue(_CACHE,_dma_unmap_area)(start, sz, flags);
}

#else

/*
 * These are private to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to system memory is
 * visible to the CPU.
 */
static inline void __nocfi dmac_map_area(const void *start, size_t sz, int flags)
{
	cpu_cache.dma_map_area(start, sz, flags);
}
static inline void __nocfi dmac_unmap_area(const void *start, size_t sz, int flags)
{
	cpu_cache.dma_unmap_area(start, sz, flags);
}

#endif

#endif
