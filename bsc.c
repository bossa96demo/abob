#include <ncurses.h>
#include <string.h>

int main() {
  char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed euismod, magna non aliquet lacinia, tellus dui bibendum tellus, vel lacinia nisl odio vel nisi. Sed euismod, magna non aliquet lacinia, tellus dui bibendum tellus, vel lacinia nisl odio vel nisi.Perferendis laborum laboriosam ut consequuntur autem. Blanditiis et architecto et voluptatem quod voluptatum aut. Est fugit iusto qui dolorem ullam laborum.Aut dignissimos et aliquid ea nihil explicabo aut quaerat. Voluptatum qui ab rerum animi ab unde minus. Dignissimos ab rerum quia cum.Autem numquam sequi sint eaque magnam perspiciatis harum expedita. Aliquam praesentium suscipit nostrum a. Mollitia ipsa sunt perferendis error reprehenderit.Exercitationem odit facere omnis. Dolor ea voluptatum distinctio repellendus. Laboriosam et debitis repudiandae vel sunt ducimus earum magni. Quibusdam voluptatem eveniet voluptas. Cum vitae ad perspiciatis harum impedit in debitis. Optio omnis rerum sunt est aut esse rerum. Quia officia id et voluptas sit aut.";

	scrollok(stdscr, TRUE);
	int sl = 0;
	for(;;){
		addstr(text);
		refresh();
		switch(getch()){
			case 'j':
				sl++;
				break;
			case 'k':
				sl--;
				break;
			default:
				break;
		}
		scrl(sl);
		refresh();
	}

	endwin();
	return 0;
}
