#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		bool Handled = false;  // 检测当前事件是否还有被响应的能力
	};

	// 将一个事件和一个函数绑定在一起，当监听的事件被触发时，就激活对应的函数
	// 事件分发器, 用于将事件分发给对应的事件监听器, 事件监听器是一个函数, 用于处理事件
	
	// 事件监听器的返回值
	// 事件监听器的返回值为true时, 表示事件已经被处理, 不需要再传递给其他的事件监听器
	// 事件监听器的返回值为false时, 表示事件还没有被处理, 需要继续传递给其他的事件监听器
	class EventDispatcher
	{
		// Define EventFunc() Template
	    // With T& input and return bool
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:

		// Bind the event to this Dispatcher,
	    // Each Dispatcher can only Dispatch 1 Event, 
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// Dispatch the event to the corresponding Event Listener
		// If the event is handled, return true
		// If the event is not handled, return false
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// Check if the event type is the same as the event listener type
			// If the event type is the same as the event listener type,
			// Call the event listener function
			// If the event type is not the same as the event listener type,
			// Return false
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Set the event handled flag to the return value of the event listener function
				// If the event listener function returns true, the event is handled
				// If the event listener function returns false, the event is not handled
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

