# aubiojs
aubiojs is a real-time audio processing library based on [aubio](https://github.com/aubio/aubio), now including:
- pitch detection
- tempo detection
- fft forward and inverse

## Usage
(put aubio.js and aubio.wasm on the same folder as your html)
```html
<script src="aubio.js"></script>
<script>
Module().then(function (module) {
  var aubioTempo = new module.AubioTempo('default', bufferSize, hopSize, sampleRate)
  // ...
  var pitch = aubioTempo.do(audioBuffer)
})
</script>
```

## Build
This project uses [emscripten](https://github.com/kripken/emscripten) to compile aubio, make sure you have installed.

Also feel free to install [Ninja](https://ninja-build.org) for faster builds.

```
emcmake cmake -Bbuild -H. -GNinja && ninja -Cbuild
```
