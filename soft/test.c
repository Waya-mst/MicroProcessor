/* Do not remove the following line. Do not remove interrupt_handler(). */

#include "crt0.c"
#include "ChrFont0.h"

void show_ball();
void play();
int btn_check_0();
int btn_check_1();
int btn_check_3();
void led_set(int data);
void led_blink();
void lcd_init();
void lcd_putc(int y, int x, int c);
void lcd_sync_vbuf();
void lcd_clear_vbuf();
void update_window();
int is_hit1();
int is_hit2();
void update_racket_pos();
void update_ball_pos();
void lcd_set_vbuf_pixel(int, int, int, int, int);
void show_racket();
void game_init();
void pos_init(int);
void show_point();
int p1_rotate2direction(int);
int p2_rotate2direction(int);

#define INIT    0
#define OPENING 1
#define PLAY    2
#define ENDING  3
#define GAMEOVER 4

#define BALL_SPEED 5
#define P1_LIMIT 85
#define P2_LIMIT 10

struct ball {
    int pos_x;
    int pos_y;
    int direction;
    int ball_size; /* 奇数でハードコーディング */
};

struct player {
    int score;
    int racket_x_center;
    int rt_direction;
    int racket_hit;
    int racket_up;
    int racket_size;
    int racket_speed;
};

struct player player1, player2;
struct ball ball;

int state = INIT, pos = 0;

/* interrupt_handler() is called every 100msec */
// 画面の描画を行う(100msごとに呼ばれるので10fps)
void interrupt_handler() {
    if (state == INIT) {
        // Do nothing
    } else if (state == OPENING) {
    } else if (state == PLAY) {
        /* Display a ball */
        show_point();
        update_ball_pos();
        update_racket_pos();
        update_window();
    } else if (state == ENDING) {
        // Do nothing
    }

    lcd_sync_vbuf();
}

void main() {
    while (1) {
        if (state == INIT) {
            game_init();
            lcd_init();
            state = OPENING; 
        } else if (state == OPENING) {
            state = PLAY;
        } else if (state == PLAY) {
            play();
            state = ENDING;
        } 
        // else if (state == GAMEOVER) {
        //     for (int i = 0; i < 64; i++) {
        //         for (int j = 0; j < 96; j++) {
        //             lcd_set_vbuf_pixel(i, j, gameover[i][j], gameover[i][j], gameover[i][j]);
        //         }
        //     }
        //     lcd_sync_vbuf();
        // } 
        else if (state == ENDING) {
            state = INIT;
        }
    }
}

/* 栗原 */
void game_init() {
    ball.pos_x = 48;
    ball.pos_y = 48;
    ball.direction = 3;
    ball.ball_size = 5;
    player1.score = 5;
    player1.racket_x_center = 32;
    player1.rt_direction = 0;
    player1.racket_hit = 0;
    player1.racket_up = 1;
    player1.racket_size = 9; /* 奇数 */
    player1.racket_speed = 8;
    player2.score = 5;
    player2.racket_x_center = 32;
    player2.rt_direction = 3;
    player2.racket_hit = 0;
    player2.racket_up = 1;
    player2.racket_size = 9; /* 奇数 */
    player2.racket_speed = 8;
}

void pos_init(int player) {
    // 
    if (player == 1) {
        // ball.pos_y = 16;
        ball.pos_y = P1_LIMIT - 1;
        ball.direction = 0;
    } else if (player == 2) {
        // ball.pos_y = 16;
        ball.pos_y = P2_LIMIT + 1;
        ball.direction = 3;
    }
    ball.pos_x = 16;
} 

/* 栗原 */
void play() {
    while (1) {
        
        if (ball.pos_y - ball.ball_size / 2 <= P1_LIMIT && P1_LIMIT <= ball.pos_y + ball.ball_size / 2 && is_hit1()) {
            volatile int *rte_ptr = (int *)0xff10;
            int rotate_value = (*rte_ptr);
            rotate_value >>= 2;
            int direction = p1_rotate2direction(rotate_value);
            ball.direction = direction;
            /////////////
            volatile int *led_ptr = (int *)0xff08;
            *led_ptr = 1;
            /////////////
        } else if (ball.pos_y - ball.ball_size / 2 >= P1_LIMIT + 1) {
            player1.score--;
            //player2.score++; // 神の手
            if (player1.score <= 0) {
                /* ゲーム終了の処理 */
                return;
            }
            /* player2からサーブすることにする。 */
            pos_init(2);
            /////////////
            volatile int *led_ptr = (int *)0xff08;
            *led_ptr = 2;
            /////////////
        } 
        if (ball.pos_y - ball.ball_size / 2 <= P2_LIMIT && P2_LIMIT <= ball.pos_y + ball.ball_size / 2 && is_hit2()) {
            volatile int *rte_ptr = (int *)0xff14;
            int rotate_value = (*rte_ptr);
            rotate_value >>= 2;
            int direction = p2_rotate2direction(rotate_value);
            ball.direction = direction;
            /////////////
            volatile int *led_ptr = (int *)0xff08;
            *led_ptr = 4;
            /////////////
        } else if (ball.pos_y + ball.ball_size / 2 <= P2_LIMIT - 1) {
            player2.score--;
            //player2.score++;
            if (player2.score <= 0) {
                /* ゲーム終了の処理 */
                return;
            }
            /* player1からサーブすることにする。 */
            pos_init(1);
            /////////////
            volatile int *led_ptr = (int *)0xff08;
            *led_ptr = 8;
            /////////////
        }
    }
}

