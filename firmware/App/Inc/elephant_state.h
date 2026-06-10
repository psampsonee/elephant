#pragma once

class Elephant;

class ElephantState {
public:
    virtual void enter(Elephant* elephant) = 0;
    virtual void toggle(Elephant* elephant) = 0;
    virtual void exit(Elephant* elephant) = 0;
    virtual ~ElephantState() {}
};