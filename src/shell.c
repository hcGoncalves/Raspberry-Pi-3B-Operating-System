#include <shell.h>
#include <fb.h>
#include <utils.h>

static char shell_buffer[SHELL_BUFFER_SIZE][SHELL_BUFFER_WIDTH];
static int shell_buffer_index;
static int shell_buffer_line_index;

static int x,y;

void shell_draw(unsigned int redraw_window) {

    if (redraw_window) {
        drawRect(x,y, SHELL_BUFFER_WIDTH*8+16, SHELL_BUFFER_SIZE*10+32, 0x000000, 1);
        drawRect(x,y, SHELL_BUFFER_WIDTH*8+16, SHELL_BUFFER_SIZE*10+32, 0xFFFFFF, 0);
        drawLine(x,y+16, x+SHELL_BUFFER_WIDTH*8+16, y+16, 0xFFFFFF);
        drawString(x+8, y+5, "Shell", 0xFFFFFF);
    }

    int y_offset = 24;

    for (int i=0; i<SHELL_BUFFER_SIZE; i++) {
        if (shell_buffer[(shell_buffer_index+i) % SHELL_BUFFER_SIZE][0] == '\0') continue;
        drawRect(x+8, y+y_offset, SHELL_BUFFER_WIDTH*8, 10, 0x000000, 1);
        drawString(x+8, y+y_offset, shell_buffer[(shell_buffer_index+i) % SHELL_BUFFER_SIZE], 0xFFFFFF);
        y_offset += 10;
    }
}

void shell_flush(void) {
    shell_buffer_index = 0;
    shell_buffer_line_index = 0;

    for (int i = 0; i < SHELL_BUFFER_SIZE; i++) {
        shell_buffer[i][0] = '\0';
    }
}

void shell_init(int screen_x, int screen_y) {
    shell_flush();
    x = screen_x;
    y = screen_y;

    shell_draw(1);
}

void shell_new_line(void) {
    shell_buffer[shell_buffer_index][shell_buffer_line_index] = '\0';
    shell_buffer_index = (shell_buffer_index+1) % SHELL_BUFFER_SIZE;
    shell_buffer_line_index = 0;

    shell_draw(0);
}

void append_to_shell_buffer_ch(char c) {
    if (c == '\n') {
        shell_new_line();
    } else {
        shell_buffer[shell_buffer_index][shell_buffer_line_index] = c;
        shell_buffer_line_index++;

        if (shell_buffer_line_index >= SHELL_BUFFER_WIDTH-1) shell_new_line();
    }
}

void append_to_shell_buffer_str(const char *str) {
    while (*str) {
        append_to_shell_buffer_ch(*str);
        str++;
    }
}

void append_to_shell_buffer_int(int num) {
    char str[12];

    intToString(str, 12, num);

    append_to_shell_buffer_str(str);
}

void append_to_shell_buffer_hex(unsigned int num) {
    unsigned int a;
    int b;

    append_to_shell_buffer_str("0x");

    for(b=28; b >= 0; b -= 4) {
        a = (num >> b) & 0xF;
        
        a += a > 9 ? 0x37 : 0x30;
        
        append_to_shell_buffer_ch((char)a);
    }
}