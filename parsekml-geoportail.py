#!/usr/bin/env python3
import sys

import xml.etree.ElementTree as et
root=et.parse(sys.argv[1]).getroot()
for pmk in root[0]:
	pnt=des=False
	for child in list(pmk):
		if(child.tag.endswith('Point')): pnt=child[0].text.split(',')
		if(child.tag.endswith('description')): des=child.text
	if (pnt and des): print(pnt[1], pnt[0], des)
