#include "precompile.h"
#include "Renderer/Renderer.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace Voxel
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexID;
		float TexScale;
	};

	struct RendererData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16; // TODO: Check gpu max

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureAndColorShader;
		//Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		//std::array<Ref<Texture>, MaxTextureSlots> TextureSlots;
		//uint32_t TextureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4];

		Renderer::Statistics Stats;
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		// OpenGL Setup
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		// VertexArray
		s_Data.QuadVertexArray = CreateRef<VertexArray>();

		//The Quad
		s_Data.QuadVertexBuffer = CreateRef<VertexBuffer>(s_Data.MaxVertices * sizeof(QuadVertex));

		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCood" },
			{ ShaderDataType::Float, "a_TexID" },
			{ ShaderDataType::Float, "a_TexScale" }
			});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = CreateRef<IndexBuffer>(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);

		delete[] quadIndices;

		// Create White Texture
		//s_Data.WhiteTexture = Texture2D::Create(1, 1);
		//uint32_t whiteTextureData = 0xffffffff;
		//s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		//int samplers[s_Data.MaxTextureSlots];
		//for (int i = 0; i < s_Data.MaxTextureSlots; i++)
		//	samplers[i] = i;

		s_Data.TextureAndColorShader = CreateRef<Shader>("assets/shaders/TextureAndColor.glsl");
		s_Data.TextureAndColorShader->Bind();
		//s_Data.TextureAndColorShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		//s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer::Shutdown()
	{
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer::OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::BeginScene(const Camera& camera, glm::mat4 transform)
	{
		//glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		s_Data.TextureAndColorShader->Bind();
		s_Data.TextureAndColorShader->SetMat4("u_ViewProjection", camera.GetProjectionMatrix() * camera.GetViewMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		//s_Data.TextureSlotIndex = 1;
	}

	void Renderer::EndScene()
	{
		uint32_t datasize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, datasize);

		Flush();
	}

	void Renderer::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return; // Nothing to draw

		//Bind Textures
		//for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		//	s_Data.TextureSlots[i]->Bind(i);

		glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);

		s_Data.Stats.DrawCalls++;
	}

	void Renderer::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::FlushAndReset()
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		//s_Data.TextureSlotIndex = 1;
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
			FlushAndReset();

		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexID = textureIndex;
			s_Data.QuadVertexBufferPtr->TexScale = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Renderer::Statistics));
	}

	Renderer::Statistics Renderer::GetStats()
	{
		return s_Data.Stats;
	}
}