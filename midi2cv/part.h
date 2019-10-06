#ifndef MIDI2CV_PART_H
#define MIDI2CV_PART_H

enum MIDIThruMode { OFF,
  ON,
  POLYCHAIN };

enum BiOutputType {
  BI_OFF = 0,
  BI_PITCH_UNI,
  BI_PITCH_BI,
  BI_SAWTOOTH,
  BI_SQUARE,
  BI_SINE,
  BI_TRIANGLE
};

enum UniOutputType {
  UNI_OFF = 0,
  UNI_PITCH,
  UNI_VELOCITY,
  UNI_MODULATION,
  UNI_AFTERTOUCH,
  UNI_BREATH,
  UNI_EXP,
  UNI_GATE
};

enum GateOutputType {
  GATE_OFF = 0,
  GATE_GATE,
  GATE_TRIGGER
};

class Part {
  public:
  Part()
      : poly_voice_count(1)
      , output_column_count(1)
      , midi_filter_channel_enabled(true)
      , midi_filter_channel(1)
      , midi_filter_lowest_note(0)
      , midi_filter_highest_note(127)
      , midi_thru_mode(OFF)
  {
    for (int i = 0; i < 4; i++) {
      output_type_row_0[i] = BI_OFF;
      output_type_row_1[i] = UNI_OFF;
      output_type_row_2[i] = UNI_OFF;
      output_type_row_3[i] = GATE_OFF;
    }
  }
  void ProcessMidiInput(/* TODO: Inputs */);

  private:
  uint8_t poly_voice_count;
  uint8_t output_column_count;
  bool midi_filter_channel_enabled;
  uint8_t midi_filter_channel;
  uint8_t midi_filter_lowest_note;
  uint8_t midi_filter_highest_note;
  MIDIThruMode midi_thru_mode;
  BiOutputType output_type_row_0[4];
  UniOutputType output_type_row_1[4];
  UniOutputType output_type_row_2[4];
  GateOutputType output_type_row_3[4];
};

#endif
