//
//  WMNumberArray.h
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WMGenericArray.h"

// so we don't get any duplicate symbols, create collections for standard objects in own file
// which we can use from different classes in our project
WMGENERICARRAY_INTERFACE(NSNumber *, WMNumberArray, WMMutableNumberArray)