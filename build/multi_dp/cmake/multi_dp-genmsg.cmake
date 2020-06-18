# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "multi_dp: 1 messages, 0 services")

set(MSG_I_FLAGS "-Imulti_dp:/home/skloe/vrx_ws/src/multi_dp/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(multi_dp_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" NAME_WE)
add_custom_target(_multi_dp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multi_dp" "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(multi_dp
  "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_dp
)

### Generating Services

### Generating Module File
_generate_module_cpp(multi_dp
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_dp
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(multi_dp_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(multi_dp_generate_messages multi_dp_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" NAME_WE)
add_dependencies(multi_dp_generate_messages_cpp _multi_dp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_dp_gencpp)
add_dependencies(multi_dp_gencpp multi_dp_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_dp_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(multi_dp
  "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_dp
)

### Generating Services

### Generating Module File
_generate_module_eus(multi_dp
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_dp
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(multi_dp_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(multi_dp_generate_messages multi_dp_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" NAME_WE)
add_dependencies(multi_dp_generate_messages_eus _multi_dp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_dp_geneus)
add_dependencies(multi_dp_geneus multi_dp_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_dp_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(multi_dp
  "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_dp
)

### Generating Services

### Generating Module File
_generate_module_lisp(multi_dp
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_dp
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(multi_dp_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(multi_dp_generate_messages multi_dp_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" NAME_WE)
add_dependencies(multi_dp_generate_messages_lisp _multi_dp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_dp_genlisp)
add_dependencies(multi_dp_genlisp multi_dp_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_dp_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(multi_dp
  "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_dp
)

### Generating Services

### Generating Module File
_generate_module_nodejs(multi_dp
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_dp
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(multi_dp_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(multi_dp_generate_messages multi_dp_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" NAME_WE)
add_dependencies(multi_dp_generate_messages_nodejs _multi_dp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_dp_gennodejs)
add_dependencies(multi_dp_gennodejs multi_dp_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_dp_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(multi_dp
  "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_dp
)

### Generating Services

### Generating Module File
_generate_module_py(multi_dp
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_dp
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(multi_dp_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(multi_dp_generate_messages multi_dp_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/skloe/vrx_ws/src/multi_dp/msg/motor_msgs.msg" NAME_WE)
add_dependencies(multi_dp_generate_messages_py _multi_dp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multi_dp_genpy)
add_dependencies(multi_dp_genpy multi_dp_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multi_dp_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_dp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multi_dp
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(multi_dp_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_dp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/multi_dp
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(multi_dp_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_dp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multi_dp
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(multi_dp_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_dp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/multi_dp
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(multi_dp_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_dp)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_dp\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multi_dp
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(multi_dp_generate_messages_py std_msgs_generate_messages_py)
endif()
