# aubiojs

aubiojs is a real-time audio processing library based on [aubio](https://github.com/aubio/aubio), now including:

- pitch detection
- tempo detection

[Online Demo](https://qiuxiang.github.io/aubiojs/)

## Usage

### Web

```html
<script src="aubio.js"></script>
<script>
  aubio().then(({ Tempo }) => {
    const tempo = new Tempo(bufferSize, hopSize, sampleRate);
    tempo.do(audioBuffer);
    const bpm = tempo.getBpm();
  });
</script>
```

### Node

`npm i aubiojs`

```js
import aubio from "aubiojs";

const { Tempo } = await aubio();
const tempo = new Tempo(bufferSize, hopSize, sampleRate);
tempo.do(audioBuffer);
const bpm = tempo.getBpm();
```

## Build

This project uses [emscripten](https://github.com/kripken/emscripten) to compile aubio, make sure you have installed.

```
emcmake cmake -Bbuild -H.
make -Cbuild -j
```