int p1_rotate2direction(int rotate_value){
    if(rotate_value <= 126){
        return 0;
    }else if(rotate_value >= 130){
        return 2;
    }else{
        return 1;
    }
}

int p2_rotate2direction(int rotate_value){
    if(rotate_value <= 126){
        return 3;
    }else if(rotate_value >= 130){
        return 5;
    }else{
        return 4;
    }
}

int is_hit1() {
    /*address of rte switch*/
    volatile int *rte_ptr = (int *)0xff10;
    struct player p;
    int is_push = (*rte_ptr) & 0x1;
    if (is_push
        && player1.racket_x_center - player1.racket_size / 2 - ball.ball_size / 2 <= ball.pos_x
        && ball.pos_x <= player1.racket_x_center + player1.racket_size / 2 + ball.ball_size / 2) {
        return 1;
    }
    else
        return 0;
}

int is_hit2() {
    /*address of rte switch*/
    volatile int *rte_ptr = (int *)0xff14;
    struct player p;
    int is_push = (*rte_ptr) & 0x1;
    if (is_push
        && player2.racket_x_center - player2.racket_size / 2 - ball.ball_size / 2 <= ball.pos_x
        && ball.pos_x <= player2.racket_x_center + player2.racket_size / 2 + ball.ball_size / 2){
            return 1;
        }
    else
        return 0;
}
/*
void show_ball(int pos) {
    lcd_clear_vbuf();
    lcd_putc(3, pos, '*');
}
*/
void update_window() {
    lcd_clear_vbuf();
    show_ball();
    show_racket();
}

void show_ball() {
    for (int i = -ball.ball_size / 2; i <= ball.ball_size / 2; i++) {
        for (int j = -ball.ball_size / 2; j <= ball.ball_size / 2; j++) {
            lcd_set_vbuf_pixel(ball.pos_x + i, ball.pos_y + j, 0, 255, 0);
        }
    }
}

void show_racket() {
    for (int i = -player1.racket_size / 2; i <= player1.racket_size / 2; i++) {
        for (int j = 0; j < 2; j++) {
            lcd_set_vbuf_pixel(player1.racket_x_center + i, P1_LIMIT + j, 0, 255, 0);
        }
    }

    for (int i = -player2.racket_size / 2; i <= player2.racket_size / 2; i++) {
        for (int j = 0; j < 2; j++) {
            lcd_set_vbuf_pixel(player2.racket_x_center + i, P2_LIMIT + j, 0, 255, 0);
        }
    }
}

void show_point() {
    volatile int *seg7_ptr = (int *)0xff18;
    *seg7_ptr = player1.score + player2.score * 10;
}

/* up and down */
void update_racket_pos() {
    volatile int *rte_ptr1 = (int *)0xff10;
    volatile int *rte_ptr2 = (int *)0xff14;

    int is_down1 = (*rte_ptr1) & 0x2;
    int is_down2 = (*rte_ptr2) & 0x2;
    is_down1 >>= 1;
    is_down1 = !(is_down1);
    is_down2 >>= 1;

    if (is_down1) {
        if (player1.racket_x_center + player1.racket_speed + player1.racket_size / 2 < 63) {
            player1.racket_x_center += player1.racket_speed;
        } else {
            player1.racket_x_center = 63 - player1.racket_size / 2;
        }
    } else {
        if (player1.racket_x_center - player1.racket_speed - player1.racket_size / 2 > 0) {
            player1.racket_x_center -= player1.racket_speed;
        } else {
            player1.racket_x_center = player1.racket_size / 2;
        }
    }
    if (is_down2) {
        if (player2.racket_x_center + player2.racket_speed + player2.racket_size / 2 < 63) {
            player2.racket_x_center += player2.racket_speed;
        } else {
            player2.racket_x_center = 63 - player2.racket_size / 2;
        }
    } else {
        if (player2.racket_x_center - player2.racket_speed - player2.racket_size / 2 > 0) {
            player2.racket_x_center -= player2.racket_speed;
        } else {
            player2.racket_x_center = player2.racket_size / 2;
        }
    }
}

