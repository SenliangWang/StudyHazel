#include "Hazel.h"
// main函数位于Hazel.h头文件中 

class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		PushOverLayer(new Hazel::ImGuiLayer());
	}

	~Sandbox() {  

	}
};

Hazel::Application* Hazel::CreateApplication()  
{
	return new Sandbox();
}
