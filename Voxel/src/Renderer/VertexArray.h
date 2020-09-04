#pragma once

#include "Renderer/Buffer.h"

namespace Voxel
{
	class VertexArray
	{
	public:
		VertexArray();
		virtual ~VertexArray();

		virtual void Bind() const;
		virtual void UnBind() const;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; };
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
	};
}
