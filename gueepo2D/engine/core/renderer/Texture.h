#pragma once

namespace gueepo {

	struct texture_data_t {
		unsigned char* texture_data;
		int width;
		int height;
		int channels;
	};

	class Texture {
	public:
		virtual ~Texture() {}
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetTextureID() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool IsLoaded() const = 0;

		static Texture* Create(const std::string& path);

	protected:
		std::string m_path;

	private:
		static texture_data_t LoadTexture(const std::string& path);

	};
}