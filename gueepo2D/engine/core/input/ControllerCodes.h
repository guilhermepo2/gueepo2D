#pragma once

// from SDL_GameController.h
namespace gueepo {
    typedef enum {
        CONTROLLER_BUTTON_INVALID = -1,
        CONTROLLER_BUTTON_A,
        CONTROLLER_BUTTON_B,
        CONTROLLER_BUTTON_X,
        CONTROLLER_BUTTON_Y,
        CONTROLLER_BUTTON_BACK,
        CONTROLLER_BUTTON_GUIDE,
        CONTROLLER_BUTTON_START,
        CONTROLLER_BUTTON_LEFTSTICK,
        CONTROLLER_BUTTON_RIGHTSTICK,
        CONTROLLER_BUTTON_LEFTSHOULDER,
        CONTROLLER_BUTTON_RIGHTSHOULDER,
        CONTROLLER_BUTTON_DPAD_UP,
        CONTROLLER_BUTTON_DPAD_DOWN,
        CONTROLLER_BUTTON_DPAD_LEFT,
        CONTROLLER_BUTTON_DPAD_RIGHT,
        CONTROLLER_BUTTON_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
        CONTROLLER_BUTTON_PADDLE1,  /* Xbox Elite paddle P1 */
        CONTROLLER_BUTTON_PADDLE2,  /* Xbox Elite paddle P3 */
        CONTROLLER_BUTTON_PADDLE3,  /* Xbox Elite paddle P2 */
        CONTROLLER_BUTTON_PADDLE4,  /* Xbox Elite paddle P4 */
        CONTROLLER_BUTTON_TOUCHPAD, /* PS4/PS5 touchpad button */
        CONTROLLER_BUTTON_MAX
    } ControllerCode;
}