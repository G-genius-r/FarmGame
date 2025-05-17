# CMakeList.txt : CMake project for FarmGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FarmGame")

# Add source to this project's executable.
add_executable (FarmGame "FarmGame.cpp"  "classes/Farm.cpp" "headers/Farm.h" "classes/GameTile.cpp" "headers/GameTile.h" "headers/Inventory.h" "headers/Plot.h" "headers/Animal.h" "headers/Barley.h" "headers/Chicken.h" "headers/Entity.h" "headers/Plant.h" "headers/Sheep.h" "headers/Shop.h" "headers/Wheat.h" "classes/Animal.cpp" "classes/Barley.cpp" "classes/Chicken.cpp" "classes/Entity.cpp" "classes/Inventory.cpp" "classes/Plant.cpp" "classes/Plot.cpp" "classes/Sheep.cpp" "classes/Shop.cpp" "classes/Wheat.cpp")

target_link_libraries(FarmGame D:/C++Project/FarmGame/library/sfml-graphics.lib)
target_link_libraries(FarmGame D:/C++Project/FarmGame/library/sfml-audio.lib)
target_link_libraries(FarmGame D:/C++Project/FarmGame/library/sfml-network.lib)
target_link_libraries(FarmGame D:/C++Project/FarmGame/library/sfml-system.lib)
target_link_libraries(FarmGame D:/C++Project/FarmGame/library/sfml-window.lib)

file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-graphics-2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-audio-2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-network-2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-system-2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dir/sfml-window-2.dll DESTINATION ${CMAKE_BINARY_DIR})

include_directories(D:/C++Project/FarmGame/include)

file(COPY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/diagrams/Silkscreen DESTINATION ${CMAKE_BINARY_DIR})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FarmGame PROPERTY CXX_STANDARD 20)
  set_property(TARGET FarmGame PROPERTY CXX_STANDART_REQUIRED ON)
endif()

# TODO: Add tests and install targets if needed.
