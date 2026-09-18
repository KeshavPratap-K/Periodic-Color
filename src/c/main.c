#include <pebble.h>

// Periodic Color
// A colour remake of Periodic for the rectangular Pebble family. The SDK maps
// each card colour to the closest available shade on monochrome hardware.

#define ELEMENT_COUNT 60
#define ANIMATION_DURATION_MS 650
#define ANIMATION_FRAME_MS 33
#define PERSIST_KEY_BACKGROUND_COLOR 1
#define PERSIST_KEY_CARD_COLORS 2
#define PERSIST_KEY_TEXT_COLORS 3

typedef enum {
  MATERIAL_COLORLESS,
  MATERIAL_SILVER,
  MATERIAL_DARK,
  MATERIAL_BROWN,
  MATERIAL_RED,
  MATERIAL_ORANGE,
  MATERIAL_YELLOW,
  MATERIAL_GREEN,
  MATERIAL_BLUE,
  MATERIAL_PURPLE,
  MATERIAL_GOLD
} MaterialTone;

typedef struct {
  const char *symbol;
  const char *name;
  const char *weight;
  MaterialTone tone;
} Element;

// The original face treats zero as Neutronium so midnight and :00 have an
// entry. Sodium keeps the rounded weight used by that face. Card colours use
// memorable chemistry cues (flame tests, gas discharge, and familiar uses)
// instead of rendering common metals as indistinguishable grey.
static const Element s_elements[ELEMENT_COUNT] = {
  { "0",  "Nuetronium",   "0.0000",  MATERIAL_DARK },
  { "H",  "Hydrogen",     "1.008",   MATERIAL_BLUE },    // water
  { "He", "Helium",       "4.0026",  MATERIAL_YELLOW },  // discharge glow
  { "Li", "Lithium",      "6.94",    MATERIAL_RED },     // lithium batteries
  { "Be", "Beryllium",    "9.0122",  MATERIAL_BLUE },    // beryl
  { "B",  "Boron",        "10.81",   MATERIAL_GREEN },   // borosilicate glass
  { "C",  "Carbon",       "12.011",  MATERIAL_DARK },
  { "N",  "Nitrogen",     "14.007",  MATERIAL_BLUE },
  { "O",  "Oxygen",       "15.999",  MATERIAL_BLUE },
  { "F",  "Fluorine",     "18.998",  MATERIAL_YELLOW },
  { "Ne", "Neon",         "20.180",  MATERIAL_ORANGE },
  { "Na", "Sodium",       "22.9898", MATERIAL_YELLOW },  // yellow flame
  { "Mg", "Magnesium",    "24.3050", MATERIAL_COLORLESS }, // white flare
  { "Al", "Aluminium",    "26.9815", MATERIAL_BLUE },    // cans
  { "Si", "Silicon",      "28.085",  MATERIAL_BLUE },    // chips
  { "P",  "Phosphorus",   "30.974",  MATERIAL_RED },
  { "S",  "Sulfur",       "32.06",   MATERIAL_YELLOW },
  { "Cl", "Chlorine",     "35.45",   MATERIAL_GREEN },
  { "Ar", "Argon",        "39.948",  MATERIAL_PURPLE },  // plasma glow
  { "K",  "Potassium",    "39.0983", MATERIAL_PURPLE },  // lilac flame
  { "Ca", "Calcium",      "40.078",  MATERIAL_ORANGE },  // brick-red flame
  { "Sc", "Scandium",     "44.9559", MATERIAL_BLUE },    // stadium lights
  { "Ti", "Titanium",     "47.867",  MATERIAL_BLUE },    // anodised titanium
  { "V",  "Vanadium",     "50.9415", MATERIAL_GREEN },   // green vanadium glass
  { "Cr", "Chromium",     "51.9961", MATERIAL_BLUE },    // blue chrome salts
  { "Mn", "Manganese",    "54.938",  MATERIAL_PURPLE },  // permanganate
  { "Fe", "Iron",         "55.845",  MATERIAL_RED },     // iron oxide
  { "Co", "Cobalt",       "58.933",  MATERIAL_BLUE },
  { "Ni", "Nickel",       "58.693",  MATERIAL_GREEN },   // nickel salts
  { "Cu", "Copper",       "63.546",  MATERIAL_ORANGE },
  { "Zn", "Zinc",         "65.38",   MATERIAL_BLUE },    // galvanising
  { "Ga", "Gallium",      "69.723",  MATERIAL_BLUE },    // blue LEDs
  { "Ge", "Germanium",    "72.630",  MATERIAL_PURPLE },  // infrared optics
  { "As", "Arsenic",      "74.922",  MATERIAL_GREEN },   // Scheele's green
  { "Se", "Selenium",     "78.971",  MATERIAL_RED },
  { "Br", "Bromine",      "79.904",  MATERIAL_RED },
  { "Kr", "Krypton",      "83.798",  MATERIAL_PURPLE },  // discharge tube
  { "Rb", "Rubidium",     "85.468",  MATERIAL_PURPLE },  // violet flame
  { "Sr", "Strontium",    "87.62",   MATERIAL_RED },     // red fireworks
  { "Y",  "Yttrium",      "88.906",  MATERIAL_RED },     // laser phosphor
  { "Zr", "Zirconium",    "91.224",  MATERIAL_BLUE },    // zircon
  { "Nb", "Niobium",      "92.906",  MATERIAL_BLUE },    // superconductors
  { "Mo", "Molybdenum",   "95.95",   MATERIAL_GREEN },   // molybdenum glass
  { "Tc", "Technetium",   "[98]",    MATERIAL_BLUE },    // medical imaging
  { "Ru", "Ruthenium",    "101.07",  MATERIAL_BLUE },    // blue dye
  { "Rh", "Rhodium",      "102.91",  MATERIAL_PURPLE },  // rose plating
  { "Pd", "Palladium",    "106.42",  MATERIAL_GREEN },   // catalytic converter
  { "Ag", "Silver",       "107.87",  MATERIAL_BLUE },    // photography
  { "Cd", "Cadmium",      "112.41",  MATERIAL_YELLOW },  // cadmium yellow
  { "In", "Indium",       "114.82",  MATERIAL_BLUE },    // touchscreens
  { "Sn", "Tin",          "118.71",  MATERIAL_BLUE },    // solder
  { "Sb", "Antimony",     "121.76",  MATERIAL_ORANGE },  // flame retardants
  { "Te", "Tellurium",    "127.60",  MATERIAL_GREEN },   // solar cells
  { "I",  "Iodine",       "126.90",  MATERIAL_PURPLE },
  { "Xe", "Xenon",        "131.29",  MATERIAL_BLUE },    // xenon lamp
  { "Cs", "Caesium",      "132.91",  MATERIAL_BLUE },    // atomic clocks
  { "Ba", "Barium",       "137.33",  MATERIAL_GREEN },   // green fireworks
  { "La", "Lanthanum",    "138.91",  MATERIAL_BLUE },    // camera lenses
  { "Ce", "Cerium",       "140.12",  MATERIAL_ORANGE },  // lighter flints
  { "Pr", "Praseodymium", "140.91",  MATERIAL_GREEN }    // green glass
};

