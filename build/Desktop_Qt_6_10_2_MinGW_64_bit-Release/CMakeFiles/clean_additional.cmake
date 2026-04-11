# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\PlannerGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PlannerGUI_autogen.dir\\ParseCache.txt"
  "PlannerGUI_autogen"
  )
endif()
