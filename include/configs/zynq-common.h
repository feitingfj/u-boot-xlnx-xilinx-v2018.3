/*
 * (C) Copyright 2012 Michal Simek <monstr@monstr.eu>
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Common configuration options for all Zynq boards.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_COMMON_H
#define __CONFIG_ZYNQ_COMMON_H

/* CPU clock */
#ifndef CONFIG_CPU_FREQ_HZ
# define CONFIG_CPU_FREQ_HZ	800000000
#endif

/* Cache options */
#define CONFIG_SYS_L2CACHE_OFF
#ifndef CONFIG_SYS_L2CACHE_OFF
# define CONFIG_SYS_L2_PL310
# define CONFIG_SYS_PL310_BASE		0xf8f02000
#endif

#define ZYNQ_SCUTIMER_BASEADDR		0xF8F00600
#define CONFIG_SYS_TIMERBASE		ZYNQ_SCUTIMER_BASEADDR
#define CONFIG_SYS_TIMER_COUNTS_DOWN
#define CONFIG_SYS_TIMER_COUNTER	(CONFIG_SYS_TIMERBASE + 0x4)

/* Serial drivers */
/* The following table includes the supported baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE  \
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}

#define CONFIG_ARM_DCC

/* Ethernet driver */
#if defined(CONFIG_ZYNQ_GEM)
# define CONFIG_MII
# define CONFIG_SYS_FAULT_ECHO_LINK_DOWN
# define CONFIG_BOOTP_BOOTPATH
# define CONFIG_BOOTP_GATEWAY
# define CONFIG_BOOTP_HOSTNAME
# define CONFIG_BOOTP_MAY_FAIL
#endif

/* SPI */
#ifdef CONFIG_ZYNQ_SPI
#endif

/* QSPI */
#ifdef CONFIG_ZYNQ_QSPI
# define CONFIG_SF_DEFAULT_SPEED	30000000
#endif

/* NOR */
#ifdef CONFIG_MTD_NOR_FLASH
# define CONFIG_SYS_FLASH_BASE		0xE2000000
# define CONFIG_SYS_FLASH_SIZE		(16 * 1024 * 1024)
# define CONFIG_SYS_MAX_FLASH_BANKS	1
# define CONFIG_SYS_MAX_FLASH_SECT	512
# define CONFIG_SYS_FLASH_ERASE_TOUT	1000
# define CONFIG_SYS_FLASH_WRITE_TOUT	5000
# define CONFIG_FLASH_SHOW_PROGRESS	10
# define CONFIG_SYS_FLASH_CFI
# undef CONFIG_SYS_FLASH_EMPTY_INFO
# define CONFIG_FLASH_CFI_DRIVER
# undef CONFIG_SYS_FLASH_PROTECTION
# define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#endif

#ifdef CONFIG_NAND_ZYNQ
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_MTD_DEVICE
#endif

/* MMC */
#if defined(CONFIG_MMC_SDHCI_ZYNQ)
# define CONFIG_ZYNQ_SDHCI_MAX_FREQ	52000000
#endif

#ifdef CONFIG_USB_EHCI_ZYNQ
# define CONFIG_EHCI_IS_TDI

# define CONFIG_SYS_DFU_DATA_BUF_SIZE	0x600000
# define DFU_DEFAULT_POLL_TIMEOUT	300
# define CONFIG_USB_CABLE_CHECK
# define CONFIG_THOR_RESET_OFF
# define CONFIG_USB_FUNCTION_THOR
# define DFU_ALT_INFO_RAM \
	"dfu_ram_info=" \
	"set dfu_alt_info " \
	"${kernel_image} ram 0x3000000 0x500000\\\\;" \
	"${devicetree_image} ram 0x2A00000 0x20000\\\\;" \
	"${ramdisk_image} ram 0x2000000 0x600000\0" \
	"dfu_ram=run dfu_ram_info && dfu 0 ram 0\0" \
	"thor_ram=run dfu_ram_info && thordown 0 ram 0\0"

