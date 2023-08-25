#include "./shear_vertical.h"

namespace spright
{
namespace editor
{
    static const float MinDiffFromHalfPi = 0.04f;

    float get_sign(float number)
    {
        return number < 0 ? -1 : 1;
    }

    float get_abs(float number)
    {
        return number < 0 ? -1 * number : number;
    }

    void copy(const TileLayer &source, TileLayer &dest, const BoundsInt &bounds)
    {
        // RectSelector rectSelector(&source);
        // rectSelector.setSelection(bounds.getBottomLeft(), bounds.getTopRight());

        // const std::vector<Rect2D *> tiles = rectSelector.getSelection();

        // for (Rect2D *tile : tiles)
        // {
        //     dest.add(*tile);
        // }
    }

    void shear_vertical(TileLayer &source, TileLayer &dest, const BoundsInt &bounds, float angle)
    {
        if (angle == 0.0 || tan(angle) == 0.0)
        {
            copy(source, dest, bounds);
            return;
        }

        int sign = get_sign(angle);
        float tanangle = tan(angle);
        float invangle = get_abs(1.0f / tanangle);
        int inityincr = (int) invangle / 2.0f;
        int yincr = (int) invangle;
    }

    float normalize_angle_for_shear(float radang, float mindif)
    {
        float pi2;

        /* Bring angle into range [-pi/2, pi/2] */
        pi2 = 3.14159265 / 2.0;
        if (radang < -pi2 || radang > pi2)
            radang = radang - (float)(radang / pi2) * pi2;

        /* If angle is too close to pi/2 or -pi/2, move it */
        if (radang > pi2 - mindif)
        {
            radang = pi2 - mindif;
        }
        else if (radang < -pi2 + mindif)
        {
            radang = -pi2 + mindif;
        }

        return radang;
    }
} // namespace editor
} // namespace spright
