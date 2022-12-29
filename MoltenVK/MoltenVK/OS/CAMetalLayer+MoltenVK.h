/*
 * CAMetalLayer+MoltenVK.h
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

#pragma once

#include "MVKCommonEnvironment.h"
#include "MVKObjCClass.h"

#import <QuartzCore/CAMetalLayer.h>

#if MVK_IOS_OR_TVOS || MVK_MACCAT
#	define PLATFORM_SCREEN_CLASS	UIScreen
#	include <UIKit/UIScreen.h>
#endif

#if MVK_MACOS && !MVK_MACCAT
#	define PLATFORM_SCREEN_CLASS	NSScreen
#	include <AppKit/NSScreen.h>
#endif

/** Extensions to CAMetalLayer to support MoltenVK. */
@interface MVK_OBJC_CATEGORY_DECL(CAMetalLayer)

/**
 * Returns the natural drawable size for this layer.
 *
 * The natural drawable size is the size of the bounds property of this layer, multiplied
 * by the contentsScale property of this layer, and is the value that the drawableSize
 * property will be set to when the updatedDrawableSizeMVK nethod is invoked.
 */
@property(nonatomic, readonly) CGSize naturalDrawableSizeMVK;

/**
 * Ensures the drawableSize property of this layer is up to date, by ensuring
 * it is set to the value returned by the naturalDrawableSizeMVK property.
 *
 * Returns the updated drawableSize value.
 */
-(CGSize) updatedDrawableSizeMVK;

/**
 * Replacement for the displaySyncEnabled property.
 *
 * This property allows support under all OS versions. Delegates to the displaySyncEnabled
 * property if it is available. otherwise, returns YES when read and does nothing when set.
 */
@property(nonatomic, readwrite) BOOL displaySyncEnabledMVK;

/**
 * Replacement for the maximumDrawableCount property.
 *
 * This property allows support under all OS versions. Delegates to the maximumDrawableCount
 * property if it is available. otherwise, returns zero when read and does nothing when set.
 */
@property(nonatomic, readwrite) NSUInteger maximumDrawableCountMVK;

/**
 * Replacement for the wantsExtendedDynamicRangeContent property.
 *
 * This property allows support under all OS versions. Delegates to the wantsExtendedDynamicRangeContent
 * property if it is available. Otherwise, returns NO when read and does nothing when set.
 */
@property(nonatomic, readwrite) BOOL wantsExtendedDynamicRangeContentMVK;

/**
 * The name of the CGColorSpaceRef in the colorspace property of this layer.
 *
 * Reading this property returns the name of the CGColorSpaceRef in the colorspace property.
 * Setting this property sets the value in the colorspace property to a CGColorSpaceRef
 * with that name, creating and releasing the CGColorSpaceRef object itself as needed.
 */
@property(nonatomic, readwrite) CFStringRef colorspaceNameMVK;

/** Returns the screen on which this layer is rendering. */
@property(nonatomic, readonly) PLATFORM_SCREEN_CLASS* screenMVK;

@end
