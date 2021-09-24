#include "aubio.h"
#include <emscripten/bind.h>

using namespace emscripten;

class Pitch {
public:
  Pitch(std::string method, uint_t buf_size, uint_t hop_size,
        uint_t sample_rate) {
    buffer = new_fvec(buf_size);
    aubio_pitch =
        new_aubio_pitch(method.c_str(), buf_size, hop_size, sample_rate);
  }

  ~Pitch() {
    del_aubio_pitch(aubio_pitch);
    del_fvec(buffer);
    del_fvec(output);
  }

  float _do(val input) {
    for (int i = 0; i < buffer->length; i += 1) {
      buffer->data[i] = input[i].as<float>();
    }
    aubio_pitch_do(aubio_pitch, buffer, output);
    return output->data[0];
  }

  float getTolerance() { return aubio_pitch_get_tolerance(aubio_pitch); }

  int setTolerance(float tol) {
    return aubio_pitch_set_tolerance(aubio_pitch, tol);
  }

  float getSilence() { return aubio_pitch_get_silence(aubio_pitch); }

  int setSilence(val tol) {
    return aubio_pitch_set_silence(aubio_pitch, tol.as<float>());
  }

  float getConfidence() { return aubio_pitch_get_confidence(aubio_pitch); }

private:
  aubio_pitch_t *aubio_pitch;
  fvec_t *buffer;
  fvec_t *output = new_fvec(1);
};

EMSCRIPTEN_BINDINGS(Pitch) {
  class_<Pitch>("Pitch")
      .constructor<std::string, uint_t, uint_t, uint_t>()
      .function("do", &Pitch::_do)
      .function("getTolerance", &Pitch::getTolerance)
      .function("setTolerance", &Pitch::setTolerance)
      .function("getSilence", &Pitch::getSilence)
      .function("setSilence", &Pitch::setSilence)
      .function("getConfidence", &Pitch::getConfidence);
}
