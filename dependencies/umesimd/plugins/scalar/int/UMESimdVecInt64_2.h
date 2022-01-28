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

#ifndef UME_SIMD_VEC_INT64_2_H_
#define UME_SIMD_VEC_INT64_2_H_

#include <type_traits>

#include "../../../UMESimdInterface.h"

namespace UME {
namespace SIMD {

    template<>
    class SIMDVec_i<int64_t, 2> :
        public SIMDVecSignedInterface<
            SIMDVec_i<int64_t, 2>,
            SIMDVec_u<uint64_t, 2>,
            int64_t,
            2,
            uint64_t,
            SIMDVecMask<2>,
            SIMDSwizzle<2>> ,
        public SIMDVecPackableInterface<
            SIMDVec_i<int64_t, 2>,
            SIMDVec_i<int64_t, 1 >>
    {
        friend class SIMDVec_u<uint64_t, 2>;
        friend class SIMDVec_f<float, 2>;
        friend class SIMDVec_f<double, 2>;

        friend class SIMDVec_i<int64_t, 4>;
    private:
        int64_t mVec[2];

    public:
        constexpr static uint32_t length() { return 2; }
        constexpr static uint32_t alignment() { return 16; }

        // ZERO-CONSTR
        UME_FUNC_ATTRIB SIMDVec_i() {};
        // SET-CONSTR
        UME_FUNC_ATTRIB SIMDVec_i(int64_t i) {
            mVec[0] = i;
            mVec[1] = i;
        }
        // This constructor is used to force types other than SCALAR_TYPES
        // to be promoted to SCALAR_TYPE instead of SCALAR_TYPE*. This prevents
        // ambiguity between SET-CONSTR and LOAD-CONSTR.
        template<typename T>
        UME_FUNC_ATTRIB SIMDVec_i(
            T i, 
            typename std::enable_if< std::is_fundamental<T>::value &&
                                    !std::is_same<T, int64_t>::value,
                                    void*>::type = nullptr)
        : SIMDVec_i(static_cast<int64_t>(i)) {}
        // LOAD-CONSTR
        UME_FUNC_ATTRIB explicit SIMDVec_i(int64_t const *p) {
            mVec[0] = p[0];
            mVec[1] = p[1];
        }
        // FULL-CONSTR
        UME_FUNC_ATTRIB SIMDVec_i(int64_t i0, int64_t i1) {
            mVec[0] = i0;
            mVec[1] = i1;
        }

        // EXTRACT
        UME_FUNC_ATTRIB int64_t extract(uint32_t index) const {
            return mVec[index & 1];
        }
        UME_FUNC_ATTRIB int64_t operator[] (uint32_t index) const {
            return extract(index);
        }

        // INSERT
        UME_FUNC_ATTRIB SIMDVec_i & insert(uint32_t index, int64_t value) {
            mVec[index] = value;
            return *this;
        }
        UME_FUNC_ATTRIB IntermediateIndex<SIMDVec_i, int64_t> operator[] (uint32_t index) {
            return IntermediateIndex<SIMDVec_i, int64_t>(index, static_cast<SIMDVec_i &>(*this));
        }

        // Override Mask Access operators
#if defined(USE_PARENTHESES_IN_MASK_ASSIGNMENT)
        UME_FUNC_ATTRIB IntermediateMask<SIMDVec_i, int64_t, SIMDVecMask<2>> operator() (SIMDVecMask<2> const & mask) {
            return IntermediateMask<SIMDVec_i, int64_t, SIMDVecMask<2>>(mask, static_cast<SIMDVec_i &>(*this));
        }
#else
        UME_FUNC_ATTRIB IntermediateMask<SIMDVec_i, int64_t, SIMDVecMask<2>> operator[] (SIMDVecMask<2> const & mask) {
            return IntermediateMask<SIMDVec_i, int64_t, SIMDVecMask<2>>(mask, static_cast<SIMDVec_i &>(*this));
        }
#endif

        // ****************************************************************************************
        // Overloading Interface functions starts here!
        // ****************************************************************************************

        // ASSIGNV
        UME_FUNC_ATTRIB SIMDVec_i & assign(SIMDVec_i const & b) {
            mVec[0] = b.mVec[0];
            mVec[1] = b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator= (SIMDVec_i const & b) {
            return assign(b);
        }
        // MASSIGNV
        UME_FUNC_ATTRIB SIMDVec_i & assign(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0] == true) mVec[0] = b.mVec[0];
            if (mask.mMask[1] == true) mVec[1] = b.mVec[1];
            return *this;
        }
        // ASSIGNS
        UME_FUNC_ATTRIB SIMDVec_i & assign(int64_t b) {
            mVec[0] = b;
            mVec[1] = b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator=(int64_t b) {
            return assign(b);
        }
        // MASSIGNS
        UME_FUNC_ATTRIB SIMDVec_i & assign(SIMDVecMask<2> const & mask, int64_t b) {
            if (mask.mMask[0] == true) mVec[0] = b;
            if (mask.mMask[1] == true) mVec[1] = b;
            return *this;
        }

        // PREFETCH0
        // PREFETCH1
        // PREFETCH2

        // LOAD
        UME_FUNC_ATTRIB SIMDVec_i & load(int64_t const *p) {
            mVec[0] = p[0];
            mVec[1] = p[1];
            return *this;
        }
        // MLOAD
        UME_FUNC_ATTRIB SIMDVec_i & load(SIMDVecMask<2> const & mask, int64_t const *p) {
            if (mask.mMask[0] == true) mVec[0] = p[0];
            if (mask.mMask[1] == true) mVec[1] = p[1];
            return *this;
        }
        // LOADA
        UME_FUNC_ATTRIB SIMDVec_i & loada(int64_t const *p) {
            mVec[0] = p[0];
            mVec[1] = p[1];
            return *this;
        }
        // MLOADA
        UME_FUNC_ATTRIB SIMDVec_i & loada(SIMDVecMask<2> const & mask, int64_t const *p) {
            if (mask.mMask[0] == true) mVec[0] = p[0];
            if (mask.mMask[1] == true) mVec[1] = p[1];
            return *this;
        }
        // STORE
        UME_FUNC_ATTRIB int64_t* store(int64_t* p) const {
            p[0] = mVec[0];
            p[1] = mVec[1];
            return p;
        }
        // MSTORE
        UME_FUNC_ATTRIB int64_t* store(SIMDVecMask<2> const & mask, int64_t* p) const {
            if (mask.mMask[0] == true) p[0] = mVec[0];
            if (mask.mMask[1] == true) p[1] = mVec[1];
            return p;
        }
        // STOREA
        UME_FUNC_ATTRIB int64_t* storea(int64_t* p) const {
            p[0] = mVec[0];
            p[1] = mVec[1];
            return p;
        }
        // MSTOREA
        UME_FUNC_ATTRIB int64_t* storea(SIMDVecMask<2> const & mask, int64_t* p) const {
            if (mask.mMask[0] == true) p[0] = mVec[0];
            if (mask.mMask[1] == true) p[1] = mVec[1];
            return p;
        }

        // BLENDV
        UME_FUNC_ATTRIB SIMDVec_i blend(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BLENDS
        UME_FUNC_ATTRIB SIMDVec_i blend(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? b : mVec[0];
            int64_t t1 = mask.mMask[1] ? b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // SWIZZLE
        // SWIZZLEA

        // ADDV
        UME_FUNC_ATTRIB SIMDVec_i add(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] + b.mVec[0];
            int64_t t1 = mVec[1] + b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator+ (SIMDVec_i const & b) const {
            return add(b);
        }
        // MADDV
        UME_FUNC_ATTRIB SIMDVec_i add(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] + b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] + b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // ADDS
        UME_FUNC_ATTRIB SIMDVec_i add(int64_t b) const {
            int64_t t0 = mVec[0] + b;
            int64_t t1 = mVec[1] + b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator+ (int64_t b) const {
            return add(b);
        }
        // MADDS
        UME_FUNC_ATTRIB SIMDVec_i add(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] + b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] + b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // ADDVA
        UME_FUNC_ATTRIB SIMDVec_i & adda(SIMDVec_i const & b) {
            mVec[0] += b.mVec[0];
            mVec[1] += b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator+= (SIMDVec_i const & b) {
            return adda(b);
        }
        // MADDVA
        UME_FUNC_ATTRIB SIMDVec_i & adda(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            mVec[0] = mask.mMask[0] ? mVec[0] + b.mVec[0] : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] + b.mVec[1] : mVec[1];
            return *this;
        }
        // ADDSA
        UME_FUNC_ATTRIB SIMDVec_i & adda(int64_t b) {
            mVec[0] += b;
            mVec[1] += b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator+= (int64_t b) {
            return adda(b);
        }
        // MADDSA
        UME_FUNC_ATTRIB SIMDVec_i & adda(SIMDVecMask<2> const & mask, int64_t b) {
            mVec[0] = mask.mMask[0] ? mVec[0] + b : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] + b : mVec[1];
            return *this;
        }
        // SADDV
        UME_FUNC_ATTRIB SIMDVec_i sadd(SIMDVec_i const & b) const {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();
            int64_t t[2];

            for (int i = 0; i < 2; i++) {
                if (mVec[i] > 0 && b.mVec[i] > 0 && (MAX_VAL - mVec[i] < b.mVec[i])) {
                    t[i] =  MAX_VAL;
                }
                else if (mVec[i] < 0 && b.mVec[i] < 0 && (MIN_VAL - mVec[i] > b.mVec[i])) {
                    t[i] = MIN_VAL;
                }
                else {
                    t[i] = mVec[i] + b.mVec[i];
                }
            }
            return SIMDVec_i(t[0], t[1]);
        }
        // MSADDV
        UME_FUNC_ATTRIB SIMDVec_i sadd(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();
            int64_t t[2];

            for (int i = 0; i < 2; i++) {
                if (mask.mMask[i] == true)
                {
                    if (mVec[i] > 0 && b.mVec[i] > 0 && (MAX_VAL - mVec[i] < b.mVec[i])) {
                        t[i] = MAX_VAL;
                    }
                    else if (mVec[i] < 0 && b.mVec[i] < 0 && (MIN_VAL - mVec[i] > b.mVec[i])) {
                        t[i] = MIN_VAL;
                    }
                    else {
                        t[i] = mVec[i] + b.mVec[i];
                    }
                }
                else {
                    t[i] = mVec[i];
                }
            }
            return SIMDVec_i(t[0], t[1]);
        }
        // SADDS
        UME_FUNC_ATTRIB SIMDVec_i sadd(int64_t b) const {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();
            int64_t t[2];

            for (int i = 0; i < 2; i++) {
                if (mVec[i] > 0 && b > 0 && (MAX_VAL - mVec[i] < b)) {
                    t[i] = MAX_VAL;
                }
                else if (mVec[i] < 0 && b < 0 && (MIN_VAL - mVec[i] > b)) {
                    t[i] = MIN_VAL;
                }
                else {
                    t[i] = mVec[i] + b;
                }
            }
            return SIMDVec_i(t[0], t[1]);
        }
        // MSADDS
        UME_FUNC_ATTRIB SIMDVec_i sadd(SIMDVecMask<2> const & mask, int64_t b) const {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();
            int64_t t[2];

            for (int i = 0; i < 2; i++) {
                if (mask.mMask[i] == true)
                {
                    if (mVec[i] > 0 && b > 0 && (MAX_VAL - mVec[i] < b)) {
                        t[i] = MAX_VAL;
                    }
                    else if (mVec[i] < 0 && b < 0 && (MIN_VAL - mVec[i] > b)) {
                        t[i] = MIN_VAL;
                    }
                    else {
                        t[i] = mVec[i] + b;
                    }
                }
                else {
                    t[i] = mVec[i];
                }
            }
            return SIMDVec_i(t[0], t[1]);
        }
        // SADDVA
        UME_FUNC_ATTRIB SIMDVec_i & sadda(SIMDVec_i const & b) {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();

            for (int i = 0; i < 2; i++) {
                if (mVec[i] > 0 && b.mVec[i] > 0 && (MAX_VAL - mVec[i] < b.mVec[i])) {
                    mVec[i] = MAX_VAL;
                }
                else if (mVec[i] < 0 && b.mVec[i] < 0 && (MIN_VAL - mVec[i] > b.mVec[i])) {
                    mVec[i] = MIN_VAL;
                }
                else {
                    mVec[i] = mVec[i] + b.mVec[i];
                }
            }
            return *this;
        }
        // MSADDVA
        UME_FUNC_ATTRIB SIMDVec_i & sadda(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();

            for (int i = 0; i < 2; i++) {
                if (mask.mMask[i] == true)
                {
                    if (mVec[i] > 0 && b.mVec[i] > 0 && (MAX_VAL - mVec[i] < b.mVec[i])) {
                        mVec[i] = MAX_VAL;
                    }
                    else if (mVec[i] < 0 && b.mVec[i] < 0 && (MIN_VAL - mVec[i] > b.mVec[i])) {
                        mVec[i] = MIN_VAL;
                    }
                    else {
                        mVec[i] = mVec[i] + b.mVec[i];
                    }
                }
            }

            return *this;
        }
        // SADDSA
        UME_FUNC_ATTRIB SIMDVec_i & sadd(int64_t b) {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();

            for (int i = 0; i < 2; i++) {
                if (mVec[i] > 0 && b > 0 && (MAX_VAL - mVec[i] < b)) {
                    mVec[i] = MAX_VAL;
                }
                else if (mVec[i] < 0 && b < 0 && (MIN_VAL - mVec[i] > b)) {
                    mVec[i] = MIN_VAL;
                }
                else {
                    mVec[i] = mVec[i] + b;
                }
            }
            return *this;
        }
        // MSADDSA
        UME_FUNC_ATTRIB SIMDVec_i & sadda(SIMDVecMask<2> const & mask, int64_t b) {
            const int64_t MAX_VAL = std::numeric_limits<int64_t>::max();
            const int64_t MIN_VAL = std::numeric_limits<int64_t>::min();

            for (int i = 0; i < 2; i++) {
                if (mask.mMask[i] == true)
                {
                    if (mVec[i] > 0 && b > 0 && (MAX_VAL - mVec[i] < b)) {
                        mVec[i] = MAX_VAL;
                    }
                    else if (mVec[i] < 0 && b < 0 && (MIN_VAL - mVec[i] > b)) {
                        mVec[i] = MIN_VAL;
                    }
                    else {
                        mVec[i] = mVec[i] + b;
                    }
                }
            }
            return *this;
        }
        // POSTINC
        UME_FUNC_ATTRIB SIMDVec_i postinc() {
            int64_t t0 = mVec[0];
            int64_t t1 = mVec[1];
            mVec[0]++;
            mVec[1]++;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator++ (int) {
            return postinc();
        }
        // MPOSTINC
        UME_FUNC_ATTRIB SIMDVec_i postinc(SIMDVecMask<2> const & mask) {
            int64_t t0 = mVec[0];
            int64_t t1 = mVec[1];
            if(mask.mMask[0] == true) mVec[0]++;
            if(mask.mMask[1] == true) mVec[1]++;
            return SIMDVec_i(t0, t1);
        }
        // PREFINC
        UME_FUNC_ATTRIB SIMDVec_i & prefinc() {
            mVec[0]++;
            mVec[1]++;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator++ () {
            return prefinc();
        }
        // MPREFINC
        UME_FUNC_ATTRIB SIMDVec_i & prefinc(SIMDVecMask<2> const & mask) {
            if (mask.mMask[0] == true) mVec[0]++;
            if (mask.mMask[1] == true) mVec[1]++;
            return *this;
        }
        // SUBV
        UME_FUNC_ATTRIB SIMDVec_i sub(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] - b.mVec[0];
            int64_t t1 = mVec[1] - b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator- (SIMDVec_i const & b) const {
            return sub(b);
        }
        // MSUBV
        UME_FUNC_ATTRIB SIMDVec_i sub(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] - b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] - b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // SUBS
        UME_FUNC_ATTRIB SIMDVec_i sub(int64_t b) const {
            int64_t t0 = mVec[0] - b;
            int64_t t1 = mVec[1] - b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator- (int64_t b) const {
            return sub(b);
        }
        // MSUBS
        UME_FUNC_ATTRIB SIMDVec_i sub(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] - b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] - b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // SUBVA
        UME_FUNC_ATTRIB SIMDVec_i & suba(SIMDVec_i const & b) {
            mVec[0] -= b.mVec[0];
            mVec[1] -= b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator-= (SIMDVec_i const & b) {
            return suba(b);
        }
        // MSUBVA
        UME_FUNC_ATTRIB SIMDVec_i & suba(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            mVec[0] = mask.mMask[0] ? mVec[0] - b.mVec[0] : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] - b.mVec[1] : mVec[1];
            return *this;
        }
        // SUBSA
        UME_FUNC_ATTRIB SIMDVec_i & suba(int64_t b) {
            mVec[0] -= b;
            mVec[1] -= b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator-= (int64_t b) {
            return suba(b);
        }
        // MSUBSA
        UME_FUNC_ATTRIB SIMDVec_i & suba(SIMDVecMask<2> const & mask, int64_t b) {
            mVec[0] = mask.mMask[0] ? mVec[0] - b : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] - b : mVec[1];
            return *this;
        }
        // SSUBV
        UME_FUNC_ATTRIB SIMDVec_i ssub(SIMDVec_i const & b) const {
            int64_t t0 = (mVec[0] < b.mVec[0]) ? 0 : mVec[0] - b.mVec[0];
            int64_t t1 = (mVec[1] < b.mVec[1]) ? 0 : mVec[1] - b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MSSUBV
        UME_FUNC_ATTRIB SIMDVec_i ssub(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mVec[0], t1 = mVec[1];
            if (mask.mMask[0] == true) {
                t0 = (mVec[0] < b.mVec[0]) ? 0 : mVec[0] - b.mVec[0];
            }
            if (mask.mMask[1] == true) {
                t1 = (mVec[1] < b.mVec[1]) ? 0 : mVec[1] - b.mVec[1];
            }
            return SIMDVec_i(t0, t1);
        }
        // SSUBS
        UME_FUNC_ATTRIB SIMDVec_i ssub(int64_t b) const {
            int64_t t0 = (mVec[0] < b) ? 0 : mVec[0] - b;
            int64_t t1 = (mVec[1] < b) ? 0 : mVec[1] - b;
            return SIMDVec_i(t0, t1);
        }
        // MSSUBS
        UME_FUNC_ATTRIB SIMDVec_i ssub(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mVec[0], t1 = mVec[1];
            if (mask.mMask[0] == true) {
                t0 = (mVec[0] < b) ? 0 : mVec[0] - b;
            }
            if (mask.mMask[1] == true) {
                t1 = (mVec[1] < b) ? 0 : mVec[1] - b;
            }
            return SIMDVec_i(t0, t1);
        }
        // SSUBVA
        UME_FUNC_ATTRIB SIMDVec_i & ssuba(SIMDVec_i const & b) {
            mVec[0] =  (mVec[0] < b.mVec[0]) ? 0 : mVec[0] - b.mVec[0];
            mVec[1] =  (mVec[1] < b.mVec[1]) ? 0 : mVec[1] - b.mVec[1];
            return *this;
        }
        // MSSUBVA
        UME_FUNC_ATTRIB SIMDVec_i & ssuba(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0] == true) {
                mVec[0] = (mVec[0] < b.mVec[0]) ? 0 : mVec[0] - b.mVec[0];
            }
            if (mask.mMask[1] == true) {
                mVec[0] = (mVec[0] < b.mVec[0]) ? 0 : mVec[0] - b.mVec[0];
            }
            return *this;
        }
        // SSUBSA
        UME_FUNC_ATTRIB SIMDVec_i & ssuba(int64_t b) {
            mVec[0] = (mVec[0] < b) ? 0 : mVec[0] - b;
            mVec[1] = (mVec[1] < b) ? 0 : mVec[1] - b;
            return *this;
        }
        // MSSUBSA
        UME_FUNC_ATTRIB SIMDVec_i & ssuba(SIMDVecMask<2> const & mask, int64_t b)  {
            if (mask.mMask[0] == true) {
                mVec[0] = (mVec[0] < b) ? 0 : mVec[0] - b;
            }
            if (mask.mMask[1] == true) {
                mVec[1] = (mVec[1] < b) ? 0 : mVec[1] - b;
            }
            return *this;
        }
        // SUBFROMV
        UME_FUNC_ATTRIB SIMDVec_i subfrom(SIMDVec_i const & b) const {
            int64_t t0 = b.mVec[0] - mVec[0];
            int64_t t1 = b.mVec[1] - mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MSUBFROMV
        UME_FUNC_ATTRIB SIMDVec_i subfrom(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? b.mVec[0] - mVec[0]: b.mVec[0];
            int64_t t1 = mask.mMask[1] ? b.mVec[1] - mVec[1]: b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // SUBFROMS
        UME_FUNC_ATTRIB SIMDVec_i subfrom(int64_t b) const {
            int64_t t0 = b - mVec[0];
            int64_t t1 = b - mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MSUBFROMS
        UME_FUNC_ATTRIB SIMDVec_i subfrom(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? b - mVec[0] : b;
            int64_t t1 = mask.mMask[1] ? b - mVec[1] : b;
            return SIMDVec_i(t0, t1);
        }
        // SUBFROMVA
        UME_FUNC_ATTRIB SIMDVec_i & subfroma(SIMDVec_i const & b) {
            mVec[0] = b.mVec[0] - mVec[0];
            mVec[1] = b.mVec[1] - mVec[1];
            return *this;
        }
        // MSUBFROMVA
        UME_FUNC_ATTRIB SIMDVec_i & subfroma(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            mVec[0] = mask.mMask[0] ? b.mVec[0] - mVec[0] : b.mVec[0];
            mVec[1] = mask.mMask[1] ? b.mVec[1] - mVec[1] : b.mVec[1];
            return *this;
        }
        // SUBFROMSA
        UME_FUNC_ATTRIB SIMDVec_i & subfroma(int64_t b) {
            mVec[0] = b - mVec[0];
            mVec[1] = b - mVec[1];
            return *this;
        }
        // MSUBFROMSA
        UME_FUNC_ATTRIB SIMDVec_i & subfroma(SIMDVecMask<2> const & mask, int64_t b) {
            mVec[0] = mask.mMask[0] ? b - mVec[0] : b;
            mVec[1] = mask.mMask[1] ? b - mVec[1] : b;
            return *this;
        }
        // POSTDEC
        UME_FUNC_ATTRIB SIMDVec_i postdec() {
            int64_t t0 = mVec[0], t1 = mVec[1];
            mVec[0]--;
            mVec[1]--;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator-- (int) {
            return postdec();
        }
        // MPOSTDEC
        UME_FUNC_ATTRIB SIMDVec_i postdec(SIMDVecMask<2> const & mask) {
            int64_t t0 = mVec[0], t1 = mVec[1];
            if (mask.mMask[0] == true) mVec[0]--;
            if (mask.mMask[1] == true) mVec[1]--;
            return SIMDVec_i(t0, t1);
        }
        // PREFDEC
        UME_FUNC_ATTRIB SIMDVec_i & prefdec() {
            mVec[0]--;
            mVec[1]--;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator-- () {
            return prefdec();
        }
        // MPREFDEC
        UME_FUNC_ATTRIB SIMDVec_i & prefdec(SIMDVecMask<2> const & mask) {
            if (mask.mMask[0] == true) mVec[0]--;
            if (mask.mMask[1] == true) mVec[1]--;
            return *this;
        }
        // MULV
        UME_FUNC_ATTRIB SIMDVec_i mul(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] * b.mVec[0];
            int64_t t1 = mVec[1] * b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator* (SIMDVec_i const & b) const {
            return mul(b);
        }
        // MMULV
        UME_FUNC_ATTRIB SIMDVec_i mul(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] * b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] * b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MULS
        UME_FUNC_ATTRIB SIMDVec_i mul(int64_t b) const {
            int64_t t0 = mVec[0] * b;
            int64_t t1 = mVec[1] * b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator* (int64_t b) const {
            return mul(b);
        }
        // MMULS
        UME_FUNC_ATTRIB SIMDVec_i mul(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] * b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] * b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MULVA
        UME_FUNC_ATTRIB SIMDVec_i & mula(SIMDVec_i const & b) {
            mVec[0] *= b.mVec[0];
            mVec[1] *= b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator*= (SIMDVec_i const & b) {
            return mula(b);
        }
        // MMULVA
        UME_FUNC_ATTRIB SIMDVec_i & mula(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            mVec[0] = mask.mMask[0] ? mVec[0] * b.mVec[0] : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] * b.mVec[1] : mVec[1];
            return *this;
        }
        // MULSA
        UME_FUNC_ATTRIB SIMDVec_i & mula(int64_t b) {
            mVec[0] *= b;
            mVec[1] *= b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator*= (int64_t b) {
            return mula(b);
        }
        // MMULSA
        UME_FUNC_ATTRIB SIMDVec_i & mula(SIMDVecMask<2> const & mask, int64_t b) {
            mVec[0] = mask.mMask[0] ? mVec[0] * b : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] * b : mVec[1];
            return *this;
        }
        // DIVV
        UME_FUNC_ATTRIB SIMDVec_i div(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] / b.mVec[0];
            int64_t t1 = mVec[1] / b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator/ (SIMDVec_i const & b) const {
            return div(b);
        }
        // MDIVV
        UME_FUNC_ATTRIB SIMDVec_i div(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] / b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] / b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // DIVS
        UME_FUNC_ATTRIB SIMDVec_i div(int64_t b) const {
            int64_t t0 = mVec[0] / b;
            int64_t t1 = mVec[1] / b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator/ (int64_t b) const {
            return div(b);
        }
        // MDIVS
        UME_FUNC_ATTRIB SIMDVec_i div(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] / b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] / b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // DIVVA
        UME_FUNC_ATTRIB SIMDVec_i & diva(SIMDVec_i const & b) {
            mVec[0] /= b.mVec[0];
            mVec[1] /= b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator/= (SIMDVec_i const & b) {
            return diva(b);
        }
        // MDIVVA
        UME_FUNC_ATTRIB SIMDVec_i & diva(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            mVec[0] = mask.mMask[0] ? mVec[0] / b.mVec[0] : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] / b.mVec[1] : mVec[1];
            return *this;
        }
        // DIVSA
        UME_FUNC_ATTRIB SIMDVec_i & diva(int64_t b) {
            mVec[0] /= b;
            mVec[1] /= b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator/= (int64_t b) {
            return diva(b);
        }
        // MDIVSA
        UME_FUNC_ATTRIB SIMDVec_i & diva(SIMDVecMask<2> const & mask, int64_t b) {
            mVec[0] = mask.mMask[0] ? mVec[0] / b : mVec[0];
            mVec[1] = mask.mMask[1] ? mVec[1] / b : mVec[1];
            return *this;
        }
        // RCP
        // MRCP
        // RCPS
        // MRCPS
        // RCPA
        // MRCPA
        // RCPSA
        // MRCPSA

        // CMPEQV
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpeq (SIMDVec_i const & b) const {
            bool m0 = mVec[0] == b.mVec[0];
            bool m1 = mVec[1] == b.mVec[1];
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator== (SIMDVec_i const & b) const {
            return cmpeq(b);
        }
        // CMPEQS
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpeq (int64_t b) const {
            bool m0 = mVec[0] == b;
            bool m1 = mVec[1] == b;
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator== (int64_t b) const {
            return cmpeq(b);
        }
        // CMPNEV
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpne (SIMDVec_i const & b) const {
            bool m0 = mVec[0] != b.mVec[0];
            bool m1 = mVec[1] != b.mVec[1];
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator!= (SIMDVec_i const & b) const {
            return cmpne(b);
        }
        // CMPNES
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpne (int64_t b) const {
            bool m0 = mVec[0] != b;
            bool m1 = mVec[1] != b;
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator!= (int64_t b) const {
            return cmpne(b);
        }
        // CMPGTV
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpgt (SIMDVec_i const & b) const {
            bool m0 = mVec[0] > b.mVec[0];
            bool m1 = mVec[1] > b.mVec[1];
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator> (SIMDVec_i const & b) const {
            return cmpgt(b);
        }
        // CMPGTS
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpgt (int64_t b) const {
            bool m0 = mVec[0] > b;
            bool m1 = mVec[1] > b;
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator> (int64_t b) const {
            return cmpgt(b);
        }
        // CMPLTV
        UME_FUNC_ATTRIB SIMDVecMask<2> cmplt (SIMDVec_i const & b) const {
            bool m0 = mVec[0] < b.mVec[0];
            bool m1 = mVec[1] < b.mVec[1];
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator< (SIMDVec_i const & b) const {
            return cmplt(b);
        }
        // CMPLTS
        UME_FUNC_ATTRIB SIMDVecMask<2> cmplt (int64_t b) const {
            bool m0 = mVec[0] < b;
            bool m1 = mVec[1] < b;
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator< (int64_t b) const {
            return cmplt(b);
        }
        // CMPGEV
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpge (SIMDVec_i const & b) const {
            bool m0 = mVec[0] >= b.mVec[0];
            bool m1 = mVec[1] >= b.mVec[1];
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator>= (SIMDVec_i const & b) const {
            return cmpge(b);
        }
        // CMPGES
        UME_FUNC_ATTRIB SIMDVecMask<2> cmpge (int64_t b) const {
            bool m0 = mVec[0] >= b;
            bool m1 = mVec[1] >= b;
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator>= (int64_t b) const {
            return cmpge(b);
        }
        // CMPLEV
        UME_FUNC_ATTRIB SIMDVecMask<2> cmple (SIMDVec_i const & b) const {
            bool m0 = mVec[0] <= b.mVec[0];
            bool m1 = mVec[1] <= b.mVec[1];
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator<= (SIMDVec_i const & b) const {
            return cmple(b);
        }
        // CMPLES
        UME_FUNC_ATTRIB SIMDVecMask<2> cmple (int64_t b) const {
            bool m0 = mVec[0] <= b;
            bool m1 = mVec[1] <= b;
            return SIMDVecMask<2>(m0, m1);
        }
        UME_FUNC_ATTRIB SIMDVecMask<2> operator<= (int64_t b) const {
            return cmple(b);
        }
        // CMPEV
        UME_FUNC_ATTRIB bool cmpe (SIMDVec_i const & b) const {
            bool m0 = mVec[0] == b.mVec[0];
            bool m1 = mVec[0] == b.mVec[1];
            return m0 && m1;
        }
        // CMPES
        UME_FUNC_ATTRIB bool cmpe(int64_t b) const {
            bool m0 = mVec[0] == b;
            bool m1 = mVec[1] == b;
            return m0 && m1;
        }
        // UNIQUE
        UME_FUNC_ATTRIB bool unique() const {
            return mVec[0] != mVec[1];
        }
        // HADD
        UME_FUNC_ATTRIB int64_t hadd() const {
            return mVec[0] + mVec[1];
        }
        // MHADD
        UME_FUNC_ATTRIB int64_t hadd(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : 0;
            int64_t t1 = mask.mMask[1] ? mVec[1] : 0;
            return t0 + t1;
        }
        // HADDS
        UME_FUNC_ATTRIB int64_t hadd(int64_t b) const {
            return mVec[0] + mVec[1] + b;
        }
        // MHADDS
        UME_FUNC_ATTRIB int64_t hadd(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] + b : b;
            int64_t t1 = mask.mMask[1] ? mVec[1] + t0 : t0;
            return t1;
        }
        // HMUL
        UME_FUNC_ATTRIB int64_t hmul() const {
            return mVec[0] * mVec[1];
        }
        // MHMUL
        UME_FUNC_ATTRIB int64_t hmul(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : 1;
            int64_t t1 = mask.mMask[1] ? mVec[1]*t0 : t0;
            return t1;
        }
        // HMULS
        UME_FUNC_ATTRIB int64_t hmul(int64_t b) const {
            return mVec[0] * mVec[1] * b;
        }
        // MHMULS
        UME_FUNC_ATTRIB int64_t hmul(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] * b : b;
            int64_t t1 = mask.mMask[1] ? mVec[1] * t0 : t0;
            return t1;
        }

        // FMULADDV
        UME_FUNC_ATTRIB SIMDVec_i fmuladd(SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = mVec[0] * b.mVec[0] + c.mVec[0];
            int64_t t1 = mVec[1] * b.mVec[1] + c.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MFMULADDV
        UME_FUNC_ATTRIB SIMDVec_i fmuladd(SIMDVecMask<2> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = mask.mMask[0] ? (mVec[0] * b.mVec[0] + c.mVec[0]) : mVec[0];
            int64_t t1 = mask.mMask[1] ? (mVec[1] * b.mVec[1] + c.mVec[1]) : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // FMULSUBV
        UME_FUNC_ATTRIB SIMDVec_i fmulsub(SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = mVec[0] * b.mVec[0] - c.mVec[0];
            int64_t t1 = mVec[1] * b.mVec[1] - c.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MFMULSUBV
        UME_FUNC_ATTRIB SIMDVec_i fmulsub(SIMDVecMask<2> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = mask.mMask[0] ? (mVec[0] * b.mVec[0] - c.mVec[0]) : mVec[0];
            int64_t t1 = mask.mMask[1] ? (mVec[1] * b.mVec[1] - c.mVec[1]) : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // FADDMULV
        UME_FUNC_ATTRIB SIMDVec_i faddmul(SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = (mVec[0] + b.mVec[0]) * c.mVec[0];
            int64_t t1 = (mVec[1] + b.mVec[1]) * c.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MFADDMULV
        UME_FUNC_ATTRIB SIMDVec_i faddmul(SIMDVecMask<2> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = mask.mMask[0] ? ((mVec[0] + b.mVec[0]) * c.mVec[0]) : mVec[0];
            int64_t t1 = mask.mMask[1] ? ((mVec[1] + b.mVec[1]) * c.mVec[1]) : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // FSUBMULV
        UME_FUNC_ATTRIB SIMDVec_i fsubmul(SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = (mVec[0] - b.mVec[0]) * c.mVec[0];
            int64_t t1 = (mVec[1] - b.mVec[1]) * c.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MFSUBMULV
        UME_FUNC_ATTRIB SIMDVec_i fsubmul(SIMDVecMask<2> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            int64_t t0 = mask.mMask[0] ? ((mVec[0] - b.mVec[0]) * c.mVec[0]) : mVec[0];
            int64_t t1 = mask.mMask[1] ? ((mVec[1] - b.mVec[1]) * c.mVec[1]) : mVec[1];
            return SIMDVec_i(t0, t1);
        }

        // MAXV
        UME_FUNC_ATTRIB SIMDVec_i max(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] > b.mVec[0] ? mVec[0] : b.mVec[0];
            int64_t t1 = mVec[1] > b.mVec[1] ? mVec[1] : b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MMAXV
        UME_FUNC_ATTRIB SIMDVec_i max(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mVec[0], t1  = mVec[1];
            if (mask.mMask[0] == true) {
                t0 = mVec[0] > b.mVec[0] ? mVec[0] : b.mVec[0];
            }
            if (mask.mMask[1] == true) {
                t0 = mVec[1] > b.mVec[1] ? mVec[1] : b.mVec[1];
            }
            return SIMDVec_i(t0, t1);
        }
        // MAXS
        UME_FUNC_ATTRIB SIMDVec_i max(int64_t b) const {
            int64_t t0 = mVec[0] > b ? mVec[0] : b;
            int64_t t1 = mVec[1] > b ? mVec[1] : b;
            return SIMDVec_i(t0, t1);
        }
        // MMAXS
        UME_FUNC_ATTRIB SIMDVec_i max(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mVec[0], t1 = mVec[1];
            if (mask.mMask[0] == true) {
                t0 = mVec[0] > b ? mVec[0] : b;
            }
            if (mask.mMask[1] == true) {
                t1 = mVec[1] > b ? mVec[1] : b;
            }
            return SIMDVec_i(t0, t1);
        }
        // MAXVA
        UME_FUNC_ATTRIB SIMDVec_i & maxa(SIMDVec_i const & b) {
            mVec[0] = mVec[0] > b.mVec[0] ? mVec[0] : b.mVec[0];
            mVec[1] = mVec[1] > b.mVec[1] ? mVec[1] : b.mVec[1];
            return *this;
        }
        // MMAXVA
        UME_FUNC_ATTRIB SIMDVec_i & maxa(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0] == true && mVec[0] < b.mVec[0]) {
                mVec[0] = b.mVec[0];
            }
            if (mask.mMask[1] == true && mVec[1] < b.mVec[1]) {
                mVec[1] = b.mVec[1];
            }
            return *this;
        }
        // MAXSA
        UME_FUNC_ATTRIB SIMDVec_i & maxa(int64_t b) {
            mVec[0] = mVec[0] > b ? mVec[0] : b;
            mVec[1] = mVec[1] > b ? mVec[1] : b;
            return *this;
        }
        // MMAXSA
        UME_FUNC_ATTRIB SIMDVec_i & maxa(SIMDVecMask<2> const & mask, int64_t b) {
            if (mask.mMask[0] == true && mVec[0] < b) {
                mVec[0] = b;
            }
            if (mask.mMask[1] == true && mVec[1] < b) {
                mVec[1] = b;
            }
            return *this;
        }
        // MINV
        UME_FUNC_ATTRIB SIMDVec_i min(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] < b.mVec[0] ? mVec[0] : b.mVec[0];
            int64_t t1 = mVec[1] < b.mVec[1] ? mVec[1] : b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MMINV
        UME_FUNC_ATTRIB SIMDVec_i min(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mVec[0], t1 = mVec[1];
            if (mask.mMask[0] == true) {
                t0 = mVec[0] < b.mVec[0] ? mVec[0] : b.mVec[0];
            }
            if (mask.mMask[1] == true) {
                t1 = mVec[1] < b.mVec[1] ? mVec[1] : b.mVec[1];
            }
            return SIMDVec_i(t0, t1);
        }
        // MINS
        UME_FUNC_ATTRIB SIMDVec_i min(int64_t b) const {
            int64_t t0 = mVec[0] < b ? mVec[0] : b;
            int64_t t1 = mVec[1] < b ? mVec[1] : b;
            return SIMDVec_i(t0, t1);
        }
        // MMINS
        UME_FUNC_ATTRIB SIMDVec_i min(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mVec[0], t1 = mVec[1];
            if (mask.mMask[0] == true) {
                t0 = mVec[0] < b ? mVec[0] : b;
            }
            if (mask.mMask[1] == true) {
                t1 = mVec[1] < b ? mVec[1] : b;
            }
            return SIMDVec_i(t0, t1);
        }
        // MINVA
        UME_FUNC_ATTRIB SIMDVec_i & mina(SIMDVec_i const & b) {
            if(mVec[0] > b.mVec[0]) mVec[0] = b.mVec[0];
            if(mVec[1] > b.mVec[1]) mVec[1] = b.mVec[1];
            return *this;
        }
        // MMINVA
        UME_FUNC_ATTRIB SIMDVec_i & mina(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0] == true && mVec[0] > b.mVec[0]) {
                mVec[0] = b.mVec[0];
            }
            if (mask.mMask[1] == true && mVec[1] > b.mVec[1]) {
                mVec[1] = b.mVec[1];
            }
            return *this;
        }
        // MINSA
        UME_FUNC_ATTRIB SIMDVec_i & mina(int64_t b) {
            if(mVec[0] > b) mVec[0] = b;
            if(mVec[1] > b) mVec[1] = b;
            return *this;
        }
        // MMINSA
        UME_FUNC_ATTRIB SIMDVec_i & mina(SIMDVecMask<2> const & mask, int64_t b) {
            if (mask.mMask[0] == true && mVec[0] > b) {
                mVec[0] = b;
            }
            if (mask.mMask[1] == true && mVec[1] > b) {
                mVec[1] = b;
            }
            return *this;
        }
        // HMAX
        UME_FUNC_ATTRIB int64_t hmax () const {
            return mVec[0] > mVec[1] ? mVec[0] : mVec[1];
        }
        // MHMAX
        UME_FUNC_ATTRIB int64_t hmax(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : std::numeric_limits<int64_t>::min();
            int64_t t1 = (mask.mMask[1] && mVec[1] > t0) ? mVec[1] : t0;
            return t1;
        }
        // IMAX
        UME_FUNC_ATTRIB int32_t imax() const {
            return mVec[0] > mVec[1] ? 0 : 1;
        }
        // MIMAX
        UME_FUNC_ATTRIB int32_t imax(SIMDVecMask<2> const & mask) const {
            int32_t i0 = 0xFFFFFFFF;
            int64_t t0 = std::numeric_limits<int64_t>::min();
            if(mask.mMask[0] == true) {
                i0 = 0;
                t0 = mVec[0];
            }
            if(mask.mMask[1] == true && mVec[1] > t0) {
                i0 = 1;
            }
            return i0;
        }
        // HMIN
        UME_FUNC_ATTRIB int64_t hmin() const {
            return mVec[0] < mVec[1] ? mVec[0] : mVec[1];
        }
        // MHMIN
        UME_FUNC_ATTRIB int64_t hmin(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : std::numeric_limits<int64_t>::max();
            int64_t t1 = (mask.mMask[1] && mVec[1] < t0) ? mVec[1] : t0;
            return t1;
        }
        // IMIN
        UME_FUNC_ATTRIB int32_t imin() const {
            return mVec[0] < mVec[1] ? 0 : 1;
        }
        // MIMIN
        UME_FUNC_ATTRIB int32_t imin(SIMDVecMask<2> const & mask) const {
            int32_t i0 = 0xFFFFFFFF;
            int64_t t0 = std::numeric_limits<int64_t>::max();
            if(mask.mMask[0] == true) {
                i0 = 0;
                t0 = mVec[0];
            }
            if(mask.mMask[1] == true && mVec[1] < t0) {
                i0 = 1;
            }
            return i0;
        }

        // BANDV
        UME_FUNC_ATTRIB SIMDVec_i band(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] & b.mVec[0];
            int64_t t1 = mVec[1] & b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator& (SIMDVec_i const & b) const {
            return band(b);
        }
        // MBANDV
        UME_FUNC_ATTRIB SIMDVec_i band(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] & b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] & b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BANDS
        UME_FUNC_ATTRIB SIMDVec_i band(int64_t b) const {
            int64_t t0 = mVec[0] & b;
            int64_t t1 = mVec[1] & b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator& (int64_t b) const {
            return band(b);
        }
        // MBANDS
        UME_FUNC_ATTRIB SIMDVec_i band(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] & b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] & b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BANDVA
        UME_FUNC_ATTRIB SIMDVec_i & banda(SIMDVec_i const & b) {
            mVec[0] &= b.mVec[0];
            mVec[1] &= b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator&= (SIMDVec_i const & b) {
            return banda(b);
        }
        // MBANDVA
        UME_FUNC_ATTRIB SIMDVec_i & banda(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0]) mVec[0] &= b.mVec[0];
            if (mask.mMask[1]) mVec[1] &= b.mVec[1];
            return *this;
        }
        // BANDSA
        UME_FUNC_ATTRIB SIMDVec_i & banda(int64_t b) {
            mVec[0] &= b;
            mVec[1] &= b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator&= (bool b) {
            return banda(b);
        }
        // MBANDSA
        UME_FUNC_ATTRIB SIMDVec_i & banda(SIMDVecMask<2> const & mask, int64_t b) {
            if(mask.mMask[0]) mVec[0] &= b;
            if(mask.mMask[1]) mVec[1] &= b;
            return *this;
        }
        // BORV
        UME_FUNC_ATTRIB SIMDVec_i bor(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] | b.mVec[0];
            int64_t t1 = mVec[1] | b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator| (SIMDVec_i const & b) const {
            return bor(b);
        }
        // MBORV
        UME_FUNC_ATTRIB SIMDVec_i bor(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] | b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] | b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BORS
        UME_FUNC_ATTRIB SIMDVec_i bor(int64_t b) const {
            int64_t t0 = mVec[0] | b;
            int64_t t1 = mVec[1] | b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator| (int64_t b) const {
            return bor(b);
        }
        // MBORS
        UME_FUNC_ATTRIB SIMDVec_i bor(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] | b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] | b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BORVA
        UME_FUNC_ATTRIB SIMDVec_i & bora(SIMDVec_i const & b) {
            mVec[0] |= b.mVec[0];
            mVec[1] |= b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator|= (SIMDVec_i const & b) {
            return bora(b);
        }
        // MBORVA
        UME_FUNC_ATTRIB SIMDVec_i & bora(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0]) mVec[0] |= b.mVec[0];
            if (mask.mMask[1]) mVec[1] |= b.mVec[1];
            return *this;
        }
        // BORSA
        UME_FUNC_ATTRIB SIMDVec_i & bora(int64_t b) {
            mVec[0] |= b;
            mVec[1] |= b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator|= (int64_t b) {
            return bora(b);
        }
        // MBORSA
        UME_FUNC_ATTRIB SIMDVec_i & bora(SIMDVecMask<2> const & mask, int64_t b) {
            if (mask.mMask[0]) mVec[0] |= b;
            if (mask.mMask[1]) mVec[1] |= b;
            return *this;
        }
        // BXORV
        UME_FUNC_ATTRIB SIMDVec_i bxor(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] ^ b.mVec[0];
            int64_t t1 = mVec[1] ^ b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator^ (SIMDVec_i const & b) const {
            return bxor(b);
        }
        // MBXORV
        UME_FUNC_ATTRIB SIMDVec_i bxor(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] ^ b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] ^ b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BXORS
        UME_FUNC_ATTRIB SIMDVec_i bxor(int64_t b) const {
            int64_t t0 = mVec[0] ^ b;
            int64_t t1 = mVec[1] ^ b;
            return SIMDVec_i(t0, t1);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator^ (int64_t b) const {
            return bxor(b);
        }
        // MBXORS
        UME_FUNC_ATTRIB SIMDVec_i bxor(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] ^ b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] ^ b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BXORVA
        UME_FUNC_ATTRIB SIMDVec_i & bxora(SIMDVec_i const & b) {
            mVec[0] ^= b.mVec[0];
            mVec[1] ^= b.mVec[1];
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator^= (SIMDVec_i const & b) {
            return bxora(b);
        }
        // MBXORVA
        UME_FUNC_ATTRIB SIMDVec_i & bxora(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0]) mVec[0] ^= b.mVec[0];
            if (mask.mMask[1]) mVec[1] ^= b.mVec[1];
            return *this;
        }
        // BXORSA
        UME_FUNC_ATTRIB SIMDVec_i & bxora(int64_t b) {
            mVec[0] ^= b;
            mVec[1] ^= b;
            return *this;
        }
        UME_FUNC_ATTRIB SIMDVec_i & operator^= (int64_t b) {
            return bxora(b);
        }
        // MBXORSA
        UME_FUNC_ATTRIB SIMDVec_i & bxora(SIMDVecMask<2> const & mask, int64_t b) {
            if (mask.mMask[0]) mVec[0] ^= b;
            if (mask.mMask[1]) mVec[1] ^= b;
            return *this;
        }
        // BNOT
        UME_FUNC_ATTRIB SIMDVec_i bnot() const {
            return SIMDVec_i(~mVec[0], ~mVec[1]);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator~ () const {
            return bnot();
        }
        // MBNOT
        UME_FUNC_ATTRIB SIMDVec_i bnot(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? ~mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? ~mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // BNOTA
        UME_FUNC_ATTRIB SIMDVec_i & bnota() {
            mVec[0] = ~mVec[0];
            mVec[1] = ~mVec[1];
            return *this;
        }
        // MBNOTA
        UME_FUNC_ATTRIB SIMDVec_i & bnota(SIMDVecMask<2> const & mask) {
            if(mask.mMask[0]) mVec[0] = ~mVec[0];
            if(mask.mMask[1]) mVec[1] = ~mVec[1];
            return *this;
        }
        // HBAND
        UME_FUNC_ATTRIB int64_t hband() const {
            return mVec[0] & mVec[1];
        }
        // MHBAND
        UME_FUNC_ATTRIB int64_t hband(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : std::numeric_limits<int64_t>::max();
            int64_t t1 = mask.mMask[1] ? mVec[1] & t0 : t0;
            return t1;
        }
        // HBANDS
        UME_FUNC_ATTRIB int64_t hband(int64_t b) const {
            return mVec[0] & mVec[1] & b;
        }
        // MHBANDS
        UME_FUNC_ATTRIB int64_t hband(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] & b: b;
            int64_t t1 = mask.mMask[1] ? mVec[1] & t0: t0;
            return t1;
        }
        // HBOR
        UME_FUNC_ATTRIB int64_t hbor() const {
            return mVec[0] | mVec[1];
        }
        // MHBOR
        UME_FUNC_ATTRIB int64_t hbor(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : 0;
            int64_t t1 = mask.mMask[1] ? mVec[1] | t0 : t0;
            return t1;
        }
        // HBORS
        UME_FUNC_ATTRIB int64_t hbor(int64_t b) const {
            return mVec[0] | mVec[1] | b;
        }
        // MHBORS
        UME_FUNC_ATTRIB int64_t hbor(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] | b : b;
            int64_t t1 = mask.mMask[1] ? mVec[1] | t0 : t0;
            return t1;
        }
        // HBXOR
        UME_FUNC_ATTRIB int64_t hbxor() const {
            return mVec[0] ^ mVec[1];
        }
        // MHBXOR
        UME_FUNC_ATTRIB int64_t hbxor(SIMDVecMask<2> const & mask) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] : 0;
            int64_t t1 = mask.mMask[1] ? mVec[1] ^ t0 : t0;
            return t1;
        }
        // HBXORS
        UME_FUNC_ATTRIB int64_t hbxor(int64_t b) const {
            return mVec[0] ^ mVec[1] ^ b;
        }
        // MHBXORS
        UME_FUNC_ATTRIB int64_t hbxor(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] ^ b : b;
            int64_t t1 = mask.mMask[1] ? mVec[1] ^ t0 : t0;
            return t1;
        }

        // GATHERS
        UME_FUNC_ATTRIB SIMDVec_i & gather(int64_t const * baseAddr, uint64_t const * indices) {
            mVec[0] = baseAddr[indices[0]];
            mVec[1] = baseAddr[indices[1]];
            return *this;
        }
        // MGATHERS
        UME_FUNC_ATTRIB SIMDVec_i & gather(SIMDVecMask<2> const & mask, int64_t const * baseAddr, uint64_t const * indices) {
            if (mask.mMask[0] == true) mVec[0] = baseAddr[indices[0]];
            if (mask.mMask[1] == true) mVec[1] = baseAddr[indices[1]];
            return *this;
        }
        // GATHERV
        UME_FUNC_ATTRIB SIMDVec_i gather(int64_t const * baseAddr, SIMDVec_u<uint64_t, 2> const & indices) {
            mVec[0] = baseAddr[indices.mVec[0]];
            mVec[1] = baseAddr[indices.mVec[1]];
            return *this;
        }
        // MGATHERV
        UME_FUNC_ATTRIB SIMDVec_i gather(SIMDVecMask<2> const & mask, int64_t const * baseAddr, SIMDVec_u<uint64_t, 2> const & indices) {
            if (mask.mMask[0] == true) mVec[0] = baseAddr[indices.mVec[0]];
            if (mask.mMask[1] == true) mVec[1] = baseAddr[indices.mVec[1]];
            return *this;
        }
        // SCATTERS
        UME_FUNC_ATTRIB int64_t* scatter(int64_t* baseAddr, uint64_t* indices) const {
            baseAddr[indices[0]] = mVec[0];
            baseAddr[indices[1]] = mVec[1];
            return baseAddr;
        }
        // MSCATTERS
        UME_FUNC_ATTRIB int64_t*  scatter(SIMDVecMask<2> const & mask, int64_t* baseAddr, uint64_t* indices) const {
            if (mask.mMask[0] == true) baseAddr[indices[0]] = mVec[0];
            if (mask.mMask[1] == true) baseAddr[indices[1]] = mVec[1];
            return baseAddr;
        }
        // SCATTERV
        UME_FUNC_ATTRIB int64_t*  scatter(int64_t* baseAddr, SIMDVec_u<uint64_t, 2> const & indices) const {
            baseAddr[indices.mVec[0]] = mVec[0];
            baseAddr[indices.mVec[1]] = mVec[1];
            return baseAddr;
        }
        // MSCATTERV
        UME_FUNC_ATTRIB int64_t*  scatter(SIMDVecMask<2> const & mask, int64_t* baseAddr, SIMDVec_u<uint64_t, 2> const & indices) const {
            if (mask.mMask[0] == true) baseAddr[indices.mVec[0]] = mVec[0];
            if (mask.mMask[1] == true) baseAddr[indices.mVec[1]] = mVec[1];
            return baseAddr;
        }

        // LSHV
        UME_FUNC_ATTRIB SIMDVec_i lsh(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] << b.mVec[0];
            int64_t t1 = mVec[1] << b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MLSHV
        UME_FUNC_ATTRIB SIMDVec_i lsh(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] << b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] << b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // LSHS
        UME_FUNC_ATTRIB SIMDVec_i lsh(int64_t b) const {
            int64_t t0 = mVec[0] << b;
            int64_t t1 = mVec[1] << b;
            return SIMDVec_i(t0, t1);
        }
        // MLSHS
        UME_FUNC_ATTRIB SIMDVec_i lsh(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] << b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] << b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // LSHVA
        UME_FUNC_ATTRIB SIMDVec_i & lsha(SIMDVec_i const & b) {
            mVec[0] = mVec[0] << b.mVec[0];
            mVec[1] = mVec[1] << b.mVec[1];
            return *this;
        }
        // MLSHVA
        UME_FUNC_ATTRIB SIMDVec_i & lsha(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if(mask.mMask[0]) mVec[0] = mVec[0] << b.mVec[0];
            if(mask.mMask[1]) mVec[1] = mVec[1] << b.mVec[1];
            return *this;
        }
        // LSHSA
        UME_FUNC_ATTRIB SIMDVec_i & lsha(int64_t b) {
            mVec[0] = mVec[0] << b;
            mVec[1] = mVec[1] << b;
            return *this;
        }
        // MLSHSA
        UME_FUNC_ATTRIB SIMDVec_i & lsha(SIMDVecMask<2> const & mask, int64_t b) {
            if(mask.mMask[0]) mVec[0] = mVec[0] << b;
            if(mask.mMask[1]) mVec[1] = mVec[1] << b;
            return *this;
        }
        // RSHV
        UME_FUNC_ATTRIB SIMDVec_i rsh(SIMDVec_i const & b) const {
            int64_t t0 = mVec[0] >> b.mVec[0];
            int64_t t1 = mVec[1] >> b.mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MRSHV
        UME_FUNC_ATTRIB SIMDVec_i rsh(SIMDVecMask<2> const & mask, SIMDVec_i const & b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] >> b.mVec[0] : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] >> b.mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // RSHS
        UME_FUNC_ATTRIB SIMDVec_i rsh(int64_t b) const {
            int64_t t0 = mVec[0] >> b;
            int64_t t1 = mVec[1] >> b;
            return SIMDVec_i(t0, t1);
        }
        // MRSHS
        UME_FUNC_ATTRIB SIMDVec_i rsh(SIMDVecMask<2> const & mask, int64_t b) const {
            int64_t t0 = mask.mMask[0] ? mVec[0] >> b : mVec[0];
            int64_t t1 = mask.mMask[1] ? mVec[1] >> b : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // RSHVA
        UME_FUNC_ATTRIB SIMDVec_i & rsha(SIMDVec_i const & b) {
            mVec[0] = mVec[0] >> b.mVec[0];
            mVec[1] = mVec[1] >> b.mVec[1];
            return *this;
        }
        // MRSHVA
        UME_FUNC_ATTRIB SIMDVec_i & rsha(SIMDVecMask<2> const & mask, SIMDVec_i const & b) {
            if (mask.mMask[0]) mVec[0] = mVec[0] >> b.mVec[0];
            if (mask.mMask[1]) mVec[1] = mVec[1] >> b.mVec[1];
            return *this;
        }
        // RSHSA
        UME_FUNC_ATTRIB SIMDVec_i & rsha(int64_t b) {
            mVec[0] = mVec[0] >> b;
            mVec[1] = mVec[1] >> b;
            return *this;
        }
        // MRSHSA
        UME_FUNC_ATTRIB SIMDVec_i & rsha(SIMDVecMask<2> const & mask, int64_t b) {
            if (mask.mMask[0]) mVec[0] = mVec[0] >> b;
            if (mask.mMask[1]) mVec[1] = mVec[1] >> b;
            return *this;
        }
        // ROLV
        // MROLV
        // ROLS
        // MROLS
        // ROLVA
        // MROLVA
        // ROLSA
        // MROLSA
        // RORV
        // MRORV
        // RORS
        // MRORS
        // RORVA
        // MRORVA
        // RORSA
        // MRORSA

        // NEG
        UME_FUNC_ATTRIB SIMDVec_i neg() const {
            return SIMDVec_i(-mVec[0], -mVec[1]);
        }
        UME_FUNC_ATTRIB SIMDVec_i operator- () const {
            return neg();
        }
        // MNEG
        UME_FUNC_ATTRIB SIMDVec_i neg(SIMDVecMask<2> const & mask) const {
            int64_t t0 = (mask.mMask[0] == true) ? -mVec[0] : mVec[0];
            int64_t t1 = (mask.mMask[1] == true) ? -mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // NEGA
        UME_FUNC_ATTRIB SIMDVec_i & nega() {
            mVec[0] = -mVec[0];
            mVec[1] = -mVec[1];
            return *this;
        }
        // MNEGA
        UME_FUNC_ATTRIB SIMDVec_i & nega(SIMDVecMask<2> const & mask) {
            if (mask.mMask[0] == true) mVec[0] = -mVec[0];
            if (mask.mMask[1] == true) mVec[1] = -mVec[1];
            return *this;
        }
        // ABS
        UME_FUNC_ATTRIB SIMDVec_i abs() const {
            int64_t t0 = (mVec[0] > 0) ? mVec[0] : -mVec[0];
            int64_t t1 = (mVec[1] > 0) ? mVec[1] : -mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // MABS
        UME_FUNC_ATTRIB SIMDVec_i abs(SIMDVecMask<2> const & mask) const {
            int64_t t0 = ((mask.mMask[0] == true) && (mVec[0] < 0)) ? -mVec[0] : mVec[0];
            int64_t t1 = ((mask.mMask[1] == true) && (mVec[1] < 0)) ? -mVec[1] : mVec[1];
            return SIMDVec_i(t0, t1);
        }
        // ABSA
        UME_FUNC_ATTRIB SIMDVec_i & absa() {
            if (mVec[0] < 0.0f) mVec[0] = -mVec[0];
            if (mVec[1] < 0.0f) mVec[1] = -mVec[1];
            return *this;
        }
        // MABSA
        UME_FUNC_ATTRIB SIMDVec_i & absa(SIMDVecMask<2> const & mask) {
            if ((mask.mMask[0] == true) && (mVec[0] < 0)) mVec[0] = -mVec[0];
            if ((mask.mMask[1] == true) && (mVec[1] < 0)) mVec[1] = -mVec[1];
            return *this;
        }

        // PACK
        UME_FUNC_ATTRIB SIMDVec_i & pack(SIMDVec_i<int64_t, 1> const & a, SIMDVec_i<int64_t, 1> const & b) {
            mVec[0] = a[0];
            mVec[1] = b[0];
            return *this;
        }
        // PACKLO
        UME_FUNC_ATTRIB SIMDVec_i & packlo(SIMDVec_i<int64_t, 1> const & a) {
            mVec[0] = a[0];
            return *this;
        }
        // PACKHI
        UME_FUNC_ATTRIB SIMDVec_i packhi(SIMDVec_i<int64_t, 1> const & b) {
            mVec[1] = b[0];
            return *this;
        }
        // UNPACK
        UME_FUNC_ATTRIB void unpack(SIMDVec_i<int64_t, 1> & a, SIMDVec_i<int64_t, 1> & b) const {
            a.insert(0, mVec[0]);
            b.insert(0, mVec[1]);
        }
        // UNPACKLO
        UME_FUNC_ATTRIB SIMDVec_i<int64_t, 1> unpacklo() const {
            return SIMDVec_i<int64_t, 1> (mVec[0]);
        }
        // UNPACKHI
        UME_FUNC_ATTRIB SIMDVec_i<int64_t, 1> unpackhi() const {
            return SIMDVec_i<int64_t, 1> (mVec[1]);
        }

        // PROMOTE
        // -
        // DEGRADE
        UME_FUNC_ATTRIB operator SIMDVec_i<int32_t, 2>() const;

        // ITOU
        UME_FUNC_ATTRIB operator SIMDVec_u<uint64_t, 2>() const;
        // ITOF
        UME_FUNC_ATTRIB operator SIMDVec_f<double, 2>() const;
    };

}
}

#endif
