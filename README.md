# aubiojs
aubiojs is a real-time audio processing library based on [aubio](https://github.com/aubio/aubio), now including:
- pitch detection, [demo](https://qiuxiang.github.io/aubiojs/examples/pitch.html)
- tempo detection, [demo](https://qiuxiang.github.io/aubiojs/examples/tempo.html)

## Usage
```html
<script src="aubio.js"></script>
<script>
var aubioTempo = new (Module().AubioTempo)('default', bufferSize, hopSize, sampleRate)
// ...
var pitch = aubioTempo.do(audioBuffer)
</script>
```

## Build
This project uses [emscripten](https://github.com/kripken/emscripten) to compile aubio,
so before you start building, you need to have emscripten.

```
cd build
cmake ..
make
```

*Note: I only tested on osx.*
