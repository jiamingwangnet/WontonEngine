#pragma once

#include "../Components/Camera.h"
#include "../Entity.h"
#include "../Math/Crypto.h"
#include "Renderable.h"
#include <unordered_map>
#include <array>
#include "Lighting.h"
#include <utility>
#include "../ThreadPool.h"

#define M_WON_LIGHTS "won_Lights"
#define WON_LIGHTS_UNIFORMS(n) M_WON_LIGHTS "[" #n "].type", \
							   M_WON_LIGHTS "[" #n "].position", \
							   M_WON_LIGHTS "[" #n "].direction",\
							   M_WON_LIGHTS "[" #n "].color", \
							   M_WON_LIGHTS "[" #n "].ambientStrength", \
							   M_WON_LIGHTS "[" #n "].linear", \
							   M_WON_LIGHTS "[" #n "].quadratic", \
							   M_WON_LIGHTS "[" #n "].cutOff", \
							   M_WON_LIGHTS "[" #n "].outerCutOff", \

namespace won
{
	namespace priv
	{
		static constexpr const char* WON_PROJECTIONMATRIX = "won_ProjectionMatrix";
		static constexpr const char* WON_VIEWMATRIX       = "won_ViewMatrix";
		static constexpr const char* WON_MODELMATRIX      = "won_ModelMatrix";
		static constexpr const char* WON_FRAMES           = "won_Frames";
		static constexpr const char* WON_TIME             = "won_Time";
		static constexpr const char* WON_WINDOWWIDTH      = "won_WindowWidth";
		static constexpr const char* WON_WINDOWHEIGHT     = "won_WindowHeight";
		static constexpr const char* WON_NUMLIGHTS	      = "won_NumLights";
		static constexpr const char* WON_LIGHTS			  =  M_WON_LIGHTS;
		static constexpr const char* WON_VIEWPOSITION     = "won_ViewPosition";
		static constexpr const char* WON_MODELVIEWPROJMAT = "won_ModelViewProjMatrix";
		static constexpr const char* WON_MODELVIEWMATRIX  = "won_ModelViewMatrix";
		static constexpr const char* WON_NORMALMATRIX     = "won_NormalMatrix";

