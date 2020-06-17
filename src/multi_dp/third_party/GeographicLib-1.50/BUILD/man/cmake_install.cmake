# Install script for directory: /home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/man

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/CartConvert.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/ConicProj.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/GeodesicProj.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/GeoConvert.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/GeodSolve.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/GeoidEval.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/Gravity.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/MagneticField.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/Planimeter.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/RhumbSolve.1"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/TransverseMercatorProj.1"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man8" TYPE FILE FILES
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/geographiclib-get-geoids.8"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/geographiclib-get-gravity.8"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/man/geographiclib-get-magnetic.8"
    )
endif()

