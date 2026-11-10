/*
 * linuxloader (Sega Lindbergh) libretro core - Core Options v2
 *
 * The English texts are edited here; the translations in
 * libretro_core_options_intl.h come from Crowdin (intl/).
 */

#ifndef LIBRETRO_CORE_OPTIONS_H__
#define LIBRETRO_CORE_OPTIONS_H__

#include <stdlib.h>
#include <string.h>

#include "libretro.h"

#ifndef HAVE_NO_LANGEXTRA
#include "libretro_core_options_intl.h"
#endif

/*
 ********************************
 * VERSION: 2.0
 ********************************
 *
 * - 2.0: Add support for core options v2 interface
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_ENGLISH */

/* Default language:
 * - All other languages must include the same keys and values
 * - Will be used as a fallback in the event that frontend language
 *   is not available
 * - Will be used as a fallback for any missing entries in
 *   frontend language definition
 * - Translations live in libretro_core_options_intl.h, which is
 *   generated from Crowdin - edit only the English texts here
 */

struct retro_core_option_v2_category option_cats_us[] = {
    {"video", "Video", "The resolution the games render at, and widescreen."},
    {"input", "Input", "The guns, steering and force feedback."},
    {"audio", "Audio", "How the sound reaches RetroArch."},
    {"debug", "Debug (Restart)", "linuxloader.ini's settings, set over the game's linuxloader.ini. Per Game, Unchanged and Detected leave the loader's own."},
    {NULL, NULL, NULL},
};

