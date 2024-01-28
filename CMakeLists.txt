# Set CMake version
cmake_minimum_required(VERSION 3.10)

project(Cnake)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Create a list of source files
set(SRC_FILES 
    src/main.c
    src/game/gameflow.c
    src/game/initSDL.c
    src/game/gamelogic.c
    src/game/AI.c
    src/log/clog.c
    src/helperfuncs/structlogic.c
    src/helperfuncs/gridlogic.c
    src/helperfuncs/rendergame.c
    src/menu/menulogic.c
    src/menu/menurenderer.c
)

# Create executable and link against SDL2 and SDL_image
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/headers/clog
	${CMAKE_CURRENT_SOURCE_DIR}/src/headers/constants
	${CMAKE_CURRENT_SOURCE_DIR}/src/headers/gameheaders
	${CMAKE_CURRENT_SOURCE_DIR}/src/headers/helperfuncs
	${CMAKE_CURRENT_SOURCE_DIR}/src/headers/menuheaders
)

# Link against SDL2 and SDL_image libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    -lSDL2_image  # Add explicit linking for SDL_image
)

# Linking SDL_image after SDL2
set_property(TARGET ${PROJECT_NAME} PROPERTY
    COMPILE_OPTIONS -D_REENTRANT
)

