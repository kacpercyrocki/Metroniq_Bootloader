/*
 * MemManager.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Kacper
 */

#include "MemManager.h"
extern OSPI_HandleTypeDef hospi1;

extern Settings_t DeviceSettings;
uint8_t SaveSettingFlag = 0;
uint8_t SaveLogFlag = 0;


void WriteEnable(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	OSPI_AutoPollingTypeDef sConfig;
	/* Initialize the Write Enable cmd in single SPI mode */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = WRITE_ENABLE_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	/* Send Write Enable command in single SPI mode */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}

	/* Initialize Automatic-Polling mode to wait until WEL=1 */
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}

	/* Set the mask to 0x02 to mask all Status REG bits except WEL */ /* Set the match to 0x02 to check if the WEL bit is set */
	sConfig.Match = WRITE_ENABLE_MATCH_VALUE;
	sConfig.Mask = WRITE_ENABLE_MASK_VALUE;
	sConfig.MatchMode = HAL_OSPI_MATCH_MODE_AND;
	sConfig.Interval = AUTO_POLLING_INTERVAL;
	sConfig.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;

	/* Start Automatic-Polling mode to wait until WEL=1 */
	if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
}


/* This function Configures Software polling to wait until WEL=1 */
void PollingWEL(void)
{
	OSPI_AutoPollingTypeDef sConfig;
	OSPI_RegularCmdTypeDef sCommand;
	/* Initialize Indirect read mode for Software Polling to wait until WEL=1 */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Address = 0x0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	/* Set the mask to 0x02 to mask all Status REG bits except WEL */
	/* Set the match to 0x02 to check if the WEL bit is Set */
	sConfig.Match = WRITE_ENABLE_MATCH_VALUE;
	sConfig.Mask = WRITE_ENABLE_MASK_VALUE;
	sConfig.MatchMode = HAL_OSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Start Automatic-Polling mode to wait until the memory is ready WEL=1 */
	if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
}

/* This function Configures Automatic-polling mode to wait until WIP=0 */
void AutoPollingWIP(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	OSPI_AutoPollingTypeDef sConfig;
	/* Initialize Automatic-Polling mode to wait until WIP=0 */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;

	/* Set the mask to 0x01 to mask all Status REG bits except WIP */
	/* Set the match to 0x00 to check if the WIP bit is Reset */
	sConfig.Match = MEMORY_READY_MATCH_VALUE;
	sConfig.Mask = MEMORY_READY_MASK_VALUE;
	sConfig.MatchMode = HAL_OSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;

	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Start Automatic-Polling mode to wait until the memory is ready WIP=0 */
	if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
}

/* This function Configures Software polling mode to wait the memory is ready WIP=0 */
void PollingWIP(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	OSPI_AutoPollingTypeDef sConfig;
	/* Initialize Automatic-Polling mode to wait until WIP=0 */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Address = 0x0;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	/* Set the mask to 0x01 to mask all Status REG bits except WIP */
	/* Set the match to 0x00 to check if the WIP bit is Reset */
	sConfig.Match = MEMORY_READY_MATCH_VALUE;
	sConfig.Mask = MEMORY_READY_MASK_VALUE;
	sConfig.MatchMode = HAL_OSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Start Automatic-Polling mode to wait until the memory is ready WIP=0 */
	if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}

}

