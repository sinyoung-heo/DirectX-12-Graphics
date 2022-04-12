#include "framework.h"
#include "IComponent.h"

IComponent::IComponent(const IComponent& rhs)
	: isClone_(true)
{
}
