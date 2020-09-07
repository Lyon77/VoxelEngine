#pragma once

#include "Core/Core.h"
#include <string>

#include <glm/glm.hpp>

namespace Voxel
{
	// TEMP: Weird issue with glad.h
	typedef unsigned int GLenum;

	class Texture
	{
	public:
		Texture(uint32_t width, uint32_t height);
		Texture(const std::string& path);
		virtual ~Texture();

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }
		virtual uint32_t GetRendererID() const { return m_RendererID; };

		virtual void SetData(void* data, uint32_t size);

		virtual void Bind(uint32_t slot = 0) const;

		virtual bool operator==(const Texture& other) const
		{
			return m_RendererID == ((Texture&)other).m_RendererID;
		};
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};

	class SubTexture
	{
	public:
		SubTexture(const Ref<Texture>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture> GetTexture() const { return m_Texture; };
		const glm::vec2* GetTexCoords() const { return m_TexCoords; };

		static Ref<SubTexture> CreateFromCoords(const Ref<Texture>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });
	private:
		Ref<Texture> m_Texture;
		glm::vec2 m_TexCoords[4];
	};
}