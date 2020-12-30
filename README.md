#SFUD Test

Simple test script to debug and fix SFUD problem on Wio Terminal.

I believe this code works now, the critical thing in the See code is the use of `sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 4);`
apprently should be `sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);`

I also cleaned up some of the code (uneccesary +0 and definining SERIAL in all uppper which overwrites an arduino.h definition)