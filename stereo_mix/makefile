# Copyright 2012 Emilie Gillet.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

VERSION        = 0.1
MCU_NAME       = 328
TARGET         = stereo_mix
PACKAGES       = avrlib avrlib/devices stereo_mix
RESOURCES      = stereo_mix/resources
PROGRAMMER     = atmelice_isp

LFUSE          = ef
HFUSE          = d8
EFUSE          = 05
LOCK           = ff

include avrlib/makefile.mk

include $(DEP_FILE)

# Rule for building the firmware update file
wav:  $(TARGET_BIN)
	python avr_audio_bootloader/fsk/encoder.py \
		-s 40000 -b 16 -n 8 -z 4 -p 128 -g 128 -k 10 \
		$(TARGET_BIN)

bootstrap_all:
		make -f stereo_mix/makefile
		make -f stereo_mix/bootloader/makefile
		make -f stereo_mix/bootloader/makefile fuses
		$(AVRDUDE) -B 1 $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) \
			-U flash:w:build/stereo_mix/stereo_mix.hex:i \
			-U flash:w:build/stereo_mix_bootloader/stereo_mix_bootloader.hex:i \
			-U lock:w:0xff:m
