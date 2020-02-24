#include "settings.h"
#include "midi2cv/part.h"

Settings::Settings() : first_start(false)
{
  persistent_data_.honor = 1;

  first_start = !chunk_storage_.Init(&persistent_data_, &state_);
}

void Settings::SavePersistentData()
{
  chunk_storage_.SavePersistentData();
}

void Settings::SaveState()
{
  chunk_storage_.SaveState();
}
