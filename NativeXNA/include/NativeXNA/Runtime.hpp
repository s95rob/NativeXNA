#pragma once

#include "NativeXNA/Common.hpp"

#include <vector>
#include <functional>
#include <string>
#include <string_view>

namespace NativeXNA {

    using IntPtr = size_t;


    class IDisposable {
    public:
        virtual ~IDisposable() = default;

        virtual void Dispose() = 0;
    };

    
    template <typename ... TEventArgs>
    class NATIVEXNA_API Event {
    public:
        using EventHandlerFn = std::function<void(TEventArgs ...)>;

        Event() = default;

        void Invoke(TEventArgs&& ... args) {
            for (auto& handler : m_Handlers) {
                handler(std::forward<TEventArgs>(args) ...);
            }
        }

        // Subscribe to this event
        void operator+=(EventHandlerFn handler) { m_Handlers.push_back(handler); }

        // Unsubscribe from this event
        void operator-=(EventHandlerFn handler) {}

    private:
        std::vector<EventHandlerFn> m_Handlers;
    };

}