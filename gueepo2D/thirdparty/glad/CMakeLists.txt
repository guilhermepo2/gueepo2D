project(glad)

add_library(${PROJECT_NAME}
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

include_directories(include)