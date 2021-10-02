#include "kb.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
/*
This layout removes unessesarry functions from the tinyexpr library,
well the functions that are not needed for the layout as this is a fairly simple calculator.
The reduction in size allows you to add more features to the firmware without compromising on the calculator.

To compile the layout
make clean && make macropad_artiomsu:minimised

To find the device plug it in and run
sudo dmesg | grep tty

To flash the firmware
sudo avrdude -p atmega32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:macropad_artiomsu_minimised.hex
*/


/*
#############################################################################################
#############################################################################################
#                                                                                           #
#                      Definitions and variables for macros, ...                            #
#                                                                                           #
#############################################################################################
#############################################################################################
*/
//https://golem.hu/article/pro-micro-pinout/
#define LED_BLUE_ON writePinHigh(F4);
#define LED_GREEN_ON writePinHigh(F5);
#define LED_RED_ON writePinHigh(F6);
#define LED_WHITE_ON writePinHigh(F7);
#define LED_ORANGE_ON writePinHigh(D1);

#define LED_BLUE_OFF writePinLow(F4);
#define LED_GREEN_OFF writePinLow(F5);
#define LED_RED_OFF writePinLow(F6);
#define LED_WHITE_OFF writePinLow(F7);
#define LED_ORANGE_OFF writePinLow(D1);

#define LED_ALL_OFF writePinLow(F4); writePinLow(F5); writePinLow(F6); writePinLow(F7); writePinLow(D1);


#define Layer_main 0
#define Layer_shortcuts 1
#define Layer_calc 2
#define Layer_extra 3

// for the calculator functionality
#define EXPRESSIONS_BUFF_SIZE 64
int input_count = 0;                            // stores the amount of the filled in expressions_buffer.
char expressions_buffer[EXPRESSIONS_BUFF_SIZE]; // stores the typed out string
int decimal_point_pressision = 2;               // how many decimal points to show by default, can be changed via macros bellow.

// for the numlock and layer leds
bool num_lock_led_is_on = false;        // if numlock should be on
int led_state_current = 0;              // what is the current layer temp
bool num_lock_triggered = false;        // was the numlock pressed
int last_led_state_current = 0;         // the latest current layer

bool enable_num_lock_animation = true;  // play the numlock animation, toggled through macro.
int count_delay = 0;                    // counter for numlock animation
int count_delay_max = 500;              // delay for which the lights change
int count_current_led = 0;              // which led to light up
int count_num_leds = 4;                 // total number of leds starting at 0
bool led_direction_left = true;         // animation direction of the leds

struct rlShiet{
    char *text;
    bool team;
};

struct rlShiet rlShiet_arr[] = {
    { "WHAT A SAVE!!!!!!", false},
    { "WHAT A SHOT!!!!!!", false},
    { "AWESOME PASS!!!!!", false},
    { "OOPs My Bad :(", false},

    { "Take the shot :)", true},
    { "I got it my son", true},
    { "Centering the boi ;)", true},
    { "Passing to you", true},

    { "On your Left ;)", true},
    { "Behind you ;)", true},
    { "Demoing Goalie", true},
    { "On your Right ;)", true},

    { "Taking Boost", true},
    { "All yours :O", true},
    { "Hold up need to take a piss", false},
    { "Hold up need to take a shiet", false},

    { "Need Sum Booost", true},
    { "y u so mad bro?", false},
    { "Its just a game bro", false}
};
/*
#############################################################################################
#############################################################################################
#                                                                                           #
#                      END of Definitions and variables for macros, ...                     #
#                                                                                           #
#############################################################################################
#############################################################################################
*/


/*
#############################################################################################
#############################################################################################
#                                                                                           #
#                            TinyExpr Definitions / Declarations                            #
#                                                                                           #
#############################################################################################
#############################################################################################
*/
typedef struct te_expr {
    int type;
    union {double value; const double *bound; const void *function;};
    void *parameters[1];
} te_expr;

enum {
    TE_VARIABLE = 0,

    TE_FUNCTION0 = 8, TE_FUNCTION1, TE_FUNCTION2, TE_FUNCTION3,
    TE_FUNCTION4, TE_FUNCTION5, TE_FUNCTION6, TE_FUNCTION7,