# if defined(CONFIG_MMC_SDHCI_ZYNQ)
#  define DFU_ALT_INFO_MMC \
	"dfu_mmc_info=" \
	"set dfu_alt_info " \
	"${kernel_image} fat 0 1\\\\;" \
	"${devicetree_image} fat 0 1\\\\;" \
	"${ramdisk_image} fat 0 1\0" \
	"dfu_mmc=run dfu_mmc_info && dfu 0 mmc 0\0" \
	"thor_mmc=run dfu_mmc_info && thordown 0 mmc 0\0"

#  define DFU_ALT_INFO	\
	DFU_ALT_INFO_RAM \
	DFU_ALT_INFO_MMC
# else
#  define DFU_ALT_INFO	\
	DFU_ALT_INFO_RAM
# endif
#endif

#if !defined(DFU_ALT_INFO)
# define DFU_ALT_INFO
#endif

#if defined(CONFIG_MMC_SDHCI_ZYNQ) || defined(CONFIG_ZYNQ_USB)
# define CONFIG_SUPPORT_VFAT
#endif

#if defined(CONFIG_ZYNQ_I2C0) || defined(CONFIG_ZYNQ_I2C1)
#define CONFIG_SYS_I2C_ZYNQ
#endif

/* I2C */
#if defined(CONFIG_SYS_I2C_ZYNQ)
# define CONFIG_SYS_I2C
# define CONFIG_SYS_I2C_ZYNQ_SPEED		100000
# define CONFIG_SYS_I2C_ZYNQ_SLAVE		0
#endif

/* EEPROM */
#ifdef CONFIG_ZYNQ_EEPROM
# define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
# define CONFIG_SYS_I2C_EEPROM_ADDR		0x54
# define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
# define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5
# define CONFIG_SYS_EEPROM_SIZE			1024 /* Bytes */
# define CONFIG_SYS_I2C_MUX_ADDR		0x74
# define CONFIG_SYS_I2C_MUX_EEPROM_SEL		0x4
#endif

/* Total Size of Environment Sector */
#ifdef CONFIG_ENV_IS_IN_EEPROM
# define CONFIG_ENV_SIZE			CONFIG_SYS_EEPROM_SIZE
# define CONFIG_EXTRA_ENV_SETTINGS
#else
# define CONFIG_ENV_SIZE			(128 << 10)
#endif

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Environment */
#ifndef CONFIG_ENV_IS_NOWHERE
# define CONFIG_ENV_SECT_SIZE		CONFIG_ENV_SIZE

/* cc108 requires to be 0xF00000 to have boot.bin with bitstream included */
# ifndef CONFIG_ENV_OFFSET
#  define CONFIG_ENV_OFFSET		0xE0000
# endif
#endif


#define CONFIG_IPADDR	192.168.31.100
#define CONFIG_SERVERIP	192.168.31.20

/* enable preboot to be loaded before CONFIG_BOOTDELAY */
#define CONFIG_PREBOOT

#define CONFIG_SYS_LOAD_ADDR		0 /* default? */

/* Distro boot enablement */

#ifdef CONFIG_SPL_BUILD
#define BOOTENV
#else
#include <config_distro_defaults.h>

#ifdef CONFIG_CMD_MMC
#define BOOT_TARGET_DEVICES_MMC(func) func(MMC, mmc, 0)
#else
#define BOOT_TARGET_DEVICES_MMC(func)
#endif

#ifdef CONFIG_CMD_USB
#define BOOT_TARGET_DEVICES_USB(func) func(USB, usb, 0)
#else
#define BOOT_TARGET_DEVICES_USB(func)
#endif

#if defined(CONFIG_CMD_PXE)
#define BOOT_TARGET_DEVICES_PXE(func) func(PXE, pxe, na)
#else
#define BOOT_TARGET_DEVICES_PXE(func)
#endif

