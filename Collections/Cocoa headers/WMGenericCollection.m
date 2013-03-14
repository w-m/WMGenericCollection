//
//  WMGenericCollection.m
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import "WMGenericCollection.h"

WMGENERICARRAY_SYNTHESIZE(NSString *,
                         WMStringArray, WMMutableStringArray)

WMGENERICSET_SYNTHESIZE(NSString *,
                       WMStringArray *,
                       WMStringSet, WMMutableStringSet, WMCountedStringSet)

WMGENERICDICTIONARY_SYNTHESIZE(id, NSString *,
                              NSArray *, WMStringArray *, WMStringSet *,
                              WMStringKeyDictionary, WMMutableStringKeyDictionary)
