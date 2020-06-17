# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.17/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "GeographicLib built using CMake")
set(CPACK_GENERATOR "TGZ")
set(CPACK_IGNORE_FILES "#;~$;/\\.git;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(tests|testdata|cgi-bin|.*\\.cache)/;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(distrib|.*-distrib|.*-installer|geodesic-papers)/;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/[^/]*\\.(xml|html|css|kmz|pdf)$;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(autogen|biblio)\\.sh$;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(robots.txt|geodesic-biblio.txt|makefile-admin|[^/]*\\.png)$;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/.*blurb.txt$")
set(CPACK_INSTALLED_DIRECTORIES "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "GeographicLib-1.50")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "GeographicLib-1.50")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "charles@karney.com")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.17/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GeographicLib library, utilities, and documentation")
set(CPACK_PACKAGE_FILE_NAME "GeographicLib-1.50")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "GeographicLib-1.50")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "GeographicLib-1.50")
set(CPACK_PACKAGE_NAME "GeographicLib")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "GeographicLib")
set(CPACK_PACKAGE_VERSION "1.50")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "50")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.17/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.17/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "#;~$;/\\.git;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(tests|testdata|cgi-bin|.*\\.cache)/;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(distrib|.*-distrib|.*-installer|geodesic-papers)/;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/[^/]*\\.(xml|html|css|kmz|pdf)$;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(autogen|biblio)\\.sh$;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/(robots.txt|geodesic-biblio.txt|makefile-admin|[^/]*\\.png)$;/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/matlab/.*blurb.txt$")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "GeographicLib-1.50")
set(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/skloe/vrx_ws/src/multi_dp/third_party/GeographicLib-1.50/BUILD/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
