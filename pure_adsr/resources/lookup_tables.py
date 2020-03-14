#!/usr/bin/python2.5
#
# Copyright 2014 Emilie Gillet.
#
# Author: Emilie Gillet (emilie.o.gillet@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# See http://creativecommons.org/licenses/MIT/ for more information.
#
# -----------------------------------------------------------------------------
#
# Lookup table definitions.

import numpy

SAMPLE_RATE = 20000000.0 / 510 / 16#/ 4  # hz

"""----------------------------------------------------------------------------
LFO and envelope increments.
----------------------------------------------------------------------------"""

lookup_tables = []
lookup_tables_32 = []
excursion = 1 << 32
sample_rate = SAMPLE_RATE
num_values = 257
min_frequency = 1.0 / 32.0  # Hertz
max_frequency = 160.0  # Hertz
min_increment = excursion * min_frequency / sample_rate
max_increment = excursion * max_frequency / sample_rate

# Create lookup table for envelope times (x^0.25).
max_time = 8.0  # seconds
min_time = 0.0005
gamma = 0.175
min_increment = excursion / (max_time * sample_rate)
max_increment = excursion / (min_time * sample_rate)

rates = numpy.linspace(numpy.power(max_increment, -gamma),
                       numpy.power(min_increment, -gamma), num_values)

values = numpy.power(rates, -1/gamma).astype(int)
lookup_tables_32.append(
    ('env_increments', values)
)

"""----------------------------------------------------------------------------
Envelope curves
-----------------------------------------------------------------------------"""

env_linear = numpy.arange(0, 257.0) / 256.0
env_linear[-1] = env_linear[-2]
env_quartic = env_linear ** 3.32
env_expo = 1.0 - numpy.exp(-4 * env_linear)

lookup_tables.append(('env_linear', env_linear / env_linear.max() * 65535.0))
lookup_tables.append(('env_expo', env_expo / env_expo.max() * 65535.0))
lookup_tables.append(
    ('env_quartic', env_quartic / env_quartic.max() * 65535.0))

raised_cosine = 0.5 - numpy.cos(env_linear * numpy.pi) / 2
lookup_tables.append(('raised_cosine', raised_cosine * 65535.0))
