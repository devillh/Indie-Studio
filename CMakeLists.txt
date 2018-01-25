cmake_minimum_required(VERSION 3.0)

project(indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(./libraries/irrklang/includes
		    ./libraries/irrlicht/includes
		    ./sources/CrossExplo
		    ./sources/Explosion
		    ./sources/Bomb
		    ./sources/Character
		    ./sources/Event
		    ./sources/Game
		    ./sources/Map
		    ./sources/Menu
		    ./sources/SplashScreen
		    ./sources/Music
		    ./sources/Menu
		    ./sources/Timer
		    ./sources/Wall
		    ./sources/Window
		    ./sources/PowerUp
		    ./sources
		    )

if(UNIX)

set(CMAKE_SKIP_BUILD_RPATH_FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "$ENV{HOME}/indie_studio")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/release")

set(IRRKLANG_LIBRARY libIrrklang.so)

link_directories(./libraries/irrklang/linux)

set(IRRLICHT_LIBRARY
    -L./libraries/irrlicht/linux
    -lIrrlicht
    -lGL
    -lGLU
    -lXext
    -lX11
    -lXxf86vm
    )

add_executable(indie_studio
	       sources/Bomb/Bomb.cpp
	       sources/Menu/EscMenu.cpp
	       sources/Character/Character.cpp
	       sources/Event/EventManager.cpp
	       sources/Game/Game.cpp
	       sources/Main.cpp
	       sources/Map/Map.cpp
	       sources/Menu/MainMenu.cpp
	       sources/Music/Music.cpp
	       sources/Timer/Clock.cpp
	       sources/Timer/Time.cpp
	       sources/Wall/Wall.cpp
	       sources/Window/Window.cpp
	       sources/SplashScreen/SplashScreen.cpp
	       sources/Explosion/Explosion.cpp
	       sources/CrossExplo/CrossExplo.cpp
	       sources/PowerUp/APowerUp.cpp
	       sources/PowerUp/BombUp.cpp
	       sources/PowerUp/SpeedUp.cpp
	       sources/PowerUp/GodUp.cpp
	       )

target_link_libraries(indie_studio
		      ${IRRKLANG_LIBRARY}
		      ${IRRLICHT_LIBRARY}
		      )

install(TARGETS indie_studio DESTINATION "$ENV{HOME}/indie_studio")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/release/ikpFlac.so"
        DESTINATION "$ENV{HOME}/indie_studio")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/release/ikpMP3.so"
        DESTINATION "$ENV{HOME}/indie_studio")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/release/media"
        DESTINATION "$ENV{HOME}/indie_studio")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libraries/irrklang/linux/libIrrklang.so" DESTINATION "$ENV{HOME}/indie_studio")

elseif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/release")

add_library(Irrklang STATIC IMPORTED)
add_library(Irrlicht STATIC IMPORTED)

set_property(TARGET Irrklang PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libraries/irrklang/windows/libIrrklang.a)
set_property(TARGET Irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libraries/irrlicht/windows/libIrrlicht.a)

add_executable(indie_studio
	       sources/Bomb/Bomb.cpp
	       sources/Menu/EscMenu.cpp
	       sources/Character/Character.cpp
	       sources/Event/EventManager.cpp
	       sources/Game/Game.cpp
	       sources/Main.cpp
	       sources/Map/Map.cpp
	       sources/Menu/MainMenu.cpp
	       sources/Music/Music.cpp
	       sources/Timer/Clock.cpp
	       sources/Timer/Time.cpp
	       sources/Wall/Wall.cpp
	       sources/Window/Window.cpp
	       sources/SplashScreen/SplashScreen.cpp
	       sources/Explosion/Explosion.cpp
	       sources/CrossExplo/CrossExplo.cpp
               sources/PowerUp/APowerUp.cpp
               sources/PowerUp/BombUp.cpp
	       sources/PowerUp/SpeedUp.cpp
	       sources/PowerUp/GodUp.cpp
	       )

target_link_libraries(indie_studio
		      Irrklang
		      Irrlicht
		      )

endif(UNIX)
