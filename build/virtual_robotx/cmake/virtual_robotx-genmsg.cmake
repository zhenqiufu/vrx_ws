# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "virtual_robotx: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ivirtual_robotx:/home/scar1et/vrx_ws/src/virtual_robotx/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(virtual_robotx_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" NAME_WE)
add_custom_target(_virtual_robotx_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "virtual_robotx" "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(virtual_robotx
  "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/virtual_robotx
)

### Generating Services

### Generating Module File
_generate_module_cpp(virtual_robotx
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/virtual_robotx
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(virtual_robotx_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(virtual_robotx_generate_messages virtual_robotx_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" NAME_WE)
add_dependencies(virtual_robotx_generate_messages_cpp _virtual_robotx_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(virtual_robotx_gencpp)
add_dependencies(virtual_robotx_gencpp virtual_robotx_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS virtual_robotx_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(virtual_robotx
  "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/virtual_robotx
)

### Generating Services

### Generating Module File
_generate_module_eus(virtual_robotx
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/virtual_robotx
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(virtual_robotx_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(virtual_robotx_generate_messages virtual_robotx_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" NAME_WE)
add_dependencies(virtual_robotx_generate_messages_eus _virtual_robotx_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(virtual_robotx_geneus)
add_dependencies(virtual_robotx_geneus virtual_robotx_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS virtual_robotx_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(virtual_robotx
  "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/virtual_robotx
)

### Generating Services

### Generating Module File
_generate_module_lisp(virtual_robotx
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/virtual_robotx
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(virtual_robotx_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(virtual_robotx_generate_messages virtual_robotx_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" NAME_WE)
add_dependencies(virtual_robotx_generate_messages_lisp _virtual_robotx_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(virtual_robotx_genlisp)
add_dependencies(virtual_robotx_genlisp virtual_robotx_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS virtual_robotx_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(virtual_robotx
  "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/virtual_robotx
)

### Generating Services

### Generating Module File
_generate_module_nodejs(virtual_robotx
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/virtual_robotx
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(virtual_robotx_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(virtual_robotx_generate_messages virtual_robotx_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" NAME_WE)
add_dependencies(virtual_robotx_generate_messages_nodejs _virtual_robotx_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(virtual_robotx_gennodejs)
add_dependencies(virtual_robotx_gennodejs virtual_robotx_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS virtual_robotx_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(virtual_robotx
  "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/virtual_robotx
)

### Generating Services

### Generating Module File
_generate_module_py(virtual_robotx
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/virtual_robotx
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(virtual_robotx_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(virtual_robotx_generate_messages virtual_robotx_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/scar1et/vrx_ws/src/virtual_robotx/msg/motor_msgs.msg" NAME_WE)
add_dependencies(virtual_robotx_generate_messages_py _virtual_robotx_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(virtual_robotx_genpy)
add_dependencies(virtual_robotx_genpy virtual_robotx_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS virtual_robotx_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/virtual_robotx)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/virtual_robotx
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(virtual_robotx_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/virtual_robotx)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/virtual_robotx
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(virtual_robotx_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/virtual_robotx)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/virtual_robotx
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(virtual_robotx_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/virtual_robotx)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/virtual_robotx
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(virtual_robotx_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/virtual_robotx)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/virtual_robotx\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/virtual_robotx
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(virtual_robotx_generate_messages_py std_msgs_generate_messages_py)
endif()
