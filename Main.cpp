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

	sprites add_sprites;

	Display display;

	MainGame main_logic;

	main_logic.main_menu(&display);
}


void MainGame::main_menu(Display *display) {
	menu_picture = al_load_bitmap("sprites/land3.png");

	control = &control_menu;

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

	while(true) {
		al_wait_for_event(event_queue, &event);

		if(event.type == ALLEGRO_EVENT_TIMER && event.timer.source == refresh_timer) {
			display->draw_bitmap(menu_picture, 0, 0);
		}

		if(refresh_timer) {
			//			al_flip_display();
		}

		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&mouse_state);
			if(al_mouse_button_down(&mouse_state, 1)) {

				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;

				if(mouse_x > 100 && mouse_x < 1500 && mouse_y > 100 && mouse_y < 350) {
					al_stop_timer(game_timer);
					al_stop_timer(refresh_timer);
					control_editor.determine_event(display);
					al_start_timer(game_timer);
					al_start_timer(refresh_timer);
				}
				else if(mouse_x > 100 && mouse_x < 1500 && mouse_y > 550 && mouse_y < 800) {
					al_stop_timer(game_timer);
					al_stop_timer(refresh_timer);
					control_game.determine_event(display);
					al_start_timer(game_timer);
					al_start_timer(refresh_timer);
				}
			}
		}
	}
}


void Control::determine_event(Display *display) {
	key_event();
	ALLEGRO_EVENT_QUEUE		*event_queue = al_create_event_queue();
	ALLEGRO_EVENT			event;

	ALLEGRO_TIMER       	*refresh_timer = al_create_timer(1.0/GAME_UPDATE);
	ALLEGRO_TIMER			*game_timer = al_create_timer(1.0/FPS);

	ALLEGRO_MOUSE_STATE		mouse_state;

	al_register_event_source(event_queue, al_get_timer_event_source(refresh_timer));
	al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	while(true) {
		al_wait_for_event(event_queue, &event);

		switch(event.type)
		{

		case ALLEGRO_EVENT_TIMER:

			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			break;

		case ALLEGRO_EVENT_KEY_UP:

			break;

		case ALLEGRO_EVENT_MOUSE_AXES:
			//			mouse_x = event.mouse.x;
			//			mouse_y = event.mouse.y;

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			//			game_running = false;

			break;

		default:
			break;
		}
	}
}


ControlMenu::~ControlMenu() {

}


void ControlEditor::key_event() {
	std::cout << "This" << std::endl;
}

void ControlEditor::mouse_event() {

}

ControlEditor::~ControlEditor() {

}


void ControlGame::key_event() {
	std::cout << "Test" << std::endl;
}

void ControlGame::mouse_event() {

}

ControlGame::~ControlGame() {

}

