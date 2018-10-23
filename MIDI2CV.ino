#include <MIDI.h>
#include <Wire.h>
#include <mcp4728.h>
#include <EEPROM.h>

#define MIDI_CHANNEL 1

#define OCTAVE_RANGE 5
#define NOTE_RANGE (OCTAVE_RANGE * 12)
#define MAX_CV (OCTAVE_RANGE * 1000)
#define BASE_NOTE 34

// Define Pitch Bend range to be a major second
#define BEND_RANGE ((1000.0 / 12.0) * 1.5)


#define PIN_GATE_0 9
#define PIN_GATE_1 10
#define PIN_GATE_2 11
#define PIN_GATE_3 12

#define MODE_MONO 0
#define MODE_ARP 1
#define MODE_SEQ 2

#define PIN_SPEED A3

#define PIN_FLIP_SWITCH_0 A6
#define PIN_FLIP_SWITCH_1 A7

#define FLIP_SWITCH_UP 0
#define FLIP_SWITCH_MIDDLE 1
#define FLIP_SWITCH_DOWN 2

#define ROTARY_SWITCH_PIN0 2
#define ROTARY_SWITCH_PIN1 3
#define ROTARY_SWITCH_PIN2 4
#define ROTARY_SWITCH_PIN3 5
#define ROTARY_SWITCH_PIN4 6
#define ROTARY_SWITCH_PIN5 7

#define MIDI_CLOCK_THRESHOLD_MILLIS 500

#define MIDI_CLOCK_DIVIDE_QUARTER 24
#define MIDI_CLOCK_DIVIDE_HALF MIDI_CLOCK_DIVIDE_QUARTER * 2
#define MIDI_CLOCK_DIVIDE_WHOLE MIDI_CLOCK_DIVIDE_HALF * 2
#define MIDI_CLOCK_DIVIDE_EIGTH MIDI_CLOCK_DIVIDE_QUARTER / 2
#define MIDI_CLOCK_DIVIDE_EIGHT_T MIDI_CLOCK_DIVIDE_QUARTER / 3
#define MIDI_CLOCK_DIVIDE_SIXTEENTH MIDI_CLOCK_DIVIDE_EIGTH / 2
#define MIDI_CLOCK_DIVIDE_SIXTEENTH_T MIDI_CLOCK_DIVIDE_EIGTH / 3
#define MIDI_CLOCK_DIVIDE_THIRTY_SECOND MIDI_CLOCK_DIVIDE_SIXTEENTH / 2
#define MIDI_CLOCK_DIVIDE_THIRTY_SECOND_T MIDI_CLOCK_DIVIDE_SIXTEENTH / 3

#define MIDI_CLOCK_DIVISION_COUNT 9
const int clockDivisions[] = { MIDI_CLOCK_DIVIDE_WHOLE,         MIDI_CLOCK_DIVIDE_HALF,
                               MIDI_CLOCK_DIVIDE_QUARTER, 
                               MIDI_CLOCK_DIVIDE_EIGTH,         MIDI_CLOCK_DIVIDE_EIGHT_T,
                               MIDI_CLOCK_DIVIDE_SIXTEENTH,     MIDI_CLOCK_DIVIDE_SIXTEENTH_T,
                               MIDI_CLOCK_DIVIDE_THIRTY_SECOND, MIDI_CLOCK_DIVIDE_THIRTY_SECOND_T
                             };

#define MANUAL_CLOCK_MIN 20
#define MANUAL_CLOCK_MAX 2000

#define SEQUENCE_COUNT 6
#define SEQUENCE_LENGTH_MAX 128

#define ARP_DIRECTION_UP 0
#define ARP_DIRECTION_DOWN 1
#define ARP_DIRECTION_BOTH 2
#define ARP_DIRECTION_ORDER 3
#define ARP_DIRECTION_RANDOM 4
#define ARP_DIRECTION_NONE 5

#define ARP_MODE_LATCH FLIP_SWITCH_UP
#define ARP_MODE_FORGET FLIP_SWITCH_MIDDLE
#define ARP_MODE_ADD FLIP_SWITCH_DOWN


mcp4728 dac = mcp4728(0);

MIDI_CREATE_DEFAULT_INSTANCE(); 

byte currentMode = MODE_MONO;

byte flipSwitch0 = FLIP_SWITCH_UP;
byte flipSwitch1 = FLIP_SWITCH_UP;
byte rotarySwitch = 0;
int speedValue = 0;


