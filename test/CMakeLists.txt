set(TESTGODESS_TARGET testgodess)

enable_testing()

find_package (Cat)
if (CAT_FOUND)
  include_directories(${CAT_INCLUDE_DIR})
  set(LIBS ${LIBS} ${CAT_LIBRARIES})
endif (CAT_FOUND)

set(TESTGODESS_DIR "${CMAKE_SOURCE_DIR}/test")

include_directories("${CMAKE_SOURCE_DIR}")

set(TESTGODESS_SOURCES 

"${TESTGODESS_DIR}/decay.C"

)

set(TESTGODESS_TARGET testgodess)
add_executable(${TESTGODESS_TARGET} ${TESTGODESS_SOURCES})
target_link_libraries(${TESTGODESS_TARGET} ${LIBS} godess)
add_dependencies(${TESTGODESS_TARGET} godess)

add_test(${TESTGODESS_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TESTGODESS_TARGET})

