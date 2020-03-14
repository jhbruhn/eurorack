#!/usr/bin/env python3
# coding=utf8

import sys
import csv
from collections import OrderedDict

in_t_file = open(sys.argv[1], 'r')
in_b_file = open(sys.argv[2], 'r')
out_file = open(sys.argv[3], 'w')

reader_t = csv.reader(in_t_file, dialect='excel-tab')
reader_b = csv.reader(in_b_file, dialect='excel-tab')
ordered_fieldnames = OrderedDict(
    [('Designator', None), ('Mid X', None), ('Mid Y', None), ('Layer', None), ('Rotation', None)])
writer = csv.DictWriter(out_file, delimiter=',',
                        quoting=csv.QUOTE_NONNUMERIC, fieldnames=ordered_fieldnames)

writer.writerow({'Designator': 'Designator', 'Mid X': 'Mid X',
                 'Mid Y': 'Mid Y', 'Layer': 'Layer', 'Rotation': 'Rotation'})


for reader in [reader_t, reader_b]:
    layer = 'Top'
    if reader == reader_b:
        layer = 'Bottom'

    for row in reader:
        row = list(filter(None, row[0].split(' ')))
        rotation = int(row[3])
        # special behaviour for SOIC8:
        print(len(row))
        if len(row) >= 6:
            print(row[5])

            if "SOIC8" in row[5]:
                if rotation == 180:
                    rotation = 0
                elif rotation == 0:
                    rotation = 180
        writer.writerow({'Designator': row[0], 'Mid X': row[1],
                         'Mid Y': row[2], 'Layer': layer, 'Rotation': rotation})

in_t_file.close()
in_b_file.close()
out_file.close()
