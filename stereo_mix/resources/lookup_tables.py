import numpy
lookup_tables = []
lookup_tables_32 = []


# linear to exponential conversion

values = []
size = 512.0
for x in range(1, int(size) + 1):
    values.append(numpy.power(x / 512.0, 2) * size)

lookup_tables.append(('linear_to_exp', values))


# Left pan Lookup table

l_pan = numpy.arange(0, 512)
r_pan = numpy.arange(0, 512)

l_pan = numpy.sin((l_pan / 512.0) * (numpy.pi / 2.0))
r_pan = numpy.cos((r_pan / 512.0) * (numpy.pi / 2.0))

l_pan = numpy.round(l_pan * 512)
r_pan = numpy.round(r_pan * 512)

r_pan[511] = 0 # dirty fix

lookup_tables.append(('left_sin_pan', l_pan))
lookup_tables.append(('right_cos_pan', r_pan))

