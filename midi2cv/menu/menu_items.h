#pragma once

#include "stmlib/stmlib.h"
#include <stdio.h>

// MenuItem without template so we can easily store pointers
class AbstractMenuItem {
  public:
  virtual const char* get_label();
  virtual char* get_string_representation();
  virtual void increase();
  virtual void decrease();
};

template <class T>
class MenuItem : public AbstractMenuItem {
  private:
  const char* label;
  T* value;
  T step;
  char stringRepresentation[24];

  protected:
  MenuItem(const char* _label, T* _value)
      : label(_label)
      , value(_value) {};

  virtual void to_string(char* buf) = 0;

  void set_value(T value)
  {
    *this->value = value;
    this->to_string(stringRepresentation);
  };

  public:
  T* get_value_ptr()
  {
    return value;
  }

  const char* get_label()
  {
    return label;
  }

  char* get_string_representation()
  {
    if (!stringRepresentation[0])
      this->to_string(stringRepresentation);
    return stringRepresentation;
  }
};

template <class T>
class NumberMenuItem : public MenuItem<T> {
  private:
  T minimumValue;
  T maximumValue;
  T step;

  protected:
  NumberMenuItem(const char* _label, T* _value, T _minimumValue, T _maximumValue, T _step)
      : MenuItem<T>(_label, _value)
      , minimumValue(_minimumValue)
      , maximumValue(_maximumValue)
      , step(_step) {};

  virtual const char* get_format_string() = 0;

  void to_string(char* buf)
  {
    sprintf(buf, this->get_format_string(), *this->get_value_ptr());
  }

  public:
  void increase()
  {
    if (*this->get_value_ptr() + step <= maximumValue && *this->get_value_ptr() + step >= minimumValue)
      this->set_value(*this->get_value_ptr() + step);
  };

  void decrease()
  {
    if (*this->get_value_ptr() - step >= minimumValue && *this->get_value_ptr() - step <= maximumValue)
      this->set_value(*this->get_value_ptr() - step);
  };
};

class UInt32MenuItem : public NumberMenuItem<uint32_t> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%u";
  }

  public:
  UInt32MenuItem(const char* _label, uint32_t* _value, uint32_t _minimumValue, uint32_t _maximumValue, uint32_t _step)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step) {};
};

class Int32MenuItem : public NumberMenuItem<int32_t> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%d";
  }

  public:
  Int32MenuItem(const char* _label, int32_t* _value, int32_t _minimumValue, int32_t _maximumValue, int32_t _step)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step) {};
};

class FloatMenuItem : public NumberMenuItem<float> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%.2f";
  }

  public:
  FloatMenuItem(const char* _label, float* _value, float _minimumValue, float _maximumValue, float _step)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step) {};
};

class BoolMenuItem : public NumberMenuItem<bool> {

  private:
  const char* on_string;
  const char* off_string;

  protected:
  const char* get_format_string()
  {
    bool value = *this->get_value_ptr();

    if (value)
      return this->on_string;
    else
      return this->off_string;
  }

  public:
  BoolMenuItem(const char* _label, bool* _value, const char* _on_string, const char* _off_string)
      : NumberMenuItem(_label, _value, 0, 1, 1)
      , on_string(_on_string)
      , off_string(_off_string) {};
};

class StringListMenuItem : public NumberMenuItem<uint8_t> {
  private:
  const char** string_labels;

  protected:
  const char* get_format_string()
  {
    return this->string_labels[*this->get_value_ptr()];
  }

  public:
  StringListMenuItem(const char* _label, uint8_t* _value, const char** _stringLabels, size_t _itemCount)
      : NumberMenuItem(_label, _value, 0, _itemCount - 1, 1)
      , string_labels(_stringLabels) {};
};

class MidiNoteMenuItem : public NumberMenuItem<uint8_t> {
  private:
  char string_buffer[4];
  const char* note_strings[12];

  protected:
  const char* get_format_string() { return ""; }

  public:
  char* get_string_representation()
  {
    uint8_t currentNote = *this->get_value_ptr();
    int note = currentNote % 12;
    int octave = (currentNote / 12) - 1;

    sprintf(this->string_buffer, "%s%d", note_strings[note], octave);

    return this->string_buffer;
  }

  MidiNoteMenuItem(const char* _label, uint8_t* _value)
      : NumberMenuItem(_label, _value, 0, 127, 1)
  {
    note_strings[0] = "C";
    note_strings[1] = "C#";
    note_strings[2] = "D";
    note_strings[3] = "D#";
    note_strings[4] = "E";
    note_strings[5] = "F";
    note_strings[6] = "F#";
    note_strings[7] = "G";
    note_strings[8] = "G#";
    note_strings[9] = "A";
    note_strings[10] = "A#";
    note_strings[11] = "B";
  };
};
