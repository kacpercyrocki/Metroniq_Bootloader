/*
 * MemManager.h
 *
 *  Created on: Nov 21, 2025
 *      Author: Kacper
 */

#ifndef INC_MEMMANAGER_H_
#define INC_MEMMANAGER_H_

#include "main.h"
#include "octospi.h"

/* MX25LM512ABA1G12 Macronix memory */ /* Flash commands */
#define OCTAL_IO_DTR_READ_CMD     	0xEE11
#define OCTAL_IO_READ_CMD         	0xEC13
#define OCTAL_PAGE_PROG_CMD        	0x12ED
#define OCTAL_READ_STATUS_REG_CMD 	0x05FA
#define OCTAL_SECTOR_ERASE_CMD      0x21DE
#define OCTAL_WRITE_ENABLE_CMD      0x06F9
#define READ_STATUS_REG_CMD        	0x05
#define WRITE_CFG_REG_2_CMD         0x01
#define WRITE_ENABLE_CMD            0x06
#define SECTOR_ERASE_CMD      		0x20
#define PAGE_PROG_CMD        	    0x38
#define IO_READ_CMD         	    0x6B
#define READ_STATUS_REG_CMD 	    0x05
/* Dummy clocks cycles */
#define DUMMY_CLOCK_CYCLES_READ          6
#define DUMMY_CLOCK_CYCLES_READ_REG 	 4
/* Auto-polling values */
#define WRITE_ENABLE_MATCH_VALUE         0x02
#define WRITE_ENABLE_MASK_VALUE          0x02
#define MEMORY_READY_MATCH_VALUE   	     0x00
#define MEMORY_READY_MASK_VALUE          0x01
#define AUTO_POLLING_INTERVAL            0x10
/* Memory registers address */
#define CONFIG_REG2_ADDR1                0x0000000
#define CR2_STR_OPI_ENABLE               0x01
#define CR2_DTR_OPI_ENABLE               0x02
#define CONFIG_REG2_ADDR3                0x300
#define CR2_DUMMY_CYCLES_66MHZ           0x07

#define SECTOR_SIZE						 0x1000  // 256KB
#define MEMORY_SIZE					     0x20000000 // 64MB
#define SECTOR_COUNT					 MEMORY_SIZE / SECTOR_SIZE // 2048 sectors

#define S25FL512S_FLASH_SIZE                            0x4000000 /* 512 MBits => 64MBytes */
#define S25FL512S_SECTOR_SIZE                           0x1000   /* 256 sectors of 256KBytes */
#define S25FL512S_PAGE_SIZE                             0x100     /* 131072 pages of 512 bytes */

#define SETTINGS_SECTOR_ADDR	0

#define FW_START_ADDR 0x40000
#define FW_MAX_SIZE   (0x40000 * 4)
#define CHUNK_SIZE    1024

#define DAY_LOG_SECTOR_ADDR S25FL512S_SECTOR_SIZE * 6 * 64
#define DAY_LOG_SECTOR_COUNT	2 * 64

#define MONTH_LOG_SECTOR_ADDR S25FL512S_SECTOR_SIZE * 8 * 64
#define MONTH_LOG_SECTOR_COUNT	24 * 64

#define PARAMTERS_SECTOR_NO				 0
#define PARAMTERS_SECTORS_COUNT		     1 * 64

#define WEBGUI_SECTOR_NO				 1 * 64
#define WEBGUI_SECTOR_COUNT			     8 * 64

#define LOGS_SECTOR_NO				     9 * 64
#define LOGS_SECTOR_COUNT				 SECTOR_COUNT - WEBGUI_SECTOR_COUNT - PARAMTERS_SECTORS_COUNT

#define LOG_SIZE						132

/* Exported macro ------------------------------------------------------*/
#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__)/sizeof(*(__BUFFER__)))
/* Size of buffers */
#define BUFFERSIZE (COUNTOF(aTxBuffer) - 1)

void WriteEnable(void);
void DTR_MemoryCfg(void);
void SectorErase(uint32_t Sector);
void DTR_MemoryWrite(uint8_t * Buffer, uint32_t Size, uint32_t Address);
void AutoPollingWIP(void);
void PollingWEL(void);
void PollingWIP(void);
void EnableMemMapped(void);
void Memory_SaveSettings(void);
void Memory_ClearCurrentFW(void);
void SaveSettingFlagSet(void);
void SaveLogFlagSet(void);
void Memory_SaveFW(uint8_t *data, uint32_t length, uint32_t address);

uint8_t Memory_SaveWiFiCredentials(const char *ssid, const char *password);
uint8_t Memory_ReadWiFiCredentials(uint8_t *ssid, uint8_t *password);
void MemoryMemHandler(void);


#endif /* INC_MEMMANAGER_H_ */
