//
//  WMGenericFunctionalCollection.h
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import <Foundation/Foundation.h>

// Created with convert.py
// with inputs NSArray.h and NSArray+Map.h,
// with ADD_PREFIX = 'WMGenericFunctional' in substitions.py
#import "WMGenericFunctionalArray.h"

// need to import the actual category implementation at some point
#import "NSArray+Map.h"

WMGENERICFUNCTIONALARRAY_INTERFACE(NSURL *, WMURLArray, WMMutableURLArray)