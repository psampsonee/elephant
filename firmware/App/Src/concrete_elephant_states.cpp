#include "elephant_state.h"
#include "concrete_elephant_states.h"

/**
 * @brief Prepare the board for "light sleep."
 * 
 * Completes the power-saving tasks necessary for the board to 
 * enter a light sleep state.  In this state, the buck converter
 * remains active to allow the STM32 to wake up from the tilt switch.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephLightSleep::enter(Elephant* elephant) {}

/**
 * @brief Trigger a transition from light sleep to playing a sound.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephLightSleep::toggle(Elephant* elephant) {
    elephant->setState(ElephPlaySound::getInstance());
}

/**
 * @brief Wake up the board from "light sleep."
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephLightSleep::exit(Elephant* elephant) {}

/**
 * @brief Get the static instance of the light sleep state.
 * 
 * @return ElephantState& Reference to the instance of the light sleep state. 
 */
ElephantState& ElephLightSleep::getInstance() {
    static ElephLightSleep singleton;
    return singleton;
}

/**
 * @brief Construct a new Light Sleep object from another Light Sleep object.
 * 
 * @param other Another Light Sleep object.
 */
ElephLightSleep::ElephLightSleep(const ElephLightSleep& other) {}

/**
 * @brief Prepare the board for "deep sleep."
 * 
 * Completes the power-saving tasks necessary for the board to 
 * enter a deep sleep state.  In this state, the buck converter
 * turns off to reduce power consumption.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephDeepSleep::enter(Elephant* elephant) {}

/**
 * @brief Trigger a transition from light sleep to deep sleep.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephDeepSleep::toggle(Elephant* elephant) {
    elephant->setState(ElephLightSleep::getInstance());
}

/**
 * @brief Wake up the board from "deep sleep."
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephDeepSleep::exit(Elephant* elephant) {}

/**
 * @brief Get the static instance of the deep sleep instance.
 * 
 * @return ElephantState& Reference to the instance of the deep sleep state. 
 */
ElephantState& ElephDeepSleep::getInstance() {
    static ElephDeepSleep singleton;
    return singleton;
}

/**
 * @brief Construct a new Deep Sleep object from another Deep Sleep object.
 * 
 * @param other Another Deep Sleep object.
 */
ElephDeepSleep::ElephDeepSleep(const ElephDeepSleep& other) {}

/**
 * @brief Prepare to play a sound.
 * 
 * Turn on the audio IC and do the tasks necessary before playing a sound.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephPlaySound::enter(Elephant* elephant) {}

/**
 * @brief Trigger a transition from playing a sound to deep sleep.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephPlaySound::toggle(Elephant* elephant) {
    elephant->setState(ElephDeepSleep::getInstance());
}

/**
 * @brief Cease sound-playing operations.
 *
 * Prepare the audio IC for shut down, and shut down the audio IC.
 * 
 * @param elephant The persistent object representing the physical system.
 */
void ElephPlaySound::exit(Elephant* elephant) {}

/**
 * @brief Get the static instance of the play sound state.
 * 
 * @return ElephantState& Reference to the instance of the play sound state. 
 */
ElephantState& ElephPlaySound::getInstance() {
    static ElephPlaySound singleton;
    return singleton;
}

/**
 * @brief Construct a new Play Sound object from another Play Sound object.
 * 
 * @param other Another Play Sound object.
 */
ElephPlaySound::ElephPlaySound(const ElephPlaySound& other) {}