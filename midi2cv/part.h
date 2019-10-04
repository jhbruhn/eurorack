#ifndef MIDI2CV_PART_H
#define MIDI2CV_PART_H

enum MIDIThruMode { OFF,
  ON,
  POLYCHAIN };

enum BiOutputMode {
  PITCH_UNI,
  PITCH_BI,
  SAWTOOTH,
  SQUARE,
  SINE,
  TRIANGLE
};

enum UniOutputMode {
  PITCH,
  VELOCITY,
  AFTERTOUCH
};

enum GateOutputMode {
  GATE,
  TRIGGER
};

class Part {
  public:
  Part()
      : voice_count(1)
      , midi_filter_channel_enabled(true)
      , midi_filter_channel(1)
      , midi_thru_mode(OFF)
      , output_mode_0(PITCH_UNI)
      , output_mode_1(VELOCITY)
      , output_mode_2(AFTERTOUCH)
      , output_mode_3(GATE)
  {
  }
  void ProcessMidiInput(/* TODO: Inputs */);

  private:
  uint8_t voice_count;
  bool midi_filter_channel_enabled;
  uint8_t midi_filter_channel;
  MIDIThruMode midi_thru_mode;
  BiOutputMode output_mode_0;
  UniOutputMode output_mode_1;
  UniOutputMode output_mode_2;
  GateOutputMode output_mode_3;
};

#endif
