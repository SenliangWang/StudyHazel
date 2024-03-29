#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Window.h"
#include "Hazel/LayerStack.h"

namespace Hazel{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_bRuning = true;
		LayerStack m_LayerStack;
	};

	// to be defined in client
	Application* CreateApplication();
}


