
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${KDE4_INCLUDES}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

set( javasettings_cfg_SRCS
    javapreferences.cpp
)

set( javasettings_cfg_UI
    javasettings.ui
)

kde4_add_ui_files( javasettings_cfg_SRCS ${javasettings_cfg_UI} )
kde4_add_kcfg_files( javasettings_cfg_SRCS javaconfig.kcfgc )
kde4_add_plugin( kcm_kdev_javasettings ${javasettings_cfg_SRCS} )
target_link_libraries( kcm_kdev_javasettings ${KDE4_KUTILS_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} kdevplatformshell )

install( TARGETS 
        kcm_kdev_javasettings
        DESTINATION ${PLUGIN_INSTALL_DIR} )

install( FILES 
        kcm_kdev_javasettings.desktop
        DESTINATION ${SERVICES_INSTALL_DIR} )
