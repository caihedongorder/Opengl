#pragma once
#include "ModelBase.hpp"
#include <vector>

class CubeModel : public ModelBase
{
public:
	virtual bool OnCreateGeometry() override
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float l = -0.5f;
		float t = 0.5f;
		float w = 1.0f;
		float h = 1.0f;

		glm::vec3 pts[] = {
			//front
			glm::vec3(l,t,w*0.5f),
			glm::vec3(l + w,t - h ,w*0.5f),
			glm::vec3(l + w,t,w*0.5f),

			glm::vec3(l,t,w*0.5f),
			glm::vec3(l,t - h,w*0.5f),
			glm::vec3(l + w ,t - h ,w*0.5f),

			//back
			glm::vec3(l,t,-w * 0.5f),
			glm::vec3(l + w,t,-w * 0.5f),
			glm::vec3(l + w,t - h ,-w * 0.5f),

			glm::vec3(l,t,-w * 0.5f),
			glm::vec3(l + w ,t - h ,-w * 0.5f),
			glm::vec3(l,t - h,-w * 0.5f),

			//right
			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l + w,t - h,-w * 0.5f),
			glm::vec3(l + w,t,-w * 0.5f),

			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l + w,t - h,w*0.5f),
			glm::vec3(l + w,t - h,-w * 0.5f),

			//left
			glm::vec3(l ,t,w*0.5f),
			glm::vec3(l ,t,-w * 0.5f),
			glm::vec3(l ,t - h,-w * 0.5f),

			glm::vec3(l ,t,w*0.5f),
			glm::vec3(l ,t - h,-w * 0.5f),
			glm::vec3(l ,t - h,w*0.5f),

			//top
			glm::vec3(l,t,w*0.5f),
			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l,t,-w * 0.5f),

			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l + w,t,-w * 0.5f),
			glm::vec3(l,t,-w * 0.5f),

			//bottom
			glm::vec3(l,t - h,w*0.5f),
			glm::vec3(l,t - h,-w * 0.5f),
			glm::vec3(l + w,t - h,w*0.5f),

			glm::vec3(l + w,t - h,w*0.5f),
			glm::vec3(l,t - h,-w * 0.5f),
			glm::vec3(l + w,t - h,-w * 0.5f),
		};
		glm::vec2 texCoords[] = {
			//front
			glm::vec2(0.0,1.0f),
			glm::vec2(1.0f,0.0f),
			glm::vec2(1.0f,1.0f),

			glm::vec2(0.0f,1.0f),
			glm::vec2(0.0f,0.0f),
			glm::vec2(1.0f,0.0f),

			//back
			glm::vec2(0.0,1.0f),
			glm::vec2(1.0f,1.0f),
			glm::vec2(1.0f,0.0f),

			glm::vec2(0.0f,1.0f),
			glm::vec2(1.0f,0.0f),
			glm::vec2(0.0f,0.0f),

			//right
			glm::vec2(0.0,1.0f),
			glm::vec2(1.0f,0.0f),
			glm::vec2(1.0f,1.0f),

			glm::vec2(0.0f,1.0f),
			glm::vec2(0.0f,0.0f),
			glm::vec2(1.0f,0.0f),

			//left
			glm::vec2(0.0,1.0f),
			glm::vec2(1.0f,1.0f),
			glm::vec2(1.0f,0.0f),

			glm::vec2(0.0f,1.0f),
			glm::vec2(1.0f,0.0f),
			glm::vec2(0.0f,0.0f),

			//top
			glm::vec2(0.0,0.0f),
			glm::vec2(1.0f,0.0f),
			glm::vec2(0.0f,1.0f),

			glm::vec2(1.0f,0.0f),
			glm::vec2(1.0f,1.0f),
			glm::vec2(0.0f,1.0f),

			//bottom
			glm::vec2(0.0,0.0f),
			glm::vec2(0.0f,1.0f),
			glm::vec2(1.0f,0.0f),

			glm::vec2(1.0f,0.0f),
			glm::vec2(0.0f,1.0f),
			glm::vec2(1.0f,1.0f),
		};
		glm::vec3 normals[] = {
			//front
			glm::vec3(0,0,1),
			glm::vec3(0,0,1),
			glm::vec3(0,0,1),

			glm::vec3(0,0,1),
			glm::vec3(0,0,1),
			glm::vec3(0,0,1),
			

			//back
			glm::vec3(0,0,-1),
			glm::vec3(0,0,-1),
			glm::vec3(0,0,-1),

			glm::vec3(0,0,-1),
			glm::vec3(0,0,-1),
			glm::vec3(0,0,-1),

			//right
			glm::vec3(1,0,0),
			glm::vec3(1,0,0),
			glm::vec3(1,0,0),

			glm::vec3(1,0,0),
			glm::vec3(1,0,0),
			glm::vec3(1,0,0),


			//left
			glm::vec3(-1,0,0),
			glm::vec3(-1,0,0),
			glm::vec3(-1,0,0),

			glm::vec3(-1,0,0),
			glm::vec3(-1,0,0),
			glm::vec3(-1,0,0),

			//top
			glm::vec3(0,1,0),
			glm::vec3(0,1,0),
			glm::vec3(0,1,0),

			glm::vec3(0,1,0),
			glm::vec3(0,1,0),
			glm::vec3(0,1,0),


			//bottom
			glm::vec3(0,-1,0),
			glm::vec3(0,-1,0),
			glm::vec3(0,-1,0),

			glm::vec3(0,-1,0),
			glm::vec3(0,-1,0),
			glm::vec3(0,-1,0),
		};
		struct VertexData
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;
		};
		std::vector<VertexData> vertexData;
		for (int i = 0 ; i < sizeof(pts) / sizeof(pts[0]) ; ++i)
		{
			vertexData.push_back({ pts[i],normals[i],texCoords[i] });
		}

		//创建VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(3* sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(6* sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}
	virtual bool OnGPUProgram() override
	{
		program = ShaderUtil::CreateProgram("shaders/demo/Cube.vert", "shaders/demo/Cube.frag");
		if (!program)
		{
			return false;
		}
		glUseProgram(program);
		textureLocation = glGetUniformLocation(program, "base");
		ModelBase::OnGPUProgram();

		Image img = Image::LoadFromFile("asserts/images/blocks/2.jpg");
		if (!img.IsValid())
			return false;

		//创建纹理
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}
	virtual void OnRender() override
	{
		UseProgram();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureLocation, 0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		UnUseProgram();

	}
private:
	GLuint textureLocation;
	GLuint texture;
};