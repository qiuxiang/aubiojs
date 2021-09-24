type InputBuffer = Float32Array | number[];

/**
 * default : use the default method
 *
 * Currently, the default method is set to yinfft .
 *
 * schmitt : Schmitt trigger
 *
 * This pitch extraction method implements a Schmitt trigger to estimate the
 * period of a signal.
 *
 * This file was derived from the tuneit project, written by Mario Lang to
 * detect the fundamental frequency of a sound.
 *
 * See http://delysid.org/tuneit.html
 *
 * fcomb : a fast harmonic comb filter
 *
 * This pitch extraction method implements a fast harmonic comb filter to
 * determine the fundamental frequency of a harmonic sound.
 *
 * This file was derived from the tuneit project, written by Mario Lang to
 * detect the fundamental frequency of a sound.
 *
 * See http://delysid.org/tuneit.html
 *
 * mcomb : multiple-comb filter
 *
 * This fundamental frequency estimation algorithm implements spectral
 * flattening, multi-comb filtering and peak histogramming.
 *
 * This method was designed by Juan P. Bello and described in:
 *
 * Juan-Pablo Bello. ``Towards the Automated Analysis of Simple Polyphonic
 * Music''.  PhD thesis, Centre for Digital Music, Queen Mary University of
 * London, London, UK, 2003.
 *
 * yin : YIN algorithm
 *
 * This algorithm was developed by A. de Cheveigne and H. Kawahara and
 * published in:
 *
 * De Cheveigné, A., Kawahara, H. (2002) "YIN, a fundamental frequency
 * estimator for speech and music", J. Acoust. Soc. Am. 111, 1917-1930.
 *
 * see http://recherche.ircam.fr/equipes/pcm/pub/people/cheveign.html
 *
 * yinfast : Yinfast algorithm
 *
 * This algorithm is equivalent to the YIN algorithm, but computed in the
 * spectral domain for efficiency. See also `python/demos/demo_yin_compare.py`.
 *
 * yinfft : Yinfft algorithm
 *
 * This algorithm was derived from the YIN algorithm. In this implementation, a
 * Fourier transform is used to compute a tapered square difference function,
 * which allows spectral weighting. Because the difference function is tapered,
 * the selection of the period is simplified.
 *
 * Paul Brossier, [Automatic annotation of musical audio for interactive
 * systems](http://aubio.org/phd/), Chapter 3, Pitch Analysis, PhD thesis,
 * Centre for Digital music, Queen Mary University of London, London, UK, 2006.
 */
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
  /**
   * execute pitch detection on an input signal frame
   */
  do(buffer: InputBuffer): number;
}

declare class Tempo {
  /**
   * execute tempo detection
   */
  do(buffer: InputBuffer): number;

  /**
   * get current tempo
   */
  getBpm(): number;

  /**
   * get current tempo confidence
   */
  getConfidence(): number;
}

declare type Aubio = {
  Pitch: {
    /**
     * Pitch detection
     *
     * @param method - pitch detection algorithm
     * @param bufferSize - size of the input buffer to analyse
     * @param hopSize - step size between two consecutive analysis instant
     * @param sampleRate - sampling rate of the signal
     */
    new (
      method: PitchMethod,
      bufferSize: number,
      hopSize: number,
      sampleRate: number
    ): Pitch;
  };
  Tempo: {
    /**
     * Tempo detection
     *
     * @param method - pitch detection algorithm
     * @param bufferSize - length of FFT
     * @param hopSize - number of frames between two consecutive runs
     * @param sampleRate - sampling rate of the signal to analyze
     */
    new (bufferSize: number, hopSize: number, sampleRate: number): Tempo;
  };
};

/**
 * aubio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * aubio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with aubio.  If not, see <http://www.gnu.org/licenses/>.
 */
declare function aubio(): Promise<Aubio>;

export default aubio;
