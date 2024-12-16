cmake_minimum_required(VERSION 3.29)
project(radarMMS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5
        COMPONENTS
        Core
        Widgets
        REQUIRED)

set(resources
    resources.qrc
)
set(include
        include/MainWindow.h
        include/CustomButton.h
        include/ThemeButton.h
        include/TemperatureWidget.h
        include/AnimatedEllipse.h
        include/HeaderWidget.h
        include/HeaderButton.h
        include/StatusBlockGraphics.h
        include/TapButton.h
        include/InterfaceManager.h
        include/SettingsDialog.h
        include/MeasurementEnums.h
        include/SettingsButton.h
        include/InputDialog.h
)

set(src
        src/MainWindow.cpp
        src/CustomButton.cpp
        src/ThemeButton.cpp
        src/StatusBlockGraphics.cpp
        src/TapButton.cpp
        src/InterfaceManager.cpp
        src/HeaderButton.cpp
        src/TemperatureWidget.cpp
        src/SettingsDialog.cpp
        src/InputDialog.cpp
        src/MeasurementEnums.cpp
        src/HeaderWidget.cpp
        src/SettingsButton.cpp
)

add_executable(radarMMS
        main.cpp
        ${include}
        ${src}
        ${resources}
)

target_link_libraries(radarMMS
        Qt5::Core
        Qt5::Widgets
)

