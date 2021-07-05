
add_library(sdfx-hal-example-serial OBJECT)

target_sources(sdfx-hal-example-serial
    PRIVATE
        main.c
)

target_link_libraries(sdfx-hal-example-serial
    PRIVATE
        mbed-os
)
