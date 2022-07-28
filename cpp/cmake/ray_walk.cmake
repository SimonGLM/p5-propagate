set(RAY_WALK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RAY_WALK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(RAY_WALK_SRC_FILES 
    "${RAY_WALK_SRC_DIR}/main.cpp"
    "${RAY_WALK_SRC_DIR}/cmdlineparser.cpp"
    "${RAY_WALK_SRC_DIR}/boundary.cpp"
    "${RAY_WALK_SRC_DIR}/ray.cpp"
)
set(RAY_WALK_HEADER_FILES
    "${RAY_WALK_INCLUDE_DIR}/forward_declarations.h"
    "${RAY_WALK_INCLUDE_DIR}/raywalkconfig.h"
    "${RAY_WALK_INCLUDE_DIR}/cmdlineparser.h"
    "${RAY_WALK_INCLUDE_DIR}/boundary.h"
    "${RAY_WALK_INCLUDE_DIR}/ray.h"
)

set(Eigen3_DIR "/home/marvin/eigen-3.4.0/build")
include("${Eigen3_DIR}/../cmake/UseEigen3.cmake")

add_executable(ray_walk ${RAY_WALK_SRC_FILES} ${COMMON_FILES_SRC_DIR})
set_target_properties(ray_walk PROPERTIES POSITION_INDEPENDENT_CODE 1)

target_include_directories(ray_walk PUBLIC
    $<BUILD_INTERFACE:${RAY_WALK_INCLUDE_DIR}>
)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(OPEN_MP_LIB OpenMP::OpenMP_CXX)
endif()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
if (TARGET Eigen3::Eigen)
  message("-- Found Eigen3")
else(TARGET Eigen3::Eigen)
  message("-- Not found Eigen3")
endif (TARGET Eigen3::Eigen)

target_link_libraries(ray_walk
    ${Boost_LIBRARIES}
    ${OPEN_MP_LIB}
    Eigen3::Eigen
    "-lpthread"
)

if (CMAKE_BUILD_TYPE STREQUAL Release)
    add_custom_command(TARGET ray_walk POST_BUILD
            COMMAND ${CMAKE_STRIP} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ray_walk.cmake")
endif()

include(GNUInstallDirs)
install(TARGETS ray_walk DESTINATION bin COMPONENT ray_walk)