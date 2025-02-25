#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <buffer.hpp>
namespace forgeGUI
{
    class BaseQuad
    {
        struct alignas(16) baseQuadData
        {
            glm::uvec2 size{};
            glm::ivec2 pos{};
            glm::vec4 bgColor{};
            unsigned int depth = 0;
        };
        static std::vector<baseQuadData> quadData;
        static bool shouldUpdateBuffer, shouldReallocateBuffer;
        unsigned int dataIndex;
        inline static FlexBuffer& getQuadDataBuffer()
        {
            static FlexBuffer buffer{};
            return buffer;
        }
    public:
        static GLuint GetVAO();
        static GLuint GetShader();
        static void DrawAll(glm::uvec2 windowSize);
        void static UpdateBuffer();
        BaseQuad(BaseQuad&) = delete;
        BaseQuad(BaseQuad&&) = delete;
        BaseQuad(glm::ivec2 size, glm::ivec2 pos, glm::vec4 bgColor);
        inline glm::uvec2& size()
        {
            return quadData[dataIndex].size;
        }
        inline const glm::uvec2& size() const
        {
            return quadData[dataIndex].size;
        }
        inline glm::ivec2& pos()
        {
            return quadData[dataIndex].pos;
        }
        inline const glm::ivec2& pos() const
        {
            return quadData[dataIndex].pos;
        }
        inline glm::vec4& bgColor()
        {
            return quadData[dataIndex].bgColor;
        }
        inline const glm::vec4& bgColor() const
        {
            return quadData[dataIndex].bgColor;
        }
        inline unsigned int& depth()
        {
            return quadData[dataIndex].depth;
        }
        inline unsigned int depth() const
        {
            return quadData[dataIndex].depth;
        }
    };
}