static Window *s_window;
static Layer *s_face_layer;
static AppTimer *s_animation_timer;
static uint32_t s_animation_started_at;
static int s_hour_now;
static int s_minute_now;
static int s_hour_before;
static int s_minute_before;
static bool s_hour_is_changing;
static bool s_minute_is_changing;
static bool s_is_animating;
static bool s_has_time;
static GColor s_background_color;
static uint8_t s_card_colors[ELEMENT_COUNT];
static uint8_t s_text_colors[ELEMENT_COUNT];

static uint32_t clock_milliseconds(void) {
  time_t seconds;
  uint16_t milliseconds;
  time_ms(&seconds, &milliseconds);
  return ((uint32_t)seconds * 1000) + milliseconds;
}

static GColor element_color(MaterialTone tone) {
  // GColorFromRGB is valid on every SDK 3 target. Colour devices use Pebble's
  // 64-colour palette; black-and-white hardware maps the result to its nearest
  // supported shade. No platform preprocessor branch is needed here.
  switch (tone) {
    case MATERIAL_COLORLESS: return GColorFromRGB(238, 242, 240);
    case MATERIAL_SILVER:    return GColorFromRGB(168, 176, 179);
    case MATERIAL_DARK:      return GColorFromRGB(48, 51, 51);
    case MATERIAL_BROWN:     return GColorFromRGB(92, 70, 49);
    case MATERIAL_RED:       return GColorFromRGB(170, 48, 40);
    case MATERIAL_ORANGE:    return GColorFromRGB(197, 91, 42);
    case MATERIAL_YELLOW:    return GColorFromRGB(239, 202, 35);
    case MATERIAL_GREEN:     return GColorFromRGB(96, 153, 57);
    case MATERIAL_BLUE:      return GColorFromRGB(84, 148, 181);
    case MATERIAL_PURPLE:    return GColorFromRGB(103, 69, 139);
    case MATERIAL_GOLD:      return GColorFromRGB(193, 151, 57);
  }
  return GColorWhite;
}

