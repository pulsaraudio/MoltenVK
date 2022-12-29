/*
 * NSString+MoltenVK.h
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

#import <Foundation/NSString.h>

/** Conveniency function to append a line to a mutable string.

    This avoid the use of an Objective-C category upon NSMutableString, because
    it lead to problems when used in multiple plugins (category methods may be
    spuriously replaced when another plugin is loaded).

    Also, subclassing NSMutableString is not that easy because it leads to abstract
    class runtime errors (we'll need to reimplement length, for instance). It is
    therefore easier to create those 2 little functions.
 */
inline void appendLineMVK(NSMutableString * mutableString, NSString* aString)
{
    [mutableString appendString: aString];
    [mutableString appendString: @"\n"];
}

/** Conveniency function to append an empty line to a mutable string.
  */
inline void appendLineMVK(NSMutableString * mutableString)
{
    [mutableString appendString: @"\n"];
}
