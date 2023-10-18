#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "epaper.h"

#define SPIBB_NODE	DT_NODELABEL(spibb0)
const struct device *const dev = DEVICE_DT_GET(SPIBB_NODE);


void test_8bit_xfer()
{
    struct spi_config config;
   
    struct spi_cs_control cs_ctrl = (struct spi_cs_control){
		.gpio = GPIO_DT_SPEC_GET(SPIBB_NODE, cs_gpios),
		.delay = 0u,
	};

	config.frequency = 1000000;
	config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8);
	config.slave = 0;
	config.cs = &cs_ctrl;

	enum { datacount = 5 };
	uint8_t buff[datacount] = { 0x01, 0x02, 0x03, 0x04, 0x05};
	uint8_t rxdata[datacount];

	struct spi_buf tx_buf[1] = {
		{.buf = buff, .len = datacount},
	};
	struct spi_buf rx_buf[1] = {
		{.buf = rxdata, .len = datacount},
	};

	struct spi_buf_set tx_set = { .buffers = tx_buf, .count = 1 };
	struct spi_buf_set rx_set = { .buffers = rx_buf, .count = 1 };

	int ret = spi_transceive(dev, &config, &tx_set, &rx_set);

    Epaper_Write_Command(0x24); 

    for(int i = 0; i < 5; i++)
    {
        Epaper_Write_Data(rxdata[i]);

        if(rxdata[i] == 0xff)
            gpio_pin_set_dt(&LED0, 0);
        else
            gpio_pin_set_dt(&LED1, 0);

    }

    for(int i = 5; i < ALLSCREEN_GRAGHBYTES; i++)
    {               
        Epaper_Write_Data(0xff);
    }

    Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
    for(int i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
    {               
        Epaper_Write_Data(0x00);
    }

    EPD_Update();   
	// printf("8bit_loopback_partial; ret: %d\n", ret);
	// printf(" tx (i)  : %02x %02x %02x %02x %02x\n",
	//        buff[0], buff[1], buff[2], buff[3], buff[4]);
	// printf(" rx (i)  : %02x %02x %02x %02x %02x\n",
	//        rxdata[0], rxdata[1], rxdata[2], rxdata[3], rxdata[4]);
}



int main()
{
    //cleanDisplay();
    epaperSetup();

    // gpio_pin_set_dt(&LED2, 0);


    gpio_pin_set_dt(&EPEN, HIGH);

    EPD_HW_Init(); // Electronic paper initialization

    test_8bit_xfer();

    EPD_DeepSleep(); // Enter deep sleep,Sleep instruction is necessary, please do not delete!!!

    gpio_pin_set_dt(&EPEN, LOW);

}