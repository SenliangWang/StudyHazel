#include "Hazel.h"
// main����λ��Hazel.hͷ�ļ��� 

class Sandbox : public Hazel::Application {
public:
	Sandbox() {

	}

	~Sandbox() {  

	}
};

Hazel::Application* Hazel::CreateApplication()  
{
	return new Sandbox();
}
