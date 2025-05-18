# ESP-IDF CMake configuration for main component
idf_component_register(SRCS "main.cpp"
                      INCLUDE_DIRS "."
                      REQUIRES esp_timer freertos)
