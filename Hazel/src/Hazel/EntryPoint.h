#pragma once

#ifdef  HZ_PLATFORM_WINDOWS

// 需要使用 extern 来告诉编译器该函数是在其他文件中定义的
extern  Hazel::Application*   Hazel::CreateApplication();

int main(int argc, char* argv[]) {
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	int a = 5;
	HZ_INFO("Hello, var = {0}", a);

	// Let the actual project to implement the CreateApplication() and return the app*
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif //  HZ_PLATFORM_WINDOWS
