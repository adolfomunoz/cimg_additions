cmake_minimum_required(VERSION 3.10)

find_package(PNG)
if(PNG_FOUND)
	include_directories(${PNG_INCLUDE_DIR})
	list(APPEND cimg_libs ${PNG_LIBRARY})
	list(APPEND cimg_defs "cimg_use_png")
endif(PNG_FOUND)

find_package(JPEG)
if(JPEG_FOUND)
	include_directories(${JPEG_INCLUDE_DIR})
	list(APPEND cimg_libs ${JPEG_LIBRARY})
	list(APPEND cimg_defs "cimg_use_jpeg")
endif(JPEG_FOUND)

find_package(TIFF)
if(TIFF_FOUND)
	include_directories(${TIFF_INCLUDE_DIR})
	list(APPEND cimg_libs ${TIFF_LIBRARY})
	list(APPEND image_defs "cimg_use_tiff")
endif(TIFF_FOUND)

if(FFTW3_FOUND)
	include_directories(${FFTW3_INCLUDE_DIR})
	list(APPEND cimg_libs ${FFTW3_LIBRARY})
	list(APPEND cimg_defs "cimg_use_fftw3")
endif(FFTW3_FOUND)

#find_package(ImageMagick COMPONENTS Magick++)
#if (ImageMagick_FOUND)
#	include_directories(${ImageMagick_INCLUDE_DIRS})
#	list(APPEND cimg_libs ${ImageMagick_LIBRARIES})
#	list(APPEND cimg_defs "cimg_use_magick")
#	list(APPEND cimg_defs "MAGICKCORE_QUANTUM_DEPTH=16")
#	list(APPEND cimg_defs "MAGICKCORE_HDRI_ENABLE=0")
#endif(ImageMagick_FOUND)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows specific code
    list(APPEND cimgdisplay_libs gdi32)
    list(APPEND cimgdisplay_defs cimg_display=2)
    list(APPEND cimg_defs cimg_OS=2)
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    list(APPEND cimg_libs pthread)
    list(APPEND cimgdisplay_libs X11)
    list(APPEND cimgdisplay_defs cimg_display=1)
    list(APPEND cimg_defs cimg_OS=1)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

include_directories(${CMAKE_CURRENT_LIST_DIR})

##################################################################################
# EXTERNAL LIBRARIES
##################################################################################
option(BUILD_OFFLINE "Build offline" OFF)

if (NOT EXTERNAL_INSTALL_LOCATION)
	set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)
endif()

if (NOT IS_DIRECTORY ${EXTERNAL_INSTALL_LOCATION})
	file(MAKE_DIRECTORY ${EXTERNAL_INSTALL_LOCATION})
endif()

# If offline you can set -DBUILD_OFFLINE=ON so it does not try to update stuff
if (${BUILD_OFFLINE})
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                 PROPERTY EP_UPDATE_DISCONNECTED 1)
endif()


include(ExternalProject)
# callable_traits (useful for parameter-type deduction for general stuff)

ExternalProject_Add(cimg
  GIT_REPOSITORY https://framagit.org/dtschump/CImg.git 
  SOURCE_DIR ${EXTERNAL_INSTALL_LOCATION}/CImg
  BUILD_COMMAND ""
  CONFIGURE_COMMAND ""
  INSTALL_COMMAND ""
)


include_directories(${EXTERNAL_INSTALL_LOCATION}/CImg)

######################################################################################
# TARGETS
######################################################################################
if (NOT EXECUTABLE_OUTPUT_PATH)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

if (NOT IS_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
	file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endif()

add_executable(image2ppm main/image2ppm.cc)
target_compile_definitions(image2ppm PRIVATE ${cimg_defs})
target_link_libraries(image2ppm ${cimg_libs})
	
