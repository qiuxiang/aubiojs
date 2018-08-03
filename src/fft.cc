#include <emscripten/bind.h>
#include "aubio.h"

using namespace emscripten;

class FFT {
public:
  FFT(uint_t buf_size) {
    buffer = new_fvec(buf_size);
    aubio_fft = new_aubio_fft(buf_size);
  }

  ~FFT() {
    del_aubio_fft(aubio_fft);
    del_fvec(buffer);
  }

  val Forward(val input) {
    cvec_t *output = new_cvec(buffer->length);
    for (int i = 0; i < buffer->length; i += 1) {
      buffer->data[i] = input[i].as<float>();
    }
    aubio_fft_do(aubio_fft, buffer, output);
    val spectrum = val::object();
    spectrum.set("norm", val::array());
    spectrum.set("phas", val::array());
    val norm = spectrum["norm"];
    val phas = spectrum["phas"];
    for (int i = 0; i < buffer->length; i += 1) {
      norm.set(i, output->norm[i]);
      phas.set(i, output->phas[i]);
    }
    del_cvec(output);
    return spectrum;
  }

  val Inverse(val input) {
    cvec_t *spectrum = new_cvec(buffer->length);
    val norm = input["norm"];
    val phas = input["phas"];
    for (int i = 0; i < buffer->length; i += 1) {
      spectrum->norm[i] = norm[i].as<float>();
      spectrum->phas[i] = phas[i].as<float>();
    }
    fvec_t *result = new_fvec(buffer->length);
    aubio_fft_rdo(aubio_fft, spectrum, result);
    val output = val::array();
    for (int i = 0; i < buffer->length; i += 1) {
      output.set(i, result->data[i]);
    }
    del_fvec(result);
    del_cvec(spectrum);
    return output;
  }

private:
  aubio_fft_t *aubio_fft;
  fvec_t *buffer;
};

EMSCRIPTEN_BINDINGS(FFT) {
  class_<FFT>("FFT")
    .constructor<uint_t>()
    .function("forward", &FFT::Forward)
    .function("inverse", &FFT::Inverse);
}