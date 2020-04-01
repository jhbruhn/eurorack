import numpy as np
lookup_tables_u16 = []

ADC_RESOLUTION = 4096
OUTPUT_RESOLUTION = 2 ** 16 - 1

# linear to exponential conversion

values = np.linspace(0, 1, num=ADC_RESOLUTION)
values = np.power(values, 2) * OUTPUT_RESOLUTION

lookup_tables_u16.append(('linear_to_exp', values))


# Left pan Lookup table

l_pan = np.linspace(0, 1, num=ADC_RESOLUTION)
r_pan = np.linspace(0, 1, num=ADC_RESOLUTION)

l_pan = np.sin(l_pan * (np.pi / 2.0))
r_pan = np.cos(r_pan * (np.pi / 2.0))

l_pan = np.round(l_pan * OUTPUT_RESOLUTION)
r_pan = np.round(r_pan * OUTPUT_RESOLUTION)

lookup_tables_u16.append(('left_sin_pan', l_pan))
lookup_tables_u16.append(('right_cos_pan', r_pan))

