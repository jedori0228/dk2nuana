LIST(APPEND TARGETS_TO_BUILD 
RunNuMIAna
)

foreach(targ ${TARGETS_TO_BUILD})
  add_executable(${targ} ${targ}.cxx)
  target_link_libraries(${targ} 
    ${ROOT_LIBRARIES}
    ROOT::Geom
    ROOT::MathMore
    dk2nuana::commondeps
    dk2nuana::interface
    dk2nuana::utility
  )

endforeach()

install(TARGETS ${TARGETS_TO_BUILD} DESTINATION bin/)
