
import re, operator

def parse_declaration(declaration):
	""" Parse a @interface ... declaration into its elements (class, superclass, protocols, category name)
	 	Requires single-line declarations to work correctly	"""
	cls = re.match(r'@.*?[ \t]+(\w+)[ \t]*(?![\(:])', declaration).group(1)

	category_match = re.match(r'@.*?\((.*?)\)', declaration)
	category = category_match.group(1) if category_match else None

	adopted_protocols_match = re.match('@.*?<(.*?)>', declaration)
	adopted_protocols = adopted_protocols_match.group(1).split(',') if adopted_protocols_match else []
	adopted_protocols = map(operator.methodcaller('strip'), adopted_protocols)
	
	superclass_match = re.match(r'@.*?:[ \t]*(.*?)[\(<)\s]', declaration)
	superclass = superclass_match.group(1) if superclass_match else None

	# interface, protocol or implementation?
	decl_type = re.match(r'@([\S]+)', declaration).group(1)

	# strip ivar blocks before parsing content
	strip_code = re.sub(r'{.*?}', '\n', declaration, flags = re.DOTALL)
	content = re.match(r'@.*?\n(.*?)@end', strip_code, flags = re.DOTALL).group(1)

	return decl_type, cls, category, superclass, adopted_protocols, content

def imports(header):
	return re.findall(r'#import.*', header)

def class_forwards(header):
	return re.findall(r'@class.*?;', header, flags = re.DOTALL)

def declaration_blocks(header):
	return re.findall(r'(?:@protocol|@interface).*?@end', header, flags = re.DOTALL)

def used_if_macros(header):
	return set(re.findall(r'#if (\S*)', header))

def check_unsupported(header):
	if re.findall(r'#(?!if |endif|import)', header):
		raise Exception('file contains unsupported c macros (no recursion possible)')

