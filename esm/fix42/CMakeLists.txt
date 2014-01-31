
add_executable(esm 
  requestApplication.cpp
  replyApplication.cpp
  main.cpp
)

target_link_libraries(esm 
  esmLib
  common 
  ${SOCI_LIBRARIES} 
  ${SOCIPOSTGRESQL_LIBRARIES} 
  ${PostgreSQL_LIBRARIES} 
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${QUICKFIX_LIBRARIES}
)
