include(CheckCXXSourceCompiles)

function(find_recfusionsdk)
    set(RECFUSION_HINT_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party/RecFusionSDK/"
    )

    find_path(
        RECFUSION_INCLUDE_DIR
        NAMES RecFusion.h
        HINTS ${RECFUSION_HINT_DIR}/include
    )

    find_library(
        RECFUSION_LIBRARY
        NAMES RecFusionSDK
        HINTS ${RECFUSION_HINT_DIR}/lib
    )

    set(CMAKE_REQUIRED_FLAGS)
    set(CMAKE_REQUIRED_INCLUDES ${RECFUSION_INCLUDE_DIR})
    set(CMAKE_REQUIRED_LIBRARIES ${RECFUSION_LIBRARY})

    check_cxx_source_compiles(
        [=[
#include <RecFusion.h>

using namespace RecFusion;

int main() {
  RecFusionSDK::majorVersion(); 
}
]=]
        RECFUSION_links
        SRC_EXT
        cpp
    )
    if(NOT RECFUSION_links)
        message(FATAL "Not compiled!")
        return()
    endif()
    message(FATAL "Compiled!")
    # add_library(RecFusion::RecFusion_CXX INTERFACE IMPORTED)

    set(RECFUSION_FOUND ${RECFUSION_links} PARENT_SCOPE)
    set(RECFUSION_INCLUDE_DIR ${CMAKE_REQUIRED_INCLUDES} PARENT_SCOPE)
    set(RECFUSION_LIBRARY ${CMAKE_REQUIRED_LIBRARIES} PARENT_SCOPE)
endfunction()

find_recfusionsdk()

if(RECFUSION_FOUND)
    if(NOT TARGET RecFusion::RecFusion_CXX)
        add_library(RecFusion::RecFusion_CXX INTERFACE IMPORTED)
        set_property(
            TARGET RecFusion::RecFusion_CXX
            PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${RECFUSION_INCLUDE_DIR}"
        )
        set_property(
            TARGET RecFusion::RecFusion_CXX
            PROPERTY INTERFACE_LINK_LIBRARIES "${RECFUSION_LIBRARY}"
        )
    endif()
endif()

if(RECFUSION_FOUND)
    message(STATUS "Found!")
endif()
