#ifndef _KAMI_GAME_SETTINGS_H_
#define _KAMI_GAME_SETTINGS_H_

// Game Settings
int square_setting_counter = 3; // 0 -> 5
int screen_setting_counter = 1; // 0 -> 3
// Possible values: 9 16 25 36 49 64
int square_size = 36;
// Possible values: 1 2 4 8
int screen_x_scale = 2;
int screen_y_scale = 2;
int half_square = square_size / 2;
int parity = square_size % 2;
int board_x_offset = static_cast<int>(square_size * (kLeftSpace + (parity / 2)));
int board_y_offset = 0;
int screen_x_size = (square_size * kSquareX_Amount) + board_x_offset;
int screen_y_size = square_size * kSquareY_Amount;
int board_x_size = square_size * kSquareX_Amount;
int board_y_size = square_size * kSquareY_Amount;

#endif
