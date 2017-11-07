# aubiojs
aubiojs is a real-time audio processing library based on [aubio](https://github.com/aubio/aubio), now including:
- pitch detection
- tempo detection
- fft forward and inverse

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
This project uses [emscripten](https://github.com/kripken/emscripten) to compile aubio, make sure you have installed.

```
cd build
cmake ..
make
```

*Note: I only tested on osx.*
