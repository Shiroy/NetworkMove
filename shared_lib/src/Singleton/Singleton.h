#ifndef SINGLETON_H
#define SINGLETON_H

#include "Util/SharedDefine.h"

/*!
 *\file Singleton.h
 *\author Eryldor
 *\brief Définis une classe gérant les Singleton
 */

 /*!
  *\class Singleton
  *\author Eryldor
  *\brief Cette classe est utiliser pour géré des singletons.
  *\details
  *Les singletons sont des objets qui ne sont instanciables qu'une seule fois. Où que vous l'appeliez dans le proogramme, ce sera toujours le même objet qui sera affecter.
  */
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
    /*!
     *\brief Retourne un pointeur sur l'instance de l'objet
     *\author Eryldor
     *\details Retourne un pointeur sur l'instance de l'objet géré par le songleton. Si l'objet n'existe pas, il sera créer.
     *\return T* Pointeur sur l'objet*/
    static T *GetInstance()
    {
        if(instance == NULL)
            instance = new T;
        return instance;
    }

    /*!
     *\brief Detruit l'objet
     *\author Eryldor
     *\details Detruit l'objet géré par le singleton. Un nouvel appel à GetInstance en créera un nouveau*/
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
