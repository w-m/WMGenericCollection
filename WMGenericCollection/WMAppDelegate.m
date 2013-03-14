//
//  WMAppDelegate.m
//  WMGenericCollection
//
//  Created by Wieland Morgenstern on 14.03.13.
//  Copyright (c) 2013 Wieland Morgenstern. All rights reserved.
//

#import "WMAppDelegate.h"

#import "WMGenericCollection.h"

#import "WMNumberArray.h"
#import "WMNumberStore.h"

#import "WMGenericFunctionalCollection.h"

#pragma clang diagnostic ignored "-Wunused-variable"

@implementation WMAppDelegate

- (void)stringArrays {
    WMStringArray *stringArray = (WMStringArray *)@[@"abc", @"bcd", @"cde"];

    // warn me: can't assign string to number
    NSNumber *someNumber = stringArray[0];

    WMMutableStringArray *mutableStringArray = [stringArray mutableCopy];
    // warn me: can't put number in string array
    mutableStringArray[0] = @4;

    // yay properties work
    NSUInteger firstLen = stringArray[0].length;

    WMStringKeyDictionary *dict = [WMStringKeyDictionary dictionaryWithObjects:@[@1, @2, @3] forKeys:stringArray];
    // warn me: keys are strings!
    NSURL *url = dict[@45];

    // caution! no actual implementations for the classes provided
    if ([[stringArray class] isKindOfClass:[WMStringArray class]]) {
        // it is not. it's an NSArray. no duck typing!
        NSLog(@"stringArray isKindOf: WMStringArray"); // will not log
    }
}

- (void)numberExample {
    WMNumberArray *smallNumbers = (WMNumberArray *)@[@1, @2.5, @3, @4.5, @5];
    WMNumberStore *numberStore = [[[WMNumberStore alloc] init] autorelease];
    numberStore.numbers = smallNumbers;

    // log the int values of numbers greater 3:
    [[numberStore numbersGreaterThan:@3] enumerateObjectsUsingBlock:^(NSNumber *obj, // sweet, Xcode creater this block with NSNumber *
                                                                      NSUInteger idx, BOOL *stop) {
        NSLog(@"%d", obj.intValue);
    }];
}

- (void)customCategory {
    // WMURLArray belongs to WMGenericFunctionalCollection, was created
    // create from NSArray.h and a custom category, NSArray+Map.h
    WMURLArray *urlArray = (WMURLArray *)@[[NSURL URLWithString:@"http://www.example.com/"], [NSURL URLWithString:@"ftp://ftp.example.com/"]];
    WMURLArray *urlSchemes = [urlArray map:^id(NSURL *obj, NSUInteger idx) {
        return obj.scheme;
    }];
    NSLog(@"%@", urlSchemes);
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [self stringArrays];
    [self numberExample];
    [self customCategory];
}

- (void)dealloc {
    [super dealloc];
}

@end
