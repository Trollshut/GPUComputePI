#pragma once
class UIElement
{
public:
	virtual ~UIElement() = default;
	virtual void OnImGuiRender() = 0;
};