static GColor element_ink(MaterialTone tone) {
  switch (tone) {
    case MATERIAL_DARK:
    case MATERIAL_BROWN:
    case MATERIAL_RED:
    case MATERIAL_BLUE:
    case MATERIAL_PURPLE:
      return GColorWhite;
    default:
      return GColorBlack;
  }
}

static void reset_colors_to_defaults(void) {
  s_background_color = GColorBlack;
  for (int index = 0; index < ELEMENT_COUNT; index++) {
    s_card_colors[index] = element_color(s_elements[index].tone).argb;
    s_text_colors[index] = element_ink(s_elements[index].tone).argb;
  }
}

static void load_colors(void) {
  reset_colors_to_defaults();
  if (persist_exists(PERSIST_KEY_BACKGROUND_COLOR)) {
    s_background_color.argb = (uint8_t)persist_read_int(PERSIST_KEY_BACKGROUND_COLOR);
  }
  if (persist_get_size(PERSIST_KEY_CARD_COLORS) == ELEMENT_COUNT) {
    persist_read_data(PERSIST_KEY_CARD_COLORS, s_card_colors, ELEMENT_COUNT);
  }
  if (persist_get_size(PERSIST_KEY_TEXT_COLORS) == ELEMENT_COUNT) {
    persist_read_data(PERSIST_KEY_TEXT_COLORS, s_text_colors, ELEMENT_COUNT);
  }
}

static void save_colors(void) {
  persist_write_int(PERSIST_KEY_BACKGROUND_COLOR, s_background_color.argb);
  persist_write_data(PERSIST_KEY_CARD_COLORS, s_card_colors, ELEMENT_COUNT);
  persist_write_data(PERSIST_KEY_TEXT_COLORS, s_text_colors, ELEMENT_COUNT);
}

static int element_hour(const struct tm *time) {
  if (clock_is_24h_style()) {
    return time->tm_hour;
  }
  return time->tm_hour % 12 == 0 ? 12 : time->tm_hour % 12;
}

// All movement goes through this one easing function. The two sides therefore
// share the same duration and every position in the curve, even on Emery.
static int eased_progress(void) {
  if (!s_is_animating) {
    return 1000;
  }

  uint32_t elapsed = clock_milliseconds() - s_animation_started_at;
  int linear = (int)((elapsed * 1000) / ANIMATION_DURATION_MS);
  if (linear > 1000) {
    linear = 1000;
  }

  // Cubic smoothstep: no abrupt start or stop, and no side-specific offsets.
  return (linear * linear * (3000 - (2 * linear))) / 1000000;
}

