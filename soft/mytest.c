/* Do not remove the following line. Do not remove interrupt_handler(). */
#include "crt0.c"

/* interrupt_handler() is called every 100msec */
unsigned char lcd_vbuf[64][96];

void lcd_wait(int n){
    for(int i = 0; i < n; i++);
}

void lcd_cmd(unsigned char cmd){
    volatile int *lcd_ptr = (unsigned char *)0xff0c;
    *lcd_ptr = cmd;
    lcd_wait(1000);
}

void lcd_data(unsigned char data){
    volatile int *lcd_ptr = (unsigned char *)0xff0c;
    *lcd_ptr = data | 0x100;
    lcd_wait(200);
}

void lcd_pwr_on(){
    volatile int *lcd_ptr = (unsigned char *)0xff0c;
    *lcd_ptr = 0x1000;
    lcd_wait(700000);
}

void lcd_clear_vbuf() {
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 96; j++)
            lcd_vbuf[i][j] = 0;
}

void lcd_set_vbuf_pixel(int row, int col, int r, int g, int b){
    r >>= 5; g >>= 5; b >>= 6;
    lcd_vbuf[row][col] = ((r << 5) | (g << 2) | (b << 0)) & 0xff; 
}

void lcd_sync_vbuf(){
    for(int row = 0; row < 64; row++){
        for(int col = 0; col < 96; col++){
            lcd_data(lcd_vbuf[row][col]);
        }
    }
}

void interrupt_handler() {
	static int cnt = 0;
    volatile int *sw_ptr = (int *)0xff04;
	volatile int *led_ptr = (int *)0xff08;
    volatile int *lcd_ptr = (int *)0xff0c;
    *led_ptr = *sw_ptr;
    lcd_clear_vbuf();
    if(*sw_ptr = 1){
        for(int i; i < 64; i++){
            for(int j; j < 96; j++){
                lcd_set_vbuf_pixel(i, j, 256, 0, 0);
                lcd_sync_vbuf();
            }
        }
    }else if (*sw_ptr = 2){
        for(int i; i < 64; i++){
            for(int j; j < 96; j++){
                lcd_set_vbuf_pixel(i, j, 0, 256, 0);
                lcd_sync_vbuf();
            }
        }
    }else if (*sw_ptr = 3){
        for(int i; i < 64; i++){
            for(int j; j < 96; j++){
                lcd_set_vbuf_pixel(i, j, 0, 0, 256);
                lcd_sync_vbuf();
            }
        }
    }
}

void main() {
    lcd_pwr_on();
    lcd_cmd(0xa0);
    lcd_cmd(0x20);
    lcd_cmd(0x15);
    lcd_cmd(0);
    lcd_cmd(95);
    lcd_cmd(0x75);
    lcd_cmd(0);
    lcd_cmd(63);
    lcd_cmd(0xaf);
	for (;;);
}
