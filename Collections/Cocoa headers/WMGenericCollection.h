//
//  WMGenericCollection.h
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WMGenericArray.h"
#import "WMGenericDictionary.h"
#import "WMGenericSet.h"

// Define some standard string collections which might be used at different places

WMGENERICARRAY_INTERFACE(NSString *, // object class
                         WMStringArray, WMMutableStringArray) // generated class names

WMGENERICSET_INTERFACE(NSString *, // object class
                       WMStringArray *, // what should '- (...)allObjects' return?
                       WMStringSet, WMMutableStringSet, WMCountedStringSet)

WMGENERICDICTIONARY_INTERFACE(id, NSString *, // object class, key class (<NSCopying> compliant!)
                              NSArray *, // (...)allValues?
                              WMStringArray *, WMStringSet *, // (...)allKeys?, (...)keysOfEntries...?
                              WMStringKeyDictionary, WMMutableStringKeyDictionary)
