type InputArray = Float32Array | number[];

declare namespace Aubio {
  class FFT {
    constructor(bufferSize: number);
    forward(buffer: InputArray): number[];
    inverse(buffer: InputArray): number[];
  }

  class Pitch {
    constructor(
      method:
        | "default" // yinfft
        | "yin" // YIN algorithm
        | "mcomb" // Multi-comb filter
        | "schmitt" // Schmitt trigger
        | "fcomb" // Fast comb filter
        | "yinfft" // Spectral YIN
        | "yinfast" // YIN fast
        | "specacf", // Spectral autocorrelation
      bufferSize: number, // size of the input buffer to analyse
      hopSize: number, // step size between two consecutive analysis instant
      sampleRate: number // sampling rate of the signal
    );
    do(buffer: InputArray): number;
  }

  class Tempo {
    constructor(
      bufferSize: number, // length of FFT
      hopSize: number, // number of frames between two consecutive runs
      sampleRate: number // sampling rate of the signal to analyze
    );
    do(buffer: InputArray): number;
    getBpm(): number;
    getConfidence(): number;
  }
}
