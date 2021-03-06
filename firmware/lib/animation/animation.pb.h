/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.2 */

#ifndef PB_ANIMATION_PB_H_INCLUDED
#define PB_ANIMATION_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _AnimationArg {
    uint32_t duration;
    uint32_t animation_id;
    uint32_t color_id;
    uint32_t speed;
    uint32_t brightness;
} AnimationArg;

typedef struct _IdleAnimationArg {
    uint32_t animation_id;
    uint32_t color_id;
    uint32_t speed;
    uint32_t brightness;
} IdleAnimationArg;


/* Initializer values for message structs */
#define AnimationArg_init_default                {0, 0, 0, 0, 0}
#define IdleAnimationArg_init_default            {0, 0, 0, 0}
#define AnimationArg_init_zero                   {0, 0, 0, 0, 0}
#define IdleAnimationArg_init_zero               {0, 0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define AnimationArg_duration_tag                1
#define AnimationArg_animation_id_tag            2
#define AnimationArg_color_id_tag                3
#define AnimationArg_speed_tag                   4
#define AnimationArg_brightness_tag              5
#define IdleAnimationArg_animation_id_tag        2
#define IdleAnimationArg_color_id_tag            3
#define IdleAnimationArg_speed_tag               4
#define IdleAnimationArg_brightness_tag          5

/* Struct field encoding specification for nanopb */
#define AnimationArg_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   duration,          1) \
X(a, STATIC,   SINGULAR, UINT32,   animation_id,      2) \
X(a, STATIC,   SINGULAR, UINT32,   color_id,          3) \
X(a, STATIC,   SINGULAR, UINT32,   speed,             4) \
X(a, STATIC,   SINGULAR, UINT32,   brightness,        5)
#define AnimationArg_CALLBACK NULL
#define AnimationArg_DEFAULT NULL

#define IdleAnimationArg_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   animation_id,      2) \
X(a, STATIC,   SINGULAR, UINT32,   color_id,          3) \
X(a, STATIC,   SINGULAR, UINT32,   speed,             4) \
X(a, STATIC,   SINGULAR, UINT32,   brightness,        5)
#define IdleAnimationArg_CALLBACK NULL
#define IdleAnimationArg_DEFAULT NULL

extern const pb_msgdesc_t AnimationArg_msg;
extern const pb_msgdesc_t IdleAnimationArg_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define AnimationArg_fields &AnimationArg_msg
#define IdleAnimationArg_fields &IdleAnimationArg_msg

/* Maximum encoded size of messages (where known) */
#define AnimationArg_size                        30
#define IdleAnimationArg_size                    24

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
