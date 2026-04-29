####### Util library

SET(UTIL_IMPLFILES
  TreeHelper.cxx
)

SET(UTIL_HDRFILES
  TreeHelper.h
  string_parsers.hh
)

add_library(dk2nuana_utility SHARED ${UTIL_IMPLFILES})
add_library(dk2nuana::utility ALIAS dk2nuana_utility)

set_target_properties(dk2nuana_utility PROPERTIES 
  PUBLIC_HEADER "${UTIL_HDRFILES}"
  EXPORT_NAME utility)



target_link_libraries(dk2nuana_utility
PUBLIC
  ${ROOT_LIBRARIES}
  ROOT::Geom
  ROOT::MathMore
  dk2nuana::commondeps
)

install(TARGETS dk2nuana_utility
    EXPORT dk2nuana-targets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    PUBLIC_HEADER DESTINATION include/dk2nuana/utility COMPONENT Development)