struct retro_core_option_v2_definition option_defs_us[] = {
    {"linuxloader_resolution", "Resolution (Restart)", NULL,
     "The width and height the games the loader can patch render at. Native keeps the linuxloader.ini's. Every frame goes through system memory to RetroArch, so the highest ones cost speed. Warning: setting this option above your display's resolution will break some games or make them unable to launch.",
     NULL, "video",
     {{"native", "Native"}, {"1280x720", NULL}, {"1920x1080", NULL}, {"2560x1440", NULL}, {"3840x2160", NULL}, {"5120x2880", NULL}, {NULL, NULL}},
     "native"},
    {"linuxloader_force_widescreen", "Force 16:9 (Restart)", NULL,
     "Makes every game run in widescreen. May break or stretch some games.",
     NULL, "video",
     {{"disabled", NULL}, {"enabled", NULL}, {NULL, NULL}},
     "disabled"},
    {"linuxloader_test_buttons", "Service and Test Buttons", NULL,
     "L3 as the cabinet's Service button and R3 as its Test button, on both pads. Disabled keeps them from being pressed by accident; the keyboard's S and T stay.",
     NULL, "input",
     {{"enabled", NULL}, {"disabled", NULL}, {NULL, NULL}},
     "enabled"},
    {"linuxloader_gun_aim", "Gun Aim", NULL,
     "What aims in the gun games, for both players. Analog Stick: each player's left stick (or D-pad) moves the aim, R2 fires, R reloads, L2 is the gun's button, L shakes the gun in The House of the Dead 4. Too Spicy: L2 reloads, L and R are the pedals. Ghost Squad Evolution: L2 is Action, L is Change. Primeval Hunt: L2 pumps. Mouse: RetroArch's light gun on each player's port, which follows the mouse; left button fires, right reloads, middle is the gun's button, aiming off the picture reloads too. Ghost Squad Evolution: right is Action, middle is Change. The House of the Dead 4: right is the gun's button, middle shakes. Too Spicy: middle is the left pedal, right the right one. Primeval Hunt: middle pumps, and the touch screen takes the mouse's clicks.",
     NULL, "input",
     {{"stick", "Analog Stick"}, {"mouse", "Mouse"}, {NULL, NULL}},
     "stick"},
    {"linuxloader_gun_sensitivity", "Gun Pointer Sensitivity", NULL,
     "How fast the sticks move the aim with Gun Aim on Analog Stick, as fast across as up and down; at 100% a full tilt crosses the picture's height in about a second. The mouse aims where it points.",
     NULL, "input",
     {{"50", "50%"}, {"60", "60%"}, {"70", "70%"}, {"80", "80%"}, {"90", "90%"}, {"100", "100%"}, {"110", "110%"},
      {"120", "120%"}, {"130", "130%"}, {"140", "140%"}, {"150", "150%"}, {"160", "160%"}, {"170", "170%"},
      {"180", "180%"}, {"190", "190%"}, {"200", "200%"}, {NULL, NULL}},
     "100"},
    {"linuxloader_crosshair", "Crosshair", NULL,
     "The gun games' crosshairs drawn over the picture: blue for player 1, red for player 2, which shows once that player aims.",
     NULL, "input",
     {{"enabled", NULL}, {"disabled", NULL}, {NULL, NULL}},
     "enabled"},
    {"linuxloader_ffb_rumble", "Force Feedback to Rumble", NULL,
     "The drive board's force feedback as rumble on player 1's pad, in the driving games: OutRun 2 SP SDX, Initial D 4 and 5, Hummer. Needs the drive board emulated, which Debug > EMULATE_DRIVEBOARD's Per Game does for those games.",
     NULL, "input",
     {{"enabled", NULL}, {"disabled", NULL}, {NULL, NULL}},
     "enabled"},
    {"linuxloader_steering", "Steering Response", NULL,
     "Linear: the left stick's X as it is. Logarithmic: on a curve with less of the turn around the centre and steeper towards the ends, as the Sega System 32 racers' dip switch has it, so a stick steers less twitchily. Its shape is set by Steering Inner Zone and Steering Effect.",
     NULL, "input",
     {{"linear", "Linear"}, {"logarithmic", "Logarithmic"}, {NULL, NULL}},
     "linear"},
    {"linuxloader_steering_inner", "Steering Inner Zone", NULL,
     "With logarithmic steering: the share of the turn at the centre. Lower is calmer around the centre. OutRun 2 plays well at 20 with Square, Initial D at 50 with Cubic.",
     NULL, "input",
     {{"5", "5%"}, {"10", "10%"}, {"15", "15%"}, {"20", "20%"}, {"25", "25%"}, {"30", "30%"}, {"35", "35%"}, {"40", "40%"}, {"45", "45%"}, {"50", "50%"}, {NULL, NULL}},
     "25"},
    {"linuxloader_steering_effect", "Steering Effect", NULL,
     "With logarithmic steering: how the rest of the turn rises towards full lock. Cubic is strong, Square weak.",
     NULL, "input",
     {{"cubic", "Cubic (Strong)"}, {"square", "Square (Weak)"}, {NULL, NULL}},
     "cubic"},
    {"linuxloader_audio_thread", "Audio Thread (Restart)", NULL,
     "Hands the sound to RetroArch's audio thread as the loader mixes it, which keeps its pace where a game drops frames. OutRun 2 SP's announcer is lost with it.",
     NULL, "audio",
     {{"enabled", NULL}, {"disabled", NULL}, {NULL, NULL}},
     "enabled"},
    {"linuxloader_debug_freeplay", "FREEPLAY", NULL, NULL, NULL, "debug",
     {{"default", "Unchanged"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_test_mode", "TEST_MODE", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_emulate_driveboard", "EMULATE_DRIVEBOARD", NULL, NULL, NULL, "debug",
     {{"default", "Per Game"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_emulate_motionboard", "EMULATE_MOTIONBOARD", NULL, NULL, NULL, "debug",
     {{"default", "Per Game"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_emulate_rideboard", "EMULATE_RIDEBOARD", NULL, NULL, NULL, "debug",
     {{"default", "Per Game"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_emulate_hw210_cardreader", "EMULATE_HW210_CARDREADER", NULL, NULL, NULL, "debug",
     {{"default", "Per Game"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_emulate_id_cardreader", "EMULATE_ID_CARDREADER", NULL, NULL, NULL, "debug",
     {{"default", "Per Game"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_emulate_touchscreen", "EMULATE_TOUCHSCREEN", NULL, NULL, NULL, "debug",
     {{"default", "Per Game"}, {"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_region", "REGION", NULL, NULL, NULL, "debug",
     {{"JP", "Japan"}, {"US", "US"}, {"EX", "Export"}, {NULL, NULL}},
     "EX"},
    {"linuxloader_debug_lindbergh_colour", "LINDBERGH_COLOUR", NULL, NULL, NULL, "debug",
     {{"YELLOW", "Yellow"}, {"RED", "Red"}, {"BLUE", "Blue"}, {"SILVER", "Silver"}, {"REDEX", "RedEX"}, {NULL, NULL}},
     "YELLOW"},
    {"linuxloader_debug_debug_msgs", "DEBUG_MSGS", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_boost_render_res", "BOOST_RENDER_RES", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    {"linuxloader_debug_hummer_flicker_fix", "HUMMER_FLICKER_FIX", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    {"linuxloader_debug_lgj_render_with_mesa", "LGJ_RENDER_WITH_MESA", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    {"linuxloader_debug_disable_builtin_font", "DISABLE_BUILTIN_FONT", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_disable_builtin_logos", "DISABLE_BUILTIN_LOGOS", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_cpu_freq_ghz", "CPU_FREQ_GHZ", NULL, NULL, NULL, "debug",
     {{"default", "Detected"}, {"1.0", "1.0 GHz"}, {"1.5", "1.5 GHz"}, {"2.0", "2.0 GHz"}, {"2.5", "2.5 GHz"}, {"3.0", "3.0 GHz"}, {"3.5", "3.5 GHz"}, {"4.0", "4.0 GHz"}, {"4.5", "4.5 GHz"}, {"5.0", "5.0 GHz"}, {NULL, NULL}},
     "default"},
    {"linuxloader_debug_skip_outrun_cabinet_check", "SKIP_OUTRUN_CABINET_CHECK", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_id_steering_reduction_percentage", "ID_STEERING_REDUCTION_PERCENTAGE", NULL, NULL, NULL, "debug",
     {{"0", "0%"}, {"5", "5%"}, {"10", "10%"}, {"15", "15%"}, {"20", "20%"}, {"25", "25%"}, {"30", "30%"}, {"35", "35%"}, {"40", "40%"}, {"45", "45%"}, {"50", "50%"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_id5_chinese_language", "ID5_CHINESE_LANGUAGE", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_harley_analog_remap", "HARLEY_ANALOG_REMAP", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_mj4_enabled_all_the_time", "MJ4_ENABLED_ALL_THE_TIME", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_rambo_guns_switch", "RAMBO_GUNS_SWITCH", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_primeval_hunt_screen_mode", "PRIMEVAL_HUNT_SCREEN_MODE", NULL, NULL, NULL, "debug",
     /* "1" itself, not the loader's default: with the key left out, Primeval Hunt opened on two screens (NNshi) */
     {{"0", "0"}, {"1", "1"}, {"2", "2"}, {"3", "3"}, {NULL, NULL}},
     "1"},
    {"linuxloader_debug_primeval_hunt_test_screen_single", "PRIMEVAL_HUNT_TEST_SCREEN_SINGLE", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    {"linuxloader_debug_id_cardfile_autoload", "ID_CARDFILE_AUTOLOAD", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    {"linuxloader_debug_enable_crosshairs", "ENABLE_CROSSHAIRS", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_gsevo_crosshair_always_on", "GSEVO_CROSSHAIR_ALWAYS_ON", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_gsevo_crosshair_always_off", "GSEVO_CROSSHAIR_ALWAYS_OFF", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "0"},
    {"linuxloader_debug_enable_network_patches", "ENABLE_NETWORK_PATCHES", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    /* The core's own (eepromSettings.c): After Burner Climax does not start
     * on a Deluxe cabinet with motion on, which it is out of the box, so on
     * by default (NNshi) */
    {"linuxloader_debug_aburner_motion_off", "ABURNER_MOTION_OFF", NULL, NULL, NULL, "debug",
     {{"0", "Off"}, {"1", "On"}, {NULL, NULL}},
     "1"},
    {NULL, NULL, NULL, NULL, NULL, NULL, {{NULL, NULL}}, NULL},
};
struct retro_core_options_v2 options_us = {
   option_cats_us,
   option_defs_us
};

/*
 ********************************
 * Language Mapping
 ********************************
*/

#ifndef HAVE_NO_LANGEXTRA
struct retro_core_options_v2 *options_intl[RETRO_LANGUAGE_LAST] = {
   &options_us,       /* RETRO_LANGUAGE_ENGLISH */
   &options_ja,       /* RETRO_LANGUAGE_JAPANESE */
   &options_fr,       /* RETRO_LANGUAGE_FRENCH */
   &options_es,       /* RETRO_LANGUAGE_SPANISH */
   &options_de,       /* RETRO_LANGUAGE_GERMAN */
   &options_it,       /* RETRO_LANGUAGE_ITALIAN */
   &options_nl,       /* RETRO_LANGUAGE_DUTCH */
   &options_pt_br,    /* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */
   &options_pt_pt,    /* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */
   &options_ru,       /* RETRO_LANGUAGE_RUSSIAN */
   &options_ko,       /* RETRO_LANGUAGE_KOREAN */
   &options_cht,      /* RETRO_LANGUAGE_CHINESE_TRADITIONAL */
   &options_chs,      /* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */
   &options_eo,       /* RETRO_LANGUAGE_ESPERANTO */
   &options_pl,       /* RETRO_LANGUAGE_POLISH */
   &options_vn,       /* RETRO_LANGUAGE_VIETNAMESE */
   &options_ar,       /* RETRO_LANGUAGE_ARABIC */
   &options_el,       /* RETRO_LANGUAGE_GREEK */
   &options_tr,       /* RETRO_LANGUAGE_TURKISH */
   &options_sk,       /* RETRO_LANGUAGE_SLOVAK */
   &options_fa,       /* RETRO_LANGUAGE_PERSIAN */
   &options_he,       /* RETRO_LANGUAGE_HEBREW */
   &options_ast,      /* RETRO_LANGUAGE_ASTURIAN */
   &options_fi,       /* RETRO_LANGUAGE_FINNISH */
   &options_id,       /* RETRO_LANGUAGE_INDONESIAN */
   &options_sv,       /* RETRO_LANGUAGE_SWEDISH */
   &options_uk,       /* RETRO_LANGUAGE_UKRAINIAN */
   &options_cs,       /* RETRO_LANGUAGE_CZECH */
   &options_val,      /* RETRO_LANGUAGE_CATALAN_VALENCIA */
   &options_ca,       /* RETRO_LANGUAGE_CATALAN */
   &options_en,       /* RETRO_LANGUAGE_BRITISH_ENGLISH */
   &options_hu,       /* RETRO_LANGUAGE_HUNGARIAN */
   &options_be,       /* RETRO_LANGUAGE_BELARUSIAN */
   &options_gl,       /* RETRO_LANGUAGE_GALICIAN */
   &options_no,       /* RETRO_LANGUAGE_NORWEGIAN */
   &options_ga,       /* RETRO_LANGUAGE_IRISH */
};
#endif

/*
 ********************************
 * Functions
 ********************************
*/

/* Handles configuration/setting of core options.
 * Should be called as early as possible - ideally inside
 * retro_set_environment(), and no later than retro_load_game()
 * > We place the function body in the header to avoid the
 *   necessity of adding more .c files (i.e. want this to
 *   be as painless as possible for core devs)
 */

static inline void libretro_set_core_options(retro_environment_t environ_cb,
      bool *categories_supported)
{
   unsigned version  = 0;
#ifndef HAVE_NO_LANGEXTRA
   unsigned language = 0;
#endif

   if (!environ_cb || !categories_supported)
      return;

   *categories_supported = false;

   if (!environ_cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &version))
      version = 0;

   if (version >= 2)
   {
#ifndef HAVE_NO_LANGEXTRA
      struct retro_core_options_v2_intl core_options_intl;

      core_options_intl.us    = &options_us;
      core_options_intl.local = NULL;

      if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
          (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH))
         core_options_intl.local = options_intl[language];

      *categories_supported = environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_V2_INTL,
            &core_options_intl);
#else
      *categories_supported = environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_V2,
            &options_us);
#endif
   }
   else
   {
      size_t i, j;
      size_t option_index              = 0;
      size_t num_options               = 0;
      struct retro_core_option_definition
            *option_v1_defs_us         = NULL;
#ifndef HAVE_NO_LANGEXTRA
      size_t num_options_intl          = 0;
      struct retro_core_option_v2_definition
            *option_defs_intl          = NULL;
      struct retro_core_option_definition
            *option_v1_defs_intl       = NULL;
      struct retro_core_options_intl
            core_options_v1_intl;
#endif
      struct retro_variable *variables = NULL;
      char **values_buf                = NULL;

      /* Determine total number of options */
      while (true)
      {
         if (option_defs_us[num_options].key)
            num_options++;
         else
            break;
      }

      if (version >= 1)
      {
         /* Allocate US array */
         option_v1_defs_us = (struct retro_core_option_definition *)
               calloc(num_options + 1, sizeof(struct retro_core_option_definition));

         /* Copy parameters from option_defs_us array */
         for (i = 0; i < num_options; i++)
         {
            struct retro_core_option_v2_definition *option_def_us = &option_defs_us[i];
            struct retro_core_option_value *option_values         = option_def_us->values;
            struct retro_core_option_definition *option_v1_def_us = &option_v1_defs_us[i];
            struct retro_core_option_value *option_v1_values      = option_v1_def_us->values;

            option_v1_def_us->key           = option_def_us->key;
            option_v1_def_us->desc          = option_def_us->desc;
            option_v1_def_us->info          = option_def_us->info;
            option_v1_def_us->default_value = option_def_us->default_value;

            /* Values must be copied individually... */
            while (option_values->value)
            {
               option_v1_values->value = option_values->value;
               option_v1_values->label = option_values->label;

               option_values++;
               option_v1_values++;
            }
         }

#ifndef HAVE_NO_LANGEXTRA
         if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
             (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH) &&
             options_intl[language])
            option_defs_intl = options_intl[language]->definitions;

         if (option_defs_intl)
         {
            /* Determine number of intl options */
            while (true)
            {
               if (option_defs_intl[num_options_intl].key)
                  num_options_intl++;
               else
                  break;
            }

            /* Allocate intl array */
            option_v1_defs_intl = (struct retro_core_option_definition *)
                  calloc(num_options_intl + 1, sizeof(struct retro_core_option_definition));

            /* Copy parameters from option_defs_intl array */
            for (i = 0; i < num_options_intl; i++)
            {
               struct retro_core_option_v2_definition *option_def_intl = &option_defs_intl[i];
               struct retro_core_option_value *option_values           = option_def_intl->values;
               struct retro_core_option_definition *option_v1_def_intl = &option_v1_defs_intl[i];
               struct retro_core_option_value *option_v1_values        = option_v1_def_intl->values;

               option_v1_def_intl->key           = option_def_intl->key;
               option_v1_def_intl->desc          = option_def_intl->desc;
               option_v1_def_intl->info          = option_def_intl->info;
               option_v1_def_intl->default_value = option_def_intl->default_value;

               /* Values must be copied individually... */
               while (option_values->value)
               {
                  option_v1_values->value = option_values->value;
                  option_v1_values->label = option_values->label;

                  option_values++;
                  option_v1_values++;
               }
            }
         }

         core_options_v1_intl.us    = option_v1_defs_us;
         core_options_v1_intl.local = option_v1_defs_intl;

         environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_INTL, &core_options_v1_intl);
#else
         environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, option_v1_defs_us);
#endif
      }
      else
      {
         /* Allocate arrays */
         variables  = (struct retro_variable *)calloc(num_options + 1,
               sizeof(struct retro_variable));
         values_buf = (char **)calloc(num_options, sizeof(char *));

         if (!variables || !values_buf)
            goto error;

         /* Copy parameters from option_defs_us array */
         for (i = 0; i < num_options; i++)
         {
            const char *key                        = option_defs_us[i].key;
            const char *desc                       = option_defs_us[i].desc;
            const char *default_value              = option_defs_us[i].default_value;
            struct retro_core_option_value *values = option_defs_us[i].values;
            size_t buf_len                         = 3;
            size_t default_index                   = 0;

            values_buf[i] = NULL;

            if (desc)
            {
               size_t num_values = 0;

               /* Determine number of values */
               while (true)
               {
                  if (values[num_values].value)
                  {
                     /* Check if this is the default value */
                     if (default_value)
                        if (strcmp(values[num_values].value, default_value) == 0)
                           default_index = num_values;

                     buf_len += strlen(values[num_values].value);
                     num_values++;
                  }
                  else
                     break;
               }

               /* Build values string */
               if (num_values > 0)
               {
                  buf_len += num_values - 1;
                  buf_len += strlen(desc);

                  values_buf[i] = (char *)calloc(buf_len, sizeof(char));
                  if (!values_buf[i])
                     goto error;

                  strcpy(values_buf[i], desc);
                  strcat(values_buf[i], "; ");

                  /* Default value goes first */
                  strcat(values_buf[i], values[default_index].value);

                  /* Add remaining values */
                  for (j = 0; j < num_values; j++)
                  {
                     if (j != default_index)
                     {
                        strcat(values_buf[i], "|");
                        strcat(values_buf[i], values[j].value);
                     }
                  }
               }
            }

            variables[option_index].key   = key;
            variables[option_index].value = values_buf[i];
            option_index++;
         }

         /* Set variables */
         environ_cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
      }

error:
      /* Clean up */

      if (option_v1_defs_us)
      {
         free(option_v1_defs_us);
         option_v1_defs_us = NULL;
      }

#ifndef HAVE_NO_LANGEXTRA
      if (option_v1_defs_intl)
      {
         free(option_v1_defs_intl);
         option_v1_defs_intl = NULL;
      }
#endif

      if (values_buf)
      {
         for (i = 0; i < num_options; i++)
         {
            if (values_buf[i])
            {
               free(values_buf[i]);
               values_buf[i] = NULL;
            }
         }

         free(values_buf);
         values_buf = NULL;
      }

      if (variables)
      {
         free(variables);
         variables = NULL;
      }
   }
}

#ifdef __cplusplus
}
#endif

#endif
