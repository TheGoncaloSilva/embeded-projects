# Source code or cpp files
set(SOURCES ./Src/main.cpp)

idf_component_register(SRCS ${SOURCES} 
                        INCLUDE_DIRS . Include ""
                        REQUIRES freertos esp_common)