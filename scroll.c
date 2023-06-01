#include <ncurses.h>
#include <string.h>

//#define TEXT_SIZE 1000
//#define WINDOW_HEIGHT 10
//#define WINDOW_WIDTH 50

int main() {
  char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed euismod, magna non aliquet lacinia, tellus dui bibendum tellus, vel lacinia nisl odio vel nisi. Sed euismod, magna non aliquet lacinia, tellus dui bibendum tellus, vel lacinia nisl odio vel nisi.Perferendis laborum laboriosam ut consequuntur autem. Blanditiis et architecto et voluptatem quod voluptatum aut. Est fugit iusto qui dolorem ullam laborum.Aut dignissimos et aliquid ea nihil explicabo aut quaerat. Voluptatum qui ab rerum animi ab unde minus. Dignissimos ab rerum quia cum.Autem numquam sequi sint eaque magnam perspiciatis harum expedita. Aliquam praesentium suscipit nostrum a. Mollitia ipsa sunt perferendis error reprehenderit.Exercitationem odit facere omnis. Dolor ea voluptatum distinctio repellendus. Laboriosam et debitis repudiandae vel sunt ducimus earum magni. Quibusdam voluptatem eveniet voluptas. Cum vitae ad perspiciatis harum impedit in debitis. Optio omnis rerum sunt est aut esse rerum. Quia officia id et voluptas sit aut.";
  
	int TEXT_SIZE = strlen(text), WINDOW_HEIGHT, WINDOW_WIDTH;
	getmaxyx(stdscr, WINDOW_HEIGHT, WINDOW_WIDTH);
	WINDOW_HEIGHT--; WINDOW_WIDTH--;

	initscr();
	noecho();
	keypad(stdscr, TRUE);

	WINDOW *win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);
	scrollok(win, TRUE);


	int pad_height = TEXT_SIZE / WINDOW_WIDTH + 1;
  
	int pad_width = WINDOW_WIDTH;

	WINDOW *pad = newpad(pad_height, pad_width);
  keypad(pad, TRUE);

  int y = 0, x = 0;
  for (int i = 0; i < TEXT_SIZE; i++) {
    if (x >= WINDOW_WIDTH) {
      x = 0;
      y++;
    }
    mvwaddch(pad, y, x, text[i]);
    x++;
  }

  int pad_y = 0, pad_x = 0;
  prefresh(pad, pad_y, pad_x, 0, 0, WINDOW_HEIGHT - 1, WINDOW_WIDTH - 1);

  int ch;
  while ((ch = getch()) != KEY_F(1)) {
    switch (ch) {
      case 'j':
        if (pad_y < pad_height - WINDOW_HEIGHT) {
          pad_y++;
          prefresh(pad, pad_y, pad_x, 0, 0, WINDOW_HEIGHT - 1, WINDOW_WIDTH - 1);
        }
        break;
      case 'k':
        if (pad_y > 0) {
          pad_y--;
          prefresh(pad, pad_y, pad_x, 0, 0, WINDOW_HEIGHT - 1, WINDOW_WIDTH - 1);
        }
        break;
    }
  }

  endwin();
  return 0;
}

