
include_directories(
    ${CMAKE_SOURCE_DIR}
)

set( javasettings_cfg_SRCS
    javapreferences.cpp
)

set( javasettings_cfg_UI
    javasettings.ui
)

ki18n_wrap_ui( javasettings_cfg_SRCS ${javasettings_cfg_UI} )
kconfig_add_kcfg_files( javasettings_cfg_SRCS javaconfig.kcfgc )
add_library(kdev_javasettings OBJECT ${javasettings_cfg_SRCS})
target_link_libraries(kdev_javasettings KDev::Util)

