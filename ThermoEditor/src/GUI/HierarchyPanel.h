#ifndef HIERARCHYPANEL_H
#define HIERARCHYPANEL_H

#include <Thermo.h>

using namespace Thermo;

namespace ThermoEditor
{
    class HierarchyPanel
    {
    public:
        static void DisplayEntities(const Ref<EntityManager> &entityManager);
    };
}

#endif //HIERARCHYPANEL_H
