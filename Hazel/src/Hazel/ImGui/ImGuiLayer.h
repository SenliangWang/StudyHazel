﻿#pragma once

#include "Hazel/Layer.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override; 
		void OnEvent(Event&) override;
		void OnUpdate() override;
	private:
		float m_Time = 0.0;
	};
}