    TE_CLOSURE0 = 16, TE_CLOSURE1, TE_CLOSURE2, TE_CLOSURE3,
    TE_CLOSURE4, TE_CLOSURE5, TE_CLOSURE6, TE_CLOSURE7,

    TE_FLAG_PURE = 32
};

typedef struct te_variable {
    const char *name;
    const void *address;
    int type;
    void *context;
} te_variable;

/* Parses the input expression, evaluates it, and frees it. */
/* Returns NaN on error. */
double te_interp(const char *expression, int *error);

/* Parses the input expression and binds variables. */
/* Returns NULL on error. */
te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error);

/* Evaluates the expression. */
double te_eval(const te_expr *n);

/* Prints debugging information on the syntax tree. */
void te_print(const te_expr *n);

/* Frees the expression. */
/* This is safe to call on NULL pointers. */
void te_free(te_expr *n);
/*
#############################################################################################
#############################################################################################
#                                                                                           #
#                            End of TinyExpr Definitions / Declarations                     #
#                                                                                           #
#############################################################################################
#############################################################################################
*/
void write_char_to_buff(char c);

enum custom_keycodes {
    // for the calc layer
    L1_1 = SAFE_RANGE,
    L1_2,
    L1_3,
    L1_4,
    L1_5,
    L1_6,
    L1_7,
    L1_8,
    L1_9,
    L1_0,
    L1_SLASH,
    L1_MULTIPLY,
    L1_MINUS,
    L1_PLUS,
    L1_EQUALS,
    L1_DOT,
    L1_PRINT_EQUATION,
    L1_POWER,
    L1_MOD,
    L1_PRECISION_MINUS,
    L1_PRECISION_PLUS,
    L1_EXIT_LAYER,
    //other
    COMPILE_MACRO,
    FLASH_MACRO,
    TOGGLE_NUM_LOCK_ANIMATION,
    G1,
    G2,
    G3,
    G4,
    G5,
    G6,
    G7,
    G8,
    G9,
    G10,
    G11,
    G12,
    G13,
    G14,
    G15,
    G16,
    G17,
    G18,
    G19
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[Layer_main] = LAYOUT_MACROPAD( //default numpad
		KC_NUMLOCK,     KC_KP_SLASH,    KC_KP_ASTERISK,     KC_KP_MINUS,
		KC_KP_7,        KC_KP_8,        KC_KP_9,            KC_KP_PLUS,
		KC_KP_4,        KC_KP_5,        KC_KP_6,            KC_KP_ENTER,
		KC_KP_1,        KC_KP_2,        KC_KP_3,            KC_COMMA,
		KC_KP_0,        KC_KP_DOT,      KC_KP_EQUAL,        LT(Layer_shortcuts, KC_BSPACE)),

	[Layer_shortcuts] = LAYOUT_MACROPAD( //layer switcher and some settings
		LCTL(LALT(LSFT(KC_1))),     LCTL(LALT(LSFT(KC_2))),     LCTL(LALT(LSFT(KC_3))),        L1_PRECISION_MINUS,
		KC_F17,                     KC_F18,                     KC_F19,                        L1_PRECISION_PLUS,
		KC_F14,                     KC_F15,                     KC_F16,                        TOGGLE_NUM_LOCK_ANIMATION,
		COMPILE_MACRO,              FLASH_MACRO,                KC_F13,                        RESET,
		KC_TRNS,                    TO(Layer_extra),            TO(Layer_calc),                TO(Layer_main)),

    [Layer_calc] = LAYOUT_MACROPAD( //hardware calculator
		L1_PRINT_EQUATION,  L1_SLASH,   L1_MULTIPLY,    L1_MINUS,
		L1_7,               L1_8,       L1_9,           L1_PLUS,
		L1_4,               L1_5,       L1_6,           L1_POWER,
		L1_1,               L1_2,       L1_3,           L1_MOD,
		L1_0,               L1_DOT,     L1_EQUALS,      L1_EXIT_LAYER),

    [Layer_extra] = LAYOUT_MACROPAD( //extra stuff for obs and things
		G1,     G2,     G3,     G4,
		G5,     G6,     G7,     G8,
        G9,     G10,    G11,    G12,
        G13,    G14,    G15,    G16,
		G17,    G18,    G19,    TO(Layer_main))
};

