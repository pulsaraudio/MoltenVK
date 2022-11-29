/*
 * MVKSimd.h
 *
 * Copyright (c) 2018-2022 Chip Davis for CodeWeavers
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
 */

#pragma once

#ifndef MVK_USE_KFR_SIMD
#   define MVK_USE_KFR_SIMD 0
#endif

#if !MVK_USE_KFR_SIMD

    // This is the original MoltenVK code + compatibility macros and namespace
    #include <simd/simd.h>
    #define simd_kfr_flt_v(x) x
    namespace simd_or_kfr = simd;

#else

    // When MVK_USE_KFR_SIMD is defined, access to the following include must be granted
    // This allow to execute on macOS 10.9 by removing the dependency to __simd_pow_f4
    // in libsystem.dylib
    #include <kfr/math.hpp>
    #define simd_kfr_flt_v(x) x.v
    namespace kfr
    {
        using opencl_names::float2;
        using opencl_names::float3;
        using opencl_names::float4;
    }
    
    namespace simd_or_kfr = kfr;

#endif

using simd_or_kfr::float2;
using simd_or_kfr::float3;
using simd_or_kfr::float4;