static void draw_card(GContext *ctx, GRect frame, const Element *element,
                      GColor fill, GColor ink) {
  const int inset = 4;
  // Emery's 200 px display creates 94 px wide cards; all other rectangular
  // targets create 66 px cards. The larger card receives a denser, larger
  // typography treatment without changing the established small-screen layout.
  const bool is_emery_layout = frame.size.w >= 90;
  const int symbol_y = frame.origin.y + (frame.size.h * 20) / 100;
  const int symbol_height = (frame.size.h * 39) / 100;
  const int name_y = is_emery_layout
      ? frame.origin.y + frame.size.h - 42
      : frame.origin.y + frame.size.h - 29;
  const int name_height = is_emery_layout ? 17 : 10;
  const int weight_y = is_emery_layout
      ? frame.origin.y + frame.size.h - 22
      : frame.origin.y + frame.size.h - 18;
  const int weight_height = is_emery_layout ? 20 : 18;
  GFont name_font = fonts_get_system_font(is_emery_layout
      ? FONT_KEY_GOTHIC_14_BOLD : FONT_KEY_GOTHIC_09);
  GFont weight_font = fonts_get_system_font(is_emery_layout
      ? FONT_KEY_GOTHIC_18_BOLD : FONT_KEY_GOTHIC_14_BOLD);
  graphics_context_set_fill_color(ctx, fill);
  graphics_fill_rect(ctx, frame, 0, GCornerNone);
  graphics_context_set_stroke_color(ctx, ink);
  graphics_draw_rect(ctx, frame);

  graphics_context_set_text_color(ctx, ink);
  graphics_draw_text(ctx, element->symbol,
                     fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD),
                     GRect(frame.origin.x + inset, symbol_y,
                           frame.size.w - (inset * 2), symbol_height),
                     GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  graphics_draw_text(ctx, element->name,
                     name_font,
                     GRect(frame.origin.x + inset, name_y,
                           frame.size.w - (inset * 2), name_height),
                     GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
  graphics_draw_text(ctx, element->weight,
                     weight_font,
                     GRect(frame.origin.x + inset, weight_y,
                           frame.size.w - (inset * 2), weight_height),
                     GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);

}

static void draw_card_number(GContext *ctx, GRect frame, int number) {
  char number_text[3];
  const bool is_emery_layout = frame.size.w >= 90;
  snprintf(number_text, sizeof(number_text), "%d", number);
  graphics_context_set_text_color(ctx, (GColor){ .argb = s_text_colors[number] });
  graphics_draw_text(ctx, number_text,
                     fonts_get_system_font(is_emery_layout
                         ? FONT_KEY_GOTHIC_24_BOLD : FONT_KEY_GOTHIC_18_BOLD),
                     GRect(frame.origin.x + 4,
                           frame.origin.y + (is_emery_layout ? 4 : 2),
                           frame.size.w - 8, is_emery_layout ? 26 : 18),
                     GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
}

static void draw_element_card(GContext *ctx, GRect frame, int number) {
  GColor fill = (GColor){ .argb = s_card_colors[number] };
  GColor ink = (GColor){ .argb = s_text_colors[number] };
  draw_card(ctx, frame, &s_elements[number], fill, ink);
  draw_card_number(ctx, frame, number);
}

static void draw_animated_side(GContext *ctx, GRect frame, int previous,
                               int current, bool is_changing, int progress) {
  if (!s_is_animating || !is_changing) {
    draw_element_card(ctx, frame, current);
    return;
  }

  // The outgoing entry travels down as the replacement crosses the same path
  // from above. Both columns receive this exact formula.
  int travel = frame.size.h + 6;
  GRect outgoing = frame;
  GRect incoming = frame;
  outgoing.origin.y += (travel * progress) / 1000;
  incoming.origin.y += -travel + ((travel * progress) / 1000);
  draw_element_card(ctx, outgoing, previous);
  draw_element_card(ctx, incoming, current);
}

static void face_layer_update(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  const int margin = 4;
  const int vertical_margin = 10;
  const int center_nudge = 1;
  int card_width = (bounds.size.w - (margin * 3)) / 2;
  int card_height = (card_width * 4) / 3;
  int progress = eased_progress();
  // Move each diagonal card inward by one pixel. This preserves the original
  // card sizes while narrowing the centre gap from four pixels to two.
  GRect hour_frame = GRect(margin + center_nudge, vertical_margin,
                           card_width, card_height);
  GRect minute_frame = GRect(bounds.size.w - card_width - margin - center_nudge,
                             bounds.size.h - card_height - vertical_margin,
                             card_width, card_height);

  graphics_context_set_fill_color(ctx, s_background_color);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  draw_animated_side(ctx, hour_frame, s_hour_before, s_hour_now,
                     s_hour_is_changing, progress);
  draw_animated_side(ctx, minute_frame, s_minute_before, s_minute_now,
                     s_minute_is_changing, progress);
}

static void animation_timer_callback(void *context) {
  (void)context;
  s_animation_timer = NULL;
  if (clock_milliseconds() - s_animation_started_at >= ANIMATION_DURATION_MS) {
    s_is_animating = false;
    s_hour_is_changing = false;
    s_minute_is_changing = false;
  } else {
    s_animation_timer = app_timer_register(ANIMATION_FRAME_MS,
                                            animation_timer_callback, NULL);
  }
  layer_mark_dirty(s_face_layer);
}

static void update_time(bool animate) {
  time_t now = time(NULL);
  struct tm *time = localtime(&now);
  int hour = element_hour(time);
  int minute = time->tm_min;

  if (!s_has_time) {
    s_hour_now = hour;
    s_minute_now = minute;
    s_hour_before = hour;
    s_minute_before = minute;
    s_has_time = true;
    layer_mark_dirty(s_face_layer);
    return;
  }

  s_hour_before = s_hour_now;
  s_minute_before = s_minute_now;
  s_hour_now = hour;
  s_minute_now = minute;
  s_hour_is_changing = hour != s_hour_before;
  s_minute_is_changing = minute != s_minute_before;

  if (animate && (s_hour_is_changing || s_minute_is_changing)) {
    s_is_animating = true;
    s_animation_started_at = clock_milliseconds();
    s_animation_timer = app_timer_register(ANIMATION_FRAME_MS,
                                            animation_timer_callback, NULL);
  } else {
    s_is_animating = false;
  }
  layer_mark_dirty(s_face_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  (void)tick_time;
  if (units_changed & MINUTE_UNIT) {
    update_time(true);
  }
}

static void inbox_received_handler(DictionaryIterator *iterator, void *context) {
  (void)context;
  Tuple *background = dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR);
  Tuple *cards = dict_find(iterator, MESSAGE_KEY_CARD_COLORS);
  Tuple *text = dict_find(iterator, MESSAGE_KEY_TEXT_COLORS);

  if (background) {
    s_background_color = GColorFromHEX((uint32_t)background->value->int32);
  }
  if (cards && cards->length == ELEMENT_COUNT) {
    memcpy(s_card_colors, cards->value->data, ELEMENT_COUNT);
  }
  if (text && text->length == ELEMENT_COUNT) {
    memcpy(s_text_colors, text->value->data, ELEMENT_COUNT);
  }
  save_colors();
  layer_mark_dirty(s_face_layer);
}

static void window_load(Window *window) {
  Layer *root_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(root_layer);
  s_face_layer = layer_create(bounds);
  layer_set_update_proc(s_face_layer, face_layer_update);
  layer_add_child(root_layer, s_face_layer);
}

static void window_unload(Window *window) {
  (void)window;
  layer_destroy(s_face_layer);
  s_face_layer = NULL;
}

static void init(void) {
  load_colors();
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);

  update_time(false);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit(void) {
  tick_timer_service_unsubscribe();
  app_message_deregister_callbacks();
  if (s_animation_timer) {
    app_timer_cancel(s_animation_timer);
  }
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
