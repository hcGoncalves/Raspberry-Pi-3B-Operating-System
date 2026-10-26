#define SHELL_BUFFER_SIZE 64
#define SHELL_BUFFER_WIDTH 128

void shell_flush(void);
void shell_init(int screen_x, int screen_y);

void append_to_shell_buffer_ch(char c);
void append_to_shell_buffer_str(const char *str);
void append_to_shell_buffer_int(int num);
void append_to_shell_buffer_hex(unsigned int num);