#ifndef YIALITE_SINGLETON_H
#define YIALITE_SINGLETON_H

#define YIALITE_SINGLETON(T) friend class Singleton<T>;

namespace yialite
{

template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
protected:
    Singleton() = default;
    ~Singleton() = default;
};

}

#endif