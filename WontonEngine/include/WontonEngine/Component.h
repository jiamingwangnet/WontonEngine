#pragma once

namespace won
{
	class Entity;

	class Component
	{
	public:
		Component(Entity& entity);

		virtual void Init() = 0;
		virtual void Update() = 0;

	protected:
		Entity& entity;
	};
}