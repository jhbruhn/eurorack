import numpy as np
import matplotlib
import matplotlib.pyplot as plt

lookup_tables_u16 = []
lookup_tables_u8 = []

ADC_RESOLUTION = 4096
OUTPUT_RESOLUTION = 2 ** 16 - 1

# linear to exponential conversion

space = np.linspace(0, 1, num=ADC_RESOLUTION)
values = np.power(space, 2) * OUTPUT_RESOLUTION

lookup_tables_u16.append(('linear_to_exp', values))
print(values.size)

fig, ax = plt.subplots()
ax.plot(space, values)
other_values = OUTPUT_RESOLUTION - np.flip(values)
ax.plot(space, OUTPUT_RESOLUTION - (np.flip(values)))
ax.plot(space, values / 2 + other_values / 2)

ax.set(xlabel='space', ylabel='values')
ax.grid()

# plt.show()


# Left pan Lookup table

space = np.linspace(0, (np.pi / 2.0), num=ADC_RESOLUTION)

l_pan = np.sqrt(space * (2.0 / np.pi) * np.sin(space))
r_pan = np.sqrt(((np.pi / 2.0) - space) * (2.0 / np.pi) * np.cos(space))

l_pan = np.floor(l_pan * OUTPUT_RESOLUTION)
r_pan = np.floor(r_pan * OUTPUT_RESOLUTION)

fig, ax = plt.subplots()
ax.plot(space, l_pan)
ax.plot(space, r_pan)

ax.set(xlabel='space', ylabel='values')
ax.grid()

#plt.show()

lookup_tables_u16.append(('left_sin_pan', l_pan))
print(l_pan.size)
lookup_tables_u16.append(('right_cos_pan', r_pan))
print(r_pan.size)

# led gamma correction
gamma = 2.4
max_in = 255
max_out = 511
input_vals = np.linspace(0, max_in, num=max_in + 1)
gamma_correction = ((input_vals / max_in) ** gamma) * max_out + 0.5
lookup_tables_u16.append(('led_gamma', np.floor(gamma_correction)))
