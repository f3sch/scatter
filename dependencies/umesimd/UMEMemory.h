// The MIT License (MIT)
//
// Copyright (c) 2015-2017 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's 
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//

#ifndef MEMORY_H_
#define MEMORY_H_

#include <cstring>
#include <cstdlib>
#include <stdlib.h>

#include <iostream>

#include "UMESimd.h"
#include "UMEInline.h"

#if defined (_MSC_VER)
//#define UME_ALIGN(alignment) __declspec(align(alignment))
    #if (_MSC_VER < 1900)
        // Visual studio until 2015 is not supporting standard 'alignas' keyword
        #ifdef alignas
            // This check can be removed when verified that for all other versions alignas works as requested
            #error "UME error: alignas already defined" 
        #else
            #define alignas(alignment) __declspec(align(alignment))
        #endif
    #endif
#elif defined (__GNUC__)
#define UME_ALIGN(alignment) __attribute__ ((aligned(alignment)))

#elif defined (__ICC) || defined(__INTEL_COMPILER)
#endif

#if defined (_MSC_VER) 
    #define UME_RESTRICT __restrict
#else
    #define UME_RESTRICT __restrict__
#endif


#define ALIGNED_TYPE(type, alignment) typedef type UME_ALIGN(alignment)

namespace UME
{

    class DynamicMemory
    {
    public:
        static inline UME_ENV_FUNC_ATTRIB void* Malloc(std::size_t size)
        {
            // TODO: specialize it depending on the architecture and OS
            return std::malloc(size);
        }

        static inline UME_ENV_FUNC_ATTRIB void* AlignedMalloc(std::size_t size, std::size_t alignment)
        {

#if defined(_MSC_VER) && !defined(__NVCC__)
            void* ptr = _aligned_malloc(size, alignment);
            return ptr;
#elif defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER)
            void* memptr;
            //std::cout << "AlignedMalloc: memptr(before):" << memptr;

            int retval = 0;
            do
            {
                retval = posix_memalign(&memptr, alignment, size);
                alignment *= 2;
            } while (retval != 0 && alignment < 2048);

            if (retval != 0)
            {
                std::cout << "posix_memalign error: " << retval << std::endl;
                std::cout << "sizeof(void*): " << sizeof(void*) << std::endl;
            }
            //std::cout << "AlignedMalloc: memptr(after):" << memptr;
            return memptr;
#elif defined(__NVCC__)
            // TODO: aligned alloc required here?
            void* memptr = malloc(size);
            return memptr;
#endif
        }

        static inline UME_ENV_FUNC_ATTRIB void Free(void *ptr)
        {
            // TODO: specialize it depending on the architecture and OS
            std::free(ptr);
        }

        static inline UME_ENV_FUNC_ATTRIB void AlignedFree(void *ptr)
        {
#if defined(_MSC_VER) && !defined(__NVCC__)
            _aligned_free(ptr);
#elif defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__NVCC__)
            free(ptr);
#endif
        }

        static inline UME_ENV_FUNC_ATTRIB void* MemCopy(void *dst, void *src, size_t num)
        {
            // TODO: specialize it depending on the architecture and OS
            return std::memcpy(dst, src, num);
        }
        static inline UME_ENV_FUNC_ATTRIB void MemSet(void *dst, int ch, std::size_t count)
        {
            // TODO: specialize it depending on the architecture and OS
            std::memset(dst, ch, count);
        }
    };

#include "utilities/ignore_warnings_push.h"
#include "utilities/ignore_warnings_unused_parameter.h"

    template<typename T1, typename T2>
    UME_FUNC_ATTRIB T1 reinterpretCast(T2 from) {
        T1 to;
        char* fromPtr = (char*)&from;
        char* toPtr = (char*)&to;
        memcpy(toPtr, fromPtr, sizeof(T2));
        return to;
    }
    
    template<class T, int SIMD_STRIDE>
    struct AlignedAllocator {
    	using value_type = T;
        UME_FUNC_ATTRIB  AlignedAllocator() {}
        UME_FUNC_ATTRIB  ~AlignedAllocator() {}
        template <class U> UME_FUNC_ATTRIB  AlignedAllocator(const AlignedAllocator<U, SIMD_STRIDE> & other) {}
        UME_FUNC_ATTRIB  T* allocate(std::size_t n) {
            uint32_t alignment = UME::SIMD::SIMDVec<T, SIMD_STRIDE>::alignment();
            return (T*)DynamicMemory::AlignedMalloc(n, std::size_t(alignment));
        }
        UME_FUNC_ATTRIB  void deallocate(T* p, std::size_t n) {
            DynamicMemory::AlignedFree(p);
        }
    };
    
    // Specialize for bool
    template<int SIMD_STRIDE>
    struct AlignedAllocator<bool, SIMD_STRIDE> {
        UME_FUNC_ATTRIB  AlignedAllocator() {}
        UME_FUNC_ATTRIB  ~AlignedAllocator() {}
        template <class U> UME_FUNC_ATTRIB AlignedAllocator(const AlignedAllocator<U, SIMD_STRIDE> & other) {}
        UME_FUNC_ATTRIB  bool* allocate(std::size_t n) {
            uint32_t alignment = UME::SIMD::SIMDVecMask<SIMD_STRIDE>::alignment();
            return (bool*)DynamicMemory::AlignedMalloc(n, std::size_t(alignment));
        }
        UME_FUNC_ATTRIB  void deallocate(bool* p, std::size_t n) {
            DynamicMemory::AlignedFree(p);
        }
    };
    
    template <class T, class U, int SIMD_STRIDE1, int SIMD_STRIDE2>
    UME_FUNC_ATTRIB bool operator==(const AlignedAllocator<T, SIMD_STRIDE1>&, const AlignedAllocator<U, SIMD_STRIDE2>&) {
        return std::is_same<T, U>::value && (SIMD_STRIDE1 == SIMD_STRIDE2);
    }
    template <class T, class U, int SIMD_STRIDE1, int SIMD_STRIDE2>
    UME_FUNC_ATTRIB bool operator!=(const AlignedAllocator<T, SIMD_STRIDE1>&, const AlignedAllocator<U, SIMD_STRIDE2>&) {
        return !(std::is_same<T, U>::value && (SIMD_STRIDE1 == SIMD_STRIDE2));
    }
#include "utilities/ignore_warnings_pop.h"
    
    
}


#endif
