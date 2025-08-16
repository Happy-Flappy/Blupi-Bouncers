cmake_minimum_required(VERSION 3.31)

project("Blupi_Bouncers" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)





file(GLOB SOURCE_FILES *.cpp) # Gets all of the cpp files in the folder so that I don't have to list each one.






# <><><><><><><><><><><><><><><><> Find SFML and link it. <><><><><><><><><><><><><><><><><><><><>

# Provide a default search location

set(SFML_DIR "C:/SFML-2.6.0/lib/cmake/SFML")

# Search

find_package(SFML REQUIRED COMPONENTS graphics window system) 

# Link

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)




# <><><><><><><><><><><><><><><><> Force no Console <><><><><><><><><><><><><><><><><><><><><><><>

if(WIN32 AND MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()
