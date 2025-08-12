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
    class Ref {
    public:
        template <typename U, typename ... TArgs>
        friend Ref<U> MakeRef(TArgs&& ...);

        Ref() = default;

        Ref(const Ref& other)
            : m_pRef(other.m_pRef), m_pRefCount(other.m_pRefCount) {
            if (m_pRef)
                ++(*m_pRefCount);
        }

        Ref(Ref&& other) noexcept 
            : m_pRef(other.m_pRef), m_pRefCount(other.m_pRefCount) {
            other.m_pRef = nullptr;
            other.m_pRefCount = nullptr;
        }

        ~Ref() {
            if (m_pRefCount) {
                if (--(*m_pRefCount) == 0) {
                    delete m_pRef;
                    delete m_pRefCount;
                }
            }
        }

        Ref& operator=(const Ref& other) {
            if (this != &other) {
                Ref temp(other);
                std::swap(m_pRef, temp.m_pRef);
                std::swap(m_pRefCount, temp.m_pRefCount);
            }

            return *this;
        }

        Ref& operator=(Ref&& other) noexcept {
            if (this != &other) {
                if (m_pRef && --(*m_pRefCount) == 0) {
                    delete m_pRef;
                    delete m_pRefCount;
                }

                m_pRef = other.m_pRef;
                m_pRefCount = other.m_pRefCount;
                other.m_pRef = nullptr;
                other.m_pRefCount = nullptr;
            }

            return *this;
        }

        T* operator->() { return m_pRef; }
        const T* operator->() const { return m_pRef; }

        operator T&() { return *m_pRef; }
        operator const T&() const { return *m_pRef; }

        bool operator==(const Ref<T>& other) const { return (m_pRef == other.m_pRef); }
        operator bool() const { return (m_pRef != nullptr); }

    private:
        Ref(T* pRef, size_t* pRefCount)
            : m_pRef(pRef), m_pRefCount(pRefCount) {}

    private:
        T* m_pRef = nullptr;
        size_t* m_pRefCount = nullptr;
    };

    template <typename T, typename ... TArgs>
    inline Ref<T> MakeRef(TArgs&& ... args) {
        // Single allocation for the Ref's control block
        struct RefAllocation {
            size_t RefCount = 1;
            alignas(alignof(T)) uint8_t ObjectMemory[sizeof(T)];
        };

        RefAllocation* block = static_cast<RefAllocation*>(::operator new(sizeof(RefAllocation)));

        // Exception-safe allocation
        try {
            T* objectPtr = new (block->ObjectMemory) T(std::forward<TArgs>(args) ...);
            return Ref<T>(objectPtr, &block->RefCount);
        } catch (...) {
            ::operator delete(block);
            throw;
        }
    }

    template <typename T>
    struct PlatformData {};
    
    template <typename T>
    class PlatformImplementation {
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