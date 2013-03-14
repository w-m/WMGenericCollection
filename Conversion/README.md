Collection templates can be created with:

    ./convert.py header ...

The files in `Collections/Cocoa headers` are created this way from the Foundation headers of the 10.8 SDK.

This script can parse a small subset of Objective-C, namely the one used in the Foundation files NSArray.h, NSDictionary.h and NSSet.h. Using it for other code might result in silent failure, garbled output or an Exception. No compiler infrastructure is involved, everything is based on regular expressions.

Customization
=============

The conversion script does not take any parameters currently.

The output can be customized with the static strings that can be found in implementation.py and substitutions.py, for example the class name prefix that is currently WMGeneric (ADD_PREFIX).

Converting catgories to Cocoa collections
=========================================

It is possible to create the macros with methods that are defined in custom categories. An example how this is done is found in `Collections/User created category`.

All the input of convert.py is concatenated, so you can just call `./convert.py NSArray.h NSArray+Map.h`.



Converting non-standard collections
===================================

 