void matrix_scan_user(void) {
    if(led_state_current != -1 || num_lock_triggered){
        if(!num_lock_triggered){
            last_led_state_current = led_state_current;
            switch (led_state_current)
                {
                    case Layer_shortcuts:
                        LED_ALL_OFF
                        LED_BLUE_ON
                        break;
                    case Layer_calc:
                        LED_ALL_OFF
                        LED_GREEN_ON
                        break;
                    case Layer_extra:
                        LED_ALL_OFF
                        LED_RED_ON
                        break;
                    case Layer_main:
                        LED_ALL_OFF
                        break;
                }
            led_state_current = -1;
        }else{
            num_lock_triggered = false;
        }
    }

    if(last_led_state_current == Layer_main && num_lock_led_is_on && enable_num_lock_animation){
        if(count_delay >= count_delay_max){
            count_delay = 0;
            LED_ALL_OFF
            switch (count_current_led){
                case 0:
                    LED_BLUE_ON
                    break;
                case 1:
                    LED_GREEN_ON
                    break;
                case 2:
                    LED_RED_ON
                    break;
                case 3:
                    LED_WHITE_ON
                    break;
                case 4:
                    LED_ORANGE_ON
                    break;

                default:
                    break;
            }
            if(led_direction_left){
                count_current_led--;
                if(count_current_led < 0){
                    count_current_led = 1;
                    led_direction_left = false;
                }
            }else{
                count_current_led++;
                if(count_current_led > count_num_leds){
                    count_current_led = count_num_leds - 1;
                    led_direction_left = true;
                }
            }

        }
        count_delay++;
    }
}
// small leg goes to ground
void keyboard_pre_init_user(void) {
    setPinOutput(F4);
    setPinOutput(F5);
    setPinOutput(F6);
    setPinOutput(F7);
    setPinOutput(D1);
}


