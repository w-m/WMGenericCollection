
import re, collections
from operator import itemgetter

REMOVE_NS_PREFIX = True
ADD_PREFIX = 'WMGeneric'
OBJECT_CLASS = 'object_class'
KEY_CLASS = 'ns_copying_compliant_key_class'

# name of argument for NSSet & NSDict for interoperability with NSArray, e.g. - (NSArray *)allObjects
NS_ARRAY_COMPATIBLE_VALUES = 'NSArray_values_class'
NS_ARRAY_COMPATIBLE_KEYS = 'NSArray_keys_class'
NS_SET_COMPATIBLE_KEYS = 'NSSet_keys_class'

def new_class_name(class_name):
	new_name = class_name[2:] if REMOVE_NS_PREFIX and class_name.startswith('NS') else class_name
	return ADD_PREFIX + new_name

NSArray_Replacement = new_class_name('NSArray')
NSSet_Replacement = new_class_name('NSSet')
NSDictionary_Replacement = new_class_name('NSDictionary')

open_paren = r'(?<=\()'
_collection_dict = {
	'cocoa_collection': {
		'applyTo': ['NSArray', 'NSMutableArray',
					'NSDictionary', 'NSMutableDictionary',
					'NSSet', 'NSMutableSet', 'NSCountedSet',],
		'arguments': [OBJECT_CLASS, ],
		'substitutions': [
			# adding/retrieving objects, blocks, initWithObjects, setObject
			(r'id(?=(\)| )(anObject|obj|firstObj(ect)?,))', OBJECT_CLASS),
			# compare operators with (id, id, void *)
			(open_paren + r'id, id(?=, void \*\))', OBJECT_CLASS +', ' + OBJECT_CLASS),
			# return types, but not initializers or (id)sharedKeySetForKeys:
			(r'(?<=[-+] \()id(?!\)(array|set|dictionary|init|shared))', OBJECT_CLASS),
			# multiple object arrays (some deprecated)
			(r'id(?=[^\(\)]*\)objects)', OBJECT_CLASS),
		]
	},
	'ns_array': {
		'applyTo': ['NSArray', 'NSMutableArray'],
		'arguments': [],
		'substitutions': [
			# (NSArray *)sortedArray/subarrayWithRange/arrayByAddingObject/array/otherArray/objects(AtIndexes);
			(open_paren + r'NSArray(?= \*\)[^:;]*?([aA]rray|objects))', NSArray_Replacement),
		],
	},
	'ns_dict': {
		'applyTo': ['NSDictionary', 'NSMutableDictionary'],
		'arguments': [KEY_CLASS, NS_ARRAY_COMPATIBLE_VALUES, NS_ARRAY_COMPATIBLE_KEYS, NS_SET_COMPATIBLE_KEYS, ],
		'substitutions': [
			# :(id)aKey; (id)key; (id key; (id <NSCopying>)aKey;
			# (id __unsafe_unretained [])keys; (id <NSCopying>)key; (const id <NSCopying> [])keys;
			(r'id( <NSCopying>)?(?=([^\()]*?\)|\s+)(a?[kK]ey))', KEY_CLASS),
			# :(NSDictionary *)otherDictionary; :(NSDictionary *)dict;
			(open_paren + r'NSDictionary(?= \*\)(otherDict|dict;))', NSDictionary_Replacement),
			# (NSArray *)allKeys; (NSArray *)keysSorted; :(NSArray *)keys
			(open_paren + r'NSArray \*(?=\)[^:;\s(objects)]*?[kK]ey)', NS_ARRAY_COMPATIBLE_KEYS),
			# (NSArray *)allValues; WithObjects:(NSArray *)objects;
			(open_paren + r'NSArray \*(?=\)(allValues|objects))', NS_ARRAY_COMPATIBLE_VALUES),
			# (NSSet *)keysOfEntriesPassingTest:(BOOL (^)
			(open_paren + r'NSSet \*(?=\)keys)', NS_SET_COMPATIBLE_KEYS),
		]
	},
	'ns_set': {
		'applyTo': ['NSSet', 'NSMutableSet', 'NSCountedSet'],
		'arguments': [NS_ARRAY_COMPATIBLE_VALUES],
		'substitutions': [
			(open_paren + r'NSSet(?= \*\)[^:;]*?([sS]et|other))', NSSet_Replacement),
			# Array:(NSArray *)other/array; (NSArray *)allObjects;
			(open_paren + r'NSArray \*(?=\)(other|array|allObjects))', NS_ARRAY_COMPATIBLE_VALUES),
		],
	},

	# user-added extra for NSArray+Map.h example
	'ns_array_map': {
		'applyTo': ['NSArray'],
		'arguments': [],
		'substitutions': [
			(open_paren + r'NSArray(?= \*\)map)', NSArray_Replacement),
		],
	}

}

# make sure the cocoa_collection arguments are the first in the final macro
collection_subs = collections.OrderedDict(sorted(_collection_dict.items(), key=lambda t: t[0]))

import pprint 

def applies(class_list):
	to_apply = lambda case: case if [c for c in case['applyTo'] if c in class_list] else None
	return filter(None, map(to_apply, collection_subs.values()))

def subs(class_list, key):
	flatten = lambda list_of_lists: [x for sub_list in list_of_lists for x in sub_list]
	return flatten(map(itemgetter(key), applies(class_list)))

def substitutions_for(class_list):
	return subs(class_list, 'substitutions')

def arguments_for(class_list):
	return subs(class_list, 'arguments')

comments = [
	# remove single line // comments
	(r'//.*', ''),
	# remove /* block comments */, http://ostermiller.org/findcomment.html
	(r'/\*(.|[\r\n])*?\*/', '', re.DOTALL),
]

typedefs = [
	(r'typedef.*?;', '', re.DOTALL),
]

target_win_32 = [
	(r'#if TARGET_OS_WIN32.*?#else(.*?)#endif', r'\1', re.DOTALL),
]

# remove complete block
without_c_macro_content = [
	(r'#if.*?#endif', '', re.DOTALL),
]

# remove only if and endif lines
with_c_macro_content = [
	(r'#if.*', ''),
	(r'#endif.*', ''),
]
