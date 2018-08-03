#include <emscripten/bind.h>
#include "aubio.h"

using namespace emscripten;

class Pitch {
public:
  Pitch(std::string method, uint_t buf_size, uint_t hop_size, uint_t sample_rate) {
    buffer = new_fvec(buf_size);
    aubio_pitch = new_aubio_pitch(method.c_str(), buf_size, hop_size, sample_rate);
  }

  ~Pitch() {
    del_aubio_pitch(aubio_pitch);
    del_fvec(buffer);
    del_fvec(output);
  }

  float Do(val input) {
    for (int i = 0; i < buffer->length; i += 1) {
      buffer->data[i] = input[i].as<float>();
    }
    aubio_pitch_do(aubio_pitch, buffer, output);
    return output->data[0];
  }

private:
  aubio_pitch_t *aubio_pitch;
  fvec_t *buffer;
  fvec_t *output = new_fvec(1);
};

EMSCRIPTEN_BINDINGS(Pitch) {
  class_<Pitch>("Pitch")
    .constructor<std::string, uint_t, uint_t, uint_t>()
    .function("do", &Pitch::Do);
}