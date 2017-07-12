#pragma once
#include <pgt/graphics/graphics_2d.h>
namespace lgs {
	class Port;
	class Connection {
	public:
		Port& p1;
		Port& p2;
		Connection(Port& p1, Port&p2):p1(p1),p2(p2) {

		}
		void render(pgt::Renderer2D& r);

	};
}