#if defined(CONFIG_CMD_DHCP)
#define BOOT_TARGET_DEVICES_DHCP(func) func(DHCP, dhcp, na)
#else
#define BOOT_TARGET_DEVICES_DHCP(func)
#endif

#define BOOT_TARGET_DEVICES(func) \
	BOOT_TARGET_DEVICES_MMC(func) \
	BOOT_TARGET_DEVICES_USB(func) \
	BOOT_TARGET_DEVICES_PXE(func) \
	BOOT_TARGET_DEVICES_DHCP(func)

#include <config_distro_bootcmd.h>
#endif /* CONFIG_SPL_BUILD */

/* Default environment */
#ifndef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"ethaddr=00:0a:35:00:01:22\0"	\
	"kernel_image=zImage\0"	\
	"kernel_load_address=0x2080000\0" \
	"ramdisk_image=uramdisk.image.gz\0"	\
	"ramdisk_load_address=0x4000000\0"	\
	"devicetree_image=devicetree.dtb\0"	\
	"devicetree_load_address=0x2000000\0"	\
	"bitstream_image=system.bit\0"	\
	"bitstream_load_address=0x800000\0"	\
	"boot_image=BOOT.bin\0"	\
	"loadbit_addr=0x100000\0"	\
	"loadbit_size=0x400000\0"	\
	"kernel_addr=0x500000\0"	\
	"kernel_size=0x480000\0"	\
	"devicetree_addr=0x980000\0"	\
	"devicetree_size=0x10000\0"	\
	"ramdisk_addr=0x990000\0"	\
	"ramdisk_size=0x670000\0"	\
	"boot_addr=0x0\0"	\
	"boot_size=0xE0000\0"	\
	"fdt_high=0x20000000\0"	\
	"initrd_high=0x20000000\0"	\
	"bootenv=uEnv.txt\0" \
	"loadbootenv_addr=0x2000000\0" \
	"loadbootenv=load mmc 0 ${loadbootenv_addr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from SD ...; " \
		"env import -t ${loadbootenv_addr} $filesize\0" \
	"sd_uEnvtxt_existence_test=test -e mmc 0 /uEnv.txt\0" \
	"preboot=if test $modeboot = sdboot && env run sd_uEnvtxt_existence_test; " \
			"then if env run loadbootenv; " \
				"then env run importbootenv; " \
			"fi; " \
		"fi; \0" \
	"mmc_loadbit=echo Loading bitstream from SD/MMC/eMMC to RAM.. && " \
		"mmcinfo && " \
		"load mmc 0 ${loadbit_addr} ${bitstream_image} && " \
		"fpga load 0 ${loadbit_addr} ${filesize}\0" \
	"norboot=echo Copying Linux from NOR flash to RAM... && " \
		"cp.b 0xE2100000 ${kernel_load_address} ${kernel_size} && " \
		"cp.b 0xE2600000 ${devicetree_load_address} ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"cp.b 0xE2620000 ${ramdisk_load_address} ${ramdisk_size} && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"qspiboot=echo Copying Linux from QSPI flash to RAM... && "  \
		"sf probe 0 0 0 && "  \
		"echo  FPGA bitstream is loading ... ... && "  \
		"sf read ${bitstream_load_address} ${loadbit_addr} ${loadbit_size} && "  \
		"fpga loadb 0 ${bitstream_load_address} ${loadbit_size} && "  \
		"sf read ${kernel_load_address} ${kernel_addr} ${kernel_size} && "  \
		"sf read ${devicetree_load_address} ${devicetree_addr} ${devicetree_size} && "  \
		"echo Copying ramdisk... && "  \
		"sf read ${ramdisk_load_address} ${ramdisk_addr} ${ramdisk_size} && "  \
		"bootz ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0"  \
	"uenvboot=" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv}; " \
			"run importbootenv; " \
		"fi; " \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...; " \
			"run uenvcmd; " \
		"fi\0" \
	"sdboot=if mmcinfo; then " \
			"run uenvboot; " \
			"echo Copying Linux from SD to RAM... && " \
			"load mmc 0 ${kernel_load_address} ${kernel_image} && " \
			"load mmc 0 ${devicetree_load_address} ${devicetree_image} && " \
			"load mmc 0 ${ramdisk_load_address} ${ramdisk_image} && " \
			"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}; " \
		"fi\0" \
	"usbboot=if usb start; then " \
			"run uenvboot; " \
			"echo Copying Linux from USB to RAM... && " \
			"load usb 0 ${kernel_load_address} ${kernel_image} && " \
			"load usb 0 ${devicetree_load_address} ${devicetree_image} && " \
			"load usb 0 ${ramdisk_load_address} ${ramdisk_image} && " \
			"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}; " \
		"fi\0" \
	"nandboot=echo Copying Linux from NAND flash to RAM... && " \
		"nand read ${kernel_load_address} 0x100000 ${kernel_size} && " \
		"nand read ${devicetree_load_address} 0x600000 ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"nand read ${ramdisk_load_address} 0x620000 ${ramdisk_size} && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"jtagboot=echo TFTPing Linux to RAM... && " \
		"tftpboot ${kernel_load_address} ${kernel_image} && " \
		"tftpboot ${devicetree_load_address} ${devicetree_image} && " \
		"tftpboot ${ramdisk_load_address} ${ramdisk_image} && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"rsa_norboot=echo Copying Image from NOR flash to RAM... && " \
		"cp.b 0xE2100000 0x100000 ${boot_size} && " \
		"zynqrsa 0x100000 && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"rsa_nandboot=echo Copying Image from NAND flash to RAM... && " \
		"nand read 0x100000 0x0 ${boot_size} && " \
		"zynqrsa 0x100000 && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"rsa_qspiboot=echo Copying Image from QSPI flash to RAM... && " \
		"sf probe 0 0 0 && " \
		"sf read 0x100000 0x0 ${boot_size} && " \
		"zynqrsa 0x100000 && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"rsa_sdboot=echo Copying Image from SD to RAM... && " \
		"load mmc 0 0x100000 ${boot_image} && " \
		"zynqrsa 0x100000 && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"rsa_jtagboot=echo TFTPing Image to RAM... && " \
		"tftpboot 0x100000 ${boot_image} && " \
		"zynqrsa 0x100000 && " \
		"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
	"update_boot=echo update bootload ... && "  \
		"tftpboot 0x800000 ${boot_image} && "  \
		"sf probe 0 0 0 && "  \
		"sf erase ${boot_addr} ${boot_size} && "  \
		"sf write 0x800000 ${boot_addr} ${filesize} \0"  \
	"update_fpga_bit=echo update FPGA bitstream... && "  \
		"tftpboot 0x800000 ${bitstream_image} && "  \
		"sf probe 0 0 0 && "  \
		"sf erase ${loadbit_addr} ${loadbit_size} && "  \
		"sf write 0x800000 ${loadbit_addr} ${filesize} \0"  \
	"update_kernel=echo update linux kernel... && "  \
		"tftpboot 0x800000 ${kernel_image} && "  \
		"sf probe 0 0 0 && "  \
		"sf erase ${kernel_addr} ${kernel_size} && "  \
		"sf write 0x800000 ${kernel_addr} ${filesize}\0"  \
	"update_dtb=echo update devicetree.dtb... && "  \
		"tftpboot 0x800000 ${devicetree_image} && "  \
		"sf probe 0 0 0 && "  \
		"sf erase ${devicetree_addr} ${devicetree_size} && "  \
		"sf write 0x800000 ${devicetree_addr} ${filesize}\0"  \
	"update_system=echo update file system... && "  \
		"tftpboot 0x800000 ${ramdisk_image} && "  \
		"sf probe 0 0 0 && "  \
		"sf erase ${ramdisk_addr} ${ramdisk_size} && "  \
		"sf write 0x800000 ${ramdisk_addr} ${filesize}\0"  \
	"update_all=echo update fpga_bit ... linux kernel ... devicetree ... file system && "  \
		"run update_fpga_bit && "  \
		"run update_kernel && "  \
		"run update_dtb && "  \
		"run update_system && \0"  \
		DFU_ALT_INFO \
		BOOTENV
