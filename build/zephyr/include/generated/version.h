#ifndef _KERNEL_VERSION_H_
#define _KERNEL_VERSION_H_

/* KERNEL and ZEPHYR_VERSION  values come from cmake/version.cmake
 * BUILD_VERSION  will be 'git describe', alternatively user defined BUILD_VERSION.
 */

#define ZEPHYR_VERSION_CODE 197120
#define ZEPHYR_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))

#define KERNELVERSION          0x3020000
#define KERNEL_VERSION_NUMBER  0x30200
#define KERNEL_VERSION_MAJOR   3
#define KERNEL_VERSION_MINOR   2
#define KERNEL_PATCHLEVEL      0
#define KERNEL_VERSION_STRING  "3.2.0-rc1"

#define BUILD_VERSION          

#endif /* _KERNEL_VERSION_H_ */
