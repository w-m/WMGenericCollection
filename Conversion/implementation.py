
INTERFACE = 'INTERFACE' # #define name for interface block
IMPLEMENTATION = 'SYNTHESIZE' # #define name for implementation block

header_comment = """//
//  %s
//  WMGenericCollection
//
//  Created with convert.py on %s.
//  Input files: %s
//
//  https://github.com/w-m/WMGenericCollection
// """

imp_block = """
@implementation new_class

+ (id)alloc {
    return (id)[original_class alloc];
}

+ (id)allocWithZone:(NSZone *)zone {
    return (id)[original_class allocWithZone:zone];
}

@end;
"""

super_declaration_start = """/** Interface from super class: %s */

"""

pragma_push = ['_Pragma("clang diagnostic push")', ]

w_incomplete = [	
	r'_Pragma("clang diagnostic ignored \"-Wincomplete-implementation\"")',
	r'_Pragma("clang diagnostic ignored \"-Wprotocol\"")',
]

pragma_pop = ['_Pragma("clang diagnostic pop")', ]

w_duplicate = [r'_Pragma("clang diagnostic ignored \"-Wduplicate-method-match\"")' ,]

def ignore(declaration_list, warnings):
	return pragma_push + warnings + declaration_list + pragma_pop