//
//
//void draw_display::camera_update(float* camera_position, float x, float y, float width, float height) {
//	camera_position[0] = -(SCREEN_WIDTH / 2) + (x + width / 2);
//	camera_position[1] = -(SCREEN_HEIGHT / 2) + (y + height / 2);
//
//	if(camera_position[0] < 0) {
//		camera_position[0] = 0;
//	}
//	else if(camera_position[0] > 1280) {
//		camera_position[0] = 1280;
//	}
//	if(camera_position[1] < 0) {
//		camera_position[1] = 0;
//	}
//	else if(camera_position[1] > 600) {
//		camera_position[1] = 600;
//	}
//}
//
//
//void main_logic::timer() {
//	if(ev.timer.source == refresh_timer) {
//		level_editor.draw_windows();
//
//		al_clear_to_color(al_map_rgb(0, 0, 0));
//
//		al_draw_bitmap(foreground, 0, 0, 0);
//
//		add_bullets.draw_to_screen();
//
//		add_item.draw_items();
//
//		load_level.draw_sprites(next);
//
//		char_move.draw_character(*display);
//
//		char_x = char_move.get_x();
//		char_y = char_move.get_y();
//
//		camera_update(camera_position, char_x, char_y, 20, 40);
//
//		al_identity_transform(&camera);
//		al_translate_transform(&camera, -camera_position[0], -camera_position[1]);		//Moves objects as the screen moves
//		al_use_transform(&camera);
//
//		al_draw_bitmap(cursor, mouse_x + camera_position[0], mouse_y + camera_position[1], 0);
//
//		al_flip_display();
//
//	} else if (ev.timer.source == game_timer && !paused){	//game_timer
//		add_bullets.calculate_movement();
//		char_move.calculate_movement();
//	}
//}
//
//
//void draw_display::key_down() {
//	if(ev.keyboard.keycode == ALLEGRO_KEY_W) {
//		char_move.set_direction(up);
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
//		char_move.set_direction(left);
//		left_pressed = true;
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
//		char_move.set_direction(right);
//		right_pressed = true;draw_display
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_R) {
//		if(basic) {
//			basic = false;
//		} else {
//			basic = true;
//		}
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_G) {
//		add_item.add_items(100, 100, 0);
//	}
//}
//
//
//void draw_display::key_up() {
//	if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
//		if(!paused) {
//			paused = true;
//		}
//		else {
//			paused = false;
//		}
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_W){
//		char_move.set_direction(stop_jump);
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_A){
//		left_pressed = false;
//		if(right_pressed) {
//			char_move.set_direction(right);
//		}
//		else {
//			char_move.set_direction(stop_x);
//		}
//	}
//	else if(ev.keyboard.keycode == ALLEGRO_KEY_D){
//		right_pressed = false;
//		if(left_pressed) {
//			char_move.set_direction(left);
//		}
//		else {
//			char_move.set_direction(stop_x);
//		}
//	}
//}
//
//
//void draw_display::mouse_down() {
//	if(!paused) {
//		char_x = char_move.get_x();
//		char_y = char_move.get_y();
//
//		mouse_x = ev.mouse.x;
//		mouse_y = ev.mouse.y;
//
//		al_get_mouse_state(&mouse_state);
//
//		if(al_mouse_button_down(&mouse_state, 1)) {
//			if(basic) {
//				add_bullets.add_basic(char_x, char_y, mouse_x + camera_position[0], mouse_y + camera_position[1]);
//			} else {
//				add_bullets.add_rocket(char_x, char_y, mouse_x + camera_position[0], mouse_y + camera_position[1]);
//			}
//		}
//		else if(al_mouse_button_down(&mouse_state, 2)) {
//			add_item.add_items(mouse_x + camera_position[0], mouse_y + camera_position[1], 0);
//			add_item.add_items(mouse_x + camera_position[0], mouse_y + camera_position[1], 0);
//		}
//	}
//}
//
//
//void main_logic::game_loop() {
//	refresh_timer = al_create_timer(1.0/FPS);
//	if(!refresh_timer) {
//		fprintf(stderr, "Failed to initialise refresh timer\n");
//	}
//
//	game_timer = al_create_timer(1.0/GAME_UPDATE);
//	if(!game_timer) {
//		fprintf(stderr, "Failed to initialise game timer\n");
//	}
//
//	event_queue = al_create_event_queue();
//	if(!event_queue) {
//		fprintf(stderr, "failed to create event_queue!\n");
//		al_destroy_timer(refresh_timer);
//	}
//
//
//	al_register_event_source(event_queue, al_get_timer_event_source(refresh_timer));
//	al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
//	al_register_event_source(event_queue, al_get_keyboard_event_source());
//	al_register_event_source(event_queue, al_get_mouse_event_source());
//
//	al_start_timer(refresh_timer);
//	al_start_timer(game_timer);
//
//
//	//Main game loop
//	while(game_running) {
//		al_wait_for_event(event_queue, &ev);
//
//		switch(ev.type)
//		{
//
//		case ALLEGRO_EVENT_TIMER:
//
//			break;
//
//		case ALLEGRO_EVENT_KEY_DOWN:
//
//			break;
//
//		case ALLEGRO_EVENT_KEY_UP:
//
//			break;
//
//		case ALLEGRO_EVENT_MOUSE_AXES:
//			mouse_x = ev.mouse.x;
//			mouse_y = ev.mouse.y;
//
//			break;
//
//		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
//
//			break;
//
//		case ALLEGRO_EVENT_DISPLAY_CLOSE:
//			game_running = false;
//
//			break;
//
//		default:
//			break;
//		}
//	}
//}
//
//
//draw_display::~draw_display() {
//	al_destroy_display(display);
//	al_destroy_bitmap(foreground);
//}