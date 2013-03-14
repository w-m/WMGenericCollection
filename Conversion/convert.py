#!/usr/bin/python

import sys, os, re, datetime, __future__
import parsing, substitutions as subs, implementation as impl

def replace(content, substitutions):
	"""Apply list of regex pairs (substitutions) with optional flags to content"""
	for sub in substitutions:
		content = re.sub(sub[0], sub[1], content, flags = (sub[2] if len(sub) > 2 else 0))
	return content

def create_declaration_header(decl_type, cls, category, superclass, protocols):
	yield "@" + decl_type + ' ' + subs.new_class_name(cls)
	if superclass: yield " : " + cls
	if category: yield " (" + category + ")"
	if protocols: yield " <" + ', '.join(protocols) + '>'

def update_all_declarations(parsed_declarations):
	"""Apply regexes to an @interface ... @end declaration block to replace class names of objects, keys, ..."""
	updated_bodies = {}
	for decl_type, cls, category, superclass, protocols, body in parsed_declarations:
		decl_header = ''.join(create_declaration_header(decl_type, cls, category, superclass, protocols))
		updated_body = replace(body, subs.substitutions_for([cls, superclass]))
		if superclass in updated_bodies:
			wrapped = impl.ignore([updated_bodies[superclass], ], impl.w_duplicate)
			updated_body += impl.super_declaration_start % superclass + '\n'.join(wrapped)
		updated_bodies[cls] = updated_bodies.get(cls, '') + updated_body
		
		yield decl_header, decl_header + '\n' + updated_body + '@end;\n'

def create_implementation(decl_type, cls, category):
	if (decl_type != 'interface') or category: return None
	return replace(impl.imp_block, [(r'new_class', subs.new_class_name(cls)), (r'original_class', cls)])

def create_c_macro_def(classes):
	def remove_duplicates(seq): seen = set(); return [x for x in seq if x not in seen and not seen.add(x)]
	argument_list = remove_duplicates(subs.arguments_for(classes) + map(subs.new_class_name, classes))
	return '#define ' + subs.new_class_name(classes[0]).upper() + '_%s(' + ', '.join(argument_list) + ')'

def create_body_variants(stripped_file_content):
	""" #if and related directives can't be used inside a #define. Since the Cocoa collection headers
		contain '#if NS_BLOCKS_AVAILABLE', do every #define twice, wrapped in the #if #else #endif"""
	macro_names = parsing.used_if_macros(stripped_file_content)
	if not macro_names: 
		return [('', stripped_file_content, ''), ]
	elif len(macro_names) > 1:
		raise Exception('Different #if directives found: %s. Can only support one.' % ', '.join(macro_names))
	else:
		macro_name = macro_names.pop()
		if_macro_body = replace(stripped_file_content, subs.with_c_macro_content)
		else_macro_body = replace(stripped_file_content, subs.without_c_macro_content)
		return [('#if ' 	 + macro_name, if_macro_body, 	  ''),
				('#else // ' + macro_name, else_macro_body, '#endif // ' + macro_name)]

def create_header(stripped_file_content, output_file_name):
	input_file_names = ', '.join(map(os.path.basename, sys.argv[1:]))
	yield [impl.header_comment % (output_file_name, datetime.date.today(), input_file_names), ]
	yield parsing.imports(stripped_file_content)
	yield parsing.class_forwards(stripped_file_content)

def create_body(stripped_file_content):
	escape_newlines = lambda line: replace(line, [(r'\n', '\\\n'), ])
	for prefix, body, suffix in create_body_variants(stripped_file_content):
		yield [prefix, ], True
		declarations = map(parsing.parse_declaration, parsing.declaration_blocks(body))
		updated_declarations = zip(*list(update_all_declarations(declarations)))
		macro_define = create_c_macro_def(zip(*declarations)[1])
		interface = ((macro_define % impl.INTERFACE, ) + updated_declarations[1])
		yield map(escape_newlines, interface), updated_declarations[0]

		new_implementations = filter(None, map(create_implementation, *zip(*declarations)[:3]))
		imp_block = [macro_define % impl.IMPLEMENTATION, ] + impl.ignore(new_implementations, impl.w_incomplete)
		yield map(escape_newlines, imp_block), False
		yield [suffix, ], True

def write_lines(file, lines, log = False, line_joint = '\n'):
	if log: print('\n'.join(lines if log == True else log))
	file.write(line_joint.join(lines) + '\n\n')

def generate_output(stripped_file_content):
	first_input_file_name = os.path.splitext(os.path.basename(sys.argv[1]))[0]
	output_file_name = subs.new_class_name(first_input_file_name) + '.h'
	with open(output_file_name, 'w') as f:
		print('Writing output file: %s\n' % output_file_name)
		map(lambda block: write_lines(f, block), create_header(stripped_file_content, output_file_name))
		map(lambda (block, log): write_lines(f, block, log, line_joint = '\\\n'), create_body(stripped_file_content))

def process_input_files(file_list):
	concat_file_content = '\n'.join([open(f).read() for f in file_list])
	stripped_comments = replace(concat_file_content, subs.comments)
	stripped_ignored = replace(stripped_comments, subs.target_win_32 + subs.typedefs)
	parsing.check_unsupported(stripped_ignored)	
	generate_output(stripped_ignored)

if __name__== '__main__':
	process_input_files(sys.argv[1:])

