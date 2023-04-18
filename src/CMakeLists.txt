
file(GLOB sources_files
"*.h"
"*.cpp"
"*.hpp"
"*.hxx"
"*.cxx")


add_executable(${PROJECT_NAME} ${sources_files} ${BINARY_DIR})

target_link_libraries(${PROJECT_NAME} RAL_LIBRARY)