#endif

/* Miscellaneous configurable options */

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_LONGHELP
#define CONFIG_CLOCKS
#define CONFIG_SYS_MAXARGS		32 /* max number of command args */
#define CONFIG_SYS_CBSIZE		2048 /* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

#ifndef CONFIG_NR_DRAM_BANKS
# define CONFIG_NR_DRAM_BANKS		1
#endif

#define CONFIG_SYS_MEMTEST_START	0
#define CONFIG_SYS_MEMTEST_END		0x1000

#define CONFIG_SYS_INIT_RAM_ADDR	0xFFFF0000
#define CONFIG_SYS_INIT_RAM_SIZE	0x2000
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)

/* Enable the PL to be downloaded */
#define CONFIG_FPGA_ZYNQPL

/* FIT support */
#define CONFIG_IMAGE_FORMAT_LEGACY /* enable also legacy image format */

/* Extend size of kernel image for uncompression */
#define CONFIG_SYS_BOOTM_LEN	(60 * 1024 * 1024)

/* Boot FreeBSD/vxWorks from an ELF image */
#define CONFIG_SYS_MMC_MAX_DEVICE	1

#define CONFIG_SYS_LDSCRIPT  "arch/arm/mach-zynq/u-boot.lds"

#undef CONFIG_BOOTM_NETBSD

