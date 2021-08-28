#pragma once

#define SPACE              32
#define APOSTROPHE         39  /* ' */
#define COMMA              44  /* , */
#define MINUS              45  /* - */
#define PERIOD             46  /* . */
#define SLASH              47  /* / */
#define NUM0                  48
#define NUM1                  49
#define NUM2                  50
#define NUM3                  51
#define NUM4                  52
#define NUM5                  53
#define NUM6                  54
#define NUM7                  55
#define NUM8                  56
#define NUM9                  57
#define SEMICOLON          59  /* ; */
#define EQUAL              61  /* = */
#define A                  65
#define B                  66
#define C                  67
#define D                  68
#define E                  69
#define F                  70
#define G                  71
#define H                  72
#define I                  73
#define J                  74
#define K                  75
#define L                  76
#define M                  77
#define N                  78
#define O                  79
#define P                  80
#define Q                  81
#define R                  82
#define S                  83
#define T                  84
#define U                  85
#define V                  86
#define W                  87
#define X                  88
#define Y                  89
#define Z                  90
#define LEFT_BRACKET       91  /* [ */
#define BACKSLASH          92  /* \ */
#define RIGHT_BRACKET      93  /* ] */
#define GRAVE_ACCENT       96  /* ` */
#define WORLD_1            161 /* non-US #1 */
#define WORLD_2            162 /* non-US #2 */

/* Function keys */
#define ESCAPE             256
#define ENTER              257
#define TAB                258
#define BACKSPACE          259
#define INSERT             260
#define DELETE             261
#define RIGHT              262
#define LEFT               263
#define DOWN               264
#define UP                 265
#define PAGE_UP            266
#define PAGE_DOWN          267
#define HOME               268
#define END                269
#define CAPS_LOCK          280
#define SCROLL_LOCK        281
#define NUM_LOCK           282
#define PRINT_SCREEN       283
#define PAUSE              284
#define F1                 290
#define F2                 291
#define F3                 292
#define F4                 293
#define F5                 294
#define F6                 295
#define F7                 296
#define F8                 297
#define F9                 298
#define F10                299
#define F11                300
#define F12                301
#define F13                302
#define F14                303
#define F15                304
#define F16                305
#define F17                306
#define F18                307
#define F19                308
#define F20                309
#define F21                310
#define F22                311
#define F23                312
#define F24                313
#define F25                314
#define KP_0               320
#define KP_1               321
#define KP_2               322
#define KP_3               323
#define KP_4               324
#define KP_5               325
#define KP_6               326
#define KP_7               327
#define KP_8               328
#define KP_9               329
#define KP_DECIMAL         330
#define KP_DIVIDE          331
#define KP_MULTIPLY        332
#define KP_SUBTRACT        333
#define KP_ADD             334
#define KP_ENTER           335
#define KP_EQUAL           336
#define LEFT_SHIFT         340
#define LEFT_CONTROL       341
#define LEFT_ALT           342
#define LEFT_SUPER         343
#define RIGHT_SHIFT        344
#define RIGHT_CONTROL      345
#define RIGHT_ALT          346
#define RIGHT_SUPER        347
#define MENU               348

//Mouse Buttons
#define MOUSE_1         0
#define MOUSE_2         1
#define MOUSE_3         2
#define MOUSE_4         3
#define MOUSE_5         4
#define MOUSE_6         5
#define MOUSE_7         6
#define MOUSE_8         7
#define MOUSE_LAST      MOUSE_8
#define MOUSE_LEFT      MOUSE_1
#define MOUSE_RIGHT     MOUSE_2
#define MOUSE_MIDDLE    MOUSE_3

//Joysticks
#define JOY_1             0
#define JOY_2             1
#define JOY_3             2
#define JOY_4             3
#define JOY_5             4
#define JOY_6             5
#define JOY_7             6
#define JOY_8             7
#define JOY_9             8
#define JOY_10            9
#define JOY_11            10
#define JOY_12            11
#define JOY_13            12
#define JOY_14            13
#define JOY_15            14
#define JOY_16            15
#define JOY_LAST          JOY_16

//Joystick inputs

#define GAMEPAD_BTN_A               0
#define GAMEPAD_BTN_B               1
#define GAMEPAD_BTN_X               2
#define GAMEPAD_BTN_Y               3
#define GAMEPAD_BTN_LEFT_BUMPER     4
#define GAMEPAD_BTN_RIGHT_BUMPER    5
#define GAMEPAD_BTN_BACK            6
#define GAMEPAD_BTN_START           7
#define GAMEPAD_BTN_GUIDE           8
#define GAMEPAD_BTN_LEFT_THUMB      9
#define GAMEPAD_BTN_RIGHT_THUMB     10
#define GAMEPAD_BTN_DPAD_UP         11
#define GAMEPAD_BTN_DPAD_RIGHT      12
#define GAMEPAD_BTN_DPAD_DOWN       13
#define GAMEPAD_BTN_DPAD_LEFT       14
#define GAMEPAD_BTN_LAST            GAMEPAD_BTN_DPAD_LEFT

#define GAMEPAD_BTN_CROSS       GAMEPAD_BTN_A
#define GAMEPAD_BTN_CIRCLE      GAMEPAD_BTN_B
#define GAMEPAD_BTN_SQUARE      GAMEPAD_BTN_X
#define GAMEPAD_BTN_TRIANGLE    GAMEPAD_BTN_Y

#define GAMEPAD_AXS_LEFT_X        0
#define GAMEPAD_AXS_LEFT_Y        1
#define GAMEPAD_AXS_RIGHT_X       2
#define GAMEPAD_AXS_RIGHT_Y       3
#define GAMEPAD_AXS_LEFT_TRIGGER  4
#define GAMEPAD_AXS_RIGHT_TRIGGER 5
#define GAMEPAD_AXS_LAST          GAMEPAD_AXS_RIGHT_TRIGGER

//Input modes and visibility

#define CURSOR                 0x00033001
#define STICKY_KEYS            0x00033002
#define STICKY_MOUSE_BUTTONS   0x00033003
#define LOCK_KEY_MODS          0x00033004
#define RAW_MOUSE_MOTION       0x00033005

#define CURSOR_NORMAL          0x00034001
#define CURSOR_HIDDEN          0x00034002
#define CURSOR_DISABLED        0x00034003