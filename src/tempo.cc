#include <emscripten/bind.h>
#include "aubio.h"

using namespace emscripten;

class AubioTempo {
public:
  AubioTempo(std::string method, uint_t buf_size, uint_t hop_size, uint_t sample_rate) {
    buffer = new_fvec(hop_size);
    aubio_tempo = new_aubio_tempo(method.c_str(), buf_size, hop_size, sample_rate);
  }

  ~AubioTempo() {
    del_aubio_tempo(aubio_tempo);
    del_fvec(buffer);
    del_fvec(output);
  }

  float Do(val input) {
    for (int i = 0; i < buffer->length; i += 1) {
      buffer->data[i] = input[i].as<float>();
    }
    aubio_tempo_do(aubio_tempo, buffer, output);
    return output->data[0];
  }

  float GetConfidence() {
    return aubio_tempo_get_confidence(aubio_tempo);
  }

  float GetBpm() {
    return aubio_tempo_get_bpm(aubio_tempo);
  }

private:
  aubio_tempo_t *aubio_tempo;
  fvec_t *buffer;
  fvec_t *output = new_fvec(1);
};

EMSCRIPTEN_BINDINGS(AubioTempo) {
  class_<AubioTempo>("AubioTempo")
    .constructor<std::string, uint_t, uint_t, uint_t>()
    .function("do", &AubioTempo::Do)
    .function("getBpm", &AubioTempo::GetBpm)
    .function("getConfidence", &AubioTempo::GetConfidence);
}