#include <baseGUIquad.hpp>
namespace forgeGUI
{
    const char* fragShaderCode = 
        #include "../shaders/baseQuadFrag.glsl"
    ;
    const char* vertShaderCode = 
        #include "../shaders/baseQuadVert.glsl"
    ;
    std::vector<BaseQuad::baseQuadData> BaseQuad::quadData{};
    bool BaseQuad::shouldUpdateBuffer = false;
    bool BaseQuad::shouldReallocateBuffer = false;
    GLuint BaseQuad::GetVAO()
    {
        static GLuint vao = 0;
        if(vao)
            return vao;
        
        glCreateVertexArrays(1, &vao);

        //size attrib
        glEnableVertexArrayAttrib(vao, 0); 
        glVertexArrayAttribIFormat(vao, 0, 2, GL_UNSIGNED_INT, 0);
        glVertexArrayAttribBinding(vao, 0, 0);
        glVertexArrayBindingDivisor(vao, 0, 1);

        //pos attrib
        glEnableVertexArrayAttrib(vao, 1); 
        glVertexArrayAttribIFormat(vao, 1, 2, GL_INT, 0);
        glVertexArrayAttribBinding(vao, 1, 1);
        glVertexArrayBindingDivisor(vao, 1, 1);

        // bgColor attrib
        glEnableVertexArrayAttrib(vao, 2); 
        glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 2, 2);
        glVertexArrayBindingDivisor(vao, 2, 1);

        //depth attrib
        glEnableVertexArrayAttrib(vao, 3); 
        glVertexArrayAttribIFormat(vao, 3, 1, GL_UNSIGNED_INT, 0);
        glVertexArrayAttribBinding(vao, 3, 3);
        glVertexArrayBindingDivisor(vao, 3, 1);
        
        return vao;
    }
    GLuint BaseQuad::GetShader()
    {
        static GLuint shader = 0;
        if(shader)
            return shader;

        GLint compileStatus, linkStatus, logLen;

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertShaderCode, nullptr);
        glCompileShader(vs);
        
		glGetShaderiv(vs, GL_COMPILE_STATUS, &compileStatus);
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logLen);
		if (compileStatus != GL_TRUE)
		{
			char log[logLen + 1];
			glGetShaderInfoLog(vs, logLen + 1, 0, log);
			std::fprintf(stderr, "Vertex Shader Compilation Error: %s\n", log);
            return 0;
		}

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragShaderCode, nullptr);
        glCompileShader(fs);
        
		glGetShaderiv(fs, GL_COMPILE_STATUS, &compileStatus);
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &logLen);
		if (compileStatus != GL_TRUE)
		{
			char log[logLen + 1];
			glGetShaderInfoLog(fs, logLen + 1, 0, log);
			std::fprintf(stderr, "Fragment Shader Compilation Error: %s\n", log);
            return 0;
		}


        shader = glCreateProgram();
        glAttachShader(shader, vs);
        glAttachShader(shader, fs);

        glLinkProgram(shader);

        glGetProgramiv(shader, GL_LINK_STATUS, &linkStatus);
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0)
        {
            char log[logLen + 1];
            glGetProgramInfoLog(shader, logLen + 1, 0, log);
            std::fprintf(stderr, "Shader Linking Error: %s\n", log);
            return 0;
        }
        return shader;
    }
    void BaseQuad::Draw()
    {
        glUseProgram(GetShader());
        glBindVertexArray(GetVAO());

        glBindVertexBuffer(0, getQuadDataBuffer().GetName(), 0, sizeof(baseQuadData));
        glBindVertexBuffer(1, getQuadDataBuffer().GetName(), offsetof(baseQuadData, pos), sizeof(baseQuadData));
        glBindVertexBuffer(2, getQuadDataBuffer().GetName(), offsetof(baseQuadData, bgColor), sizeof(baseQuadData));
        glBindVertexBuffer(3, getQuadDataBuffer().GetName(), offsetof(baseQuadData, depth), sizeof(baseQuadData));
        
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, quadData.size());
    }

    BaseQuad::BaseQuad(glm::ivec2 size, glm::ivec2 pos, glm::vec3 bgColor):
        dataIndex(quadData.size())
    {
        quadData.emplace_back(size, pos, bgColor);
        shouldReallocateBuffer = true;
    }
    void BaseQuad::updateBuffer()
    {
        if(shouldReallocateBuffer)
        {
            getQuadDataBuffer().ReallocBuffer(quadData.size(), quadData.data(), GL_DYNAMIC_DRAW);
            shouldReallocateBuffer = shouldUpdateBuffer = false;
        }
        if(shouldUpdateBuffer)
        {
            getQuadDataBuffer().SetData(0, quadData.size(), quadData.data());
            shouldUpdateBuffer = false;
        }
    }
}