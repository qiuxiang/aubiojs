type InputArray = Float32Array | number[];

declare class FFT {
  forward(buffer: InputArray): number[];
  inverse(buffer: InputArray): number[];
}

declare type PitchMethod =
  | "default"
  | "yin"
  | "mcomb"
  | "schmitt"
  | "fcomb"
  | "yinfft"
  | "yinfast"
  | "specacf";

declare class Pitch {
  do(buffer: InputArray): number;
}

declare class Tempo {
  do(buffer: InputArray): number;
  getBpm(): number;
  getConfidence(): number;
}

declare type Aubio = {
  FFT: {
    new (bufferSize: number): FFT;
  };
  Pitch: {
    new (
      method: PitchMethod, // Spectral autocorrelation
      bufferSize: number, // length of FFT
      hopSize: number, // number of frames between two consecutive runs
      sampleRate: number // sampling rate of the signal to analyze
    ): Pitch;
  };
  Tempo: {
    new (
      bufferSize: number, // length of FFT
      hopSize: number, // number of frames between two consecutive runs
      sampleRate: number // sampling rate of the signal to analyze
    ): Tempo;
  };
};

declare function aubio(): Promise<Aubio>;

export default aubio;
