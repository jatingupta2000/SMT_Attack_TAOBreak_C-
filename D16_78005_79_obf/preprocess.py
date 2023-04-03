f = open('D16_78005_79_obf.c')

code = ''
struct_name_list = []

# Remove struct definition & populating struct name list
struct_bracket_match = True
for x in f:
	xs = x.strip().replace('\n','')
	if struct_bracket_match and xs.startswith('struct') and xs.endswith('{'):
		struct_bracket_match = False
		continue
	if not struct_bracket_match and xs.startswith('}') and xs.endswith(';'):
		struct_bracket_match = True		
		continue
	if xs.startswith('struct') and xs.endswith(';'):
		struct_name_list.append(xs.split(' ')[-1][:-1])
		continue
	code = code + x
f.close()

# Removing traces of structs
for temp in struct_name_list:
	code = code.replace(temp+'.', '')
	
# Adjusting datatypes
code = code.replace('char', 'int')
code = code.replace('_Bool', 'bool')

print(code)
print(struct_name_list)
