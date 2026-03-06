#include "IRender.h"

int IRender::GetWidth() const
{
	return this->width;
}

int IRender::GetHeight() const
{
	return this->height;
}

void IRender::SetWidth(int width)
{
	this->width = width;
}

void IRender::SetHeight(int height)
{
	this->height = height;
}

