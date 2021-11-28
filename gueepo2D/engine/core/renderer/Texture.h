#pragma once

namespace gueepo {
	class Texture {
	public:
		virtual ~Texture() {}
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetTextureID() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool IsLoaded() const = 0;

		static Texture* Create(const std::string& path);
	};
}