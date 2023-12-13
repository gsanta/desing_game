#pragma once

#include "../../../maths/data/bounds.h"
#include "../containers/group.h"
#include "canvas_component.h"

namespace spright
{
namespace engine
{
#define CANVAS_TYPE_TILE "tile-canvas"
#define CANVAS_TYPE_2D "2d-canvas"
#define CANVAS_TYPE_3D "3d-canvas"

    class Canvas
    {
    public:
        enum RenderTarget
        {
            Screen,
            Image
        };

        enum Type
        {
            CANVAS_2D,
            CANVAS_3D,
            TILE_CANVAS
        };

        virtual ~Canvas() = default;

        Canvas(const std::string &uuid, std::string type, const Bounds &bounds, const Renderer2D &renderer);

        Canvas(const Canvas &other);

        Canvas &operator=(const Canvas &other);

        const Bounds &getBounds() const;

        const std::string getUuid() const;

        virtual void render(const Camera &camera, Canvas::RenderTarget target);

        Renderer2D &getRenderer();

        Group<Renderable2D> &getGizmoLayer();

        virtual Canvas *clone() const = 0;

        virtual Camera *getCamera() = 0;

        const std::string &getType() const;

        template <typename T>
        std::shared_ptr<T> getComponent();

        template <typename T, typename... Args>
        std::shared_ptr<T> addComponent(Args &&...args);

        template <typename T>
        void removeComponent();

    protected:
        Bounds m_Bounds;

        Group<Renderable2D> m_GizmoLayer;

        std::string m_Uuid;

        std::unique_ptr<Renderer2D> m_Renderer;

        std::string m_Type;

        std::unordered_map<std::string, std::shared_ptr<CanvasComponent>> m_Components;
    };

    template <typename T>
    std::shared_ptr<T> Canvas::getComponent()
    {
        const std::string typeName = typeid(T).name();
        auto it = m_Components.find(typeName);
        if (it != m_Components.end())
        {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> Canvas::addComponent(Args &&...args)
    {
        const std::string typeName = typeid(T).name();
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->onAddedToCanvas(*this);
        m_Components[typeName] = component;
        return component;
    }

    template <typename T>
    void Canvas::removeComponent()
    {
        const std::string typeName = typeid(T).name();
        auto it = m_Components.find(typeName);
        if (it != m_Components.end())
        {
            m_Components.erase(it);
        }
    }

} // namespace engine
} // namespace spright
