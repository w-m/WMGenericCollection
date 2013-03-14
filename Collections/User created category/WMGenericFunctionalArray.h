//
//  WMGenericFunctionalArray.h
//  WMGenericCollection
//
//  Created with convert.py on 2013-03-14.
//  Input files: NSArray.h, NSArray+Map.h
//
//  https://github.com/w-m/WMGenericCollection
// 

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/Foundation.h>

@class NSData, NSIndexSet, NSString, NSURL;

#if NS_BLOCKS_AVAILABLE

#define WMGENERICFUNCTIONALARRAY_INTERFACE(object_class, WMGenericFunctionalArray, WMGenericFunctionalMutableArray)\
@interface WMGenericFunctionalArray : NSArray <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>\
\
- (NSUInteger)count;\
- (object_class)objectAtIndex:(NSUInteger)index;\
    \
@end;\
\
@interface WMGenericFunctionalArray (NSExtendedArray)\
\
- (WMGenericFunctionalArray *)arrayByAddingObject:(object_class)anObject;\
- (WMGenericFunctionalArray *)arrayByAddingObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (NSString *)componentsJoinedByString:(NSString *)separator;\
- (BOOL)containsObject:(object_class)anObject;\
- (NSString *)description;\
- (NSString *)descriptionWithLocale:(id)locale;\
- (NSString *)descriptionWithLocale:(id)locale indent:(NSUInteger)level;\
- (object_class)firstObjectCommonWithArray:(WMGenericFunctionalArray *)otherArray;\
- (void)getObjects:(object_class __unsafe_unretained [])objects range:(NSRange)range;\
- (NSUInteger)indexOfObject:(object_class)anObject;\
- (NSUInteger)indexOfObject:(object_class)anObject inRange:(NSRange)range;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject inRange:(NSRange)range;\
- (BOOL)isEqualToArray:(WMGenericFunctionalArray *)otherArray;\
- (object_class)lastObject;\
- (NSEnumerator *)objectEnumerator;\
- (NSEnumerator *)reverseObjectEnumerator;\
- (NSData *)sortedArrayHint;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context hint:(NSData *)hint;\
- (WMGenericFunctionalArray *)sortedArrayUsingSelector:(SEL)comparator;\
- (WMGenericFunctionalArray *)subarrayWithRange:(NSRange)range;\
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;\
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;\
\
- (void)makeObjectsPerformSelector:(SEL)aSelector;\
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;\
\
- (WMGenericFunctionalArray *)objectsAtIndexes:(NSIndexSet *)indexes;\
\
- (object_class)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);\
\
\
- (void)enumerateObjectsUsingBlock:(void (^)(object_class obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);\
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(object_class obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);\
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(object_class obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);\
\
- (NSUInteger)indexOfObjectPassingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
\
- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
\
- (WMGenericFunctionalArray *)sortedArrayUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);\
- (WMGenericFunctionalArray *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);\
\
\
\
- (NSUInteger)indexOfObject:(object_class)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator)cmp NS_AVAILABLE(10_6, 4_0); \
\
\
\
@end;\
\
@interface WMGenericFunctionalArray (NSArrayCreation)\
\
+ (id)array;\
+ (id)arrayWithObject:(object_class)anObject;\
+ (id)arrayWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
+ (id)arrayWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
+ (id)arrayWithArray:(WMGenericFunctionalArray *)array;\
\
- (id)initWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
- (id)initWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
- (id)initWithArray:(WMGenericFunctionalArray *)array;\
- (id)initWithArray:(WMGenericFunctionalArray *)array copyItems:(BOOL)flag;\
\
+ (id)arrayWithContentsOfFile:(NSString *)path;\
+ (id)arrayWithContentsOfURL:(NSURL *)url;\
- (id)initWithContentsOfFile:(NSString *)path;\
- (id)initWithContentsOfURL:(NSURL *)url;\
\
@end;\
\
@interface WMGenericFunctionalArray (NSDeprecated)\
\
\
- (void)getObjects:(object_class __unsafe_unretained [])objects;\
\
@end;\
\
@interface WMGenericFunctionalMutableArray : NSMutableArray\
\
- (void)addObject:(object_class)anObject;\
- (void)insertObject:(object_class)anObject atIndex:(NSUInteger)index;\
- (void)removeLastObject;\
- (void)removeObjectAtIndex:(NSUInteger)index;\
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(object_class)anObject;\
\
/** Interface from super class: NSArray */\
\
_Pragma("clang diagnostic push")\
_Pragma("clang diagnostic ignored \"-Wduplicate-method-match\"")\
\
- (NSUInteger)count;\
- (object_class)objectAtIndex:(NSUInteger)index;\
    \
