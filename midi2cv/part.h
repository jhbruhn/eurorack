#pragma once

#include "stmlib/algorithms/voice_allocator.h"
#include "stmlib/stmlib.h"
#include "voice.h"

using namespace stmlib;

const int kMaximumPolyphony = 4;

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

struct PartData { // Everything defined here will be stored in flash even in power down
  PartVoiceCount_t part_voice_count = VOICE_COUNT_1;
  PartVoiceDetail_t part_voice_detail = VOICE_DETAIL_S;
  bool midi_filter_channel_enabled = true;
  uint8_t midi_filter_channel = 1;
  uint8_t midi_filter_lowest_note = 0;
  uint8_t midi_filter_highest_note = 127;
  MIDIInput_t midi_filter_input = MIDI_INPUT_OMNI;
  MIDIThruMode_t midi_thru_mode = MIDI_THRU_OFF;
  /*BiOutputType_t output_type_row_0[TOTAL_COLUMN_COUNT];
  UniOutputType_t output_type_row_1[TOTAL_COLUMN_COUNT];
  UniOutputType_t output_type_row_2[TOTAL_COLUMN_COUNT];
  GateOutputType_t output_type_row_3[TOTAL_COLUMN_COUNT];*/
};

class Part {
  public:
  Part()
  {
    for (int i = 0; i < TOTAL_COLUMN_COUNT; i++) {
      /*data.output_type_row_0[i] = BI_OFF;
      data.output_type_row_1[i] = UNI_OFF;
      data.output_type_row_2[i] = UNI_OFF;
      data.output_type_row_3[i] = GATE_OFF;*/
    }
  }

  bool NoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  bool NoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
  bool Aftertouch(uint8_t channel, uint8_t note, uint8_t velocity);
  bool Aftertouch(uint8_t channel, uint8_t velocity);
  bool ControlChange(uint8_t channel, uint8_t controller, uint8_t value);
  bool ProgramChange(uint8_t channel, uint8_t program);
  bool PitchBend(uint8_t channel, uint16_t pitch_bend);

  uint8_t required_columns();

  inline PartData* mutable_part_data() { return &data; }
  inline PartData part_data() { return data; }
  void Refresh(); // called whenever the settings change (for example voice count etc)

  private:
  bool is_message_handled(uint8_t channel, uint8_t note); // TODO: add origin
  PartData data;
  VoiceAllocator<kMaximumPolyphony> voiceAllocator;
  Voice voices[kMaximumPolyphony];
};

extern Part parts[];
