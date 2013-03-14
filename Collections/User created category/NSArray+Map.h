//
//  NSArray_Map.h
//  PolyVoicer
//
// http://stackoverflow.com/questions/6127638/nsarray-equivalent-of-map
//

#import <Foundation/Foundation.h>

@interface NSArray (Map)

- (NSArray *)map:(id (^)(id obj, NSUInteger idx))block;

@end

@implementation NSArray (Map)

- (NSArray *)map:(id (^)(id obj, NSUInteger idx))block {
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:[self count]];
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if (obj) {
            [result addObject:block(obj, idx)];
        }
    }];
    return [[result copy] autorelease];
}

@end

@interface NSArray (Filter)

- (NSArray *)arrayByFiltering:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))block;

@end

@implementation NSArray (Filter)

- (NSArray *)arrayByFiltering:(BOOL (^)(id, NSUInteger, BOOL *))block {
    NSIndexSet *indexSet = [self indexesOfObjectsPassingTest:block];
    return [self objectsAtIndexes:indexSet];
}

@end

