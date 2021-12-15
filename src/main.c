/* Dariusz Sabala, 2021, MIT License, https://github.com/dsabala */

#include "hd44780.h"
#include "bsp_lcd.h"
#include "stm32f4xx_hal.h"

int main(void) {
  HAL_Init();

  /* Remember to wait 15ms after power up */
  HAL_Delay(15);

  hd44780_hdl * lcd_hdl = hd44780_get_handle();

  hd44780_init(lcd_hdl);

  static uint8_t const alarm_icon_index = 0U;
  static uint8_t const alarm_icon[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x0E, 0x1F, 0x04, 0x00};
  hd44780_def_char(lcd_hdl, alarm_icon_index, alarm_icon);

  hd44780_clear(lcd_hdl);
  hd44780_set_pos(lcd_hdl, 0, 0);
  hd44780_write_text(lcd_hdl, "github.com/dsabala");

  hd44780_set_pos(lcd_hdl, 1, 0);
  hd44780_write_text(lcd_hdl, "dependency free,");

  hd44780_set_pos(lcd_hdl, 2, 0);
  hd44780_write_text(lcd_hdl, "multi-instantaneous,");

  hd44780_set_pos(lcd_hdl, 3, 0);
  hd44780_write_text(lcd_hdl, "HD44780 LCD driver");

  hd44780_disp_char(lcd_hdl, alarm_icon_index);

  HAL_Delay(2000);

  hd44780_cursor_cfg(lcd_hdl, CURSOR_BLINK);

  while (1) {
    /* intentionally do nothing */
  }
}

/* Own systick implementation due to HAL delivered delay function usage */
void SysTick_Handler(void);
void SysTick_Handler(void)
{
  HAL_IncTick();
}
