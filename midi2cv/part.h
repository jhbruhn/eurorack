#ifndef MIDI2CV_PART_H
#define MIDI2CV_PART_H

#include <inttypes.h>

#define TOTAL_COLUMN_COUNT 4

typedef enum { MIDI_THRU_OFF = 0,
  MIDI_THRU_ON = 1,
  MIDI_THRU_POLYCHAIN = 2 } MIDIThruMode_t;

typedef enum {
  BI_OFF = 0,
  BI_PITCH_UNI,
  BI_PITCH_BI
} BiOutputType_t;

typedef enum {
  UNI_OFF = 0,
  UNI_PITCH,
  UNI_VELOCITY,
  UNI_MODULATION,
  UNI_AFTERTOUCH,
  UNI_BREATH,
  UNI_EXP,
  UNI_GATE
} UniOutputType_t;

typedef enum {
  GATE_OFF = 0,
  GATE_GATE,
  GATE_TRIGGER
} GateOutputType_t;

typedef enum {
  VOICE_COUNT_1 = 1,
  VOICE_COUNT_2 = 2,
  VOICE_COUNT_3 = 3,
  VOICE_COUNT_4 = 4
} PartVoiceCount_t;

typedef enum {
  VOICE_DETAIL_S = 0,
  VOICE_DETAIL_M = 1,
  VOICE_DETAIL_L = 2,
  VOICE_DETAIL_XL = 3
} PartVoiceDetail_t;

class Part {
  public:
  Part()
      : part_voice_count(VOICE_COUNT_1)
      , part_voice_detail(VOICE_DETAIL_S)
      , midi_filter_channel_enabled(true)
      , midi_filter_channel(1)
      , midi_filter_lowest_note(0)
      , midi_filter_highest_note(127)
      , midi_thru_mode(MIDI_THRU_OFF)
  {
    for (int i = 0; i < TOTAL_COLUMN_COUNT; i++) {
      output_type_row_0[i] = BI_OFF;
      output_type_row_1[i] = UNI_OFF;
      output_type_row_2[i] = UNI_OFF;
      output_type_row_3[i] = GATE_OFF;
    }
  }
  void ProcessMidiInput(/* TODO: Inputs */);

  uint8_t RequiredColumns();

  private:
  PartVoiceCount_t part_voice_count;
  PartVoiceDetail_t part_voice_detail;
  bool midi_filter_channel_enabled;
  uint8_t midi_filter_channel;
  uint8_t midi_filter_lowest_note;
  uint8_t midi_filter_highest_note;
  MIDIThruMode_t midi_thru_mode;
  BiOutputType_t output_type_row_0[TOTAL_COLUMN_COUNT];
  UniOutputType_t output_type_row_1[TOTAL_COLUMN_COUNT];
  UniOutputType_t output_type_row_2[TOTAL_COLUMN_COUNT];
  GateOutputType_t output_type_row_3[TOTAL_COLUMN_COUNT];
};

extern Part parts[];

#endif