int cv[] =    {0,   0,   0,   0};   // 0 to MAX_CV
bool gate[] = {LOW, LOW, LOW, LOW}; // LOW or HIGH
bool midiStartSignal = LOW;
bool midiClockSignal = LOW;
unsigned long activeNotes[NOTE_RANGE];
unsigned long noteCount = 1;
byte activeNoteCount = 0;
int currentPitchBend = 0;
byte currentModulation = 0;
byte currentVelocity = 0;
bool trigger = false;
bool released = false;

byte lastChannel = 0;

int clockCounter = 0;
unsigned long lastClockMillis = 0;
byte currentClockDivide = 0;
byte nextClockDivide = 0;

unsigned long lastManualClockMillis = 0;

byte currentSequencePosition = 0;

byte currentArpPosition = 0;
unsigned long activeArpNotes[NOTE_RANGE];
byte activeArpNoteCount = 0;
bool arpLatchReadyForNew = true;

void setup() {
  dac.begin();
  dac.vdd(5000);
  dac.setVref(1,1,1,1); // set to use internal voltage reference (2.048V)
  dac.setGain(1, 1); // set the gain of internal voltage reference ( 2.048V x 2 = 4.096V )
  
  pinMode(PIN_GATE_0, OUTPUT);
  pinMode(PIN_GATE_1, OUTPUT);
  pinMode(PIN_GATE_2, OUTPUT);
  pinMode(PIN_GATE_3, OUTPUT);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleClock(onMidiClock);
  MIDI.setHandleNoteOn(onMidiNoteOn);
  MIDI.setHandleNoteOff(onMidiNoteOff);
  MIDI.setHandleStart(onMidiStart);
  MIDI.setHandleControlChange(onMidiControlChange);
  MIDI.setHandlePitchBend(onMidiPitchBend);
}

void onMidiClock() {
  if(clockCounter == 0) {
    midiClockSignal = HIGH;
  }
  clockCounter++;
  if(clockCounter == clockDivisions[currentClockDivide]) {
    clockCounter = 0;
    currentClockDivide = nextClockDivide;
  }
  lastClockMillis = millis();
}

void onMidiNoteOn(byte channel, byte note, byte velocity) {
  if(channel > MIDI_CHANNEL + 1) return;

  lastChannel = channel;
  
  if(velocity == 0) { onMidiNoteOff(channel, note, velocity); return; }

  activeNotes[note - BASE_NOTE] = noteCount++;
  activeNoteCount++;
  currentVelocity = velocity;
  trigger = true;
}

void onMidiNoteOff(byte channel, byte note, byte velocity) {
  if(channel > MIDI_CHANNEL + 1) return;
  activeNotes[note - BASE_NOTE] = 0;
  activeNoteCount--;
  if(activeNoteCount == 0) currentVelocity = 0;
  released = 0;
}

void onMidiControlChange(byte channel, byte number, byte value) {
  if(channel > MIDI_CHANNEL + 1) return;
  currentModulation = value; 
}

void onMidiPitchBend(byte channel, int bend) {
  if(channel > MIDI_CHANNEL + 1) return;
  currentPitchBend = bend;
}

void onMidiStart() {
  midiStartSignal = HIGH;
  clockCounter = 0;
  currentClockDivide = nextClockDivide;
}

int midiToCV(byte note) {
  if(note < BASE_NOTE) return 0;
  if(note - BASE_NOTE > NOTE_RANGE) return MAX_CV;
  return map(note - BASE_NOTE, 0, NOTE_RANGE, 0, MAX_CV);
}

byte getMostRecentNote() {
  byte note;
  unsigned long maxTime = 0;
  for(byte i = 0; i < NOTE_RANGE; i++) {
    if(activeNotes[i] != 0 && activeNotes[i] >= maxTime) {
      note = i;
      maxTime = activeNotes[i];
    }
  }
  
  return note;
}

