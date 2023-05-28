cmake_minimum_required(VERSION 3.8)
project(tb3_sim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

set(
  DEPENDENCIES
  tf2
  tf2_ros
  geometry_msgs
)

set(
  SOURCES
  src/cmd_vel_filter.cpp
)

# Create odom_filter executable
# add_executable(odom_filter ${SOURCES})
# ament_target_dependencies(odom_filter ${DEPENDENCIES})
# target_include_directories(odom_filter PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>
#   )
# target_compile_features(odom_filter PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# install(TARGETS odom_filter  DESTINATION lib/${PROJECT_NAME})

add_executable(vel_filter ${SOURCES})
ament_target_dependencies(vel_filter ${DEPENDENCIES})

target_include_directories(vel_filter PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(vel_filter PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


install(TARGETS vel_filter
DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch config include rviz worlds
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
