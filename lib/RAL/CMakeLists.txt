
add_library(RAL_LIBRARY
    RAL.cpp
    RAL.h
    ModelCSVRAL.cpp
    ModelCSVRAL.h
)

file(COPY RALColors.csv DESTINATION ${CMAKE_BINARY_DIR}/data)

target_include_directories(RAL_LIBRARY
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
PRIVATE   ${CMAKE_CURRENT_BINARY_DIR}
)
