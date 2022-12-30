/*
 * MVKObjCClass.h
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

/** By default, MoltenVK will use Objective-C categories.

    However, using categories has serious drawbacks when the MoltenVK library is
    statically linked to different plugins or shared libraries loaded in the same
    process space: when a new bundle is loaded, loaded category methods will replace
    all that has been already defined in a previous bundle.

    If one of the category method is used in a thread of the first bundle, it will
    be aggressively replaced on the fly by the another implementation laying in
    the second bundle, and this is likely to crash because method access and replacement
    is not mutex-protected.

    For this reason, we prefer to replace categories by subclasses, and furthermore
    use cloned classes of these subclasses. Cloning is mandatory to be sure each
    bundle address space will define its own classes and set of methods, that will
    be different from their equivalent in the other bundles.

    Be aware that subclassing is not adapted to some system abstract classes like
    NSMutableString, or you will need to provide a lot of methods already in the
    base class.

    `MVK_USE_OBJC_CLASS_CLONING` may be set to 1 on the command line or via CMake.

    `MVK_OBJC_CATEGORY_DECL` declares the subclass or the category, depending on
    the `MVK_USE_OBJC_CLASS_CLONING` macro, and intended to be used with `@interface`.

    `MVK_OBJC_CATEGORY_IMPL` is the name of the subclass or category to be used
    with `@implementation`.

    `MVK_OBJC_CLASS` gives the name of the subclass or category. Subclasses are given
    the `_MVK` suffix.

    `MVK_OBJC_CLASS_ALIAS` defines the "subclass" to be an alias to the original class,
    instead, thus no subclassing takes place. This is when you provide a full class
    yourself instead of using `MVK_OBJC_CATEGORY_DECL`.

    The following macros do nothing with categories, and only act on subclasses:

    `MVK_OBJC_CLONE` is to be used with alloc to create a clone of the declared subclass.
    Cloned class names are given an hexadecimal suffix of the form `_MVK_XXXXXX`.

    \code
        MVK_OBJC_CLASS(MyClass)* myObject = [MVK_OBJC_CLONE(MyClass) alloc] init];
    \endcode

    `MVK_OBJC_SETCLASS` allow to change the class of an object on the fly to the
    cloned class. This is useful when we catch an object created somewhere else
    and when we cannot use `MVK_OBJC_CLONE`.

    \code
        MyBaseClass * myObject = getSomeBaseClassObject();
        MVK_OBJC_CLASS(MyClass)* myReclassedObject = MVK_OBJC_SETCLASS(myObject, MyClass);
    \endcode

    \note: Cannot be included from C/Objective-C (.c/.m) files, only from
    C++/Objective-C++ (.cpp/.mm) files
 */

#ifndef MVK_USE_OBJC_CLASS_CLONING
#define MVK_USE_OBJC_CLASS_CLONING 0
#endif

#ifdef __OBJC__
#define MVK_FWD_CLASS(Class) @class Class
#else
#define MVK_FWD_CLASS(Class) class Class
#endif

#if MVK_USE_OBJC_CLASS_CLONING

// This will define the ObjCClassCloner template class
#include <core_ObjCDefs.h>

#define MVK_OBJC_CLASS(Class) Class ## _MVK
#define MVK_OBJC_CLASS_ALIAS(Class) CORE_OBJC_CLASS_ALIAS(MVK_OBJC_CLASS(Class), Class)
#define MVK_OBJC_CLONE(Class) core::ObjCClassCloner<MVK_OBJC_CLASS(Class)>()

#define MVK_OBJC_CATEGORY_IMPL(Class) MVK_OBJC_CLASS(Class)
#define MVK_OBJC_CATEGORY_DECL(Class) MVK_OBJC_CATEGORY_IMPL(Class) : Class

/** If Object is an instance of Class (or a subclass), its class will be set to
    the clone of `MVK_OBJC_CLASS(Class)`, otherwise we return nil.
 */
#define MVK_OBJC_SETCLASS(Object, Class) core::ObjCClassCloner<MVK_OBJC_CLASS(Class)>::setObjectClass<Class>(Object)

#else // !MVK_USE_OBJC_CLASS_CLONING

#define MVK_OBJC_CLASS(Class) Class
#define MVK_OBJC_CLASS_ALIAS(Class) MVK_FWD_CLASS(Class)
#define MVK_OBJC_CLONE(Class) Class

#define MVK_OBJC_CATEGORY_IMPL(Class) Class (MoltenVK)
#define MVK_OBJC_CATEGORY_DECL(Class) MVK_OBJC_CATEGORY_IMPL(Class)

#define MVK_OBJC_SETCLASS(Object, Class) Object

#endif
