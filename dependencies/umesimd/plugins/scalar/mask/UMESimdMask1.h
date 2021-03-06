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

#ifndef UME_SIMD_MASK_1_H_
#define UME_SIMD_MASK_1_H_

#include "UMESimdMaskPrototype.h"

namespace UME {
namespace SIMD {

    template<>
    class SIMDVecMask<1> :
        public SIMDMaskBaseInterface<
        SIMDVecMask<1>,
        uint32_t,
        1>
    {
        friend class SIMDVec_u<uint32_t, 1>;
        friend class SIMDVec_u<uint64_t, 1>;
        friend class SIMDVec_i<int32_t, 1>;
        friend class SIMDVec_i<int64_t, 1>;
        friend class SIMDVec_f<float, 1>;
        friend class SIMDVec_f<double, 1>;
    private:
        bool mMask;

    public:
        UME_FUNC_ATTRIB SIMDVecMask() {}

        // Regardless of the mask representation, the interface should only allow initialization using 
        // standard bool or using equivalent mask
        UME_FUNC_ATTRIB SIMDVecMask(bool m) {
            mMask = m;
        }

        // LOAD-CONSTR - Construct by loading from memory
        UME_FUNC_ATTRIB explicit SIMDVecMask(bool const * p) {
            mMask = p[0];
        }

        UME_FUNC_ATTRIB SIMDVecMask(SIMDVecMask const & mask) {
            mMask = mask.mMask;
        }

#include "../../../utilities/ignore_warnings_push.h"
#include "../../../utilities/ignore_warnings_unused_parameter.h"

        UME_FUNC_ATTRIB bool extract(uint32_t index) const {
            return mMask;
        }

        // A non-modifying element-wise access operator
        UME_FUNC_ATTRIB bool operator[] (uint32_t index) const {
            return mMask;
        }

        // Element-wise modification operator
        UME_FUNC_ATTRIB void insert(uint32_t index, bool x) {
            mMask = x;
        }

        UME_FUNC_ATTRIB SIMDVecMask & operator= (SIMDVecMask const & mask) {
            mMask = mask.mMask;
            return *this;
        }
#include "../../../utilities/ignore_warnings_pop.h"

        // LANDV
        UME_FUNC_ATTRIB SIMDVecMask land(SIMDVecMask const & maskOp) const {
            bool m0 = mMask && maskOp.mMask;
            return SIMDVecMask(m0);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator& (SIMDVecMask const & maskOp) const {
            return land(maskOp);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator&& (SIMDVecMask const & maskOp) const {
            return land(maskOp);
        }
        // LANDS
        UME_FUNC_ATTRIB SIMDVecMask land(bool value) const {
            bool m0 = mMask && value;
            return SIMDVecMask(m0);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator& (bool value) const {
            return land(value);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator&& (bool value) const {
            return land(value);
        }
        // LANDVA
        UME_FUNC_ATTRIB SIMDVecMask & landa(SIMDVecMask const & maskOp) {
            mMask = mMask && maskOp.mMask;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVecMask & operator&= (SIMDVecMask const & maskOp) {
            return landa(maskOp);
        }
        // LANDSA
        UME_FUNC_ATTRIB SIMDVecMask & landa(bool value) {
            mMask = mMask && value;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVecMask & operator&= (bool value) {
            return landa(value);
        }
        // LORV
        UME_FUNC_ATTRIB SIMDVecMask lor(SIMDVecMask const & maskOp) const {
            bool m0 = mMask || maskOp.mMask;
            return SIMDVecMask(m0);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator| (SIMDVecMask const & maskOp) const {
            return lor(maskOp);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator|| (SIMDVecMask const & maskOp) const {
            return lor(maskOp);
        }
        // LORS
        UME_FUNC_ATTRIB SIMDVecMask lor(bool value) const {
            bool m0 = mMask || value;
            return SIMDVecMask(m0);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator| (bool value) const {
            return lor(value);
        }
        UME_FUNC_ATTRIB SIMDVecMask operator|| (bool value) const {
            return lor(value);
        }
        // LORVA
        UME_FUNC_ATTRIB SIMDVecMask & lora(SIMDVecMask const & maskOp) {
            mMask = mMask || maskOp.mMask;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVecMask & operator|= (SIMDVecMask const & maskOp) {
            return lora(maskOp);
        }
        // LORSA
        UME_FUNC_ATTRIB SIMDVecMask & lora(bool value) {
            mMask = mMask || value;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVecMask & operator|= (bool value) {
            return lora(value);
        }
        // LNOT
        UME_FUNC_ATTRIB SIMDVecMask lnot () const {
            bool m0 = !mMask;
            return SIMDVecMask(m0);
        }
        
        UME_FUNC_ATTRIB SIMDVecMask operator!() const {
            return lnot();
        }

        // HLAND
        UME_FUNC_ATTRIB bool hland() const {
            return mMask;
        }
        // HLOR
        UME_FUNC_ATTRIB bool hlor() const {
            return mMask;
        }
    };

}
}

#endif