bool led_update_user(led_t led_state) {
    num_lock_led_is_on = led_state.num_lock;
    if(led_state.num_lock){
        num_lock_led_is_on = true;
        num_lock_triggered = true;
    }else{
        if(last_led_state_current == Layer_main){
            LED_ALL_OFF
        }
        num_lock_led_is_on = false;
        num_lock_triggered = true;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    led_state_current = get_highest_layer(state);
    return state;
}

void rl2(int n){
    rlShiet_arr[n].team ? tap_code(KC_Y) : tap_code(KC_T);
    _delay_ms(100);
    send_string(rlShiet_arr[n].text);
    tap_code(KC_ENTER);
    tap_code(KC_ENTER);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L1_1:
            if (record->event.pressed) {
                write_char_to_buff('1');
            }
            break;
        case L1_2:
            if (record->event.pressed) {
                write_char_to_buff('2');
            }
            break;
        case L1_3:
            if (record->event.pressed) {
                write_char_to_buff('3');
            }
            break;
        case L1_4:
            if (record->event.pressed) {
                write_char_to_buff('4');
            }
            break;
        case L1_5:
            if (record->event.pressed) {
                write_char_to_buff('5');
            }
            break;
        case L1_6:
            if (record->event.pressed) {
                write_char_to_buff('6');
            }
            break;
        case L1_7:
            if (record->event.pressed) {
                write_char_to_buff('7');
            }
            break;
        case L1_8:
            if (record->event.pressed) {
                write_char_to_buff('8');
            }
            break;
        case L1_9:
            if (record->event.pressed) {
                write_char_to_buff('9');
            }
            break;
        case L1_0:
            if (record->event.pressed) {
                write_char_to_buff('0');
            }
            break;
        case L1_PLUS:
            if (record->event.pressed) {
                write_char_to_buff('+');
            }
            break;
        case L1_MINUS:
            if (record->event.pressed) {
                write_char_to_buff('-');
            }
            break;
        case L1_MULTIPLY:
            if (record->event.pressed) {
                write_char_to_buff('*');
            }
            break;
        case L1_SLASH:
            if (record->event.pressed) {
                write_char_to_buff('/');
            }
            break;
        case L1_DOT:
            if (record->event.pressed) {
                write_char_to_buff('.');
            }
            break;
        case L1_POWER:
            if (record->event.pressed) {
                write_char_to_buff('^');
            }
            break;
        case L1_MOD:
            if (record->event.pressed) {
                write_char_to_buff('%');
            }
            break;
        case L1_EQUALS:
            if (record->event.pressed) {
                double result = te_interp(expressions_buffer, 0);
                char output_string[EXPRESSIONS_BUFF_SIZE];

                dtostrf(result, 1, decimal_point_pressision, output_string);
                send_string(output_string);
                input_count = 0;
            }
            break;
        case L1_PRINT_EQUATION:
            if (record->event.pressed) {
                if(input_count>0){
                    send_string(expressions_buffer);
                }
            }
            break;
        case L1_PRECISION_MINUS:
            if (record->event.pressed) {
                if(decimal_point_pressision > 0){
                    decimal_point_pressision--;
                }
            }
            break;
        case L1_PRECISION_PLUS:
            if (record->event.pressed) {
                if(decimal_point_pressision < 10){
                    decimal_point_pressision++;
                }
            }
            break;
        case L1_EXIT_LAYER:
            if(record->event.pressed){
                input_count = 0;
                expressions_buffer[0] = '\0';
                layer_move(Layer_main);
            }
            break;
        case COMPILE_MACRO:
            if(record->event.pressed){
                SEND_STRING("cd /media/veracrypt1/GIT/qmk_firmware && make clean && make macropad_artiomsu:simple");
            }
            break;
        case FLASH_MACRO:
            if(record->event.pressed){
                SEND_STRING("cd /media/veracrypt1/GIT/qmk_firmware && sudo avrdude -p atmega32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:macropad_artiomsu_simple.hex");
            }
            break;
        case G1:
            if(record->event.pressed){
                rl2(0);
            }
            break;
        case G2:
            if(record->event.pressed){
                rl2(1);
            }
            break;
        case G3:
            if(record->event.pressed){
                rl2(2);
            }
            break;
        case G4:
            if(record->event.pressed){
                rl2(3);
            }
            break;
        case G5:
            if(record->event.pressed){
                rl2(4);
            }
            break;
        case G6:
            if(record->event.pressed){
                rl2(5);
            }
            break;
        case G7:
            if(record->event.pressed){
                rl2(6);
            }
            break;
        case G8:
            if(record->event.pressed){
                rl2(7);
            }
            break;
        case G9:
            if(record->event.pressed){
                rl2(8);
            }
            break;
        case G10:
            if(record->event.pressed){
                rl2(9);
            }
            break;
        case G11:
            if(record->event.pressed){
                rl2(10);
            }
            break;
        case G12:
            if(record->event.pressed){
                rl2(11);
            }
            break;
        case G13:
            if(record->event.pressed){
                rl2(12);
            }
            break;
        case G14:
            if(record->event.pressed){
                 rl2(13);
            }
            break;
        case G15:
            if(record->event.pressed){
                 rl2(14);
            }
            break;
        case G16:
            if(record->event.pressed){
                 rl2(15);
            }
            break;
        case G17:
            if(record->event.pressed){
                 rl2(16);
            }
            break;
        case G18:
            if(record->event.pressed){
                 rl2(17);
            }
            break;
        case G19:
            if(record->event.pressed){
                 rl2(18);
            }
            break;
        case TOGGLE_NUM_LOCK_ANIMATION:
            if(record->event.pressed){
                enable_num_lock_animation=!enable_num_lock_animation;
            }
            break;
    }
	return true;
}


void write_char_to_buff(char c){
    if(input_count+1 < EXPRESSIONS_BUFF_SIZE){
        expressions_buffer[input_count] = c;
        expressions_buffer[input_count+1] = '\0';
        input_count++;
    }
}


/*
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#                                                                                           #
#                               TinyExpr Functions                                          #
#                                                                                           #
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
*/



#ifndef NAN
#define NAN (0.0/0.0)
#endif

#ifndef INFINITY
#define INFINITY (1.0/0.0)
#endif


typedef double (*te_fun2)(double, double);

enum {
    TOK_NULL = TE_CLOSURE7+1, TOK_ERROR, TOK_END,
    TOK_NUMBER, TOK_VARIABLE, TOK_INFIX
};