void loop() {
  readSwitches();

  if(flipSwitch0 == FLIP_SWITCH_UP) currentMode = MODE_MONO;
  else if(flipSwitch0 == FLIP_SWITCH_MIDDLE) currentMode = MODE_SEQ;
  else if(flipSwitch0 == FLIP_SWITCH_DOWN) currentMode = MODE_ARP;
  
  readSpeed();
  MIDI.read();

  if(millis() - lastClockMillis > MIDI_CLOCK_THRESHOLD_MILLIS) {
    // Apparently we are not getting any midi clocks, so we will just generate our own signal.
    long waitTime = map(speedValue, 0, 1023, (60000) / MANUAL_CLOCK_MIN, (60000) / MANUAL_CLOCK_MAX);
    if(millis() - lastManualClockMillis > waitTime) {
      // Time for another clock signal!
      lastManualClockMillis = millis();
      midiClockSignal = HIGH;
    }
  } else {
    nextClockDivide = map(speedValue, 0, 1023, 0, MIDI_CLOCK_DIVISION_COUNT);
  }

  bool triggerOut = false;

  
  switch(currentMode) {
    case MODE_MONO:
      if(activeNoteCount > 0) {
        // Find most recent hit key
        byte note = getMostRecentNote();
        
        int value = midiToCV(note + BASE_NOTE);
        cv[0] = value + mapfloat(currentPitchBend, 0, MIDI_PITCHBEND_MAX, -BEND_RANGE, BEND_RANGE);
        cv[1] = map(currentVelocity, 0, 127, 0, MAX_CV);
        cv[2] = map(currentModulation, 0, 127, 0, MAX_CV);
        triggerOut = trigger;
        if(lastChannel == MIDI_CHANNEL + 1 && trigger) { // IF on second channel, we retrigger the gate.
          gate[0] = LOW;
        } else {
          gate[0] = HIGH;
        }
      } else {
        gate[0] = LOW;
      }
      break;
    case MODE_SEQ:
      if(flipSwitch1 == FLIP_SWITCH_UP) {
        // Rec mode. 
        if(activeNoteCount > 0) {
          // Find most recent hit key
          byte note = getMostRecentNote();
          int value = midiToCV(note + BASE_NOTE);
          cv[0] = value + mapfloat(currentPitchBend, 0, MIDI_PITCHBEND_MAX, -BEND_RANGE, BEND_RANGE);
          gate[0] = HIGH;
          if(trigger) {
            triggerOut = true;
  
            EEPROM.update(rotarySwitch, EEPROM[rotarySwitch] + 1);
            byte notePosition = EEPROM[rotarySwitch] - 1;
            EEPROM.update(SEQUENCE_COUNT + rotarySwitch * SEQUENCE_LENGTH_MAX + notePosition, note);
          }
        } else {
          gate[0] = LOW;
          triggerOut = false;  
        }
      } else if(flipSwitch1 == FLIP_SWITCH_MIDDLE) {
        // Play Mode
        if(activeNoteCount > 0 && EEPROM[rotarySwitch] > 0) {
          byte note = getMostRecentNote();
          byte currentSequenceValue = EEPROM[SEQUENCE_COUNT + rotarySwitch * SEQUENCE_LENGTH_MAX + currentSequencePosition];
          note = currentSequenceValue + note - EEPROM[SEQUENCE_COUNT + rotarySwitch * SEQUENCE_LENGTH_MAX + 0];
          
          if(trigger && millis() - lastClockMillis > MIDI_CLOCK_THRESHOLD_MILLIS) {
            // no midi input but a key was pressed, so we start the sequence now instead of at next clock signal
            midiClockSignal = HIGH;
            lastManualClockMillis = millis();
          }
          
          if(midiClockSignal) { // trigger a new note!
            triggerOut = true;
            int value = midiToCV(note + BASE_NOTE);
            cv[0] = value + mapfloat(currentPitchBend, 0, MIDI_PITCHBEND_MAX, -BEND_RANGE, BEND_RANGE);
            currentSequencePosition = (currentSequencePosition + 1) % EEPROM[rotarySwitch];
          }
          gate[0] = HIGH;
        } else {
          gate[0] = LOW;
          currentSequencePosition = 0;
        }
      } else if(flipSwitch1 == FLIP_SWITCH_DOWN) {
        // clear on note
        if(activeNoteCount > 0 && trigger) {
          EEPROM.update(rotarySwitch, 0);
        }
      }
      break;
    case MODE_ARP:
      if(flipSwitch1 == ARP_MODE_LATCH) {
        // ARP Mode LATCH
        if(trigger) {
          if(activeNoteCount == 1) {
             // first note of the new arpeggio pressed
             currentArpPosition = 0;
             activeArpNoteCount = 1;
             for(int i = 0; i < NOTE_RANGE; i++) {
              if(activeNotes[i] != 0) currentArpPosition = i; // This is the first note of our arpeggio, so set it to this
              activeArpNotes[i] = activeNotes[i]; 
             }
          } else {
            // new note for current arpeggio
            for(int i = 0; i < NOTE_RANGE; i++) {
              if(activeNotes[i] != 0 && activeArpNotes[i] == 0) activeArpNoteCount++;
              if(activeNotes[i] != 0) // We don't want to disable any notes, only activate new ones
                activeArpNotes[i] = activeNotes[i]; 
            }
          }
        }
      } else if(flipSwitch1 == ARP_MODE_FORGET) {
        // activeArpNotes is equivalent to activeNotes. ezpz
        for(int i = 0; i < NOTE_RANGE; i++) {
          activeArpNotes[i] = activeNotes[i]; 
        }
        activeArpNoteCount = activeNoteCount;
        if(released && activeNoteCount == 0) {
          currentArpPosition = 0;
        }
      } else if(flipSwitch1 == ARP_MODE_ADD) {
        // we just add any active Note until some mysterious signal tells us to reset (modulation > 63!)
        if(currentModulation < 64) {
          byte active = 0;
          for(int i = 0; i < NOTE_RANGE; i++) {
            if(activeNotes[i] > 0) {
              activeArpNotes[i] = activeNotes[i];
              
            }
            if(activeArpNotes[i] != 0)
              active++;
          }
          activeArpNoteCount = active;
        } else {
          activeArpNoteCount = 0;  
          for(int i = 0; i < NOTE_RANGE; i++) 
            activeArpNotes[i] = 0;
        }
      }

      

      if(activeArpNoteCount > 0) {

        if( activeArpNotes[currentArpPosition] == 0) {
          // find the first note in the arp.
          switch(rotarySwitch) {
            case ARP_DIRECTION_UP:
            case ARP_DIRECTION_BOTH:
              for(int i = 0; i < NOTE_RANGE; i++)
                if(activeArpNotes[i] != 0) {
                  currentArpPosition = i;
                  break;
                }
              break;
            case ARP_DIRECTION_DOWN:
              for(int i = NOTE_RANGE - 1; i >= 0; i--)
                if(activeArpNotes[i] != 0) {
                  currentArpPosition = i;
                  break;
                }
              break;
            case ARP_DIRECTION_RANDOM:
              byte newIndex = 0;

              do {
                newIndex = random(0, 255);  
              } while(activeArpNotes[newIndex] == 0 || currentArpPosition == newIndex);

              currentArpPosition = newIndex;
              break;
            case ARP_DIRECTION_ORDER:
              byte minValue = 0;
              byte minValueIndex = 0;
              for(int i = 0; i < NOTE_RANGE; i++) {
               if(i == currentArpPosition || activeArpNotes[i] == 0) continue;
                 if(activeArpNotes[i] < minValue) {
                   minValue = activeArpNotes[i];
                   minValueIndex = i;  
                 } 
              }
              currentArpPosition = minValueIndex;
              break;
          }
        }
        
        byte note = currentArpPosition; // This is the current Arp Note to play
        
        if(midiClockSignal) { // trigger a new note!
          triggerOut = true;
          int value = midiToCV(note + BASE_NOTE);
          cv[0] = value + mapfloat(currentPitchBend, 0, MIDI_PITCHBEND_MAX, -BEND_RANGE, BEND_RANGE);
          // now we have to find the next arp position. this depends on the current mode.
          bool foundNote = false;

          switch(rotarySwitch) {
            case ARP_DIRECTION_UP:
              if(activeArpNoteCount == 1) break;
              
              // We just go up and if we reach the last note in the arp, we go back to the first one
              for(int i = currentArpPosition + 1; i < NOTE_RANGE; i++) {
                if(activeArpNotes[i] != 0) {
                  // found the next note!
                  currentArpPosition = i;
                  foundNote = true;
                  break;  
                }
              }

              if(!foundNote) {
                // We have to find the first note at the beginning of the arpeggio now...
                for(int i = 0; i < NOTE_RANGE; i++) {
                  if(activeArpNotes[i] != 0) {
                    // found the next note!
                    currentArpPosition = i;
                    break;  
                  }
                }
              }
              
              break;
            case ARP_DIRECTION_DOWN:
              if(activeArpNoteCount == 1) break;
              // We just go down and if we reach the first note in the arp, we go forward to the last one
              for(int i = currentArpPosition - 1; i >= 0; i--) {
                if(activeArpNotes[i] != 0) {
                  // found the next note!
                  currentArpPosition = i;
                  foundNote = true;
                  break;  
                }
              }

              if(!foundNote) {
                // We have to find the last note at the beginning of the arpeggio now...
                for(int i = NOTE_RANGE - 1; i >= 0; i--) {
                  if(activeArpNotes[i] != 0) {
                    // found the next note!
                    currentArpPosition = i;
                    break;  
                  }
                }
              }
              break;
            case ARP_DIRECTION_BOTH:
              if(activeArpNoteCount == 1) break;
              // We just go up and if we reach the last note in the arp, we go back one note
              for(int i = currentArpPosition + 1; i < NOTE_RANGE; i++) {
                if(activeArpNotes[i] != 0) {
                  // found the next note!
                  currentArpPosition = i;
                  foundNote = true;
                  break;  
                }
              }
              // we are going downwards, so let's search!
              if(!foundNote) {
                for(int i = currentArpPosition - 1; i >= 0; i--) {
                  if(activeArpNotes[i] != 0) {
                    // found the next note!
                    currentArpPosition = i;
                    foundNote = true;
                    break;  
                  }
                }  
              }
              
              break;
            case ARP_DIRECTION_ORDER:
              if(activeArpNoteCount == 1) break;
              // We find the note that has the least distance to the current notes value.
              // If we can't find one, we assign the note with the lowest value
              byte minValue = 255;
              byte minValueIndex = 0;
              for(int i = 0; i < NOTE_RANGE; i++) {
                if(i == currentArpPosition || activeArpNotes[i] == 0) continue;
                byte distance = abs(activeArpNotes[i] - activeArpNotes[currentArpPosition]);
                if(distance < minValue) {
                  minValue = distance;
                  minValueIndex = i;
                }
              }

              if(minValue == 255) { // We did not find a higher note, so let's go back to the first one.
                minValue = 0;
                for(int i = 0; i < NOTE_RANGE; i++) {
                  if(i == currentArpPosition || activeArpNotes[i] == 0) continue;
                  if(activeArpNotes[i] < minValue) {
                    minValue = activeArpNotes[i];
                    minValueIndex = i;  
                  } 
                }
              }
              
              currentArpPosition = minValueIndex;  
              break;
            case ARP_DIRECTION_RANDOM:
              byte newIndex = 0;

              do {
                newIndex = random(0, 255);  
              } while(activeArpNotes[newIndex] == 0 || currentArpPosition == newIndex);

              currentArpPosition = newIndex;
              
              break;
            case ARP_DIRECTION_NONE:
              // Noone knows what happens here.
              break;
          }
          
        }
        gate[0] = HIGH;

        

        
      } else {
        gate[0] = LOW;
        currentArpPosition = 0;
      }   
      
      break;
  }
  
  gate[1] = triggerOut ? HIGH : LOW;
  gate[2] = midiStartSignal;
  gate[3] = midiClockSignal;
  
  trigger = false;
  released = false;
  midiStartSignal = LOW;
  midiClockSignal = LOW;
  
  writeDACs();
  writeGates();
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void readSwitches() {
  int analogValue = analogRead(PIN_FLIP_SWITCH_0);
  if(analogValue < 100) flipSwitch0 = FLIP_SWITCH_UP;
  else if(analogValue < 900) flipSwitch0 = FLIP_SWITCH_DOWN;
  else flipSwitch0 = FLIP_SWITCH_MIDDLE;
  analogValue = analogRead(PIN_FLIP_SWITCH_1);
  if(analogValue < 100) flipSwitch1 = FLIP_SWITCH_UP;
  else if(analogValue < 900) flipSwitch1 = FLIP_SWITCH_DOWN;
  else flipSwitch1 = FLIP_SWITCH_MIDDLE;

  if(digitalRead(ROTARY_SWITCH_PIN0) == LOW) rotarySwitch = 0;
  else if(digitalRead(ROTARY_SWITCH_PIN1) == LOW) rotarySwitch = 1;
  else if(digitalRead(ROTARY_SWITCH_PIN2) == LOW) rotarySwitch = 2;
  else if(digitalRead(ROTARY_SWITCH_PIN3) == LOW) rotarySwitch = 3;
  else if(digitalRead(ROTARY_SWITCH_PIN4) == LOW) rotarySwitch = 4;
  else if(digitalRead(ROTARY_SWITCH_PIN5) == LOW) rotarySwitch = 5;
}

void readSpeed() {
  speedValue = analogRead(PIN_SPEED);
}

void writeDACs() {
  dac.analogWrite(map(cv[0], 0, MAX_CV, 0, 4095), map(cv[1], 0, MAX_CV, 0, 4095), map(cv[2], 0, MAX_CV, 0, 4095), map(cv[3], 0, MAX_CV, 0, 4095));
}

void writeGates() {
  digitalWrite(PIN_GATE_0, gate[0] == HIGH ? LOW : HIGH);
  digitalWrite(PIN_GATE_1, gate[1] == HIGH ? LOW : HIGH);
  digitalWrite(PIN_GATE_2, gate[2] == HIGH ? LOW : HIGH);
  digitalWrite(PIN_GATE_3, gate[3] == HIGH ? LOW : HIGH);
}
