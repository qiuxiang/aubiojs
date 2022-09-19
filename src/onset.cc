#include "aubio.h"
#include <emscripten/bind.h>

using namespace emscripten;

class Onset
{
public:
  Onset(std::string method, int buf_size, int hop_size,
        int sample_rate)
  {
    buffer = new_fvec(buf_size);
    aubio_onset =
        new_aubio_onset(method.c_str(), buf_size, hop_size, sample_rate);
  }

  ~Onset()
  {
    del_aubio_onset(aubio_onset);
    del_fvec(buffer);
    del_fvec(output);
  }

  float _do(val input)
  {
    for (int i = 0; i < buffer->length; i += 1)
    {
      buffer->data[i] = input[i].as<float>();
    }
    aubio_onset_do(aubio_onset, buffer, output);
    return output->data[0];
  }

  int getLast() { return aubio_onset_get_last(aubio_onset); }

  float getLastS() { return aubio_onset_get_last_s(aubio_onset); }

  float getLastMs() { return aubio_onset_get_last_ms(aubio_onset); }

  int setAwhitening(val enable)
  {
    return aubio_onset_set_awhitening(aubio_onset, enable.as<int>());
  }

  float getAwhitening()
  {
    return aubio_onset_get_awhitening(aubio_onset);
  }

  int setCompression(val enable)
  {
    return aubio_onset_set_compression(aubio_onset, enable.as<int>());
  }

  float getCompression()
  {
    return aubio_onset_get_compression(aubio_onset);
  }

  int setSilence(val silence)
  {
    return aubio_onset_set_silence(aubio_onset, silence.as<float>());
  }

  float getSilence() { return aubio_onset_get_silence(aubio_onset); }

  float getDescriptor() { return aubio_onset_get_descriptor(aubio_onset); }

  float getThresholdedDescriptor() { return aubio_onset_get_thresholded_descriptor(aubio_onset); }

  int setThreshold(val threshold)
  {
    return aubio_onset_set_threshold(aubio_onset, threshold.as<float>());
  }

  float getThreshold() { return aubio_onset_get_threshold(aubio_onset); }

  int setMinioi(val minioi) { return aubio_onset_set_minioi(aubio_onset, minioi.as<int>()); }

  int setMinioiS(val minioi) { return aubio_onset_set_minioi_s(aubio_onset, minioi.as<float>()); }

  int setMinioiMs(val minioi) { return aubio_onset_set_minioi_ms(aubio_onset, minioi.as<float>()); }

  int getMinioi() { return aubio_onset_get_minioi(aubio_onset); }

  float getMinioiS() { return aubio_onset_get_minioi_s(aubio_onset); }

  float getMinioiMs() { return aubio_onset_get_minioi_ms(aubio_onset); }

  int setDelay(val delay)
  {
    return aubio_onset_set_delay(aubio_onset, delay.as<int>());
  }

  int setDelayS(val delay)
  {
    return aubio_onset_set_delay_s(aubio_onset, delay.as<float>());
  }

  int setDelayMs(val delay)
  {
    return aubio_onset_set_delay_ms(aubio_onset, delay.as<float>());
  }

  int getDelay() { return aubio_onset_get_delay(aubio_onset); }

  float getDelayS() { return aubio_onset_get_delay_s(aubio_onset); }

  float getDelayMs() { return aubio_onset_get_delay_ms(aubio_onset); }

  int setDefaultParameters(std::string mode)
  {
    return aubio_onset_set_default_parameters(aubio_onset, mode.c_str());
  }

  void reset()
  {
    aubio_onset_reset(aubio_onset);
  }

private:
  aubio_onset_t *aubio_onset;
  fvec_t *buffer;
  fvec_t *output = new_fvec(1);
};

EMSCRIPTEN_BINDINGS(Onset)
{
  class_<Onset>("Onset")
      .constructor<std::string, int, int, int>()
      .function("do", &Onset::_do)
      .function("getLast", &Onset::getLast)
      .function("getLastS", &Onset::getLastS)
      .function("getLastMs", &Onset::getLastMs)
      .function("setAwhitening ", &Onset::setAwhitening)
      .function("getAwhitening ", &Onset::getAwhitening)
      .function("setCompression", &Onset::setCompression)
      .function("getCompression", &Onset::getCompression)
      .function("setSilence", &Onset::setSilence)
      .function("getSilence", &Onset::getSilence)
      .function("getDescriptor", &Onset::getDescriptor)
      .function("getThresholdedDescriptor", &Onset::getThresholdedDescriptor)
      .function("setThreshold", &Onset::setThreshold)
      .function("getThreshold", &Onset::getThreshold)
      .function("setMinioi ", &Onset::setMinioi)
      .function("setMinioiS ", &Onset::setMinioiS)
      .function("setMinioiMs ", &Onset::setMinioiMs)
      .function("getMinioi ", &Onset::getMinioi)
      .function("getMinioiS ", &Onset::getMinioiS)
      .function("getMinioiMs ", &Onset::getMinioiMs)
      .function("setDelay", &Onset::setDelay)
      .function("setDelayS", &Onset::setDelayS)
      .function("setDelayMs", &Onset::setDelayMs)
      .function("getDelay", &Onset::getDelay)
      .function("getDelayS", &Onset::getDelayS)
      .function("getDelayMs", &Onset::getDelayMs)
      .function("setDefaultParameters", &Onset::setDefaultParameters)
      .function("reset", &Onset::reset);
}
