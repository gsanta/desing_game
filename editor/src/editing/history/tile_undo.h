#pragma once

#include "../../engine/graphics/mesh/meshes/rect2d.h"
#include "../../engine/scene/containers/tile_layer.h"
#include "../document/document.h"
#include "../tool/tool_handler.h"
#include "../utils/conversions.h"
#include "./undoable.h"

#include <set>

// TODO: move file into tool folder
namespace spright
{
namespace editing
{
    struct SharedPtrCompare
    {
        inline bool operator()(const std::shared_ptr<Rect2D> &ptr1, const std::shared_ptr<Rect2D> &ptr2) const
        {
            if (ptr1->getCenterPosition2d().y < ptr2->getCenterPosition2d().y)
            {
                return true;
            }
            else if (ptr1->getCenterPosition2d().y > ptr2->getCenterPosition2d().y)
            {
                return false;
            }

            return ptr1->getCenterPosition2d().x < ptr2->getCenterPosition2d().x;
        }
    };


    class TileUndo : public Undoable
    {
    public:
        TileUndo(Document &document, std::shared_ptr<ToolStore> tools);

        static TileUndo createForActiveTileLayer(Document &document, std::shared_ptr<ToolStore> tools);

        void undo(Document &document) const override;

        void redo(Document &document) const override;

        void addTile(std::shared_ptr<Rect2D> prevRect, std::shared_ptr<Rect2D> newRect);

        void setPrevTiles(const BoundsInt &area, const TileLayer &activeLayer);

        void setNewTiles(const BoundsInt &area, const TileLayer &activeLayer);

        void setSelection(const std::vector<int> &prevSelectedIndexes, const std::vector<int> &newSelectedIndexes);

        void setPrevSelection(const std::vector<int> &prevSelectedIndexes);

        void setNewSelection(const std::vector<int> &newSelectedIndexes);

        bool isEmpty() const;

    private:
        void setTiles(const BoundsInt &area,
                      const TileLayer &activeLayer,
                      std::set<std::shared_ptr<Rect2D>, SharedPtrCompare> &set);

        TileLayer &getUndoLayer(Document &document) const;

        TileLayer &getRedoLayer(Document &document) const;

    private:
        std::set<std::shared_ptr<Rect2D>, SharedPtrCompare> m_PrevList;

        std::set<std::shared_ptr<Rect2D>, SharedPtrCompare> m_NewList;

        size_t m_TileLayerIndex;

        size_t m_FrameIndex;

        int m_CanvasIndex;

        std::vector<int> m_PrevSelectedIndexes;

        std::vector<int> m_NewSelectedIndexes;

        std::shared_ptr<ToolStore> m_Tools;
    };

} // namespace editing
} // namespace spright
