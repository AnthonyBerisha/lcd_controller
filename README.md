# lcd_controller
Some simple code interfacing an arduino uno and an 1602 lcd display.

So far you can:
  - initialize the display in 4-bit mode with ```void lcd_init(void)```
  - print a single char or a string on the display with ```void lcd_putc(const char c)``` | ```void lcd_puts(const char *s)```
  - the latter function manages the case if the string is longer than 16 bytes and add spaces so the rest of the string appears on the second line
  - set and reset the enable pin with ```void strobe(void)```
  - send any byte of data with ``` void send_byte(byte c) ```
  
I'm sure there are a lot of issues as I only briefly worked on this, but feel free if you have any suggestions.

---

## The schematics

In the folder you will find a file called lcd_controller.fzz, it can be opened using the free fritzing software [available here](https://fritzing.org/home/).

The red leds display the bits sent to RS / RW / E and the green display the bits sent to the data pins D4 - D7.
It makes visible what's going on with the display and it's easier to debug.

![alt text](https://github.com/AnthonyBerisha/lcd_controller/blob/master/lcd_controller_bb.png "breadboard")
