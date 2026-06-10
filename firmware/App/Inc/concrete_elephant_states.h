#pragma once
#include "elephant_state.h"
#include "elephant.h"

class ElephLightSleep : public ElephantState
{
public:
    void enter(Elephant* elephant);
    void toggle(Elephant* elephant);
    void exit(Elephant* elephant);
    static ElephantState& getInstance();

private:
    ElephLightSleep() {}
    ElephLightSleep(const ElephLightSleep& other);
    ElephLightSleep& operator=(const ElephLightSleep& other);
};


class ElephDeepSleep : public ElephantState
{
public:
    void enter(Elephant* elephant);
    void toggle(Elephant* elephant);
    void exit(Elephant* elephant);
    static ElephantState& getInstance();

private:
    ElephDeepSleep() {}
    ElephDeepSleep(const ElephDeepSleep& other);
    ElephDeepSleep& operator=(const ElephDeepSleep& other);
};

class ElephPlaySound : public ElephantState
{
public:
    void enter(Elephant* elephant);
    void toggle(Elephant* elephant);
    void exit(Elephant* elephant);
    static ElephantState& getInstance();

private:
    ElephPlaySound() {}
    ElephPlaySound(const ElephPlaySound& other);
    ElephPlaySound& operator=(const ElephPlaySound& other);
};