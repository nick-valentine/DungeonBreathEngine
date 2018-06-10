add_subdirectory (lua)
add_subdirectory (ui)
add_subdirectory (render)
add_subdirectory (scene)
add_subdirectory (core)
add_subdirectory (play)

SET (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicManager.cpp
    PARENT_SCOPE
)