\
- (WMGenericFunctionalArray *)arrayByAddingObject:(object_class)anObject;\
- (WMGenericFunctionalArray *)arrayByAddingObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (NSString *)componentsJoinedByString:(NSString *)separator;\
- (BOOL)containsObject:(object_class)anObject;\
- (NSString *)description;\
- (NSString *)descriptionWithLocale:(id)locale;\
- (NSString *)descriptionWithLocale:(id)locale indent:(NSUInteger)level;\
- (object_class)firstObjectCommonWithArray:(WMGenericFunctionalArray *)otherArray;\
- (void)getObjects:(object_class __unsafe_unretained [])objects range:(NSRange)range;\
- (NSUInteger)indexOfObject:(object_class)anObject;\
- (NSUInteger)indexOfObject:(object_class)anObject inRange:(NSRange)range;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject inRange:(NSRange)range;\
- (BOOL)isEqualToArray:(WMGenericFunctionalArray *)otherArray;\
- (object_class)lastObject;\
- (NSEnumerator *)objectEnumerator;\
- (NSEnumerator *)reverseObjectEnumerator;\
- (NSData *)sortedArrayHint;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context hint:(NSData *)hint;\
- (WMGenericFunctionalArray *)sortedArrayUsingSelector:(SEL)comparator;\
- (WMGenericFunctionalArray *)subarrayWithRange:(NSRange)range;\
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;\
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;\
\
- (void)makeObjectsPerformSelector:(SEL)aSelector;\
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;\
\
- (WMGenericFunctionalArray *)objectsAtIndexes:(NSIndexSet *)indexes;\
\
- (object_class)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);\
\
\
- (void)enumerateObjectsUsingBlock:(void (^)(object_class obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);\
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(object_class obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);\
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(object_class obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);\
\
- (NSUInteger)indexOfObjectPassingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
\
- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);\
\
- (WMGenericFunctionalArray *)sortedArrayUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);\
- (WMGenericFunctionalArray *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);\
\
\
\
- (NSUInteger)indexOfObject:(object_class)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator)cmp NS_AVAILABLE(10_6, 4_0); \
\
\
\
\
+ (id)array;\
+ (id)arrayWithObject:(object_class)anObject;\
+ (id)arrayWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
+ (id)arrayWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
+ (id)arrayWithArray:(WMGenericFunctionalArray *)array;\
\
- (id)initWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
- (id)initWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
- (id)initWithArray:(WMGenericFunctionalArray *)array;\
- (id)initWithArray:(WMGenericFunctionalArray *)array copyItems:(BOOL)flag;\
\
+ (id)arrayWithContentsOfFile:(NSString *)path;\
+ (id)arrayWithContentsOfURL:(NSURL *)url;\
- (id)initWithContentsOfFile:(NSString *)path;\
- (id)initWithContentsOfURL:(NSURL *)url;\
\
\
\
- (void)getObjects:(object_class __unsafe_unretained [])objects;\
\
\
_Pragma("clang diagnostic pop")@end;\
\
@interface WMGenericFunctionalMutableArray (NSExtendedMutableArray)\
    \
