set(APP_NAME "rodeo-env-sensor-example")

add_executable(${APP_NAME} app_main.c)

target_link_libraries(${APP_NAME} PRIVATE
    ${RodeoIot_LIBRARIES}
)

add_custom_command(
    TARGET ${APP_NAME}
    POST_BUILD
        COMMAND ${CMAKE_OBJCOPY}
        ARGS -O binary ${APP_NAME}.axf ${APP_NAME}.bin
 )

set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME "${APP_NAME}.axf")
