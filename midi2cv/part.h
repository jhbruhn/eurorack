#ifndef MIDI2CV_PART_H
#define MIDI2CV_PART_H

#include <inttypes.h>

#define TOTAL_COLUMN_COUNT 4

typedef enum : uint8_t {
  MIDI_THRU_OFF = 0,
  MIDI_THRU_ON = 1,
  MIDI_THRU_POLYCHAIN = 2
} MIDIThruMode_t;

typedef enum : uint8_t {
  MIDI_INPUT_OMNI = 0,
  MIDI_INPUT_MIDI = 1,
  MIDI_INPUT_USB = 2
} MIDIInput_t;

typedef enum : uint32_t {
  BI_OFF = 0,
  BI_PITCH_UNI = 1,
  BI_PITCH_BI = 2
} BiOutputType_t;

typedef enum : uint32_t {
  UNI_OFF = 0,
  UNI_PITCH = 1,
  UNI_VELOCITY = 2,
  UNI_MODULATION = 3,
  UNI_AFTERTOUCH = 4,
  UNI_BREATH = 5,
  UNI_EXP = 6,
  UNI_GATE = 7
} UniOutputType_t;

typedef enum : uint32_t {
  GATE_OFF = 0,
  GATE_GATE = 2,
  GATE_TRIGGER = 3
} GateOutputType_t;

typedef enum : uint8_t {
  VOICE_COUNT_1 = 1,
  VOICE_COUNT_2 = 2,
  VOICE_COUNT_3 = 3,
  VOICE_COUNT_4 = 4
} PartVoiceCount_t;

typedef enum : uint8_t {
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

  PartVoiceCount_t part_voice_count;
  PartVoiceDetail_t part_voice_detail;
  bool midi_filter_channel_enabled;
  uint8_t midi_filter_channel;
  uint8_t midi_filter_lowest_note;
  uint8_t midi_filter_highest_note;
  MIDIInput_t midi_filter_input;
  MIDIThruMode_t midi_thru_mode;
  BiOutputType_t output_type_row_0[TOTAL_COLUMN_COUNT];
  UniOutputType_t output_type_row_1[TOTAL_COLUMN_COUNT];
  UniOutputType_t output_type_row_2[TOTAL_COLUMN_COUNT];
  GateOutputType_t output_type_row_3[TOTAL_COLUMN_COUNT];
};

extern Part parts[];

#endif
