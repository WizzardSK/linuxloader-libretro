/*
 * ALSA for the games on Linux, as the Windows build gives them (alsa2sdl.c
 * through elfLoader/alsa2sdlBridge.cpp): for the libretro core, SDL.
 *
 * Standalone, a game reaches the system's ALSA through the AppDir's
 * libasound, as before: these forward to it. For the core, the system's ALSA
 * is no place to play: Primeval Hunt's sound went past RetroArch on x86, and
 * under FEX on aarch64 there is no i386 ALSA configuration or plugin at all,
 * so the PCM device did not open, CRI's PSMALSA_Create returned nothing and
 * the game crashed on the null handle in PSMALSA_SetNotifyCallback.
 *
 * linuxloader.so is preloaded and has no symbol versions, so its definitions
 * take the games' versioned references (snd_pcm_open@ALSA_0.9) first.
 */
#ifdef __linux__

#include <dlfcn.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "alsa2sdl.h"
#include "../../../libretro/libretroBridge.h"

/* the system's function, of the same type as alsa2sdl.c's */
#define REAL(name) \
    static __typeof__(shared_##name) *real; \
    if (!real) \
        real = (__typeof__(shared_##name) *)dlsym(RTLD_NEXT, #name)

#define FORWARD(ret, name, params, args) \
    ret name params \
    { \
        if (libretroMode()) \
            return shared_##name args; \
        REAL(name); \
        return real ? real args : (ret)-38; /* -ENOSYS */ \
    }

#define FORWARD_VOID(name, params, args) \
    void name params \
    { \
        if (libretroMode()) \
        { \
            shared_##name args; \
            return; \
        } \
        REAL(name); \
        if (real) \
            real args; \
    }

FORWARD(int, snd_pcm_open, (snd_pcm_t **pcm, const char *name, int stream, int mode), (pcm, name, stream, mode))
FORWARD(int, snd_pcm_close, (snd_pcm_t *pcm), (pcm))

FORWARD(int, snd_pcm_hw_params_malloc, (snd_pcm_hw_params_t **ptr), (ptr))
FORWARD_VOID(snd_pcm_hw_params_free, (snd_pcm_hw_params_t *obj), (obj))
FORWARD(int, snd_pcm_hw_params_any, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params), (pcm, params))
FORWARD(int, snd_pcm_hw_params_set_access, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, int access), (pcm, params, access))
FORWARD(int, snd_pcm_hw_params_set_format, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, int val), (pcm, params, val))
FORWARD(int, snd_pcm_hw_params_set_channels, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, int val), (pcm, params, val))
FORWARD(int, snd_pcm_hw_params_set_rate_near, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir),
        (pcm, params, val, dir))
FORWARD(int, snd_pcm_hw_params_set_periods, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val, int dir),
        (pcm, params, val, dir))
FORWARD(int, snd_pcm_hw_params_set_buffer_size, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t val),
        (pcm, params, val))
FORWARD(int, snd_pcm_hw_params_set_buffer_size_near, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned long *val),
        (pcm, params, val))
FORWARD(int, snd_pcm_hw_params_set_period_size_near, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned long *val, int *dir),
        (pcm, params, val, dir))
FORWARD(int, snd_pcm_hw_params, (snd_pcm_t *pcm, snd_pcm_hw_params_t *params), (pcm, params))

FORWARD(int, snd_pcm_sw_params_malloc, (snd_pcm_sw_params_t **ptr), (ptr))
FORWARD_VOID(snd_pcm_sw_params_free, (snd_pcm_sw_params_t *obj), (obj))
FORWARD(int, snd_pcm_sw_params_current, (snd_pcm_t *pcm, snd_pcm_sw_params_t *params), (pcm, params))
FORWARD(int, snd_pcm_sw_params_set_avail_min, (snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val),
        (pcm, params, val))
FORWARD(int, snd_pcm_sw_params_set_start_threshold, (snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val),
        (pcm, params, val))
FORWARD(int, snd_pcm_sw_params_set_xfer_align, (snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val),
        (pcm, params, val))
FORWARD(int, snd_pcm_sw_params, (snd_pcm_t *pcm, snd_pcm_sw_params_t *params), (pcm, params))

FORWARD(int, snd_pcm_prepare, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_start, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_drop, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_resume, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_drain, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_delay, (snd_pcm_t *pcm, snd_pcm_sframes_t *delayp), (pcm, delayp))
FORWARD(snd_pcm_sframes_t, snd_pcm_writei, (snd_pcm_t *pcm, const void *buffer, unsigned long size), (pcm, buffer, size))
FORWARD(int, snd_pcm_avail_update, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_state, (snd_pcm_t *pcm), (pcm))
FORWARD(int, snd_pcm_format_width, (int format), (format))

const char *snd_strerror(int errnum)
{
    if (libretroMode())
        return shared_snd_strerror(errnum);
    REAL(snd_strerror);
    return real ? real(errnum) : "Unknown error";
}

#endif
