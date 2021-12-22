#pragma once

namespace gueepo {
	
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void Swap() = 0;
		virtual std::string GraphicsContextString() = 0;

		static GraphicsContext* Create(void* window);
	};
}