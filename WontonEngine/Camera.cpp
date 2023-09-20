#include "include/WontonEngine/Components/Camera.h"

won::cmp::Camera::Camera(Entity& entity, float near, float far, float fov, float aspect)
	: Component{ entity }, near{ near }, far{ far }, fov{ fov }, aspect{ aspect }, projType{ ProjectionType::Perspective }, viewRect{ {0.0f, 0.0f}, 0.0f, 0.0f }
{

}

won::cmp::Camera::Camera(Entity& entity, float near, float far, Rect viewRect)
	: Component{entity}, near{ near }, far{ far }, viewRect{viewRect}, projType{ ProjectionType::Perspective }
{}
