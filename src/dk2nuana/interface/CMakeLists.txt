SET(IFCE_IMPLFILES
  LoopRecord.cxx
)

SET(IFCE_HDRFILES
  LoopRecord.h
)


add_library(dk2nuana_interface SHARED ${IFCE_IMPLFILES})
add_library(dk2nuana::interface ALIAS dk2nuana_interface)

set_target_properties(dk2nuana_interface PROPERTIES 
  PUBLIC_HEADER "${IFCE_HDRFILES}"
  EXPORT_NAME interface )

target_link_libraries(dk2nuana_interface
PUBLIC
  ${ROOT_LIBRARIES}
  ROOT::Geom
  ROOT::MathMore
  dk2nu::dk2nuTree
  dk2nuana::commondeps
  dk2nuana::utility
)
target_include_directories(dk2nuana_interface
  PRIVATE
  $ENV{SRPROXY_INC}
)

install(TARGETS dk2nuana_interface
    EXPORT dk2nuana-targets
    PUBLIC_HEADER DESTINATION include/dk2nuana/interface COMPONENT Development)
