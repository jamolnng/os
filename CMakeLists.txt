cmake_minimum_required (VERSION 3.10)

set(program_name os)
set(CMAKE_BUILD_TYPE Debug)
set(arch i686)
set(target ${arch}-elf)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
project(${program_name} VERSION 0.0.0.1 LANGUAGES C CXX ASM NONE)

set(CMAKE_C_COMPILER $ENV{HOME}/opt/cross/bin/${target}-gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVERSION=\"${PROJECT_VERSION}\" -g -D__is_libk -ffreestanding -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -Werror -T ${PROJECT_SOURCE_DIR}/src/kernel/arch/${arch}/linker.ld")

set(CMAKE_CXX_COMPILER $ENV{HOME}/opt/cross/bin/${target}-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ASM_COMPILER $ENV{HOME}/opt/cross/bin/${target}-as)
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g")

file(GLOB_RECURSE LIBC_SOURCES "src/libc/*.c")
file(GLOB_RECURSE LIBC_HEADERS "src/libc/*.h")

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=crtbegin.o
    OUTPUT_VARIABLE crtbegin
)
string(REGEX REPLACE "\n$" "" crtbegin "${crtbegin}")
execute_process(COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=crtend.o
    OUTPUT_VARIABLE crtend
)
string(REGEX REPLACE "\n$" "" crtend "${crtend}")

file(GLOB_RECURSE KERNEL_SOURCES "src/kernel/*.c" "src/kernel/*.cpp" "src/kernel/*.asm")
file(GLOB_RECURSE KERNEL_HEADERS "src/kernel/*.h" "src/kernel/*.hpp")
get_filename_component(crti_path ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/arch/${arch}/crti.asm ABSOLUTE)
list(REMOVE_ITEM KERNEL_SOURCES "${crti_path}")
get_filename_component(crtn_path ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/arch/${arch}/crtn.asm ABSOLUTE)
list(REMOVE_ITEM KERNEL_SOURCES "${crtn_path}")

add_library(c ${LIBC_SOURCES} ${LIBC_HEADERS})
target_include_directories(c PUBLIC "src/libc/include" "src/kernel/include")

add_custom_target(crt ALL DEPENDS ${crti_path} ${crtn_path}
    COMMAND ${CMAKE_ASM_COMPILER} ${FLAGS} ${CMAKE_ASM_LINK_FLAGS} ${LINK_FLAGS} ${crti_path} -o ${CMAKE_BINARY_DIR}/crti.asm.o
    COMMAND ${CMAKE_ASM_COMPILER} ${FLAGS} ${CMAKE_ASM_LINK_FLAGS} ${LINK_FLAGS} ${crtn_path} -o ${CMAKE_BINARY_DIR}/crtn.asm.o
)

add_executable(kernel.bin ${KERNEL_SOURCES} ${KERNEL_HEADERS})
target_link_libraries(kernel.bin c gcc)
add_dependencies(kernel.bin crt)
target_include_directories(kernel.bin PUBLIC "src/libc/include" "src/kernel/include")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> ${CMAKE_BINARY_DIR}/crti.asm.o ${crtbegin} <OBJECTS> ${crtend} ${CMAKE_BINARY_DIR}/crtn.asm.o -o <TARGET> <LINK_LIBRARIES>")

add_custom_target(iso ALL mkdir -p $<TARGET_FILE_DIR:kernel.bin>/isodir/boot/grub
    COMMAND cp $<TARGET_FILE:kernel.bin> $<TARGET_FILE_DIR:kernel.bin>/isodir/boot/kernel.bin
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/scripts/grub.cfg $<TARGET_FILE_DIR:kernel.bin>/isodir/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o $<TARGET_FILE_DIR:kernel.bin>/${PROJECT_NAME}.iso $<TARGET_FILE_DIR:kernel.bin>/isodir
    DEPENDS $<TARGET_FILE:kernel.bin>
)

