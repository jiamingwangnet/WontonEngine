#pragma once

namespace won
{
	class Game;

	class Scene
	{
	public:
		virtual void Init(Game& game) = 0;
	};
}