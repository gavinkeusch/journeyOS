volatile unsigned char* video;

int next_text_pos;
int curr_line;

void screen_init();
void print(char*);
void println();
void printi(int);