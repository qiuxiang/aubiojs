cmake_minimum_required(VERSION 3.6)
project(aubiojs)

set(source_files
  ${PROJECT_SOURCE_DIR}/aubio/src/onset/onset.c
  ${PROJECT_SOURCE_DIR}/aubio/src/onset/peakpicker.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitch.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchfcomb.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchmcomb.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchschmitt.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchspecacf.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchyin.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchyinfast.c
  ${PROJECT_SOURCE_DIR}/aubio/src/pitch/pitchyinfft.c
  ${PROJECT_SOURCE_DIR}/aubio/src/spectral/awhitening.c
  ${PROJECT_SOURCE_DIR}/aubio/src/spectral/fft.c
  ${PROJECT_SOURCE_DIR}/aubio/src/spectral/ooura_fft8g.c
  ${PROJECT_SOURCE_DIR}/aubio/src/spectral/phasevoc.c
  ${PROJECT_SOURCE_DIR}/aubio/src/spectral/specdesc.c
  ${PROJECT_SOURCE_DIR}/aubio/src/spectral/statistics.c
  ${PROJECT_SOURCE_DIR}/aubio/src/tempo/beattracking.c
  ${PROJECT_SOURCE_DIR}/aubio/src/tempo/tempo.c
  ${PROJECT_SOURCE_DIR}/aubio/src/temporal/biquad.c
  ${PROJECT_SOURCE_DIR}/aubio/src/temporal/c_weighting.c
  ${PROJECT_SOURCE_DIR}/aubio/src/temporal/filter.c
  ${PROJECT_SOURCE_DIR}/aubio/src/utils/hist.c
  ${PROJECT_SOURCE_DIR}/aubio/src/utils/log.c
  ${PROJECT_SOURCE_DIR}/aubio/src/utils/scale.c
  ${PROJECT_SOURCE_DIR}/aubio/src/cvec.c
  ${PROJECT_SOURCE_DIR}/aubio/src/fvec.c
  ${PROJECT_SOURCE_DIR}/aubio/src/lvec.c
  ${PROJECT_SOURCE_DIR}/aubio/src/mathutils.c
  ${PROJECT_SOURCE_DIR}/src/tempo.cc
  ${PROJECT_SOURCE_DIR}/src/pitch.cc
  ${PROJECT_SOURCE_DIR}/src/onset.cc)

include_directories(src)
include_directories(aubio/src)
add_definitions(-DHAVE_CONFIG_H)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sMODULARIZE=1 -sEXPORT_NAME=aubio -Oz --bind")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
add_subdirectory(cmake/aubio)
add_subdirectory(cmake/aubio.esm)