- (void)addObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;\
- (void)removeAllObjects;\
- (void)removeObject:(object_class)anObject inRange:(NSRange)range;\
- (void)removeObject:(object_class)anObject;\
- (void)removeObjectIdenticalTo:(object_class)anObject inRange:(NSRange)range;\
- (void)removeObjectIdenticalTo:(object_class)anObject;\
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);\
- (void)removeObjectsInArray:(WMGenericFunctionalArray *)otherArray;\
- (void)removeObjectsInRange:(NSRange)range;\
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(WMGenericFunctionalArray *)otherArray range:(NSRange)otherRange;\
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (void)setArray:(WMGenericFunctionalArray *)otherArray;\
- (void)sortUsingFunction:(NSInteger (*)(object_class, object_class, void *))compare context:(void *)context;\
- (void)sortUsingSelector:(SEL)comparator;\
\
- (void)insertObjects:(WMGenericFunctionalArray *)objects atIndexes:(NSIndexSet *)indexes;\
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;\
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(WMGenericFunctionalArray *)objects;\
\
- (void)setObject:(object_class)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);\
\
\
- (void)sortUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);\
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);\
\
\
@end;\
\
@interface WMGenericFunctionalMutableArray (NSMutableArrayCreation)\
\
+ (id)arrayWithCapacity:(NSUInteger)numItems;\
- (id)initWithCapacity:(NSUInteger)numItems;\
\
@end;\
\
@interface WMGenericFunctionalArray (Map)\
\
- (WMGenericFunctionalArray *)map:(id (^)(object_class obj, NSUInteger idx))block;\
\
@end;\
\
@interface WMGenericFunctionalArray (Filter)\
\
- (WMGenericFunctionalArray *)arrayByFiltering:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))block;\
\
@end;\


#define WMGENERICFUNCTIONALARRAY_SYNTHESIZE(object_class, WMGenericFunctionalArray, WMGenericFunctionalMutableArray)\
_Pragma("clang diagnostic push")\
_Pragma("clang diagnostic ignored \"-Wincomplete-implementation\"")\
_Pragma("clang diagnostic ignored \"-Wprotocol\"")\
\
@implementation WMGenericFunctionalArray\
\
+ (id)alloc {\
    return (id)[NSArray alloc];\
}\
\
+ (id)allocWithZone:(NSZone *)zone {\
    return (id)[NSArray allocWithZone:zone];\
}\
\
@end;\
\
\
@implementation WMGenericFunctionalMutableArray\
\
+ (id)alloc {\
    return (id)[NSMutableArray alloc];\
}\
\
+ (id)allocWithZone:(NSZone *)zone {\
    return (id)[NSMutableArray allocWithZone:zone];\
}\
\
@end;\
\
_Pragma("clang diagnostic pop")



#else // NS_BLOCKS_AVAILABLE

#define WMGENERICFUNCTIONALARRAY_INTERFACE(object_class, WMGenericFunctionalArray, WMGenericFunctionalMutableArray)\
@interface WMGenericFunctionalArray : NSArray <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>\
\
- (NSUInteger)count;\
- (object_class)objectAtIndex:(NSUInteger)index;\
    \
