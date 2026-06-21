# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-src"
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-build"
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix"
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix/tmp"
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix/src/pisubmarine.input.api-populate-stamp"
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix/src"
  "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix/src/pisubmarine.input.api-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix/src/pisubmarine.input.api-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Software/GitHub/PiSubmarine/Input.Fake/out/build/windows-msvc-debug/_deps/pisubmarine.input.api-subbuild/pisubmarine.input.api-populate-prefix/src/pisubmarine.input.api-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
