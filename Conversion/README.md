Collection templates can be created with:

    ./convert.py header ...

The files in `Collections/Cocoa headers` are created this way from the Foundation headers of the 10.8 SDK.

Keep in mind: this script can parse only a very small subset of Objective-C, namely the one used in the Foundation files NSArray.h, NSDictionary.h and NSSet.h. Using it for other code might result in silent failure, garbled output or an Exception. No compiler infrastructure is involved, everything is based on regular expressions. Some unsupported language features are described in *Unsupported constructs*.

Customization
=============

The conversion script does not take any parameters currently.

The output can be customized with the static strings that can be found in `implementation.py` and `substitutions.py`, for example the class name prefix that is currently WMGeneric (`ADD_PREFIX`).

Converting catgories of Cocoa collections
=========================================

It is possible to create the templates containing methods that are defined in custom categories. An example how this is done is found in `Collections/User created category`.

All the input of convert.py is concatenated, so you can just call `./convert.py NSArray.h NSArray+Map.h`. In this example, `ADD_PREFIX` was changed to WMGenericFunctional, so that multiple macros of the same class can exist in one project without name collision.

Converting non-standard collections
===================================

It is possible to create similar templates for completely different classes. The idea is the same, but the probability that the script will parse correctly and substitute anything of value diminishes if the coding style is different from the standard collections.

Script throws an Exception
==========================

Some `Unsupported constructs` are caught in the script, which will throw an exception for it. Bad are especially C preprocessing directives, of which very few are handled. Remove them from the header or let the compiler preprocess your file, before using it as an input

Conversion works, but (id) is not changed to (object_class)
===========================================================

Try to adhere to the naming scheme of the standard container classes:
* an object argument could be named `object, obj, anObject or firstObject`
* multiple objects are `objects`
* return types depend on the first syllable of the method name, e.g. (NSArray *)arrayWith...

For example, `arrayByFiltering:` will convert correctly out of the box, while `map:` would not.

The informal naming scheme is defined through the regexes of `_collection_dict` of `substitutions.py`.

Can't adhere to the naming scheme
=================================

If you can't change the method and argument names to the expected ones, you have to add additional regexes. An example is found in substitutions.py

    'ns_array_map': {
		'applyTo': ['NSArray'],
		'arguments': [],
		'substitutions': [
			(open_paren + r'NSArray(?= \*\)map)', NSArray_Replacement),
		],
	}

This defines a single regular expressions, which replaces `(NSArray *)map` with `(WMGenericArray *)map` in NSArray, requiring no further macro arguments.

Make sure that your additional regexes have no ill effect on the creation of the standard collections. There is currently no automatic test suite in place.

Unsupported constructs
======================

The goal of this script is to parse the standard collection correctly, not a Objective-C header file. No compiler infrastructure is involved. Here's a short list of constructs which will fail:

* C preprocessor directives:
     
    Pretty much everything (`#define, ifdef, #else, ...`) will fail, with the following exceptions:
    + `#import` (passed through, not resolved)
    + `#if x, #endif`: supported for a unique x, not for multiple per file
    + `#if TARGET_WIN_32 #else x #endif`: code x is used, rest thrown out

* typedefs are silently removed
* @implementation blocks are silently removed
* multiline definitions, e.g. 
        @interface MyObject : 
                 NSArray
* `(void)setObject:(object_class)anObject forKey:(id <NSCopying>)aKey`: the NSCopying is removed to be able to support both fixed typed pointers and id



