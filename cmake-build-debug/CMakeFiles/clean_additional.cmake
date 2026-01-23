# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\RGB_Gulag_GUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RGB_Gulag_GUI_autogen.dir\\ParseCache.txt"
  "RGB_Gulag_GUI_autogen"
  )
endif()
