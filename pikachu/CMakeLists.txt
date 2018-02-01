cmake_minimum_required(VERSION 3.7)
project(3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        tracker/clock.cpp
        tracker/clock.h
        tracker/drawable.h
        tracker/engine.cpp
        tracker/engine.h
        tracker/frameGenerator.cpp
        tracker/frameGenerator.h
        tracker/gamedata.cpp
        tracker/gamedata.h
        tracker/image.cpp
        tracker/image.h
        tracker/imageFactory.cpp
        tracker/imageFactory.h
        tracker/ioMod.cpp
        tracker/ioMod.h
        tracker/main.cpp
        tracker/multisprite.cpp
        tracker/multisprite.h
        tracker/parseXML.cpp
        tracker/parseXML.h
        tracker/renderContext.cpp
        tracker/renderContext.h
        tracker/sprite.cpp
        tracker/sprite.h
        tracker/spriteSheet.cpp
        tracker/spriteSheet.h
        tracker/sound.h
        tracker/sound.cpp
        tracker/vector2f.cpp
        tracker/vector2f.h
        tracker/viewport.cpp
        tracker/viewport.h
        tracker/world.cpp
        tracker/world.h
        tracker/twowayMultisprite.h
        tracker/twowayMultisprite.cpp
        tracker/player.h
        tracker/player.cpp
        tracker/HUD.h
        tracker/HUD.cpp
        tracker/collisionStrategy.h
        tracker/collisionStrategy.cpp
        tracker/smartSprite.h
        tracker/smartSprite.cpp
        tracker/bullet.h
        tracker/bullet.cpp
        tracker/chunk.h
        tracker/chunk.cpp
        tracker/explodingSprite.h
        tracker/explodingSprite.cpp)

add_executable(3 ${SOURCE_FILES})