enum {TE_CONSTANT = 1};


typedef struct state {
    const char *start;
    const char *next;
    int type;
    union {double value; const double *bound; const void *function;};
    void *context;

    const te_variable *lookup;
    int lookup_len;
} state;


#define TYPE_MASK(TYPE) ((TYPE)&0x0000001F)

#define IS_PURE(TYPE) (((TYPE) & TE_FLAG_PURE) != 0)
#define IS_FUNCTION(TYPE) (((TYPE) & TE_FUNCTION0) != 0)
#define IS_CLOSURE(TYPE) (((TYPE) & TE_CLOSURE0) != 0)
#define ARITY(TYPE) ( ((TYPE) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((TYPE) & 0x00000007) : 0 )
#define NEW_EXPR(type, ...) new_expr((type), (const te_expr*[]){__VA_ARGS__})

static te_expr *new_expr(const int type, const te_expr *parameters[]) {
    const int arity = ARITY(type);
    const int psize = sizeof(void*) * arity;
    const int size = (sizeof(te_expr) - sizeof(void*)) + psize + (IS_CLOSURE(type) ? sizeof(void*) : 0);
    te_expr *ret = malloc(size);
    memset(ret, 0, size);
    if (arity && parameters) {
        memcpy(ret->parameters, parameters, psize);
    }
    ret->type = type;
    ret->bound = 0;
    return ret;
}


void te_free_parameters(te_expr *n) {
    if (!n) return;
    switch (TYPE_MASK(n->type)) {
        case TE_FUNCTION7: case TE_CLOSURE7: te_free(n->parameters[6]);     /* Falls through. */
        case TE_FUNCTION6: case TE_CLOSURE6: te_free(n->parameters[5]);     /* Falls through. */
        case TE_FUNCTION5: case TE_CLOSURE5: te_free(n->parameters[4]);     /* Falls through. */
        case TE_FUNCTION4: case TE_CLOSURE4: te_free(n->parameters[3]);     /* Falls through. */
        case TE_FUNCTION3: case TE_CLOSURE3: te_free(n->parameters[2]);     /* Falls through. */
        case TE_FUNCTION2: case TE_CLOSURE2: te_free(n->parameters[1]);     /* Falls through. */
        case TE_FUNCTION1: case TE_CLOSURE1: te_free(n->parameters[0]);
    }
}


void te_free(te_expr *n) {
    if (!n) return;
    te_free_parameters(n);
    free(n);
}



