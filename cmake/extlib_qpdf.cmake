cmake_minimum_required(VERSION 3.5)

message(STATUS "entering in extlib_qpdf.cmake")

include(ExternalProject)
include(CMakeParseArguments)

#set(PCRE2_URL https://github.com/PCRE2Project/pcre2.git)
#set(PCRE2_TAG pcre2-10.40)

#set(QPDF_URL git@github.ibm.com:CognitiveCore/qpdf-multipart-stream-patched.git)
set(QPDF_URL https://github.com/qpdf/qpdf.git)
#set(QPDF_TAG v11.0.0)
set(QPDF_TAG release-qpdf-10.0.4)

ExternalProject_Add(extlib_qpdf
    PREFIX extlib_qpdf

    DEPENDS extlib_jpeg

    UPDATE_COMMAND ""

    GIT_REPOSITORY ${QPDF_URL}
    GIT_TAG        ${QPDF_TAG}
    
    BUILD_ALWAYS OFF

    INSTALL_DIR ${EXTERNALS_PREFIX_PATH}

    CONFIGURE_COMMAND ./configure --enable-shared=no \\
      --prefix=${EXTERNALS_PREFIX_PATH} \\
      CPPFLAGS=-I${EXTERNALS_PREFIX_PATH}/include \\
      LDFLAGS=-L${EXTERNALS_PREFIX_PATH}/lib/

    #CMAKE_ARGS \\
    #  -DCMAKE_INSTALL_PREFIX=${EXTERNALS_PREFIX_PATH} 
    #  -DCMAKE_INSTALL_LIBDIR=lib \\
    #  -DCMAKE_CXX_FLAGS=${CMAKE_LIB_FLAGS}

    BUILD_IN_SOURCE ON
    LOG_DOWNLOAD ON
    LOG_BUILD ON)

add_library(qpdf STATIC IMPORTED)
set_target_properties(qpdf PROPERTIES IMPORTED_LOCATION ${EXTERNALS_PREFIX_PATH}/lib/libqpdf.a)
add_dependencies(qpdf extlib_qpdf)
