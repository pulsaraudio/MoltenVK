/*
 * mvk_datatypes.hpp
 *
 * Copyright (c) 2015-2022 The Brenwill Workshop Ltd. (http://www.brenwill.com)
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

#ifndef __mvkDataTypes_hpp_
#define __mvkDataTypes_hpp_ 1


#include "mvk_datatypes.h"

#include <functional>

class MVKBaseObject;
class MVKPixelFormats;

/*
 * This header file should be used internally within MoltenVK in place of mvk_datatypes.h,
 * which is part of the public external MoltenVK C API.
 */

#pragma mark -
#pragma mark Support for VK_EXT_debug_report extension

/*
 * The following function declarations are variations of functions declared in mvk_datatypes.h.
 *
 * Each function variation declared here accepts an MVKBaseObject instance, which, if not nil,
 * allows calls to MVKBaseObject::reportError() to be made from within these functions to perform
 * debug report callbacks in support of the VK_EXT_debug_report extension.
 *
 * The original functions in mvk_datatypes.h are redefined here to redirect to the equivalent
 * functions declared here, passing the calling instance, which is assumed to be an instance
 * of an MVKBaseObject subclass, which is true for all but static calling functions.
 */

API_AVAILABLE(macos(10.11), ios(8.0))
MTLPrimitiveType mvkMTLPrimitiveTypeFromVkPrimitiveTopologyInObj(VkPrimitiveTopology vkTopology, MVKBaseObject* mvkObj);
#define mvkMTLPrimitiveTypeFromVkPrimitiveTopology(vkTopology) mvkMTLPrimitiveTypeFromVkPrimitiveTopologyInObj(vkTopology, this)

API_AVAILABLE(macos(10.11), ios(12.0))
MTLPrimitiveTopologyClass mvkMTLPrimitiveTopologyClassFromVkPrimitiveTopologyInObj(VkPrimitiveTopology vkTopology, MVKBaseObject* mvkObj);
#define mvkMTLPrimitiveTopologyClassFromVkPrimitiveTopology(vkTopology) mvkMTLPrimitiveTopologyClassFromVkPrimitiveTopologyInObj(vkTopology, this)

API_AVAILABLE(macos(10.11), ios(8.0))
MTLTriangleFillMode mvkMTLTriangleFillModeFromVkPolygonModeInObj(VkPolygonMode vkFillMode, MVKBaseObject* mvkObj);
#define mvkMTLTriangleFillModeFromVkPolygonMode(vkFillMode) mvkMTLTriangleFillModeFromVkPolygonModeInObj(vkFillMode, this)

API_AVAILABLE(macos(10.11), ios(8.0))
MTLLoadAction mvkMTLLoadActionFromVkAttachmentLoadOpInObj(VkAttachmentLoadOp vkLoadOp, MVKBaseObject* mvkObj);
#define mvkMTLLoadActionFromVkAttachmentLoadOp(vkLoadOp) mvkMTLLoadActionFromVkAttachmentLoadOpInObj(vkLoadOp, this)

API_AVAILABLE(macos(10.11), ios(8.0))
MTLStoreAction mvkMTLStoreActionFromVkAttachmentStoreOpInObj(VkAttachmentStoreOp vkStoreOp, bool hasResolveAttachment, bool canResolveFormat, MVKBaseObject* mvkObj);
#define mvkMTLStoreActionFromVkAttachmentStoreOp(vkStoreOp, hasResolveAttachment, canResolveFormat) mvkMTLStoreActionFromVkAttachmentStoreOpInObj(vkStoreOp, hasResolveAttachment, canResolveFormat, this)

API_AVAILABLE(macos(10.14), ios(9.0))
MTLMultisampleDepthResolveFilter mvkMTLMultisampleDepthResolveFilterFromVkResolveModeFlagBitsInObj(VkResolveModeFlagBits vkResolveMode, MVKBaseObject* mvkObj);
#define mvkMTLMultisampleDepthResolveFilterFromVkResolveModeFlagBits(vkResolveMode) mvkMTLMultisampleDepthResolveFilterFromVkResolveModeFlagBitsInObj(vkResolveMode, this)

#if MVK_MACOS_OR_IOS
API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
MTLMultisampleStencilResolveFilter mvkMTLMultisampleStencilResolveFilterFromVkResolveModeFlagBitsInObj(VkResolveModeFlagBits vkResolveMode, MVKBaseObject* mvkObj);
#define mvkMTLMultisampleStencilResolveFilterFromVkResolveModeFlagBits(vkResolveMode) mvkMTLMultisampleStencilResolveFilterFromVkResolveModeFlagBitsInObj(vkResolveMode, this)
#endif

MVKShaderStage mvkShaderStageFromVkShaderStageFlagBitsInObj(VkShaderStageFlagBits vkStage, MVKBaseObject* mvkObj);
#define mvkShaderStageFromVkShaderStageFlagBits(vkStage) mvkShaderStageFromVkShaderStageFlagBitsInObj(vkStage, this)

API_AVAILABLE(macos(10.11), ios(8.0))
MTLWinding mvkMTLWindingFromSpvExecutionModeInObj(uint32_t spvMode, MVKBaseObject* mvkObj);
#define mvkMTLWindingFromSpvExecutionMode(spvMode) mvkMTLWindingFromSpvExecutionModeInObj(spvMode, this)

API_AVAILABLE(macos(10.12), ios(10.0))
MTLTessellationPartitionMode mvkMTLTessellationPartitionModeFromSpvExecutionModeInObj(uint32_t spvMode, MVKBaseObject* mvkObj);
#define mvkMTLTessellationPartitionModeFromSpvExecutionMode(spvMode) mvkMTLTessellationPartitionModeFromSpvExecutionModeInObj(spvMode, this)

#endif
