cmake_minimum_required(VERSION 3.1)
# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})

include(${NODEGUI_PLUGIN_CMAKE_HELPER})
include(./config/multimedia.cmake)

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "nodegui_plugin_multimedia")

project(${PLUGIN_ADDON_NAME})

add_library(${PLUGIN_ADDON_NAME} SHARED  
    "${CMAKE_JS_SRC}"
    "${PROJECT_SOURCE_DIR}/src/cpp/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimedia/QMediaContent/qmediacontent_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimedia/QMediaPlayer/qmediaplayer_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimedia/QMediaPlayer/nmediaplayer.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimedia/QMediaPlaylist/NMediaPlaylist.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimedia/QMediaPlaylist/QMediaPlaylist_wrap.cpp"

    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimediaWidgets/QVideoWidget/nvideowidget.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QtMultimediaWidgets/QVideoWidget/qvideowidget_wrap.cpp"
) 

AddPluginConfig(${PLUGIN_ADDON_NAME})
AddQtMultimediaSupport(${PLUGIN_ADDON_NAME})

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE 
    "${CMAKE_JS_INC}" 
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)

