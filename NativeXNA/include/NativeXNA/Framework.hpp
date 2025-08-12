#pragma once

namespace NativeXNA {

    struct Point {
        int X, Y;

        Point()
            : Point(0, 0) {}
        Point(int x, int y)
            : X(x), Y(y) {}
    };

    struct Rectangle {
        int X, Y, Width, Height;

        int& Left = X,
           & Top = Y,
           & Right = Width,
           & Bottom = Height;

        Rectangle()
            : Rectangle(0, 0, 0, 0) {}
        Rectangle(int x, int y, int width, int height)
            : X(x), Y(y), Width(width), Height(height) {}

        // Determines whether a specified Rectangle intersects with this Rectangle.
        inline bool Intersects(const Rectangle& other) const {
            return (
                X < other.X + other.Width &&
                X + Width > other.X &&
                Y < other.Y + other.Height &&
                Y + Height > other.Y
            );
        }

        // Determines whether this Rectangle contains a specified Point.
        inline bool Contains(const Point& point) const {
            return (
                X <= point.X &&
                X + Width > point.X &&
                Y <= point.Y &&
                Y + Height > point.Y
            );
        }
    };

}