//
//  WMNumberStore.m
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import "WMNumberStore.h"

#import "WMNumberArray.h"
#import "WMFraction.h"

@interface WMNumberStore ()
@property (nonatomic, retain) WMMutableNumberArray *mutableStore;
@end

@implementation WMNumberStore

- (WMNumberArray *)numbersGreaterThan:(NSNumber *)compNumber {

    // NSNumber *obj was created by Xcode
    NSIndexSet *greaterIndexes = [self.mutableStore indexesOfObjectsPassingTest:^BOOL(NSNumber *obj, NSUInteger idx, BOOL *stop) {
        return (obj.doubleValue > compNumber.doubleValue);
    }];

    return [self.mutableStore objectsAtIndexes:greaterIndexes];
}

- (void)setNumbers:(WMNumberArray *)numbers {
    self.mutableStore = [[numbers mutableCopy] autorelease];
}

- (WMNumberArray *)numbers {
    return [[self.mutableStore copy] autorelease];
}

@end
