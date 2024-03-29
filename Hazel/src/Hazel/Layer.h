#pragma once
#include "Hazel/Core.h"
#include "Events/Event.h"

namespace Hazel
{
	class HAZEL_API Layer
	{
	public:
		Layer(const std::wstring& name = L"Layer");
		virtual ~Layer();

		virtual void OnAttach() {}; // 当layer添加到layer stack的时候会调用此函数, 相当于Init函数
		virtual void OnDetach() {}; // 当layer从layer stack移除的时候会调用此函数, 相当于Shutdown函数
		virtual void OnUpdate() {}; // 在layer更新时由应用层调用, 应该每帧调用一次
		virtual void OnEvent(Event& event) {};
		virtual void OnImGuiRender() {};

		inline const std::wstring& GetName() const{ return m_DebugName; }
	protected:
		bool isEnabled;	// 值为fasle时，该Layer会被禁用，不会绘制画面，也不会接收事件
		std::wstring m_DebugName;
	};

}