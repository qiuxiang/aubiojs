cmake_minimum_required(VERSION 3.6)
project(aubiojs)

set(source_files
  ./aubio/src/onset/onset.c
  ./aubio/src/onset/peakpicker.c
  ./aubio/src/pitch/pitch.c
  ./aubio/src/pitch/pitchfcomb.c
  ./aubio/src/pitch/pitchmcomb.c
  ./aubio/src/pitch/pitchschmitt.c
  ./aubio/src/pitch/pitchspecacf.c
  ./aubio/src/pitch/pitchyin.c
  ./aubio/src/pitch/pitchyinfast.c
  ./aubio/src/pitch/pitchyinfft.c
  ./aubio/src/spectral/awhitening.c
  ./aubio/src/spectral/fft.c
  ./aubio/src/spectral/ooura_fft8g.c
  ./aubio/src/spectral/phasevoc.c
  ./aubio/src/spectral/specdesc.c
  ./aubio/src/spectral/statistics.c
  ./aubio/src/tempo/beattracking.c
  ./aubio/src/tempo/tempo.c
  ./aubio/src/temporal/biquad.c
  ./aubio/src/temporal/c_weighting.c
  ./aubio/src/temporal/filter.c
  ./aubio/src/utils/hist.c
  ./aubio/src/utils/log.c
  ./aubio/src/utils/scale.c
  ./aubio/src/cvec.c
  ./aubio/src/fvec.c
  ./aubio/src/lvec.c
  ./aubio/src/mathutils.c)

include_directories(.)
include_directories(aubio/src)
add_definitions(-DHAVE_CONFIG_H)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
  -sEXPORTED_FUNCTIONS=[_aubio_db_spl,_new_fvec] \
  --post-js ${PROJECT_SOURCE_DIR}/post.js \
  -sENVIRONMENT=web,worker -sSINGLE_FILE=1 -Oz")
add_executable(aubio ${source_files})
