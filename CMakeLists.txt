project(ktexteditor_zealsearch)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(ktexteditor_zealsearch_SRCS zealsearch_config.cpp zealsearchplugin.cpp)

kde4_add_plugin(ktexteditor_zealsearch ${ktexteditor_zealsearch_SRCS})

target_link_libraries(ktexteditor_zealsearch ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS})

install(TARGETS ktexteditor_zealsearch DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES zealsearchui.rc DESTINATION ${DATA_INSTALL_DIR}/ktexteditor_zealsearch)

install(FILES ktexteditor_zealsearch.desktop ktexteditor_zealsearch_config.desktop DESTINATION ${SERVICES_INSTALL_DIR})
 
