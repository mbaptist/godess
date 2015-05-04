set(LIB_TARGET godess)

find_package (Cat)
if (CAT_FOUND)
  include_directories(${CAT_INCLUDE_DIR})
  set(LIBS ${LIBS} ${CAT_LIBRARIES})
endif (CAT_FOUND)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${SRC_DIR})

set(HEADERS

"${SRC_DIR}/adams_bashford_2.h"
"${SRC_DIR}/adams_bashford_4.h"
"${SRC_DIR}/explicit_euler.h"
"${SRC_DIR}/godess.h"
#"${SRC_DIR}/method_template.h"
"${SRC_DIR}/odebase.h"
"${SRC_DIR}/ode.h"
"${SRC_DIR}/runge_kutta_2.h"
"${SRC_DIR}/runge_kutta_4.h"

)

set(TEMPLATE_IMPLEMENTATIONS

"${SRC_DIR}/adams_bashford_2.C"
"${SRC_DIR}/adams_bashford_4.C"
"${SRC_DIR}/explicit_euler.C"
#"${SRC_DIR}/method_template.C"
"${SRC_DIR}/odebase.C"
"${SRC_DIR}/runge_kutta_2.C"
"${SRC_DIR}/runge_kutta_4.C"

)

set(SOURCES

"${SRC_DIR}/godess.C"

)

add_library(${LIB_TARGET} SHARED ${SOURCES})
target_include_directories(${LIB_TARGET}
  PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${SRC_DIR}>"
    # Headers used from installed location:
    "$<INSTALL_INTERFACE:include/godess>"     
)
target_link_libraries(${LIB_TARGET} ${LIBS})

install (TARGETS ${LIB_TARGET} DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include/${LIB_TARGET})
install (FILES ${TEMPLATE_IMPLEMENTATIONS} DESTINATION include/${LIB_TARGET})

