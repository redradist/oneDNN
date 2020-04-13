/*******************************************************************************
 * Copyright 2020 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#ifndef MEMORY_DEBUG_HPP
#define MEMORY_DEBUG_HPP

#ifndef DNNL_MEM_DEBUG_PROTECT_SIZE
#define DNNL_MEM_DEBUG_PROTECT_SIZE 1
#endif

#define DNNL_MEM_DEBUG_UNDERFLOW 0
#define DNNL_MEM_DEBUG_OVERFLOW 1

#include <stddef.h>

#include "c_types_map.hpp"

namespace dnnl {
namespace impl {
namespace memory_debug {

// Static inline for optimization purposes when memory_debug is disabled
static inline bool is_mem_debug() {
#ifndef DNNL_ENABLE_MEM_DEBUG
    return false;
#else
    return true;
#endif
}

// Static inline for optimization purposes when memory_debug is disabled
static inline bool is_mem_debug_overflow() {
    if (is_mem_debug())
#if (DNNL_ENABLE_MEM_DEBUG == DNNL_MEM_DEBUG_UNDERFLOW)
        return false;
#else
        // Default to DNNL_MEM_DEBUG_OVERFLOW as buffer overflows are a
        // more common memory error.
        return true;
#endif
    else
        return false;
}

void *malloc(size_t size, int alignment);
void free(void *p);

size_t protect_size();
void protect_buffer(const void *addr, size_t size, engine_kind_t engine_kind);
void unprotect_buffer(const void *addr, size_t size, engine_kind_t engine_kind);

} // namespace memory_debug
} // namespace impl
} // namespace dnnl
#endif

// vim: et ts=4 sw=4 cindent cino+=l0,\:4,N-s
