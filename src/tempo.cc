#include "aubio.h"
#include <emscripten/bind.h>

using namespace emscripten;

class Tempo {
public:
  Tempo(uint_t buf_size, uint_t hop_size, uint_t sample_rate) {
    buffer = new_fvec(hop_size);
    aubio_tempo = new_aubio_tempo("default", buf_size, hop_size, sample_rate);
  }

  ~Tempo() {
    del_aubio_tempo(aubio_tempo);
    del_fvec(buffer);
    del_fvec(output);
  }

  float _do(val input) {
    for (int i = 0; i < buffer->length; i += 1) {
      buffer->data[i] = input[i].as<float>();
    }
    aubio_tempo_do(aubio_tempo, buffer, output);
    return output->data[0];
  }

  float getConfidence() { return aubio_tempo_get_confidence(aubio_tempo); }

  float getBpm() { return aubio_tempo_get_bpm(aubio_tempo); }

private:
  aubio_tempo_t *aubio_tempo;
  fvec_t *buffer;
  fvec_t *output = new_fvec(1);
};

EMSCRIPTEN_BINDINGS(Tempo) {
  class_<Tempo>("Tempo")
      .constructor<uint_t, uint_t, uint_t>()
      .function("do", &Tempo::_do)
      .function("getBpm", &Tempo::getBpm)
      .function("getConfidence", &Tempo::getConfidence);
}
