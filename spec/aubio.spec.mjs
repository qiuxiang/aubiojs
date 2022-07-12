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
    "https://file-examples.com/storage/fe64bbb60e62cc956a036bf/2017/11/file_example_WAV_1MG.wav"
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
