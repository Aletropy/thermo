#ifndef LAYER_H
#define LAYER_H

namespace Thermo {

    class Layer 
    {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach() { }
        virtual void OnDetach() { }
        virtual void OnUpdate(float deltaTime) { }
        virtual void OnEvent() { }
    };

} // Thermo

#endif //LAYER_H
