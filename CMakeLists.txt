cmake_minimum_required (VERSION 3.8)

project ("Weather_app")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)


include(FetchContent)

FetchContent_Declare(sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 5383d2b3948f805af55c9f8a4587ac72ec5981d1
)
FetchContent_Declare(tgui
    GIT_REPOSITORY https://github.com/texus/TGUI.git
    GIT_TAG 6d76a435fb649e0dc597c320a29d7f00f2525f32
)
FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 2b2b16989708d81d4fe062240e085a2f5a61f74a
)
FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json sfml cpr tgui)
add_definitions(-DSFML_STATIC)
#compileaza sursele cpp
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable (${PROJECT_NAME} ${MY_SOURCES})

#compileaza headerele
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics cpr::cpr nlohmann_json::nlohmann_json TGUI::TGUI)