		static constexpr const unsigned int WON_LIGHT_INTERNAL_NPROPERTIES = 9;
		static constexpr const char* WON_LIGHT_UNIFORMS_ARRAY[MAX_LIGHTS * WON_LIGHT_INTERNAL_NPROPERTIES]
		{
#pragma region WON_LIGHT_UNIFORMS_128
			WON_LIGHTS_UNIFORMS(0)
			WON_LIGHTS_UNIFORMS(1)
			WON_LIGHTS_UNIFORMS(2)
			WON_LIGHTS_UNIFORMS(3)
			WON_LIGHTS_UNIFORMS(4)
			WON_LIGHTS_UNIFORMS(5)
			WON_LIGHTS_UNIFORMS(6)
			WON_LIGHTS_UNIFORMS(7)
			WON_LIGHTS_UNIFORMS(8)
			WON_LIGHTS_UNIFORMS(9)
			WON_LIGHTS_UNIFORMS(10)
			WON_LIGHTS_UNIFORMS(11)
			WON_LIGHTS_UNIFORMS(12)
			WON_LIGHTS_UNIFORMS(13)
			WON_LIGHTS_UNIFORMS(14)
			WON_LIGHTS_UNIFORMS(15)
			WON_LIGHTS_UNIFORMS(16)
			WON_LIGHTS_UNIFORMS(17)
			WON_LIGHTS_UNIFORMS(18)
			WON_LIGHTS_UNIFORMS(19)
			WON_LIGHTS_UNIFORMS(20)
			WON_LIGHTS_UNIFORMS(21)
			WON_LIGHTS_UNIFORMS(22)
			WON_LIGHTS_UNIFORMS(23)
			WON_LIGHTS_UNIFORMS(24)
			WON_LIGHTS_UNIFORMS(25)
			WON_LIGHTS_UNIFORMS(26)
			WON_LIGHTS_UNIFORMS(27)
			WON_LIGHTS_UNIFORMS(28)
			WON_LIGHTS_UNIFORMS(29)
			WON_LIGHTS_UNIFORMS(30)
			WON_LIGHTS_UNIFORMS(31)
			WON_LIGHTS_UNIFORMS(32)
			WON_LIGHTS_UNIFORMS(33)
			WON_LIGHTS_UNIFORMS(34)
			WON_LIGHTS_UNIFORMS(35)
			WON_LIGHTS_UNIFORMS(36)
			WON_LIGHTS_UNIFORMS(37)
			WON_LIGHTS_UNIFORMS(38)
			WON_LIGHTS_UNIFORMS(39)
			WON_LIGHTS_UNIFORMS(40)
			WON_LIGHTS_UNIFORMS(41)
			WON_LIGHTS_UNIFORMS(42)
			WON_LIGHTS_UNIFORMS(43)
			WON_LIGHTS_UNIFORMS(44)
			WON_LIGHTS_UNIFORMS(45)
			WON_LIGHTS_UNIFORMS(46)
			WON_LIGHTS_UNIFORMS(47)
			WON_LIGHTS_UNIFORMS(48)
			WON_LIGHTS_UNIFORMS(49)
			WON_LIGHTS_UNIFORMS(50)
			WON_LIGHTS_UNIFORMS(51)
			WON_LIGHTS_UNIFORMS(52)
			WON_LIGHTS_UNIFORMS(53)
			WON_LIGHTS_UNIFORMS(54)
			WON_LIGHTS_UNIFORMS(55)
			WON_LIGHTS_UNIFORMS(56)
			WON_LIGHTS_UNIFORMS(57)
			WON_LIGHTS_UNIFORMS(58)
			WON_LIGHTS_UNIFORMS(59)
			WON_LIGHTS_UNIFORMS(60)
			WON_LIGHTS_UNIFORMS(61)
			WON_LIGHTS_UNIFORMS(62)
			WON_LIGHTS_UNIFORMS(63)
			WON_LIGHTS_UNIFORMS(64)
			WON_LIGHTS_UNIFORMS(65)
			WON_LIGHTS_UNIFORMS(66)
			WON_LIGHTS_UNIFORMS(67)
			WON_LIGHTS_UNIFORMS(68)
			WON_LIGHTS_UNIFORMS(69)
			WON_LIGHTS_UNIFORMS(70)
			WON_LIGHTS_UNIFORMS(71)
			WON_LIGHTS_UNIFORMS(72)
			WON_LIGHTS_UNIFORMS(73)
			WON_LIGHTS_UNIFORMS(74)
			WON_LIGHTS_UNIFORMS(75)
			WON_LIGHTS_UNIFORMS(76)
			WON_LIGHTS_UNIFORMS(77)
			WON_LIGHTS_UNIFORMS(78)
			WON_LIGHTS_UNIFORMS(79)
			WON_LIGHTS_UNIFORMS(80)
			WON_LIGHTS_UNIFORMS(81)
			WON_LIGHTS_UNIFORMS(82)
			WON_LIGHTS_UNIFORMS(83)
			WON_LIGHTS_UNIFORMS(84)
			WON_LIGHTS_UNIFORMS(85)
			WON_LIGHTS_UNIFORMS(86)
			WON_LIGHTS_UNIFORMS(87)
			WON_LIGHTS_UNIFORMS(88)
			WON_LIGHTS_UNIFORMS(89)
			WON_LIGHTS_UNIFORMS(90)
			WON_LIGHTS_UNIFORMS(91)
			WON_LIGHTS_UNIFORMS(92)
			WON_LIGHTS_UNIFORMS(93)
			WON_LIGHTS_UNIFORMS(94)
			WON_LIGHTS_UNIFORMS(95)
			WON_LIGHTS_UNIFORMS(96)
			WON_LIGHTS_UNIFORMS(97)
			WON_LIGHTS_UNIFORMS(98)
			WON_LIGHTS_UNIFORMS(99)
			WON_LIGHTS_UNIFORMS(100)
			WON_LIGHTS_UNIFORMS(101)
			WON_LIGHTS_UNIFORMS(102)
			WON_LIGHTS_UNIFORMS(103)
			WON_LIGHTS_UNIFORMS(104)
			WON_LIGHTS_UNIFORMS(105)
			WON_LIGHTS_UNIFORMS(106)
			WON_LIGHTS_UNIFORMS(107)
			WON_LIGHTS_UNIFORMS(108)
			WON_LIGHTS_UNIFORMS(109)
			WON_LIGHTS_UNIFORMS(110)
			WON_LIGHTS_UNIFORMS(111)
			WON_LIGHTS_UNIFORMS(112)
			WON_LIGHTS_UNIFORMS(113)
			WON_LIGHTS_UNIFORMS(114)
			WON_LIGHTS_UNIFORMS(115)
			WON_LIGHTS_UNIFORMS(116)
			WON_LIGHTS_UNIFORMS(117)
			WON_LIGHTS_UNIFORMS(118)
			WON_LIGHTS_UNIFORMS(119)
			WON_LIGHTS_UNIFORMS(120)
			WON_LIGHTS_UNIFORMS(121)
			WON_LIGHTS_UNIFORMS(122)
			WON_LIGHTS_UNIFORMS(123)
			WON_LIGHTS_UNIFORMS(124)
			WON_LIGHTS_UNIFORMS(125)
			WON_LIGHTS_UNIFORMS(126)
			WON_LIGHTS_UNIFORMS(127)
#pragma endregion
		};


		class ScreenRenderer
		{
		public:
			ScreenRenderer();
			ScreenRenderer(const ScreenRenderer&) = delete;

			void Render(const Game& game);
			void SetActiveCamera(cmp::Camera* camera);

			void CreateRenderable(Entity entity);
			Renderable* RetrieveRenderable(Entity entity);
			bool HasRenderable(Entity entity);

			void CreateLight(Entity entity);
			LightInternal* RetrieveLight(Entity entity);
			bool HasLight(Entity entity);

			void EntityDestroyed(Entity entity);
			void Clear();

		private:
			won::Matrix4x4 CalculateMatrix(Renderable& renderable, Matrix4x4& model);
			bool IsTransformDirty(Renderable& renderable);

		private:
			cmp::Camera* camera = nullptr;

			std::unique_ptr<std::array<Renderable, MAX_ENTITIES>> renderables; // use vector instead?
			std::unordered_map<EntId, std::size_t> entityToIndex{};
			std::unordered_map<std::size_t, EntId> indexToEntity{};
			std::size_t rdsize = 0;
			
			std::unique_ptr<std::array<LightInternal, MAX_LIGHTS>> lights; // abstract into new datatype? 
			std::unordered_map<EntId, std::size_t> lEntityToIndex{};
			std::unordered_map<std::size_t, EntId> lIndexToEntity{};
			std::size_t lsize = 0;

			std::array<std::size_t, MAX_LIGHTS> lIndexToEIndex; // gives the index to the renderable not entity ID

			std::array<std::size_t, MAX_LIGHTS> dirtyLights;
			std::size_t dirtyLsize = 0;
		};
	}
}