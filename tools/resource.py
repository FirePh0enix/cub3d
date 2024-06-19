#!/bin/env python3

FILES=[
	"assets/M_DISP.tga",
	"assets/M_HOST.tga",

	"assets/textures/DOBWIRE.tga",

	"assets/textures/HELL5_1.tga",
	"assets/textures/LAVA1.tga"
]

fileSizes = {}

def sanitizeName(name):
	nn = ""

	for ch in name:
		if ch.lower() not in "0123456789abcdefghijklmnopqrstuvwxyz_":
			nn += "_"
		else:
			nn += ch.lower()

	return nn

def genRes(file):
	name = "g__" + sanitizeName(file)

	s = ""
	s += "static const char\t" + name + "[] = {\n\t"

	with open(file, "rb") as f:
		data = f.read()
		fileSizes[file] = len(data)

	i = 0
	j = 0

	for b in data:
		s += hex(b)

		if i == 11:
			i = 0
			s += ",\n\t"
		elif j < len(data) - 1:
			s += ", "
			i += 1
		j += 1

	s += "\n};"

	return s

with open("src/resource_gen.c", "w") as fp:
	fp.write("#include \"libft.h\"\n\n")

	for file in FILES:
		s = genRes(file)
		s += "\n"
		fp.write(s)

	# static void *files_map[3] = {
	# 	{ <filename>, (void *) <data>, (void *) <fileSize> }
	# };

	fp.write("static void\t*g__file_map[][3] = {\n")

	for file in FILES:
		name = "g__" + sanitizeName(file)
		fp.write("{{\"{}\", (void *) {}, (void *) {}}},\n".format(file, name, str(fileSizes[file])))

	fp.write("};\n")

	fp.write("""
char	*_get_file_data(char *filename)
{{
	size_t	i;

	i = 0;
	while (i < {0})
	{{
		if (!ft_strcmp(filename, g__file_map[i][0]))
			return (g__file_map[i][1]);
		i++;
	}}
	return (NULL);
}}

size_t	_get_file_size(char *filename)
{{
	size_t	i;

	i = 0;
	while (i < {0})
	{{
		if (!ft_strcmp(filename, g__file_map[i][0]))
			return ((size_t) g__file_map[i][2]);
		i++;
	}}
	return (0);
}}
""".format(len(FILES)))
