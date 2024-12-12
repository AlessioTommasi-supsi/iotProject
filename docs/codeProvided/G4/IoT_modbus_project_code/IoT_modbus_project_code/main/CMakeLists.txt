set(PROJECT_NAME "modbus_master")

idf_component_register(SRCS "modbus_master_params.c" "slave.c" "master.c" "display.c" "modbus_params_iot.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES "index.html" "connectme.html")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
