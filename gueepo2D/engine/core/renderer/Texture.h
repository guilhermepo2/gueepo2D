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

		virtual void SetData(uint32_t* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool IsLoaded() const = 0;

		static Texture* Create(const std::string& path);
		static Texture* Create(uint32_t width, uint32_t height);

	protected:
		std::string m_path;

	private:
		static texture_data_t LoadTexture(const std::string& path);

	};
}