#!/usr/bin/env python3
# coding=utf8

import sys
import csv
from collections import OrderedDict

package_remap = {
        "R0603": "0603_R",
        "C0603": "0603_C",
        "R0402": "0402_R",
        "C0402": "0402_C",
        "SO08": "SOIC-8_150mil",
        "SO14": "SOIC-14_150MIL"
}

value_remap = {
    "TL072D": "TL072",
    "TL074D": "TL074",
    "1N4148-2": "1N4148"
}

in_file = open(sys.argv[1], 'r')
out_file = open(sys.argv[2], 'w')

reader = csv.DictReader(in_file, delimiter=';')
ordered_fieldnames = OrderedDict([('Comment', None), ('Designator', None), ('Footprint', None), ('LCSC Part #', None), ('LCSC Part Type', None)])
writer = csv.DictWriter(out_file, delimiter=',', quoting=csv.QUOTE_NONNUMERIC, fieldnames=ordered_fieldnames)

writer.writerow({'Comment': 'Comment', 'Designator': 'Designator', 'Footprint': 'Footprint', 'LCSC Part #': 'LCSC Part #', 'LCSC Part Type': 'LCSC Part Type'})

for row in reader:
    names, value, package, num = [row['Parts'], row['Value'], row['Package'], row['Qty']]
    package = package_remap.get(package, package)
    value = value_remap.get(value, value)
    namestring = ""
    for name in names.split(','):
        name = name.strip()
        namestring += name+ ', '
    namestring = namestring[:len(namestring) - 2]
    writer.writerow({'Comment': value, 'Designator': namestring, 'Footprint': package, 'LCSC Part #': '', 'LCSC Part Type': ''})

in_file.close()
out_file.close()
