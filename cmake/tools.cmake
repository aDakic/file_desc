if(${PROJECT_NAME}_ENABLE_CLANG_TIDY)
find_program(CLANGTIDY clang-tidy)
if(CLANGTIDY)
  set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
  message("Clang-Tidy finished setting up.")
else()
  message(SEND_ERROR "Clang-Tidy requested but executable not found.")
endif()
endif()

if(${PROJECT_NAME}_ENABLE_CLANG_FORMAT)
file(GLOB_RECURSE ALL_SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/base/*.hpp
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/sync/*.hpp
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/async/*.hpp
  ${PROJECT_SOURCE_DIR}/src/base/*.hpp
  ${PROJECT_SOURCE_DIR}/src/base/*.cpp
  ${PROJECT_SOURCE_DIR}/src/sync/*.hpp
  ${PROJECT_SOURCE_DIR}/src/sync/*.cpp
  ${PROJECT_SOURCE_DIR}/src/async/*.hpp
  ${PROJECT_SOURCE_DIR}/src/async/*.cpp
  ${PROJECT_SOURCE_DIR}/tests/*.cpp
)

find_program(${PROJECT_NAME}_CLANG_FORMAT_BINARY clang-format)

add_custom_target(
  clang-format
  COMMAND ${${PROJECT_NAME}_CLANG_FORMAT_BINARY}
  -i ${ALL_SOURCE_FILES}
)
endif()