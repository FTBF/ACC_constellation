project(ACC_constellation)

# Find Constellation via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(CNSTLN_SAT REQUIRED ConstellationSatellite)
pkg_check_modules(CNSTLN_EXEC REQUIRED ConstellationExec)
#pkg_check_modules(CNSTLN_CORE REQUIRED ConstellationCore)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Create shared library for satellite
add_library(ACCTransmitterSatellite SHARED "src/ACCTransmitterSatellite.cpp" "src/ACC.cpp" "src/EthernetInterface.cpp" "src/ACDC.cpp" "src/ACCTransmitterSatelliteGenerator.cpp")
add_library(ACCReceiverSatellite SHARED "src/ACCReceiverSatellite.cpp" "src/ACC.cpp" "src/EthernetInterface.cpp" "src/ACDC.cpp" "src/ACCReceiverSatelliteGenerator.cpp")



target_include_directories(ACCTransmitterSatellite PRIVATE "include")
target_include_directories(ACCReceiverSatellite PRIVATE "include")

# Add project internal dependencies
#target_link_libraries(ACCTransmitterSatellite PUBLIC acctransmitter-lib)

# Ensure compilation with (at least) C++20
set_target_properties(ACCTransmitterSatellite PROPERTIES CXX_STANDARD 20)
set_target_properties(ACCReceiverSatellite PROPERTIES CXX_STANDARD 20)

# Add Constellation dependencies
target_include_directories(ACCTransmitterSatellite PUBLIC ${CNSTLN_SAT_INCLUDE_DIRS})
target_link_directories(ACCTransmitterSatellite PUBLIC ${CNSTLN_SAT_LIBRARY_DIRS})
target_link_libraries(ACCTransmitterSatellite PUBLIC ${CNSTLN_SAT_LIBRARIES})
target_compile_options(ACCTransmitterSatellite PUBLIC ${CNSTLN_SAT_CFLAGS_OTHER})

target_include_directories(ACCReceiverSatellite PUBLIC ${CNSTLN_SAT_INCLUDE_DIRS})
target_link_directories(ACCReceiverSatellite PUBLIC ${CNSTLN_SAT_LIBRARY_DIRS})
target_link_libraries(ACCReceiverSatellite PUBLIC ${CNSTLN_SAT_LIBRARIES})
target_compile_options(ACCReceiverSatellite PUBLIC ${CNSTLN_SAT_CFLAGS_OTHER})

# Set library output name to satellite type (used in `Satellite -t`)
set_target_properties(ACCTransmitterSatellite PROPERTIES LIBRARY_OUTPUT_NAME "acctransmitter")
set_target_properties(ACCReceiverSatellite PROPERTIES LIBRARY_OUTPUT_NAME "accreceiver")

# Install satellite to Constellation prefix
set(CNSTLN_SAT_INSTALL_DIR "${CNSTLN_EXEC_LIBDIR}/ConstellationSatellites")
message(STATUS "Installing satellite to: \"${CNSTLN_SAT_INSTALL_DIR}\"")
install(TARGETS
    ACCTransmitterSatellite
    LIBRARY DESTINATION ${CNSTLN_SAT_INSTALL_DIR}
)

install(TARGETS
   ACCReceiverSatellite
   LIBRARY DESTINATION ${CNSTLN_SAT_INSTALL_DIR}
)