static const te_variable functions[] = {
    /* must be in alphabetical order */
    {"pow", pow,      TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {0, 0, 0, 0}
};

static const te_variable *find_builtin(const char *name, int len) {
    int imin = 0;
    int imax = sizeof(functions) / sizeof(te_variable) - 2;

    /*Binary search.*/
    while (imax >= imin) {
        const int i = (imin + ((imax-imin)/2));
        int c = strncmp(name, functions[i].name, len);
        if (!c) c = '\0' - functions[i].name[len];
        if (c == 0) {
            return functions + i;
        } else if (c > 0) {
            imin = i + 1;
        } else {
            imax = i - 1;
        }
    }

    return 0;
}

static const te_variable *find_lookup(const state *s, const char *name, int len) {
    int iters;
    const te_variable *var;
    if (!s->lookup) return 0;

    for (var = s->lookup, iters = s->lookup_len; iters; ++var, --iters) {
        if (strncmp(name, var->name, len) == 0 && var->name[len] == '\0') {
            return var;
        }
    }
    return 0;
}



static double add(double a, double b) {return a + b;}
static double sub(double a, double b) {return a - b;}
static double mul(double a, double b) {return a * b;}
static double divide(double a, double b) {return a / b;}
static double negate(double a) {return -a;}

void next_token(state *s) {
    s->type = TOK_NULL;

    do {

        if (!*s->next){
            s->type = TOK_END;
            return;
        }

        /* Try reading a number. */
        if ((s->next[0] >= '0' && s->next[0] <= '9') || s->next[0] == '.') {
            s->value = strtod(s->next, (char**)&s->next);
            s->type = TOK_NUMBER;
        } else {
            /* Look for a variable or builtin function call. */
            if (s->next[0] >= 'a' && s->next[0] <= 'z') {
                const char *start;
                start = s->next;
                while ((s->next[0] >= 'a' && s->next[0] <= 'z') || (s->next[0] >= '0' && s->next[0] <= '9') || (s->next[0] == '_')) s->next++;

                const te_variable *var = find_lookup(s, start, s->next - start);
                if (!var) var = find_builtin(start, s->next - start);

                if (!var) {
                    s->type = TOK_ERROR;
                } else {
                    switch(TYPE_MASK(var->type))
                    {
                        case TE_VARIABLE:
                            s->type = TOK_VARIABLE;
                            s->bound = var->address;
                            break;

                        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:         /* Falls through. */
                        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:         /* Falls through. */
                            s->context = var->context;                                                  /* Falls through. */

                        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:     /* Falls through. */
                        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:     /* Falls through. */
                            s->type = var->type;
                            s->function = var->address;
                            break;
                    }
                }

            } else {
                /* Look for an operator or special character. */
                switch (s->next++[0]) {
                    case '+': s->type = TOK_INFIX; s->function = add; break;
                    case '-': s->type = TOK_INFIX; s->function = sub; break;
                    case '*': s->type = TOK_INFIX; s->function = mul; break;
                    case '/': s->type = TOK_INFIX; s->function = divide; break;
                    case '^': s->type = TOK_INFIX; s->function = pow; break;
                    case '%': s->type = TOK_INFIX; s->function = fmod; break;
                    case ' ': case '\t': case '\n': case '\r': break;
                    default: s->type = TOK_ERROR; break;
                }
            }
        }
    } while (s->type == TOK_NULL);
}


static te_expr *list(state *s);
static te_expr *expr(state *s);
static te_expr *power(state *s);

static te_expr *base(state *s) {
    /* <base>      =    <constant> | <variable> | <function-0> {"(" ")"} | <function-1> <power> | <function-X> "(" <expr> {"," <expr>} ")" | "(" <list> ")" */
    te_expr *ret;
    int arity;

    switch (TYPE_MASK(s->type)) {
        case TOK_NUMBER:
            ret = new_expr(TE_CONSTANT, 0);
            ret->value = s->value;
            next_token(s);
            break;

        case TOK_VARIABLE:
            ret = new_expr(TE_VARIABLE, 0);
            ret->bound = s->bound;
            next_token(s);
            break;

        case TE_FUNCTION0:
        case TE_CLOSURE0:
            ret = new_expr(s->type, 0);
            ret->function = s->function;
            if (IS_CLOSURE(s->type)) ret->parameters[0] = s->context;
            next_token(s);
            break;

        case TE_FUNCTION1:
        case TE_CLOSURE1:
            ret = new_expr(s->type, 0);
            ret->function = s->function;
            if (IS_CLOSURE(s->type)) ret->parameters[1] = s->context;
            next_token(s);
            ret->parameters[0] = power(s);
            break;

        case TE_FUNCTION2: case TE_FUNCTION3: case TE_FUNCTION4:
        case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
        case TE_CLOSURE2: case TE_CLOSURE3: case TE_CLOSURE4:
        case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            arity = ARITY(s->type);

            ret = new_expr(s->type, 0);
            ret->function = s->function;
            if (IS_CLOSURE(s->type)) ret->parameters[arity] = s->context;
            next_token(s);

            s->type = TOK_ERROR;
            break;

        default:
            ret = new_expr(0, 0);
            s->type = TOK_ERROR;
            ret->value = NAN;
            break;
    }

    return ret;
}


static te_expr *power(state *s) {
    /* <power>     =    {("-" | "+")} <base> */
    int sign = 1;
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        if (s->function == sub) sign = -sign;
        next_token(s);
    }

    te_expr *ret;

    if (sign == 1) {
        ret = base(s);
    } else {
        ret = NEW_EXPR(TE_FUNCTION1 | TE_FLAG_PURE, base(s));
        ret->function = negate;
    }

    return ret;
}


static te_expr *factor(state *s) {
    /* <factor>    =    <power> {"^" <power>} */
    te_expr *ret = power(s);

    while (s->type == TOK_INFIX && (s->function == pow)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, power(s));
        ret->function = t;
    }

    return ret;
}



