project(Rendering CXX C)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17) # for all targets
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(DEFINED ENV{VULKAN_SDK})
	message(STATUS "Vulkan SDK: $ENV{VULKAN_SDK}")
else()
	message(WARNING "You may need to set the VULKAN_SDK environment variable before invoking CMake: “$ENV{VULKAN_SDK}”")
endif()

set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory(glfw)

add_executable(glfw_vulkan_test EXCLUDE_FROM_ALL glfw/tests/vulkan.c)
target_link_libraries(glfw_vulkan_test glfw)


set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE) # we use the font vectors directly; HarfBuzz’s hinting is not used
add_subdirectory(freetype₂)


add_executable(lorem_ipsum renderer/main.cpp renderer/geometry.cpp renderer/outline.cpp)
target_link_libraries(lorem_ipsum glfw freetype)
target_include_directories(lorem_ipsum PRIVATE freetype₂/include)



# LunarG SDK’s MoltenVK support still seems a bit… iffy… at the moment
if (APPLE)
	target_compile_definitions(glfw PRIVATE -D_GLFW_VULKAN_STATIC)
	add_library(MoltenVK INTERFACE) # glfw needs to find the dylib, but we need to link statically

	target_link_libraries(MoltenVK INTERFACE "-framework QuartzCore -framework Metal -framework IOSurface") # these seem to be missing elsewhere
	target_link_libraries(MoltenVK INTERFACE $ENV{VULKAN_SDK}/MoltenVK/macOS/MoltenVK.framework/Versions/Current/MoltenVK)
	target_include_directories(MoltenVK INTERFACE $ENV{VULKAN_SDK}/MoltenVK/macOS/MoltenVK.framework/Versions/Current/Headers)
	target_include_directories(MoltenVK INTERFACE $ENV{VULKAN_SDK})

	target_include_directories(MoltenVK INTERFACE $ENV{VULKAN_SDK}/macOS/include)
	target_sources(MoltenVK INTERFACE $ENV{VULKAN_SDK}/macOS/include/vulkan/vulkan.h)
	target_sources(MoltenVK INTERFACE $ENV{VULKAN_SDK}/macOS/include/vulkan/vulkan.hpp)

	set_target_properties(glfw_vulkan_test PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries(glfw_vulkan_test MoltenVK)

	set_target_properties(lorem_ipsum PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries(lorem_ipsum MoltenVK)
endif()

