Generics for Cocoa collections: providing templates to easily create custom Objective-C collection subclasses. The custom classes store a fixed type - e.g. an array which only stores NSString instances.

This enables the compiler to generate warnings on incompatible types, allows for easier property access for container members, and enables much improved code completion as well as overall more readale and self-documenting code.

<br\>

### Quick Start

To create an NSArray allowing only NSStrings as content (like `NSArray<NSString>` in Java or C#):

* Copy `WMGenericArray.h` from [Collections/Cocoa headers](Collections/Cocoa headers/) to your project
* Add a new Objective-C class with your desired name, like `WMStringArray`, to your project
* Replace the content of `WMStringArray.h` with:
```
    // WMStringArray.h
    #import "WMGenericArray.h" // import template definitions from Collections/Cocoa headers
  
    WMGENERICARRAY_INTERFACE(NSString *, // type of the desired value class
                             WMStringArray, WMMutableStringArray) // generated class names
```
* Replace the content of `WMStringArray.m` with:
```    
	// WMStringArray.m
    WMGENERICARRAY_SYNTHESIZE(NSString *, // type of the desired value class
                              WMStringArray, WMMutableStringArray) // generated class names
```

And you're done. `#import` and use WMStringArray wherever you need it in your project.

<br\>

***
<br\>

You can create collections for any custom class by changing the arguments in the macro.

```
    WMGENERICARRAY_INTERFACE(XYObject *, // type of the desired value class
                             XYObjectArray, XYMutableObjectArray) // generated class names
```

<br\>
<br\>

### Features of generated classes

Using custom collections created with the generic templates has many advantages.

#### Compiler warnings when using incompatible types

When using collections with a specified value type, the compiler will issue a warning on all actions which assign objects of incompatible types.

![Compiler warnings on incompatible types](/usage examples/set warning.png )

#### Better self-documentation of code

Often, methods return collections or take them as an argument. If the collection wraps a fixed type, this context information can be provided for the reader of the code:

    @property (nonatomic, retain) WMNumberArray *numbers;
    - (WMNumberArray *)numbersGreaterThan:(NSNumber *)compNumber;

#### Property access

Where standard collections return `(id)`, the collections with specified type return objects of this type, enabling for example direct property access.

![Property access of contained values](/usage examples/property access.png)

#### Automatic code creation improved

Xcode automatically creates code for methods that take blocks as arguments. This code is created automatically for the specified type, not for id. This enables property access in the code block, and better code completion.

![Improved code creation](/usage examples/code block.png)

#### Code completion improved

When accessing values of a collection, the compiler will know the specified type and will provide much better code completion.

![Improved code completion](/usage examples/code completion.png)

<br\>
<br\>

### Creating custom collections

An example for an NSArray class is given in Quick Start. [Collections/Cocoa headers/WMGenericCollection.h](Collections/Cocoa headers/WMGenericCollection.h) provides further example code for NSDictionary and NSSet subclasses for NSStrings.

#### Custom NSArray

To create a custom NSArray containing only NSString objects, add a new Objective-C class to the project, which we will name `WMStringArray` in this example. Replace the `@interface` and `@implementation` blocks with the following:

    // WMStringArray.h
    #import "WMGenericArray.h" // import template definitions from Collections/Cocoa headers
  
    WMGENERICARRAY_INTERFACE(NSString *, // type of the value class
                             WMStringArray, WMMutableStringArray) // generated class names

    // WMStringArray.m
    WMGENERICARRAY_SYNTHESIZE(NSString *, // type of the value class
                              WMStringArray, WMMutableStringArray) // generated class names

And that's it! With these two lines you have created two classes, `WMStringArray` and `WMMutableStringArray`, which provide the complete interface of `NSArray` and `NSMutableArray`. The big difference: they will take and return `NSString *`, where NSArray would use `id`.

#### Custom NSSet

Sets are created in a similar manner, but take an additional parameter, as they interact with NSArrays, for example in `-allObjects`. The type of the collection that is returned there needs to be configured as well. We can use the WMStringArray we just created like this:

    WMGENERICSET_INTERFACE(NSString *, // type of the value class
                           WMStringArray *, // what should '- (...)allObjects' return?
                           WMStringSet, WMMutableStringSet, WMCountedStringSet) // generated class names

    // don't forget to put WMGENERICSET_SYNTHESIZE with the same parameters in the implementation file

#### Custom NSDictionary

Dictionaries require parameters for the types of the represented values and keys. In this example, we will create an NSDictionary which will take any value type, but requires NSString keys.

This makes the first two parameters `id`(any value) and `NSString *`(key). The third value is the type of value collections, as in `-allValues`, in our case simply `NSArray *`.

The following two parameters are the collection types for the keys, an array and a set. We have already defined both, so let's use them, and specify the names for the resulting classes:

    WMGENERICDICTIONARY_INTERFACE(id, NSString *, // types of value class, NSCopying compliant key class
                                  NSArray *, // -(...)allValues?
                                  WMStringArray *, WMStringSet *, // -(...)allKeys?, -(...)keysOfEntries:?
                                  WMStringKeyDictionary, WMMutableStringKeyDictionary)

<br\>
<br\>


### Notes

These templates provide merely syntactic sugar at development time. At runtime, `WMStringArray` will return an object from the `NSArray` class cluster, *not* a `WMStringArray`. This forbids dynamic type checking:

    // caution! no actual implementations for the classes provided
    if ([[stringArray class] isKindOfClass:[WMStringArray class]]) {
        // it is not. it's an NSArray. no type checking at runtime!
        NSLog(@"stringArray isKindOf: WMStringArray"); // will not log
    }

For most methods of the Cocoa classes, type checks are performed at compilation time and will throw warnings. Two exceptions stand out:

* Object creation:
    
        WMStringArray *stringArray = (WMStringArray *)@[@"abc", @"bcd", @"cde"];
    This needs a cast (can be `(id)`) and does not check contained types.

* for loops:
    
        for (NSNumber *n in stringArray) {
            ...
        }
    Use `enumerateObjectsUsingBlock:` instead, which will check the type and even provide it correctly in the automatically created code block in Xcode.

#### How does it work


The code that is created with the macros provides interfaces of classes which
* are subclasses of a Cocoa collection
* redefine all methods of the super class by substituting (`id`) with the given type
* in case of the mutable subclasses, redefine all methods of both the mutable class and its immutable parent with substitution

The SYNTHESIZE macro will create an `@implementation` block containing `+alloc` and `+allocWithZone:` which will basically return `[super alloc]`. No other methods are implemented.

Furthermore, clang is told to ignore duplicated methods (redefinition in subclasses) and missing implementations, as another class is returned on `alloc` and none of the defined methods will ever be called.

#### Overhead

There is no overhead in using WMGenericCollections, as they only provide an interface for easier development, but use the standard Cocoa collections at runtime.

As the only implementation provided is that of redirecting object creating, there is a theoretical overhead (of one method call) there, but it does not create an actual measurable difference to normal object creation.

An overhead on method calls on the object after its creation is not theoretically possible, as the standard objects are used.

#### Custom categories and collections

This project provides the macro for subclasses of `NSArray`, `NSMutableArray`, `NSSet`, `NSMutableSet`, `NSCountedSet`, `NSDictionary` and `NSMutableDictionary`, which are created from the Foundation headers of the 10.8 SDK.

The conversion is done with a [python script](Conversion/convert.py) that parses Objective-C header files and generates the macro.

It is possible to generate custom macros for other collections, or categories of the standard Cocoa collections. Some work may be required to get it right. See the README in the [Conversion folder](Conversion/).

<br\>
<br\>


### License

WMGenericCollection is available under the MIT license. See the LICENSE file for more info.
