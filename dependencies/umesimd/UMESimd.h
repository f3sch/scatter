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

#ifndef UME_SIMD_H_
#define UME_SIMD_H_

// Version macros.
#define UME_SIMD_VERSION_MAJOR 0
#define UME_SIMD_VERSION_MINOR 8
#define UME_SIMD_VERSION_PATCH 1

#include <iostream>

#include "UMEBasicTypes.h"

// Always include emulated vector types, so that plugins can use them to emulate unsupported types.
// If an emulated mode is selected, this plugin defines all necessary vector types.

// Define static warning for emulation instantiation. This will be used to inform user which parts of vectorization code are emulated.

// ************************************************************************************************
// Uncomment this define for debug/inefficiences identification. 
//  VS requires at least W3 warning level!!!

//#define UME_SIMD_SHOW_EMULATION_WARNINGS 1

//  Enabling emulation warnings allows tracing of following information:
//    1. UME_EMULATION_WARNING informs which emulated functions are used. Emulated functions are 
//       created for compatibility reasons and thus are considered unoptimal. They should
//       be used for functional testing and debugging, and should be avoided in production codes.
//
//          This type of warning is a STATIC warning emited at compile time.
//
//    2. UME_PERFORMANCE_UNOPTIMAL_WARNING used in plugins to inform that certain operation
//       does not have a counter part in instruction set or specific library. When this warning
//       appears, user should re-consider use of designated function/operator and replace it with
//       specialized code. 
//         
//         This type of warning is a STATIC warning emited at compile time
//
//    3. UME_ALIGNMENT_CHECK used to verify if data pointer is aligned correctly.
//
//         This type of warning is a DYNAMIC warning emited at run time.
//
// ************************************************************************************************
//#define UME_SIMD_SHOW_EMULATION_WARNINGS

#include "UMEInline.h"

// Define target specific attributes
#ifdef __NVCC__
#ifdef __CUDA_ARCH__
// For CUDA we need to mark each function as device code.
#define UME_ENV_FUNC_ATTRIB __device__
#else
#define UME_ENV_FUNC_ATTRIB __host__
#endif
#else
#define UME_ENV_FUNC_ATTRIB
#endif

#define UME_FUNC_ATTRIB UME_FORCE_INLINE UME_ENV_FUNC_ATTRIB


namespace UME {
namespace SIMD {
    // Eache plugin should define this with a 'value' field
    // specialized depending on the architecture used.
    // Sugested values are not guaranteed to give optimal results
    // on any platform, but they could be used as a baseline for
    // specific derived software.
    template<typename SCALAR_T> struct SuggestedVecLen{/*const int value = ? */};
}
}

#if defined FORCE_SCALAR
    #define USING_EMULATED_TYPES 1
    #include "plugins/UMESimdPluginScalarEmulation.h"
#elif defined FORCE_OPENMP
    #include "plugins/UMESimdPluginOpenMP.h"
#else
    #if defined __AVX512F__
        #include "plugins/UMESimdPluginAVX512.h"
    #elif defined (__MIC__)
        #include "plugins/UMESimdPluginKNC.h"
    #elif defined __AVX2__
        #include "plugins/UMESimdPluginAVX2.h"
    #elif defined __AVX__
        #include "plugins/UMESimdPluginAVX.h"
    #elif defined (__aarch64__) || defined (__arm__)
        #include "plugins/UMESimdPluginARM.h"
    #elif defined (__ALTIVEC__)
        #include "plugins/UMESimdPluginAltivec.h"
    #else
        // Use scalar emulation if not specializing
        #define USING_EMULATED_TYPES 1
        #include "plugins/UMESimdPluginScalarEmulation.h"
    #endif // INSTRUCTION SET
#endif

// Traits need to be defined after all SIMD vectors are defined. 
#include "UMESimdTraits.h"
#include "UMESimdScalarOperators.h"
#include "UMESimdInterfaceFunctions.h"

namespace UME {
    namespace SIMD {
        template<typename SCALAR_T, uint32_t VEC_LEN>
        struct BaseVectorType {
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<uint8_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_u<uint8_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<uint16_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_u<uint16_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<uint32_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_u<uint32_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<uint64_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_u<uint64_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<int8_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_i<int8_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<int16_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_i<int16_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<int32_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_i<int32_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<int64_t, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_i<int64_t, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<float, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_f<float, VEC_LEN> BASE_T;
        };

        template<uint32_t VEC_LEN>
        struct BaseVectorType<double, VEC_LEN> {
            typedef typename UME::SIMD::SIMDVec_f<double, VEC_LEN> BASE_T;
        };

        template<typename SCALAR_T, uint32_t VEC_LEN>
        using SIMDVec = typename BaseVectorType<SCALAR_T, VEC_LEN>::BASE_T;
    }
}

#include "UMEMemory.h"

#endif
