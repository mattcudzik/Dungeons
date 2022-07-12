#include "State.h"
State::State(): updatable(true), drawable(true) {}

bool State::IsDrawable()
{
	return this->drawable;
}
bool State::IsUpdatable()
{
	return this->updatable;
}
void State::SetDrawable(bool cond)
{
	this->drawable = cond;
}
void State::SetUpdatable(bool cond)
{
	this->updatable = cond;
}