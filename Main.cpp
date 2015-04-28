#include "Main.h"

float FPS = 60.0;
float GAME_UPDATE = 500;
float SCREEN_WIDTH = 640.0;
float SCREEN_HEIGHT = 480.0;

int main() {
	if(!al_init()) {
		fprintf(stderr, "Failed to initialise Allegro\n");
		return -1;
	}

	if(!al_init_primitives_addon()) {
		fprintf(stderr, "Failed to initialise Allegro Primitives\n");
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "Failed to install image addon\n");
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "Failed to install keyboard\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to install mouse\n");
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	sprites add_sprites;

	Display display;

	MainGame main_logic;

	main_logic.main_menu(&display);
}


void MainGame::main_menu(Display *display) {
	menu_picture = al_load_bitmap("sprites/land5.png");

	refresh_timer = al_create_timer(1.0/FPS);
	if(!refresh_timer) {
		fprintf(stderr, "Failed to initialise refresh timer\n");
	}

	game_timer = al_create_timer(1.0/GAME_UPDATE);
	if(!game_timer) {
		fprintf(stderr, "Failed to initialise game timer\n");
	}

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_timer(refresh_timer);
	}

	al_register_event_source(event_queue, al_get_timer_event_source(refresh_timer));
	al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(game_timer);
	al_start_timer(refresh_timer);

	menu_font = al_load_font("fonts/LiberationMono-Bold.ttf", 48, 0);

	while(true) {
		al_wait_for_event(event_queue, &event);

		if(event.type == ALLEGRO_EVENT_TIMER && event.timer.source == refresh_timer) {
			display->draw_bitmap(menu_picture, 0, 0);
			display->set_default_display();
			al_draw_text(menu_font, al_map_rgb(255, 255, 255), 500, 200, 0, "Editor");
			al_draw_text(menu_font, al_map_rgb(255, 255, 255), 500, 650, 0, "Game");
			al_draw_text(menu_font, al_map_rgb(255, 255, 255), 1400, 850, 0, "Exit");
		}

		if(refresh_timer) {
			al_flip_display();
		}

		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&mouse_state);
			if(al_mouse_button_down(&mouse_state, 1)) {

				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;

				if(mouse_x > 100 && mouse_x < 1500 && mouse_y > 100 && mouse_y < 350) {
					al_stop_timer(game_timer);
					al_stop_timer(refresh_timer);
					al_unregister_event_source(event_queue, al_get_mouse_event_source());
					control_editor.determine_event(display);
					al_start_timer(game_timer);
					al_start_timer(refresh_timer);
					al_register_event_source(event_queue, al_get_mouse_event_source());
					display->set_default_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
				}
				else if(mouse_x > 100 && mouse_x < 1500 && mouse_y > 550 && mouse_y < 800) {
					al_stop_timer(game_timer);
					al_stop_timer(refresh_timer);
					al_unregister_event_source(event_queue, al_get_mouse_event_source());
					control_game.determine_event(display);
					al_start_timer(game_timer);
					al_start_timer(refresh_timer);
					al_register_event_source(event_queue, al_get_mouse_event_source());
				}
				else if(mouse_x > 1400 && mouse_y > 700) {
					break;
				}
			}
		}
	}
}


void Control::determine_event(Display *display) {
	event_queue = al_create_event_queue();

	refresh_timer = al_create_timer(1.0/GAME_UPDATE);
	game_timer = al_create_timer(1.0/FPS);

	mouse_x = 0;
	mouse_y = 0;

	al_register_event_source(event_queue, al_get_timer_event_source(refresh_timer));
	al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(refresh_timer);
	al_start_timer(game_timer);

	loop_running = true;
	paused = false;

	while(loop_running) {
		al_wait_for_event(event_queue, &event);

		switch(event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			if(event.timer.source == game_timer) {
				start(display);
			}
			else if(event.timer.source == refresh_timer) {
				al_flip_display();
			}

			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			key_event(&event);

			break;

		case ALLEGRO_EVENT_KEY_UP:
			key_release(&event);

			break;

		case ALLEGRO_EVENT_MOUSE_AXES:
			mouse_x = event.mouse.x;
			mouse_y = event.mouse.y;
			mouse_event("axis moved");

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			al_get_mouse_state(&mouse_state);

			if(al_mouse_button_down(&mouse_state, 1)) {
				mouse_event("left");
			}
			else if(al_mouse_button_down(&mouse_state, 2)) {
				mouse_event("right");
			}

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			al_get_mouse_state(&mouse_state);
			if(event.mouse.button == 1) {
				mouse_event("left release");
			}
			else if(event.mouse.button == 2) {
				mouse_event("right release");
			}

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			//			game_running = false;

			break;

		default:
			break;
		}
	}
	display->show_mouse_pointer();
}


void ControlEditor::start(Display *display) {
	level_editor.draw_windows(display);
	level_editor.set_mouse_pos_pointers(&mouse_x, &mouse_y);
}

void ControlEditor::key_event(ALLEGRO_EVENT *event) {
	level_editor.key_pressed(event);
}

void ControlEditor::key_release(ALLEGRO_EVENT *event) {
	level_editor.key_released(event);
}

void ControlEditor::mouse_event(std::string button) {
	if(button == "left") {
		if(mouse_x > 30 && mouse_x < 80 && mouse_y > 800 && mouse_y < 825) {
			loop_running = false;
		}
		else {
			level_editor.mouse_click("left");
		}
	}
	else if(button == "left release") {
		level_editor.mouse_release("left");
	}
	else if(button == "axis moved") {
		level_editor.move_main_window();
	}
}

void ControlEditor::exit_loop() {
	level_editor.exit_editor();
}

ControlEditor::~ControlEditor() {

}


void ControlGame::start(Display *display) {
	if(!paused) {
		game_screen.update_game();
	}
	game_screen.refresh_screen(display);
	game_screen.cursor_update(mouse_x, mouse_y, display);
}

void ControlGame::key_event(ALLEGRO_EVENT *event) {
	if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		if(!paused) {
			paused = true;
		}
		else if(paused) {
			paused = false;
		}
	}
	else if(event->keyboard.keycode == ALLEGRO_KEY_SPACE) {
		if(paused) {
			exit_loop();
		}
	}
	else {
		game_screen.key_down(event);
	}
}

void ControlGame::key_release(ALLEGRO_EVENT *event) {
	game_screen.key_up(event);
}

void ControlGame::mouse_event(std::string button) {
	if(button == "left") {
		game_screen.mouse_down(mouse_x, mouse_y, "left");
	}
}

void ControlGame::exit_loop() {
	loop_running = false;
}

ControlGame::~ControlGame() {

}

