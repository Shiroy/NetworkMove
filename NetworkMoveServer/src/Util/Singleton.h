#ifndef SINGLETON_H
#define SINGLETON_H

#include <Util/SharedDefine.h>

template<class T>
class Singleton
{
    protected:
    Singleton()
    {
        instance = NULL;
    }
    ~Singleton()
    {
        if(instance != NULL)
            delete instance;
    }

    public:
    static T *GetInstance()
    {
        if(instance == NULL)
            instance = new T;
        return instance;
    }

    static void Destroy()
    {
        if(instance != NULL)
        {
            delete instance;
            instance = NULL;
        }
    }

    private:
    static T *instance;
};

template <typename T>
T *Singleton<T>::instance = NULL;

#endif
