#include "crt0.c"
#include "ChrFont0.h"

#define INIT    0
#define OPENING 1
#define PLAY    2
#define ENDING  3

int state = INIT;

struct ball {
    int pos_x;
    int pos_y;
    int direction;
};

struct player {
    int score;
    int racket_y_center;
    int rt_direction;
    int racket_hit;
    int racket_up;
    int racket_size;
};

struct ball ball;
struct player player1, player2;

void interrupt_handler() {
    static int cnt;

    if (state == INIT) {
        // Do nothing
        ball.pos_x = 32;
        ball.pos_y = 5;
        ball.direction = 0;
    } else if (state == OPENING) {
        cnt = 0;
    } else if (state == PLAY) {
        /* Display a ball */

        if (++cnt >= 24) {
            cnt = 0;
        }
    } else if (state == ENDING) {
        // Do nothing
    }

    lcd_sync_vbuf();
}

void main(){
    while (1) {
        if (state == INIT) {
            lcd_init();
            state = OPENING; 
        } else if (state == OPENING) {
            state = PLAY;
        } else if (state == PLAY) {
            play();
            state = ENDING;
        } else if (state == ENDING) {
            state = OPENING;
        }
    }
}

void update_ball_pos(){
    if(ball.direction == 0){
        ball.pos_x++;
        ball.pos_y++;
        if(ball.pos_x == 63){
            ball.direction = 2;
        }
    }else if(ball.direction == 1){
        ball.pos_x++;
    }else if(ball.direction == 2){
        ball.pos_x++;
        ball.pos_y--;
        if(ball.pos_x == 0){
            ball.direction = 1;
        }
    }else if(ball.direction == 3){
        ball.pos_x--;
        ball.pos_y++;
        if(ball.pos_x == 63){
            ball.direction = 1;
        }
    }else if(ball.direction == 4){
        ball.pos_x--;
    }else if(ball.direction == 5){
        ball.pos_x--;
        ball.pos_y--;
        if(ball.pos_x == 0){
            ball.direction = 3;
        }
    }
}


unsigned char lcd_vbuf[64][96];

void lcd_wait(int n) {
    for (int i = 0; i < n; i++);
}

void lcd_cmd(unsigned char cmd) {
    volatile int *lcd_ptr = (int *)0xff0c;
    *lcd_ptr = cmd;
    lcd_wait(1000);
}

void lcd_data(unsigned char data) {
    volatile int *lcd_ptr = (int *)0xff0c;
    *lcd_ptr = 0x100 | data;
    lcd_wait(200);
}

void lcd_pwr_on() {
    volatile int *lcd_ptr = (int *)0xff0c;
    *lcd_ptr = 0x200;
    lcd_wait(7000000);
}

void lcd_set_vbuf_pixel(int row, int col, int r, int g, int b) {
    r >>= 5; g >>= 5; b >>= 6;
    lcd_vbuf[row][col] = ((r << 5) | (g << 2) | (b << 0)) & 0xff;
}

void lcd_clear_vbuf() {
    for (int row = 0; row < 64; row++)
        for (int col = 0; col < 96; col++)
            lcd_vbuf[row][col] = 0;
}

void lcd_sync_vbuf() {
    for (int row = 0; row < 64; row++)
        for (int col = 0; col < 96; col++)
            lcd_data(lcd_vbuf[row][col]);
}

void lcd_putc(int y, int x, int c) {
    for (int v = 0; v < 8; v++)
        for (int h = 0; h < 8; h++)
            if ((font8x8[(c - 0x20) * 8 + h] >> v) & 0x01)
                lcd_set_vbuf_pixel(y * 8 + v, x * 8 + h, 0, 255, 0);
}

void lcd_puts(int y, int x, char *str) {
    for (int i = x; i < 12; i++)
        if (str[i] < 0x20 || str[i] > 0x7f)
            break;
        else
            lcd_putc(y, i, str[i]);
}