#define CONFIG_SYS_HZ			1000

/* For development/debugging */
#ifdef DEBUG
# define CONFIG_CMD_REGINFO
# define CONFIG_PANIC_HANG
#endif

/* SPL part */
#define CONFIG_SPL_FRAMEWORK

/* MMC support */
#ifdef CONFIG_MMC_SDHCI_ZYNQ
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION     1
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME     "u-boot.img"
#endif

/* Disable dcache for SPL just for sure */
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_DCACHE_OFF
#endif

/* Address in RAM where the parameters must be copied by SPL. */
#define CONFIG_SYS_SPL_ARGS_ADDR	0x10000000

#define CONFIG_SPL_FS_LOAD_ARGS_NAME		"system.dtb"
#define CONFIG_SPL_FS_LOAD_KERNEL_NAME		"uImage"

/* Not using MMC raw mode - just for compilation purpose */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR	0
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTORS	0
#define CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR	0

/* qspi mode is working fine */
#ifdef CONFIG_ZYNQ_QSPI
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x100000
#define CONFIG_SYS_SPI_ARGS_OFFS	0x200000
#define CONFIG_SYS_SPI_ARGS_SIZE	0x80000
#define CONFIG_SYS_SPI_KERNEL_OFFS	(CONFIG_SYS_SPI_ARGS_OFFS + \
					CONFIG_SYS_SPI_ARGS_SIZE)
#endif

/* for booting directly linux */

/* SP location before relocation, must use scratch RAM */
#define CONFIG_SPL_TEXT_BASE	0x0

/* 3 * 64kB blocks of OCM - one is on the top because of bootrom */
#define CONFIG_SPL_MAX_SIZE	0x30000

/* On the top of OCM space */
#define CONFIG_SYS_SPL_MALLOC_START	CONFIG_SPL_STACK_R_ADDR
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x2000000

/*
 * SPL stack position - and stack goes down
 * 0xfffffe00 is used for putting wfi loop.
 * Set it up as limit for now.
 */
#define CONFIG_SPL_STACK	0xfffffe00

/* BSS setup */
#define CONFIG_SPL_BSS_START_ADDR	0x100000
#define CONFIG_SPL_BSS_MAX_SIZE		0x100000

#define CONFIG_SYS_UBOOT_START	CONFIG_SYS_TEXT_BASE

#endif /* __CONFIG_ZYNQ_COMMON_H */
