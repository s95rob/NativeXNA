file(GLOB_RECURSE NATIVEXNA_SRCS "src/*")
add_library(NativeXNA SHARED ${NATIVEXNA_SRCS})
target_include_directories(NativeXNA
PUBLIC
    "include"
PRIVATE
    "src"
)
target_compile_definitions(NativeXNA
PUBLIC
    $<$<CONFIG:Debug>:NATIVEXNA_DEBUG>

    $<$<BOOL:${WIN32}>:NATIVEXNA_PLATFORM_WIN32>
    $<$<BOOL:${LINUX}>:NATIVEXNA_PLATFORM_LINUX>
)