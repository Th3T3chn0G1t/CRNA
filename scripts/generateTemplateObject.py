#!/usr/bin/python3

import io
from sys import argv

name = argv[1]

def read_file(path: str, delimiter: str = '\n'):
	f = open(path, 'r')
	data = f.read()
	if(not delimiter == ''):
		data = data.split(delimiter)
	f.close()
	return data

def write_file(path: str, data: str = ""):
	text_file = open(path, "w+")
	text_file.write(data)
	text_file.close()


header = read_file("res/templates/template_object.h", '')

header = header.replace("TEMPLATE_OBJECT", name.upper())
header = header.replace("template_object_T", name + "_T")
header = header.replace("template_object(", name + "(")

write_file("src/object/include/" + name + ".h", header)


source = read_file("res/templates/template_object.c", '')

source = source.replace("TEMPLATE_OBJECT", name.upper())
source = source.replace("template_object_T", name + "_T")
source = source.replace("template_object(", name + "(")
source = source.replace("template_object_tick", name + "_tick")
source = source.replace("template_object_on_collide", name + "_on_collide")
source = source.replace("template_object.h", "include/" + name + ".h")

write_file("src/object/" + name + ".c", source)
