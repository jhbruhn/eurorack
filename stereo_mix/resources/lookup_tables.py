import numpy as np
lookup_tables_u16 = []
lookup_tables_u8 = []

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

# led gamma correction
gamma = 2.1
max_in = 255
max_out = 255
input_vals = np.linspace(0, max_in, num=max_in + 1)
gamma_correction = ((input_vals / max_in) ** gamma) * max_out + 0.5
lookup_tables_u8.append(('led_gamma', np.floor(gamma_correction)))

