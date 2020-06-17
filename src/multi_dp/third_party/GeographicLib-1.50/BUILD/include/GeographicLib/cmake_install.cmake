# Install script for directory: /home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GeographicLib" TYPE FILE FILES
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Accumulator.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/AlbersEqualArea.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/AzimuthalEquidistant.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/CassiniSoldner.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/CircularEngine.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Constants.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/DMS.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Ellipsoid.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/EllipticFunction.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GARS.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GeoCoords.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Geocentric.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Geodesic.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GeodesicExact.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GeodesicLine.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GeodesicLineExact.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Geohash.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Geoid.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Georef.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Gnomonic.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GravityCircle.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/GravityModel.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/LambertConformalConic.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/LocalCartesian.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/MGRS.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/MagneticCircle.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/MagneticModel.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Math.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/NearestNeighbor.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/NormalGravity.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/OSGB.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/PolarStereographic.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/PolygonArea.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Rhumb.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/SphericalEngine.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/SphericalHarmonic.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/SphericalHarmonic1.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/SphericalHarmonic2.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/TransverseMercator.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/TransverseMercatorExact.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/UTMUPS.hpp"
    "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/include/GeographicLib/Utility.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GeographicLib" TYPE FILE FILES "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/include/GeographicLib/Config.h")
endif()

