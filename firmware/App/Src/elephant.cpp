#include "elephant.h"

Elephant::Elephant()
{
    this->setState(ElephLightSleep::getInstance());
}

void Elephant::toggle()
{
    currentState->toggle(this);
}

void Elephant::setState(ElephantState& newState)
{
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}