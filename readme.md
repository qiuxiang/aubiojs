# aubiojs [![npm-badge]][npm] [![build-badge]][build]

[Online Demo](https://qiuxiang.github.io/aubiojs/)

aubiojs is a real-time audio processing library based on [aubio](https://github.com/aubio/aubio), now including:

- pitch detection
- tempo detection

## Usage

### Web

```html
<script src="https://unpkg.com/aubiojs"></script>
<script>
  aubio().then(({ Tempo }) => {
    const tempo = new Tempo(bufferSize, hopSize, sampleRate);
    tempo.do(audioBuffer);
    const bpm = tempo.getBpm();
  });
</script>
```

### Node

```
npm i aubiojs
```

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
npm run build
```

[npm]: https://www.npmjs.com/package/aubiojs
[npm-badge]: https://img.shields.io/npm/v/aubiojs.svg
[build]: https://github.com/qiuxiang/aubiojs/actions/workflows/build.yml
[build-badge]: https://github.com/qiuxiang/aubiojs/actions/workflows/build.yml/badge.svg
