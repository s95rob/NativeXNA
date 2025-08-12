#pragma once

#include "NativeXNA/Common.hpp"

#include <vector>
#include <functional>
#include <string>
#include <string_view>
#include <type_traits>

namespace NativeXNA {

    using IntPtr = size_t;


    class IDisposable {
    public:
        virtual ~IDisposable() = default;

        virtual void Dispose() = 0;
    };

    struct EventArgs {};
    
    template <typename TEventArgs>
    class NATIVEXNA_API EventHandler {
    public:
        static_assert(std::is_base_of_v<EventArgs, TEventArgs>, "TEventArgs must be derived from EventArgs");

        using EventHandlerFn = std::function<void(const TEventArgs&)>;

        EventHandler() = default;

        void Invoke(const TEventArgs& args = EventArgs()) {
            for (auto& handler : m_Handlers) {
                handler(args);
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