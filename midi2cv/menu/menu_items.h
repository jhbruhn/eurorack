#pragma once

#include "stmlib/stmlib.h"
#include <stdio.h>

// MenuItem without template so we can easily store pointers
class AbstractMenuItem {
  public:
  virtual const char* get_label();
  virtual char* get_string_representation();
};

template <class T>
class MenuItem : public AbstractMenuItem {
  private:
  const char* label;
  bool visible;
  T value;
  T step;
  char stringRepresentation[24];

  protected:
  MenuItem(const char* _label, T _initialValue)
      : label(_label)
      , visible(true)
      , value(_initialValue) {};

  virtual void to_string(char* buf) = 0;

  void set_value(T value)
  {
    this->value = value;
    this->to_string(stringRepresentation);
  };

  public:
  T get_value()
  {
    return value;
  }

  const char* get_label()
  {
    return label;
  }

  char* get_string_representation()
  {
    return stringRepresentation;
  }
};

template <class T>
class NumberMenuItem : public MenuItem<T> {
  private:
  T step;
  T minimumValue;
  T maximumValue;

  protected:
  NumberMenuItem(const char* _label, T _initialValue, T _minimumValue, T _maximumValue, T _step)
      : MenuItem<T>(_label, _initialValue)
      , minimumValue(_minimumValue)
      , maximumValue(_maximumValue) {};

  virtual const char* get_format_string() = 0;

  void to_string(char* buf)
  {
    sprintf(buf, this->get_format_string(), this->get_value());
  }

  public:
  void increase()
  {
    if (this->get_value() + step <= maximumValue)
      this->set_value(this->get_value() + step);
  };

  void decrease()
  {
    if (this->get_value() - step >= minimumValue)
      this->set_value(this->get_value() - step);
  };
};

class UIntMenuItem : public NumberMenuItem<uint32_t> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%u";
  }

  public:
  UIntMenuItem(const char* _label, uint32_t _initialValue, uint32_t _minimumValue, uint32_t _maximumValue, uint32_t _step)
      : NumberMenuItem(_label, _initialValue, _minimumValue, _maximumValue, _step)
  {
    this->set_value(_initialValue);
  };
};

class IntMenuItem : public NumberMenuItem<int32_t> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%d";
  }

  public:
  IntMenuItem(const char* _label, int32_t _initialValue, int32_t _minimumValue, int32_t _maximumValue, int32_t _step)
      : NumberMenuItem(_label, _initialValue, _minimumValue, _maximumValue, _step) {};
};

class FloatMenuItem : public NumberMenuItem<float> {
  private:
  protected:
  const char* get_format_string()
  {
    return "%f.2";
  }

  public:
  FloatMenuItem(const char* _label, float _initialValue, float _minimumValue, float _maximumValue, float _step)
      : NumberMenuItem(_label, _initialValue, _minimumValue, _maximumValue, _step) {};
};
