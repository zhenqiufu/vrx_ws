execute_process(COMMAND "/home/scar1et/vrx_ws/build/vrx/vrx_gazebo/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/scar1et/vrx_ws/build/vrx/vrx_gazebo/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