static te_expr *term(state *s) {
    /* <term>      =    <factor> {("*" | "/" | "%") <factor>} */
    te_expr *ret = factor(s);

    while (s->type == TOK_INFIX && (s->function == mul || s->function == divide || s->function == fmod)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, factor(s));
        ret->function = t;
    }

    return ret;
}


static te_expr *expr(state *s) {
    /* <expr>      =    <term> {("+" | "-") <term>} */
    te_expr *ret = term(s);

    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, term(s));
        ret->function = t;
    }

    return ret;
}


static te_expr *list(state *s) {
    /* <list>      =    <expr> {"," <expr>} */
    te_expr *ret = expr(s);
    return ret;
}


#define TE_FUN(...) ((double(*)(__VA_ARGS__))n->function)
#define M_tinyexpr(e) te_eval(n->parameters[e])


double te_eval(const te_expr *n) {
    if (!n) return NAN;

    switch(TYPE_MASK(n->type)) {
        case TE_CONSTANT: return n->value;
        case TE_VARIABLE: return *n->bound;

        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
            switch(ARITY(n->type)) {
                case 0: return TE_FUN(void)();
                case 1: return TE_FUN(double)(M_tinyexpr(0));
                case 2: return TE_FUN(double, double)(M_tinyexpr(0), M_tinyexpr(1));
                case 3: return TE_FUN(double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2));
                case 4: return TE_FUN(double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3));
                case 5: return TE_FUN(double, double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4));
                case 6: return TE_FUN(double, double, double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5));
                case 7: return TE_FUN(double, double, double, double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5), M_tinyexpr(6));
                default: return NAN;
            }

        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            switch(ARITY(n->type)) {
                case 0: return TE_FUN(void*)(n->parameters[0]);
                case 1: return TE_FUN(void*, double)(n->parameters[1], M_tinyexpr(0));
                case 2: return TE_FUN(void*, double, double)(n->parameters[2], M_tinyexpr(0), M_tinyexpr(1));
                case 3: return TE_FUN(void*, double, double, double)(n->parameters[3], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2));
                case 4: return TE_FUN(void*, double, double, double, double)(n->parameters[4], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3));
                case 5: return TE_FUN(void*, double, double, double, double, double)(n->parameters[5], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4));
                case 6: return TE_FUN(void*, double, double, double, double, double, double)(n->parameters[6], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5));
                case 7: return TE_FUN(void*, double, double, double, double, double, double, double)(n->parameters[7], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5), M_tinyexpr(6));
                default: return NAN;
            }

        default: return NAN;
    }

}

#undef TE_FUN
#undef M_tinyexpr

static void optimize(te_expr *n) {
    /* Evaluates as much as possible. */
    if (n->type == TE_CONSTANT) return;
    if (n->type == TE_VARIABLE) return;

    /* Only optimize out functions flagged as pure. */
    if (IS_PURE(n->type)) {
        const int arity = ARITY(n->type);
        int known = 1;
        int i;
        for (i = 0; i < arity; ++i) {
            optimize(n->parameters[i]);
            if (((te_expr*)(n->parameters[i]))->type != TE_CONSTANT) {
                known = 0;
            }
        }
        if (known) {
            const double value = te_eval(n);
            te_free_parameters(n);
            n->type = TE_CONSTANT;
            n->value = value;
        }
    }
}


te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error) {
    state s;
    s.start = s.next = expression;
    s.lookup = variables;
    s.lookup_len = var_count;

    next_token(&s);
    te_expr *root = list(&s);

    if (s.type != TOK_END) {
        te_free(root);
        if (error) {
            *error = (s.next - s.start);
            if (*error == 0) *error = 1;
        }
        return 0;
    } else {
        optimize(root);
        if (error) *error = 0;
        return root;
    }
}


double te_interp(const char *expression, int *error) {
    te_expr *n = te_compile(expression, 0, 0, error);
    double ret;
    if (n) {
        ret = te_eval(n);
        te_free(n);
    } else {
        ret = NAN;
    }
    return ret;
}


/*
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#                                                                                           #
#                              End OF TinyExpr Functions                                    #
#                                                                                           #
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
*/
