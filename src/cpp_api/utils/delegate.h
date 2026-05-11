#ifndef YIALITE_DELEGATE_H
#define YIALITE_DELEGATE_H

#include "utility.h"
#include "memory/allocator.h"

namespace yialite
{

template <typename FuncType>
struct DelegateImpl;

template <typename Ret, typename... Args>
struct DelegateImpl<Ret(Args...)>
{
    struct CallableBase
    {
        virtual ~CallableBase() = default;
        virtual Ret invoke(Args...) = 0;
    };

    template <typename Fx>
    struct Callable : CallableBase
    {
        Fx m_func;

        Callable(Fx&& func) : m_func(yialite::forward<Fx>(func)) {}

        Ret invoke(Args... args) override
        {
            return m_func(yialite::forward<Args>(args)...);
        }
    };

    struct Type
    {
        CallableBase* m_callable = nullptr;

        bool isEmpty() const
        {
            return m_callable == nullptr;
        }

        template <typename Fx>
        void reset(Fx&& func)
        {
            DEALLOCATE_OBJECT(CallableBase, m_callable);
            m_callable = ALLOCATE_OBJECT(Callable<Fx>, yialite::forward<Fx>(func));
        }

        void resetMove(Type&& other)
        {
            DEALLOCATE_OBJECT(CallableBase, m_callable);
            m_callable = other.m_callable;
            other.m_callable = nullptr;
        }

        void tidy()
        {
            DEALLOCATE_OBJECT(CallableBase, m_callable);
        }

        Ret operator()(Args... args) const
        {
            if (m_callable) return m_callable->invoke(yialite::forward<Args>(args)...);
            
            if constexpr(yialite::is_void_v<Ret>) return;
            else return {};
        }

        ~Type() { tidy(); }
    };
};

template <typename FuncType>
class Delegate : public DelegateImpl<FuncType>::Type
{
private:
    using Base = typename DelegateImpl<FuncType>::Type;
public:
    Delegate() noexcept = default;
    Delegate(yialite::nullptr_t) noexcept {}

    Delegate(const Delegate& other) = delete;
    Delegate& operator=(const Delegate& other) = delete;

    template <class Fx>
    Delegate(Fx&& func)
    {
        this->reset(yialite::forward<Fx>(func));
    }

    Delegate(Delegate&& other) noexcept
    {
        this->resetMove(yialite::move(other));
    }

    Delegate& operator=(Delegate&& other) noexcept
    {
        if (this != &other) this->resetMove(yialite::move(other));
        return *this;
    }

    template <class Fx>
    Delegate& operator=(Fx&& func)
    {
        this->reset(yialite::forward<Fx>(func));
        return *this;
    }

    Delegate& operator=(yialite::nullptr_t) noexcept
    {
        this->tidy();
        return *this;
    }

    explicit operator bool() const noexcept
    {
        return !this->isEmpty();
    }

    ~Delegate() = default;
};

template <class FuncType>
bool operator==(const Delegate<FuncType>& func, yialite::nullptr_t) noexcept
{
    return !func;
}

}

#endif