/*** This function configures the MX25LM51245G memory ***/
void DTR_MemoryCfg(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	uint8_t tmp[2];
	/* Enable writing to memory in order to set Dummy */
	WriteEnable();
	/* Initialize Indirect write mode to configure Dummy */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Instruction = WRITE_CFG_REG_2_CMD;
	sCommand.Address = CONFIG_REG2_ADDR3;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DataDtrMode= HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.NbData = 2;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Write Configuration register 2 with new dummy cycles */
	tmp[1] = 0x02;
	tmp[0] = 0x00;
	if (HAL_OSPI_Transmit(&hospi1, &tmp, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	AutoPollingWIP();
	/* Enable writing to memory in order to set Octal DTR mode */
	WriteEnable();
	/* Initialize OCTOSPI1 to Indirect write mode to configure Octal mode */
	sCommand.Instruction = 0x17;
	sCommand.Address = CONFIG_REG2_ADDR1;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_NONE;
	sCommand.NbData = 1;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Write Configuration register 2 with with Octal mode */
	tmp[0] = 0x80;
	if (HAL_OSPI_Transmit(&hospi1, &tmp, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}

}


/* This function erases the first memory sector */

void SectorErase(uint32_t Sector)
{
	OSPI_RegularCmdTypeDef sCommand;
	/* Initialize Indirect write mode to erase the first sector */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = SECTOR_ERASE_CMD;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_NONE;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address = Sector;// * 0x40000;

	/* Send Octal Sector erase cmd */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
}


void DTR_MemoryWrite(uint8_t * Buffer, uint32_t Size, uint32_t Address)
{
	OSPI_RegularCmdTypeDef sCommand;
	/* Initialize Indirect write mode for memory programming */
	sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.Instruction = 0x12;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.Address = Address;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.NbData = Size;
	sCommand.DummyCycles = 0;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_ONLY_FIRST_CMD;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	} /* Memory Page programming */
	if (HAL_OSPI_Transmit(&hospi1, Buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
	{
		Error_Handler();
	}
}

/* This function enables memory-mapped mode for Read and Write */
void EnableMemMapped(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	OSPI_MemoryMappedTypeDef sMemMappedCfg;
	/* Initialize memory-mapped mode for read operations */
	sCommand.OperationType = HAL_OSPI_OPTYPE_READ_CFG;
	sCommand.FlashId = HAL_OSPI_FLASH_ID_1;
	sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
	sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
	sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = HAL_OSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
	sCommand.Instruction = 0x13;
	sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
	sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;

	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}
	/* Initialize memory-mapped mode for write operations */
	sCommand.OperationType = HAL_OSPI_OPTYPE_WRITE_CFG;
	sCommand.Instruction = PAGE_PROG_CMD;
	sCommand.DummyCycles = 0;
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	} /* Configure the memory mapped mode with TimeoutCounter Disabled*/
	sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;
	if (HAL_OSPI_MemoryMapped(&hospi1, &sMemMappedCfg) != HAL_OK)
	{
		Error_Handler();
	}
}

uint8_t Memory_SaveWiFiCredentials(const char *ssid, const char *password)
{
    HAL_StatusTypeDef status;
    uint8_t ssid_len = strlen(ssid);
    uint8_t pass_len = strlen(password);

    // Bufor na dane użytkowe
    uint8_t data[256];
    uint32_t addr = 0x10UL;
    uint32_t data_len = 3 + ssid_len + pass_len;


    if (data_len > sizeof(data))
        return HAL_ERROR;

    if (memcmp((__IO uint8_t *)OCTOSPI1_BASE + 0x10, data, data_len) == 0)
    {
        // Dane są takie same → pomijamy zapis
        return 1;
    }

    memcpy(&data[0], (__IO uint8_t *)OCTOSPI1_BASE + 0x10, sizeof(data));


    // Format danych
    data[0] = 1;
    data[1] = ssid_len;
    data[2] = pass_len;
    memcpy(&data[3], ssid, ssid_len);
    memcpy(&data[3 + ssid_len], password, pass_len);

    HAL_OSPI_Abort(&hospi1);

    DTR_MemoryCfg();
    WriteEnable();
    PollingWEL();
    SectorErase(0);
    PollingWIP();
    WriteEnable();
    PollingWEL();
    DTR_MemoryWrite(data, sizeof(data), addr);

    EnableMemMapped();

    return HAL_OK;
}

void Memory_SaveSettings(void)
{
	uint8_t SettingsBuffer[1024];
	uint32_t addr = 0x00UL;

	SettingsBuffer[0] = 0xDE;
	memcpy(SettingsBuffer + 1, &DeviceSettings, sizeof(DeviceSettings));

    HAL_OSPI_Abort(&hospi1);

    DTR_MemoryCfg();
    WriteEnable();
    PollingWEL();
    SectorErase(0);
    PollingWIP();

    for(uint8_t i = 0; i < sizeof(SettingsBuffer) / 512; i++)
    {
        WriteEnable();
        PollingWEL();
        DTR_MemoryWrite(SettingsBuffer + i*512, 512, addr  + i*512);
        PollingWIP();
    }


    EnableMemMapped();
}

void Memory_ClearCurrentFW(void)
{
	HAL_OSPI_Abort(&hospi1);
	DTR_MemoryCfg();
	for(uint8_t i = 0; i < 4; i++)
	{

	    WriteEnable();
	    PollingWEL();
	    SectorErase(i + 1 + SECTOR_SIZE);
	    PollingWIP();
	}
	EnableMemMapped();
}

void Memory_SaveFW(uint8_t *data, uint32_t length, uint32_t address)
{
	HAL_OSPI_Abort(&hospi1);
	DTR_MemoryCfg();

    for(uint8_t i = 0; i <= length / 512; i++)
    {
        WriteEnable();
        PollingWEL();
        DTR_MemoryWrite(data + i*512, 512, address  + i*512);
        PollingWIP();
    }
    EnableMemMapped();
}



