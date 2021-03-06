set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/third_party/cmake/Modules/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(BUILD_SHARED_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(GFlags REQUIRED)
find_package(Glog REQUIRED)

set(CMAKE_PREFIX_PATH
        ${CMAKE_SOURCE_DIR}/third_party/install/opencv/
        ${CMAKE_SOURCE_DIR}/third_party/install/c-blosc/
        )

find_package(OpenCV REQUIRED
        PATHS ${CMAKE_SOURCE_DIR}/third_party/install/opencv/
        )

find_package(ASSIMP REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(BLOSC REQUIRED)

find_package(EGL)
find_package(GLESv2)

find_package(Eigen3 REQUIRED
        PATHS ${CMAKE_SOURCE_DIR}/third_party/repos/eigen
        )

add_library(cpp_gsl INTERFACE)
target_include_directories(cpp_gsl INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/repos/cpp_gsl/include
        )

add_library(third_party_core INTERFACE)
target_include_directories(third_party_core INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/repos/cpp_gsl/include
        ${CMAKE_CURRENT_LIST_DIR}/repos/sqlite_modern_cpp/hdr
        ${CMAKE_CURRENT_LIST_DIR}/repos/concurrentqueue
        ${CMAKE_CURRENT_LIST_DIR}/repos/cpp-lru-cache/include
        ${GFLAGS_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${GLOG_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIR}
        ${ASSIMP_INCLUDE_DIR}
        ${BLOSC_INCLUDE_DIR}
        ${SQLITE3_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/third_party/repos/eigen
        ${CMAKE_SOURCE_DIR}/third_party/install/protobuf/include
        )

target_link_libraries(third_party_core INTERFACE
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${GFLAGS_LIBRARIES}
        ${GLOG_LIBRARIES}
        ${OpenCV_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        ${BLOSC_LIBRARIES}
        ${SQLITE3_LIBRARY_RELEASE}
        )


# tensorflow_cc.so must be installed in ~/usr/tensorflow
add_library(tensorflow SHARED IMPORTED GLOBAL)
set_property(TARGET tensorflow PROPERTY
        IMPORTED_LOCATION
        $ENV{HOME}/usr/tensorflow/lib/libtensorflow_cc.so
        )
set_property(TARGET tensorflow PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES
        $ENV{HOME}/usr/tensorflow/include/tf
        $ENV{HOME}/usr/tensorflow/include/tf/bazel-genfiles
        $ENV{HOME}/usr/tensorflow/include/tf/third_party/eigen3
        ${CMAKE_SOURCE_DIR}/third_party/repos/eigen
        ${CMAKE_SOURCE_DIR}/third_party/install/protobuf
        )


add_library(egl INTERFACE)
target_link_libraries(egl INTERFACE
        ${EGL_LIBRARY}
        ${GLESv2_LIBRARY}
        )
target_include_directories(egl SYSTEM INTERFACE
        ${EGL_INCLUDE_DIR}
        ${GLESv2_INCLUDE_DIR}
        )

# mve

find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(TIFF REQUIRED)

add_library(mve INTERFACE)
target_link_libraries(mve INTERFACE
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/mve/libmve.a
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/dmrecon/libmve_dmrecon.a
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/ogl/libmve_ogl.a
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/sfm/libmve_sfm.a
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/fssr/libmve_fssr.a
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/util/libmve_util.a
        ${PNG_LIBRARY} ${JPEG_LIBRARY} ${TIFF_LIBRARY}
        )
target_include_directories(mve INTERFACE
        ${CMAKE_SOURCE_DIR}/third_party/repos/mve/libs/
        ${PNG_INCLUDE_DIR}
        ${JPEG_INCLUDE_DIR}
        ${TIFF_INCLUDE_DIR}
        )
target_compile_options(mve INTERFACE ${OpenMP_CXX_FLAGS})


# polygon2voxel
add_library(polygon2voxel STATIC
        ${CMAKE_SOURCE_DIR}/third_party/src/polygon2voxel/polygon2voxel_double.cc
        ${CMAKE_SOURCE_DIR}/third_party/src/polygon2voxel/polygon2voxel_double.h
        )
target_include_directories(polygon2voxel INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/polygon2voxel/
        )
