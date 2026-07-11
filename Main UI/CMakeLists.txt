cmake_minimum_required(VERSION 3.19)
project(UTH_Management LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(UTH_Management
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    applicationmanager.h
    applicationmanager.cpp
    navigationmanager.h
    navigationmanager.cpp
    loginscreen.h
    loginscreen.cpp
    loginscreen.ui
    posview.h
    posview.cpp
    posview.ui
)

target_link_libraries(UTH_Management
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS UTH_Management
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET UTH_Management
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
