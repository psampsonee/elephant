#pragma once
#include "elephant_state.h"
#include "concrete_elephant_states.h"

class Elephant
{
public:
    Elephant();

    inline ElephantState* getCurrentState() const { return currentState; }

    void toggle();
    void setState(ElephantState& newState);
private:
    ElephantState* currentState;
};