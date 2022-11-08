import fetch from "node-fetch";
import { decode } from "wav-decoder";
import aubio from "../build/aubio.js";

async function getAudioData(url) {
  const response = await fetch(url);
  const { sampleRate, channelData } = await decode(await response.buffer());
  return [sampleRate, channelData[0]];
}

it("pitch detection", async () => {
  const { Pitch } = await aubio();
  const [sampleRate, data] = await getAudioData(
    "https://www.soundjay.com/buttons/beep-01a.wav"
  );
  const bufferSize = 4096;
  const pitch = new Pitch("default", bufferSize, bufferSize / 4, sampleRate);
  for (let i = 0; i < data.length - bufferSize; i += bufferSize) {
    const frequency = pitch.do(data.slice(i, i + bufferSize));
    console.log(`${frequency.toFixed(0)} Hz`);
  }
});

it("tempo detection", async () => {
  const { Tempo } = await aubio();
  const [sampleRate, data] = await getAudioData(
    "https://www.soundjay.com/buttons/beep-01a.wav"
  );
  const bufferSize = 1024;
  const tempo = new Tempo(bufferSize, bufferSize / 8, sampleRate);
  const length = (data.length - bufferSize) / 2;
  for (let i = 0; i < length; i += bufferSize) {
    tempo.do(data.slice(i, i + bufferSize));
    const bpm = tempo.getBpm();
    if (bpm) {
      console.log("bpm", bpm.toFixed(0));
    }
  }
});

it("onset detection", async () => {
  const { Onset } = await aubio();
  const [sampleRate, data] = await getAudioData(
    "https://www.soundjay.com/buttons/beep-01a.wav"
  );
  const bufferSize = 512;
  const onset = new Onset("default", bufferSize * 4, bufferSize, sampleRate);
  for (let i = 0; i < data.length - bufferSize; i += bufferSize) {
    if (onset.do(data.slice(i, i + bufferSize))){
      const attack = onset.getLast();
      console.log(`${attack.toFixed(0)}`);
    }
  }
});
