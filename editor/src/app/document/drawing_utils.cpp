#include "drawing_utils.h"

namespace spright
{
namespace editor
{
    void copy_pixels(Drawing &from, Bounds &newBounds)
    {
        Drawing newDrawing(newBounds);
        for (Frame &frame : from.getFrameStore().getFrames())
        {
            Frame &newFrame = newDrawing.getFrameStore().addFrame(FrameImpl(frame.getIndex()));
            for (TileLayer &layer : frame.getLayers()) {
                newFrame.addLayer(TileLayer(layer.getName(),)
            }
        }
    }
} // namespace editor
} // namespace spright