@end;\
\
@interface WMGenericFunctionalArray (NSExtendedArray)\
\
- (WMGenericFunctionalArray *)arrayByAddingObject:(object_class)anObject;\
- (WMGenericFunctionalArray *)arrayByAddingObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (NSString *)componentsJoinedByString:(NSString *)separator;\
- (BOOL)containsObject:(object_class)anObject;\
- (NSString *)description;\
- (NSString *)descriptionWithLocale:(id)locale;\
- (NSString *)descriptionWithLocale:(id)locale indent:(NSUInteger)level;\
- (object_class)firstObjectCommonWithArray:(WMGenericFunctionalArray *)otherArray;\
- (void)getObjects:(object_class __unsafe_unretained [])objects range:(NSRange)range;\
- (NSUInteger)indexOfObject:(object_class)anObject;\
- (NSUInteger)indexOfObject:(object_class)anObject inRange:(NSRange)range;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject inRange:(NSRange)range;\
- (BOOL)isEqualToArray:(WMGenericFunctionalArray *)otherArray;\
- (object_class)lastObject;\
- (NSEnumerator *)objectEnumerator;\
- (NSEnumerator *)reverseObjectEnumerator;\
- (NSData *)sortedArrayHint;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context hint:(NSData *)hint;\
- (WMGenericFunctionalArray *)sortedArrayUsingSelector:(SEL)comparator;\
- (WMGenericFunctionalArray *)subarrayWithRange:(NSRange)range;\
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;\
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;\
\
- (void)makeObjectsPerformSelector:(SEL)aSelector;\
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;\
\
- (WMGenericFunctionalArray *)objectsAtIndexes:(NSIndexSet *)indexes;\
\
- (object_class)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);\
\
\
\
@end;\
\
@interface WMGenericFunctionalArray (NSArrayCreation)\
\
+ (id)array;\
+ (id)arrayWithObject:(object_class)anObject;\
+ (id)arrayWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
+ (id)arrayWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
+ (id)arrayWithArray:(WMGenericFunctionalArray *)array;\
\
- (id)initWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
- (id)initWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
- (id)initWithArray:(WMGenericFunctionalArray *)array;\
- (id)initWithArray:(WMGenericFunctionalArray *)array copyItems:(BOOL)flag;\
\
+ (id)arrayWithContentsOfFile:(NSString *)path;\
+ (id)arrayWithContentsOfURL:(NSURL *)url;\
- (id)initWithContentsOfFile:(NSString *)path;\
- (id)initWithContentsOfURL:(NSURL *)url;\
\
@end;\
\
@interface WMGenericFunctionalArray (NSDeprecated)\
\
\
- (void)getObjects:(object_class __unsafe_unretained [])objects;\
\
@end;\
\
@interface WMGenericFunctionalMutableArray : NSMutableArray\
\
- (void)addObject:(object_class)anObject;\
- (void)insertObject:(object_class)anObject atIndex:(NSUInteger)index;\
- (void)removeLastObject;\
- (void)removeObjectAtIndex:(NSUInteger)index;\
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(object_class)anObject;\
\
/** Interface from super class: NSArray */\
\
_Pragma("clang diagnostic push")\
_Pragma("clang diagnostic ignored \"-Wduplicate-method-match\"")\
\
- (NSUInteger)count;\
- (object_class)objectAtIndex:(NSUInteger)index;\
    \
\
- (WMGenericFunctionalArray *)arrayByAddingObject:(object_class)anObject;\
- (WMGenericFunctionalArray *)arrayByAddingObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (NSString *)componentsJoinedByString:(NSString *)separator;\
- (BOOL)containsObject:(object_class)anObject;\
- (NSString *)description;\
- (NSString *)descriptionWithLocale:(id)locale;\
- (NSString *)descriptionWithLocale:(id)locale indent:(NSUInteger)level;\
- (object_class)firstObjectCommonWithArray:(WMGenericFunctionalArray *)otherArray;\
- (void)getObjects:(object_class __unsafe_unretained [])objects range:(NSRange)range;\
- (NSUInteger)indexOfObject:(object_class)anObject;\
- (NSUInteger)indexOfObject:(object_class)anObject inRange:(NSRange)range;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject;\
- (NSUInteger)indexOfObjectIdenticalTo:(object_class)anObject inRange:(NSRange)range;\
- (BOOL)isEqualToArray:(WMGenericFunctionalArray *)otherArray;\
- (object_class)lastObject;\
- (NSEnumerator *)objectEnumerator;\
- (NSEnumerator *)reverseObjectEnumerator;\
- (NSData *)sortedArrayHint;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context;\
- (WMGenericFunctionalArray *)sortedArrayUsingFunction:(NSInteger (*)(object_class, object_class, void *))comparator context:(void *)context hint:(NSData *)hint;\
- (WMGenericFunctionalArray *)sortedArrayUsingSelector:(SEL)comparator;\
- (WMGenericFunctionalArray *)subarrayWithRange:(NSRange)range;\
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;\
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;\
\
- (void)makeObjectsPerformSelector:(SEL)aSelector;\
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;\
\
- (WMGenericFunctionalArray *)objectsAtIndexes:(NSIndexSet *)indexes;\
\
- (object_class)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);\
\
\
\
\
+ (id)array;\
+ (id)arrayWithObject:(object_class)anObject;\
+ (id)arrayWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
+ (id)arrayWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
+ (id)arrayWithArray:(WMGenericFunctionalArray *)array;\
\
- (id)initWithObjects:(const object_class [])objects count:(NSUInteger)cnt;\
- (id)initWithObjects:(object_class)firstObj, ... NS_REQUIRES_NIL_TERMINATION;\
- (id)initWithArray:(WMGenericFunctionalArray *)array;\
- (id)initWithArray:(WMGenericFunctionalArray *)array copyItems:(BOOL)flag;\
\
+ (id)arrayWithContentsOfFile:(NSString *)path;\
+ (id)arrayWithContentsOfURL:(NSURL *)url;\
- (id)initWithContentsOfFile:(NSString *)path;\
- (id)initWithContentsOfURL:(NSURL *)url;\
\
\
\
- (void)getObjects:(object_class __unsafe_unretained [])objects;\
\
\
_Pragma("clang diagnostic pop")@end;\
\
@interface WMGenericFunctionalMutableArray (NSExtendedMutableArray)\
    \
