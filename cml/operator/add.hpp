//
// Copyright (c) 2017 James Simpson, Timothée Feuillet
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

#pragma once

#include "../matrix.hpp"
#include "../fixed_point.hpp"
#include <type_traits>

namespace cml::implementation
{
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_mm_add(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1.components[Idxs] + v2.components[Idxs]...};
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_ms_add(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
        return {v1.components[Idxs] + v2...};
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr auto operator + (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2) -> auto
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_mm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_sm_add(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1 + v2.components[Idxs]...};
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr auto operator + (VType v1, const matrix<DimX, DimY, VType, Kind>& v2) -> auto
    {
        return matrix_sm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_smm_add(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] += v2.components[Idxs]), 0)...});
#endif
        return v1;
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_sms_add(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] += v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] += v2), 0)...});
#endif
        return v1;
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>& operator += (matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_sms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_smm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>&& operator += (matrix<DimX, DimY, VType, Kind>&& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_sms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2));
        else
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_smm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2));
    }
}
