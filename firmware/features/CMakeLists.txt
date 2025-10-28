# firmware/features/CMakeLists.txt
# Drop-in replacement to make Pico SDK headers available while compiling this static lib.

add_library(pico_synth_features STATIC
    features.c
    feature_midi_monitor.c
)

# Public headers (consumed by main app and other libs)
target_include_directories(pico_synth_features PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../tui/include
    ${CMAKE_CURRENT_LIST_DIR}/../midi/include
)

# Make Pico SDK headers visible to this target's own compilation
target_include_directories(pico_synth_features PRIVATE
    ${PICO_SDK_PATH}/src/common/pico_stdlib/include
    ${PICO_SDK_PATH}/src/boards/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_platform/include
    ${PICO_SDK_PATH}/src/rp2040/hardware_regs/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_base/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_sync/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include
    ${PICO_SDK_PATH}/src/common/pico_sync/include
    ${PICO_SDK_PATH}/src/common/pico_time/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_timer/include
    ${PICO_SDK_PATH}/src/common/pico_util/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_uart/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_resets/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_clocks/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_pll/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_vreg/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_watchdog/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_xosc/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_divider/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_runtime/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_printf/include
    ${PICO_SDK_PATH}/src/common/pico_bit_ops/include
    ${PICO_SDK_PATH}/src/common/pico_divider/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_double/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_float/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_malloc/include
    ${PICO_SDK_PATH}/src/rp2_common/boot_stage2/include
    ${PICO_SDK_PATH}/src/common/pico_binary_info/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_stdio/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_stdio_uart/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_unique_id/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_flash/include
    ${PICO_SDK_PATH}/lib/tinyusb/src
    ${PICO_SDK_PATH}/lib/tinyusb/src/common
    ${PICO_SDK_PATH}/lib/tinyusb/hw
    ${CMAKE_BINARY_DIR}/generated/pico_base
)

# Link against stdlib (no TUI sources here; main target already links pico_synth_tui)
target_link_libraries(pico_synth_features PUBLIC
    pico_stdlib
)