- (void)addObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;\
- (void)removeAllObjects;\
- (void)removeObject:(object_class)anObject inRange:(NSRange)range;\
- (void)removeObject:(object_class)anObject;\
- (void)removeObjectIdenticalTo:(object_class)anObject inRange:(NSRange)range;\
- (void)removeObjectIdenticalTo:(object_class)anObject;\
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);\
- (void)removeObjectsInArray:(WMGenericFunctionalArray *)otherArray;\
- (void)removeObjectsInRange:(NSRange)range;\
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(WMGenericFunctionalArray *)otherArray range:(NSRange)otherRange;\
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(WMGenericFunctionalArray *)otherArray;\
- (void)setArray:(WMGenericFunctionalArray *)otherArray;\
- (void)sortUsingFunction:(NSInteger (*)(object_class, object_class, void *))compare context:(void *)context;\
- (void)sortUsingSelector:(SEL)comparator;\
\
- (void)insertObjects:(WMGenericFunctionalArray *)objects atIndexes:(NSIndexSet *)indexes;\
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;\
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(WMGenericFunctionalArray *)objects;\
\
- (void)setObject:(object_class)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);\
\
\
\
@end;\
\
@interface WMGenericFunctionalMutableArray (NSMutableArrayCreation)\
\
+ (id)arrayWithCapacity:(NSUInteger)numItems;\
- (id)initWithCapacity:(NSUInteger)numItems;\
\
@end;\
\
@interface WMGenericFunctionalArray (Map)\
\
- (WMGenericFunctionalArray *)map:(id (^)(object_class obj, NSUInteger idx))block;\
\
@end;\
\
@interface WMGenericFunctionalArray (Filter)\
\
- (WMGenericFunctionalArray *)arrayByFiltering:(BOOL (^)(object_class obj, NSUInteger idx, BOOL *stop))block;\
\
@end;\


#define WMGENERICFUNCTIONALARRAY_SYNTHESIZE(object_class, WMGenericFunctionalArray, WMGenericFunctionalMutableArray)\
_Pragma("clang diagnostic push")\
_Pragma("clang diagnostic ignored \"-Wincomplete-implementation\"")\
_Pragma("clang diagnostic ignored \"-Wprotocol\"")\
\
@implementation WMGenericFunctionalArray\
\
+ (id)alloc {\
    return (id)[NSArray alloc];\
}\
\
+ (id)allocWithZone:(NSZone *)zone {\
    return (id)[NSArray allocWithZone:zone];\
}\
\
@end;\
\
\
@implementation WMGenericFunctionalMutableArray\
\
+ (id)alloc {\
    return (id)[NSMutableArray alloc];\
}\
\
+ (id)allocWithZone:(NSZone *)zone {\
    return (id)[NSMutableArray allocWithZone:zone];\
}\
\
@end;\
\
_Pragma("clang diagnostic pop")

#endif // NS_BLOCKS_AVAILABLE

