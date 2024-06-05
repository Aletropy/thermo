#ifndef THERMOENGINE_SYSTEM_H
#define THERMOENGINE_SYSTEM_H

namespace Thermo
{

    class System {
    public:
        virtual void Initialize() = 0;
        virtual void Update(float deltaTime) = 0;
    };

} // Thermo

#endif //THERMOENGINE_SYSTEM_H
