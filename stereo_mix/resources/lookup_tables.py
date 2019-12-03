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
