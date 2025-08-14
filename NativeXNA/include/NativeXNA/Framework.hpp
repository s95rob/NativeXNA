#pragma once

namespace NativeXNA {

    struct Color {
		float R, G, B, A;

		Color()
			: Color(0.0f, 0.0f, 0.0f, 1.0f) {}
		Color(float r, float g, float b, float a = 1.0f)
			: R(r), G(g), B(b), A(a) {}
		Color(int r, int g, int b, int a = 255)
			: R(r / 255.0f), G(g / 255.0f), B(b / 255.0f), A(a / 255.0f) {}
    };

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