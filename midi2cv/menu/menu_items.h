#pragma once

#include "stmlib/stmlib.h"
#include <functional>
#include <stdio.h>

static auto always_visible = [] { return true; };

// MenuItem without template so we can easily store pointers
class AbstractMenuItem {
  private:
  std::function<bool()> visibility_indicator;

  public:
  AbstractMenuItem(std::function<bool()> visibility_indicator = always_visible)
      : visibility_indicator(visibility_indicator) {};
  bool visible()
  {
    if (visibility_indicator)
      return visibility_indicator();
    return true;
  }
  virtual const char* get_label() = 0;
  virtual char* get_string_representation() = 0;
  virtual void increase() = 0;
  virtual void decrease() = 0;
};

template <class T>
class MenuItem : public AbstractMenuItem {
  private:
  const char* label;
  T* value;
  T step;
  char stringRepresentation[24];

  protected:
  MenuItem()
      : AbstractMenuItem(always_visible) {};
  MenuItem(const char* _label, T* _value, std::function<bool()> visibility_indicator = always_visible)
      : AbstractMenuItem(visibility_indicator)
      , label(_label)
      , value(_value) {};

  virtual void to_string(char* buf) = 0;

  void set_value(T value)
  {
    if (!this->value)
      return;
    *this->value = value;
    this->to_string(stringRepresentation);
  };

  public:
  bool visible()
  {
    if (this->visibility_indicator)
      return this->visibility_indicator();
    return true;
  }

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
    if (!this->value) {
      sprintf(stringRepresentation, "ERROR");
    } else if (!stringRepresentation[0])
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
  NumberMenuItem() {};
  NumberMenuItem(const char* _label, T* _value, T _minimumValue, T _maximumValue, T _step, std::function<bool()> visibility_indicator = always_visible)
      : MenuItem<T>(_label, _value, visibility_indicator)
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
    if (this->get_value_ptr())
      if (*this->get_value_ptr() + step <= maximumValue && *this->get_value_ptr() + step >= minimumValue)
        this->set_value(*this->get_value_ptr() + step);
  };

  void decrease()
  {
    if (this->get_value_ptr())
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
  UInt32MenuItem(const char* _label, uint32_t* _value, uint32_t _minimumValue, uint32_t _maximumValue, uint32_t _step, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step, visibility_indicator) {};
  UInt32MenuItem() {};
};

class UInt8MenuItem : public NumberMenuItem<uint8_t> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%u";
  }

  public:
  UInt8MenuItem(const char* _label, uint8_t* _value, uint8_t _minimumValue, uint8_t _maximumValue, uint8_t _step, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step, visibility_indicator) {};
  UInt8MenuItem() {};
};

class Int32MenuItem : public NumberMenuItem<int32_t> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%d";
  }

  public:
  Int32MenuItem(const char* _label, int32_t* _value, int32_t _minimumValue, int32_t _maximumValue, int32_t _step, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step, visibility_indicator) {};
  Int32MenuItem();
};

class FloatMenuItem : public NumberMenuItem<float> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%.2f";
  }

  public:
  FloatMenuItem(const char* _label, float* _value, float _minimumValue, float _maximumValue, float _step, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, _minimumValue, _maximumValue, _step, visibility_indicator) {};
  FloatMenuItem() {};
};

class BoolMenuItem : public NumberMenuItem<bool> {

  private:
  const char* on_string;
  const char* off_string;

  protected:
  const char* get_format_string()
  {
    bool value = false;
    if (this->get_value_ptr())
      value = *this->get_value_ptr();
    if (value)
      return this->on_string;
    else
      return this->off_string;
  }

  public:
  BoolMenuItem(const char* _label, bool* _value, const char* _on_string, const char* _off_string, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, 0, 1, 1, visibility_indicator)
      , on_string(_on_string)
      , off_string(_off_string) {};
  BoolMenuItem() {};
};

class StringListMenuItem : public NumberMenuItem<uint8_t> {
  private:
  const char** string_labels;

  protected:
  const char* get_format_string()
  {
    size_t index = 0;
    if (this->get_value_ptr())
      index = *this->get_value_ptr();
    return this->string_labels[index];
  }

  public:
  StringListMenuItem(const char* _label, uint8_t* _value, const char** _stringLabels, size_t _itemCount, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, 0, _itemCount - 1, 1, visibility_indicator)
      , string_labels(_stringLabels) {};
  StringListMenuItem() {};
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
    uint8_t currentNote = 0;
    if (this->get_value_ptr())
      currentNote = *this->get_value_ptr();
    int note = currentNote % 12;
    int octave = (currentNote / 12) - 1;

    sprintf(this->string_buffer, "%s%d", note_strings[note], octave);

    return this->string_buffer;
  }

  MidiNoteMenuItem(const char* _label, uint8_t* _value, std::function<bool()> visibility_indicator = always_visible)
      : NumberMenuItem(_label, _value, 0, 127, 1, visibility_indicator)
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
  MidiNoteMenuItem() {};
};
