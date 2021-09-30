#ifndef ZJVL_EVENT_EVENT_H
#define ZJVL_EVENT_EVENT_H

namespace ZJVL
{
	enum class EventType
	{
		APPLICATION,
		WINDOW_QUIT,
		KEYDOWN,
		MOUSEMOVE,
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType get_type() const = 0;

		bool should_be_handled() const;

		void stop_propagation();

	protected:
		bool m_propagate = true;
	};
}

#endif