// void update_ball_pos(){
//     if(ball.direction == 0){
//         if (ball.pos_x + 5 + ball.ball_size / 2 > 63){
//             ball.pos_x = 63 - ball.ball_size / 2;
//             ball.direction = 2;
//             return;
//         }else{
//             ball.pos_x += 5;
//             ball.pos_y -= 5;
//         }
//     }else if(ball.direction == 1){
//         ball.pos_y -= 5;
//     }else if(ball.direction == 2){
//         if (ball.pos_x - 5 - ball.ball_size / 2 < 0){
//             ball.pos_x = ball.ball_size / 2;
//             ball.direction = 0;
//             return;
//         }else{
//             ball.pos_x -= 5;
//             ball.pos_y -= 5;
//         }

//     }else if(ball.direction == 3){
//         if (ball.pos_x + 5 + ball.ball_size / 2 > 63){
//             ball.pos_x = 63 - ball.ball_size / 2;
//             ball.direction = 5;
//             return;
//         }else{
//             ball.pos_x += 5;
//             ball.pos_y += 5;
//         }
//     }else if(ball.direction == 4){
//         ball.pos_y += 5;
//     }else if(ball.direction == 5){
//         if (ball.pos_x - 5 - ball.ball_size / 2 < 0){
//             ball.pos_x = ball.ball_size / 2;
//             ball.direction = 3;
//             return;
//         }else{
//             ball.pos_x -= 5;
//             ball.pos_y += 5;
//         }
//     }
//     return;
// }

void update_ball_pos()
{
    if (ball.direction == 0)
    {
        ball.pos_x += BALL_SPEED;
        ball.pos_y -= BALL_SPEED;
        if (ball.pos_x + ball.ball_size / 2 > 63)
        {
            ball.pos_x = 63 - ball.ball_size / 2;
            ball.direction = 2;
        }
        if (ball.pos_y - ball.ball_size / 2 < 0)
        {
            ball.pos_y = P2_LIMIT + ball.ball_size / 2;
        }
    }
    else if (ball.direction == 1)
    {
        ball.pos_y -= BALL_SPEED;
        if (ball.pos_y - ball.ball_size / 2 < 0)
        {
            ball.pos_y = P2_LIMIT + ball.ball_size / 2;
            ball.direction = 3;
        }
    }
    else if (ball.direction == 2)
    {
        ball.pos_x -= BALL_SPEED;
        ball.pos_y -= BALL_SPEED;
        if (ball.pos_x - ball.ball_size / 2 < 0)
        {
            ball.pos_x = ball.ball_size / 2;
            ball.direction = 0;
        }
        if (ball.pos_y - ball.ball_size / 2 < 0)
        {
            ball.pos_y = P2_LIMIT + ball.ball_size / 2;
        }
    }
    else if (ball.direction == 3)
    {
        ball.pos_x += BALL_SPEED;
        ball.pos_y += BALL_SPEED;
        if (ball.pos_x + ball.ball_size / 2 > 63)
        {
            ball.pos_x = 63 - ball.ball_size / 2;
            ball.direction = 5;
        }
        if(ball.pos_y + ball.ball_size / 2 > 95){
            ball.pos_y = P1_LIMIT - ball.ball_size / 2;
        }

    }
    else if (ball.direction == 4)
    {
        ball.pos_y += BALL_SPEED;
        if(ball.pos_y + ball.ball_size / 2 > 95){
            ball.pos_y = P1_LIMIT - ball.ball_size / 2;
        }
    }
    else if (ball.direction == BALL_SPEED)
    {
        ball.pos_x -= BALL_SPEED;
        ball.pos_y += BALL_SPEED;
        if (ball.pos_x - ball.ball_size / 2 < 0)
        {
            ball.pos_x = ball.ball_size / 2;
            ball.direction = 3;
        }
        if(ball.pos_y + ball.ball_size / 2 > 95){
            ball.pos_y = P1_LIMIT - ball.ball_size / 2;
        }
    }
}

/*
 * Switch functions
 */
int btn_check_0() {
    volatile int *sw_ptr = (int *)0xff04;
    return (*sw_ptr & 0x10) ? 1 : 0;
}

int btn_check_1() {
    volatile int *sw_ptr = (int *)0xff04;
    return (*sw_ptr & 0x20) ? 1 : 0;
}

int btn_check_3() {
    volatile int *sw_ptr = (int *)0xff04;
    return (*sw_ptr & 0x80) ? 1 : 0;
}

/*
 * LED functions
 */
void led_set(int data) {
    volatile int *led_ptr = (int *)0xff08;
    *led_ptr = data;
}

void led_blink() {
    led_set(0xf);                /* Turn on */
    for (int i = 0; i < 300000; i++);    /* Wait */
    led_set(0x0);                /* Turn off */
    for (int i = 0; i < 300000; i++);    /* Wait */
    led_set(0xf);                /* Turn on */
    for (int i = 0; i < 300000; i++);    /* Wait */
    led_set(0x0);                /* Turn off */
}

/*
 * LCD functions
 */
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

void lcd_init() {
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

