
# Project name
PROJECT = STK526-series2-hidio

# CPU architecture : {avr0|...|avr6}
# Parts : {at90usb646|at90usb647|at90usb1286|at90usb1287|at90usb162|at90usb82}
MCU = at90usb162

# Source files
CSRCS = \
  ../../../lib_mcu/wdt/wdt_drv.c\
  ../../../lib_mcu/power/power_drv.c\
  ../../../lib_mcu/util/start_boot.c\
  ../../../lib_mcu/usb/usb_drv.c\
  ../../../modules/scheduler/scheduler.c\
  ../../../modules/usb/device_chap9/usb_device_task.c\
  ../../../modules/usb/device_chap9/usb_standard_request.c\
  ../../../modules/usb/usb_task.c\
  ../hid_task.c\
  ../usb_descriptors.c\
  ../usb_specific_request.c\
  ../main.c\

# Assembler source files
ASSRCS = \

