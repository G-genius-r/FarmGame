﻿cmake_minimum_required(VERSION 3.8)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("FarmGame")

# Настройка выходного каталога
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Add source to this project's executable.
add_executable (FarmGame "FarmGame.cpp"  "classes/Farm.cpp" "headers/Farm.h" "classes/GameTile.cpp" "headers/GameTile.h" "headers/Inventory.h" "headers/Plot.h" "headers/Animal.h" "headers/Barley.h" "headers/Chicken.h" "headers/Entity.h" "headers/Plant.h" "headers/Sheep.h" "headers/Shop.h" "headers/Wheat.h" "classes/Animal.cpp" "classes/Barley.cpp" "classes/Chicken.cpp" "classes/Entity.cpp" "classes/Inventory.cpp" "classes/Plant.cpp" "classes/Plot.cpp" "classes/Sheep.cpp" "classes/Shop.cpp" "classes/Wheat.cpp" "classes/menu.cpp" "headers/menu.h" "classes/MoneyPanel.cpp" "headers/MoneyPanel.h" "classes/MessagePanel.cpp" "headers/MessagePanel.h" "headers/MusicMenu.h" "classes/MusicMenu.cpp" "classes/Button.cpp" "headers/Button.h" "classes/NotificationPanel.cpp" "headers/NotificationPanel.h" "headers/ConfirmationDialog.h" "classes/ConfirmationDialog.cpp" "classes/GameState.cpp")

if(WIN32)
    # Убираем консольное окно для Windows
    set_target_properties(FarmGame PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()

# Подключение SFML
target_link_libraries(FarmGame 
    D:/C++Project/FarmGame/library/sfml-graphics.lib
    D:/C++Project/FarmGame/library/sfml-audio.lib
    D:/C++Project/FarmGame/library/sfml-network.lib
    D:/C++Project/FarmGame/library/sfml-system.lib
    D:/C++Project/FarmGame/library/sfml-window.lib)

# Копирование DLL и ресурсов в бинарный каталог
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-graphics-2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-audio-2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-network-2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-system-2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-window-2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(COPY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/audio DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/diagrams/Silkscreen DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include_directories(D:/C++Project/FarmGame/include)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FarmGame PROPERTY CXX_STANDARD 20)
  set_property(TARGET FarmGame PROPERTY CXX_STANDART_REQUIRED ON)
endif()

# Настройка установки
install(TARGETS FarmGame RUNTIME DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/dir/sfml-graphics-2.dll DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/dir/sfml-audio-2.dll DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/dir/sfml-network-2.dll DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/dir/sfml-system-2.dll DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/dir/sfml-window-2.dll DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/sprites/icon.ico DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/sprites DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/audio DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/diagrams/Silkscreen DESTINATION .)

# Настройка CPack
set(CPACK_PACKAGE_NAME "FarmGame")
set(CPACK_PACKAGE_VENDOR "Mandrik Valeriya")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Farm life simulator")
set(CPACK_PACKAGE_EXECUTABLES "FarmGame" "Фермерские будни")  # Имя ярлыка
set(CPACK_CREATE_DESKTOP_LINKS "FarmGame")
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_DISPLAY_NAME "FarmGame")
set(CPACK_NSIS_INSTALLED_ICON_NAME "FarmGame.exe")
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/sprites/icon.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/sprites/icon.ico")

# Указываем, что нужно добавить рабочий каталог в ярлыки
set(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
set(CPACK_NSIS_START_MENU_DIRECTORY "Фермерские будни")
set(CPACK_NSIS_FORCE_SET_NSIS_FLAGS ON)

# Указываем, что ярлыки должны запускаться из папки установки
  set(CPACK_NSIS_CREATE_ICONS_EXTRA "
    CreateShortCut '$DESKTOP\\\\Фермерские будни.lnk' '$INSTDIR\\\\FarmGame.exe' '' '$INSTDIR\\\\icon.ico'
    CreateShortCut '$SMPROGRAMS\\\\$START_MENU_FOLDER\\\\Фермерские будни.lnk' '$INSTDIR\\\\FarmGame.exe' '' '$INSTDIR\\\\icon.ico'
  ")

include(CPack)