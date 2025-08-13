#pragma once

#include <utility>
#include <cstdlib>
#include <memory>
#include <cassert>

#define NATIVEXNA_ASSERT(expression) assert(expression)

#ifdef NATIVEXNA_PLATFORM_WIN32
    #define NATIVEXNA_API __declspec(dllexport)
#else
    #define NATIVEXNA_API __attribute__((visibility("default")))
#endif

namespace NativeXNA {

    template <typename T>
    class NATIVEXNA_API Ref {
    private:
        // Single allocation for the Ref's control block
        struct RefAllocation {
            size_t RefCount = 1;
            alignas(alignof(T)) uint8_t ObjectMemory[sizeof(T)] = {};

            T* GetObject() {
				return reinterpret_cast<T*>(ObjectMemory);
            }

            const T* GetObject() const {
                return reinterpret_cast<const T*>(ObjectMemory);
            }
        };

    public:
        template <typename U, typename ... TArgs>
        friend Ref<U> MakeRef(TArgs&& ...);

        Ref() = default;

        Ref(const Ref& other)
            : m_pAllocation(other.m_pAllocation) {
            if (m_pAllocation)
                ++(m_pAllocation->RefCount);
        }

        Ref(Ref&& other) noexcept 
			: m_pAllocation(other.m_pAllocation) {
			other.m_pAllocation = nullptr;
        }

        ~Ref() {
			if (m_pAllocation) {
				if (--(m_pAllocation->RefCount) == 0) {
					m_pAllocation->GetObject()->~T();
					delete m_pAllocation;
				}
			}
        }

        Ref& operator=(Ref other) {
			std::swap(m_pAllocation, other.m_pAllocation);
            return *this;
        }

        T* operator->() { return m_pAllocation->GetObject(); }
        const T* operator->() const { return m_pAllocation->GetObject(); }

        operator T&() { return *m_pAllocation->GetObject(); }
        operator const T&() const { return *m_pAllocation->GetObject(); }

        bool operator==(const Ref<T>& other) const { return (m_pAllocation == other.m_pAllocation); }
        operator bool() const { return (m_pAllocation != nullptr); }

    private:
        Ref(RefAllocation* pAlloc)
            : m_pAllocation(pAlloc) {}


    private:
		RefAllocation* m_pAllocation = nullptr;
    };

    template <typename T, typename ... TArgs>
    inline NATIVEXNA_API Ref<T> MakeRef(TArgs&& ... args) {
		// Allocate memory for the Ref's control block
		auto block = new typename Ref<T>::RefAllocation();

        // Exception-safe allocation
        try {
			new (block->ObjectMemory) T(std::forward<TArgs>(args)...);
        } catch (...) {
            delete block;
            block = nullptr;
            throw;
        }

        return Ref<T>(block);
    }

    template <typename T>
    struct NATIVEXNA_API PlatformData {};
    
    template <typename T>
    class NATIVEXNA_API PlatformImplementation {
    public:
        virtual ~PlatformImplementation() = default;

        const PlatformData<T>& GetPlatformData() const { return *m_PlatformData; }

    protected:
        PlatformImplementation()
            : m_PlatformData(std::make_unique<PlatformData<T>>()) {}

    protected:
        std::unique_ptr<PlatformData<T>> m_PlatformData;        
    };

}