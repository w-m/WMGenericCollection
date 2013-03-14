//
//  WMNumberStore.h
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WMNumberArray, WMMutableNumberArray, WMFractionArray;

@interface WMNumberStore : NSObject {

}

// get/set only arrays containing numbers
@property (nonatomic, retain) WMNumberArray *numbers;

// collection of custom objects
@property (nonatomic, retain) WMFractionArray *fractions;

// it's clear this returns an array of numbers, without
// need for further documentation
// also will enable better code completion for the receiver
- (WMNumberArray *)numbersGreaterThan:(NSNumber *)compNumber;

@end
