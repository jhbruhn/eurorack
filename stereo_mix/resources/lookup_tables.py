import numpy
lookup_tables = []
lookup_tables_32 = []


# linear to exponential conversion

values = []
size = 1024.0
for x in range(int(size)):
  if x == 0:
    values.append(0)
  else:
    values.append((x ** 2) / x)

lookup_tables.append(('linear_to_exp', values))


# Left pan Lookup table

l_pan = numpy.arange(0, 1024)
r_pan = numpy.arange(0, 1024)

l_pan = numpy.sin((l_pan / 1024.0) * (numpy.pi / 2.0))
r_pan = numpy.cos((r_pan / 1024.0) * (numpy.pi / 2.0))

l_pan = numpy.round(l_pan * 1024)
r_pan = numpy.round(r_pan * 1024)

r_pan[1023] = 0 # dirty fix

lookup_tables.append(('left_sin_pan', l_pan))
lookup_tables.append(('right_cos_pan', r_pan))

