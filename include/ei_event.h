/**
 *  @file ei_event.h
 *  @brief  Allows the binding and unbinding of callbacks to events.
 *
 *  \author
 *  Created by François Bérard on 30.12.11.
 *  Copyright 2011 Ensimag. All rights reserved.
 *
 */
#ifndef EI_EVENT_H
#define EI_EVENT_H

#include "ei_types.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief A string that can be attached to a widget.
 *        All widget have the tag of the name of their widget class, and the tag "all".
 */
typedef char* ei_tag_t;

/**
 * @brief A tag and a pointer to create a linked list.
 */
typedef struct ei_linked_tag_t {
  ei_tag_t tag;
  struct ei_linked_tag_t* next;
} ei_linked_tag_t;

/**
 * @brief The types of events.
 */
typedef enum {
  ei_ev_none = 0,  ///< No event, used on an un-initialized structure.
  ei_ev_app,       ///< An application event, created by \ref hw_event_post_app.
  ei_ev_display,   ///< A display / window event.
  ei_ev_timer,     ///< A timer event.
  ei_ev_keydown,   ///< A keyboard key has been pressed.
  ei_ev_keyup,     ///< A keyboard key has been released.
  ei_ev_keychar,   ///< A character was typed on the keyboard.

  /* event types at or below "ei_ev_mouse_buttondown" are mouse events, need picking. */
  ei_ev_mouse_buttondown,  ///< A mouse button has been pressed.
  ei_ev_mouse_buttonup,    ///< A mouse button has been released.
  ei_ev_mouse_move,        ///< The mouse has moved.

  /* event types at or below "ei_ev_touch_begin" are touch events, need picking. */
  ei_ev_touch_begin,  ///< The touch input device registered a new touch.
  ei_ev_touch_end,    ///< A touch ended.
  ei_ev_touch_move,   ///< The position of a touch changed.

  ei_ev_last  ///< Last event type, its value is the number of event types.
} ei_eventtype_t;

/**
 * @brief The modifier keys (shift, alt, etc.)
 */
typedef enum {
  ei_mod_shift = 0x00001,       ///< The "shift" key.
  ei_mod_ctrl = 0x00002,        ///< The "control" key.
  ei_mod_alt = 0x00004,         ///< The "alternate" key at the left of the space bar.
  ei_mod_meta_left = 0x00008,   ///< The "meta" (command) key at the left of the space bar.
  ei_mod_meta_right = 0x00010,  ///< The "meta" (command) key at the right of the space bar.
  ei_mod_alt_grad = 0x00040     ///< The "alternate" key at the right of the space bar.
} ei_modifier_key_t;

/**
 * @brief A bitfield indicating which of the modifier keys are currently pressed.
 */
typedef uint32_t ei_modifier_mask_t;

/**
 * @brief Tests is a modifier key is currently pressed, according to a bitfield.
 *
 * @param mask      The bitfield.
 * @param modifier  The modifier key that is tested.
 *
 * @return      EI_TRUE is this modifier key is currently pressed, EI_FALSE otherwise.
 */
static inline ei_bool_t ei_has_modifier(ei_modifier_mask_t mask,
                                        ei_modifier_key_t modifier)
{
  return (ei_bool_t)(mask == modifier);
}

/**
 * @brief The event parameter for display-related event types.
 */
typedef struct {
  ei_bool_t resized;      ///< The window has been resized.
  ei_bool_t closed;       ///< The close button of the window has been pressed.
  ei_bool_t switched_out; ///< The window is no longer active.
  ei_bool_t switched_in;  ///< The window is active once again.
} ei_display_event_t;

/**
 * @brief The event parameter for keyboard-related event types.
 */
typedef struct {
  int key_sym;  ///< The keyboard key symbol (see \ref allegro5/keycodes.h).
  int unichar;  ///< For \ref ei_ev_keychar, a Unicode code point (character).
  ei_modifier_mask_t modifier_mask;  ///< The state of the modifier keys at the time of the event.
} ei_key_event_t;

/**
 * @brief The event parameter for mouse-related event types.
 */
typedef struct {
  ei_point_t where;   ///< Where the mouse pointer was at the time of the event.
  int button_number;  ///< The number of the button that was pressed or released.
  /// Only valid for \ref ei_ev_mouse_buttondown or \ref ei_ev_mouse_buttonup event types.
} ei_mouse_event_t;

/**
 * @brief The event parameter for mouse-related event types.
 */
typedef struct {
  ei_point_t where;  ///< Where the touch was at the time of the event.
  ei_point_t speed;  ///< Movement speed in pixels.
  int touch_id;      ///< An identifier for this touch. If supported by the device
  /// it will stay the same for events from the same finger until the touch ends.
  ei_bool_t primary; ///< Whether this is the only/first touch or an additional touch.
} ei_touch_event_t;

/**
 * @brief The event parameter for application defined event types.
 */
typedef struct { void* user_param; } ei_app_event_t;

/**
 * @brief Describes an event.
 */
typedef struct ei_event_t {
  ei_eventtype_t type;       ///< The type of the event.
  union {
    ei_display_event_t display;  ///< Event parameter for display-realted events (see \ref ei_display_event_t).
    ei_key_event_t key;          ///< Event parameters for keyboard-related events (see \ref ei_key_event_t).
    ei_mouse_event_t mouse;      ///< Event parameters for mouse-related events (see \ref ei_mouse_event_t).
    ei_touch_event_t touch;      ///< Event parameters for touch-related events (see \ref ei_touch_event_t).
    ei_app_event_t application;  ///< Event parameters for application-related events (see \ref ei_app_event_t).
  } param;
} ei_event_t;

#ifdef __cplusplus
}
#endif

#endif
