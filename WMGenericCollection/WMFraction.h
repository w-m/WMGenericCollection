//
//  WMFraction.h
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WMGenericArray.h"

// for our custom class, we can create the collection right here
// no need to create extra header/implementation files
@class WMFraction;
WMGENERICARRAY_INTERFACE(WMFraction *, WMFractionArray, WMMutableFractionArray)

@interface WMFraction : NSObject

@property (nonatomic, retain) NSNumber *numerator;
@property (nonatomic, retain) NSNumber *denominator;

@end
