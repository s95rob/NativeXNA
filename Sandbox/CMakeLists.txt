add_executable(NativeXNASandbox "Main.cpp")
target_link_libraries(NativeXNASandbox PRIVATE NativeXNA)

add_custom_command(TARGET NativeXNASandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        $<TARGET_FILE:NativeXNA>
        $<TARGET_FILE_DIR:NativeXNASandbox>
    COMMENT "Copying NativeXNA to NativeXNASandbox directory"
)