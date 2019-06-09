#pragma once

#pragma region time
#define MS_PER_UPDATE					2.0f
#define MS_PER_RENDER					50.0f
#define MS_PER_ANIM						50.0f
#pragma endregion time

#pragma region window_size
#define WINDOW_HEIGHT					1000
#define WINDOW_WIDTH					1500
#pragma endregion window_size

#pragma region map_initializing_constant
#define MAX_INDIVIDUALS					40
#define MAX_ELEMENTS					0
#pragma endregion map_initializing_constant

#pragma region individualsprite

#define WEAK_SPRITE_SIZE				16
#define STRONG_SPRITE_SIZE				16
#define GROUP_SUB_RANGE					60
#define GROUP_LEAD_RANGE				80

#pragma endregion individual_sprite

#pragma region movement_constant
#define DISTANCE_RUN_SUBORDINATE		1.0f
#define DISTANCE_RUN_LEADER				1.0f
#define DIST_BETWEEN_INDIVIDUAL			16*5
#define DIST_TO_ELEMENTS				50
#define PI								3.14159265358979323846f
#define MAX_TURN						180

#define MAX_RUN_ATTRACTION				2.0f
#define MAX_POWER						3.0f
#define NATURAL_ATTRACTION				1.5f
#pragma endregion movement_constant

#pragma region law_constant
#define LAW_PROPORTION					600
#define LAW_MENU_HEIGHT					WINDOW_HEIGHT/2
#define LAW_MENU_WIDTH					WINDOW_WIDTH/4
#pragma endregion law_constant

#pragma region element_sprite
#define ELEMENT_SPRITE_SIZE				20
#define DEFAULT_RANGE					30
#define FILL_COLOR						sf::Color(255,255,255,0)
#define OUTLINE_COLOR					sf::Color(255,255,255,255)
#pragma endregion element_sprite

#pragma region law_sprite
#define BAR_WIDTH 34
#define BAR_HEIGHT 10
#define BAR_RELATIVE_COORD_X -(BAR_WIDTH-ELEMENT_SPRITE_SIZE)/2 // X is from left to right.
#define BAR_RELATIVE_COORD_Y -15 // Y is from top to bottom.
//Fillbar dimension must be smaller than Bar.
#define FILLBAR_HEIGHT 8
#define FILLBAR_WIDTH 30
#define FILLBAR_RELATIVE_COORD_X BAR_RELATIVE_COORD_X + (BAR_WIDTH-FILLBAR_WIDTH)/2
#define FILLBAR_RELATIVE_COORD_Y BAR_RELATIVE_COORD_Y + (BAR_HEIGHT-FILLBAR_HEIGHT)/2
#define ATTRACTION_COLOR sf::Color::Green
#define REPULSION_COLOR sf::Color::Red
#pragma endregion law_sprite

#pragma region danger_sprite
#define DEFAULT_COUNTDOWN_DANGER		10.0f
#define DEFAULT_DURATION_DANGER			3.0f
#define DEFAULT_RADIUS_DANGER			100.0f
#define DEFAULT_DIRECTION_DANGER		sf::Vector2f(1.0, -1.0)
#define DEFAULT_WIDTH_DANGER			10.0f
#define MAX_TIME_WITHOUT_DANGER			20.0f
#define MIN_TIME_WITHOUT_DANGER			2.0f
#define MIN_RADIUS_DANGER				50.0f
#define MAX_RADIUS_DANGER				150.0f
#define MIN_WIDTH_DANGER				5.0f
#define MAX_WIDTH_DANGER				25.0f
#define MIN_TIME_BEFORE_APPARITION		2.0f
#define MAX_TIME_BEFORE_APPARITION		18.0f
#define MIN_TIME_BEFORE_NEXT			1.0f
#define MAX_TIME_BEFORE_NEXT			10.0f
#pragma endregion danger_sprite
