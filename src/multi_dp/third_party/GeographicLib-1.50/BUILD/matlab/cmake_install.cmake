# Install script for directory: /home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/matlab/geographiclib" TYPE FILE FILES
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/Contents.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/cassini_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/cassini_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/defaultellipsoid.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/ecc2flat.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/eqdazim_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/eqdazim_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/flat2ecc.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/gedistance.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/gedoc.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geocent_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geocent_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geodarea.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geoddistance.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geoddoc.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geodreckon.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geographiclib_test.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geoid_height.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/geoid_load.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/gereckon.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/gnomonic_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/gnomonic_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/loccart_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/loccart_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/mgrs_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/mgrs_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/polarst_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/polarst_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/projdoc.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/tranmerc_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/tranmerc_inv.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/utmups_fwd.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/utmups_inv.m"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/matlab/geographiclib/private" TYPE FILE FILES
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/A1m1f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/A2m1f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/A3coeff.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/A3f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/AngDiff.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/AngNormalize.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/AngRound.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C1f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C1pf.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C2f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C3coeff.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C3f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C4coeff.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/C4f.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/G4coeff.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/GeoRotation.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/LatFix.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/SinCosSeries.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/atan2dx.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/cbrtx.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/copysignx.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/cvmgt.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/eatanhe.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/geoid_file.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/geoid_load_file.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/norm2.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/remx.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/sincosdx.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/sumx.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/swap.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/tauf.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib/private/taupf.m"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/matlab/geographiclib-legacy" TYPE FILE FILES
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/Contents.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/geocentricforward.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/geocentricreverse.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/geodesicdirect.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/geodesicinverse.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/geodesicline.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/geoidheight.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/localcartesianforward.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/localcartesianreverse.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/mgrsforward.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/mgrsreverse.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/polygonarea.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/utmupsforward.m"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/geographiclib-legacy/utmupsreverse.m"
    )
endif()

