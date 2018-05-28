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
		
		struct VertexData
		{
			glm::vec3 position;
			glm::vec2 uv;
		};
		std::vector<VertexData> vertexData;
		for (int i = 0 ; i < sizeof(pts) / sizeof(pts[0]) ; ++i)
		{
			
			vertexData.push_back({ pts[i],texCoords[i] });
		}

		//创建VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(3* sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}
	virtual bool OnGPUProgram() override
	{
		program = ShaderUtil::CreateProgram("shaders/demo/Cube.vert", "shaders/demo/Cube.frag");
		mvpLocation = glGetUniformLocation(program, "mvp");
		textureLocation = glGetUniformLocation(program, "base");

		Image img = Image::LoadFromFile("asserts/images/terrains/1.jpg");
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
		glUseProgram(program);
		glm::mat4 mvp = Camera::GetCamera()->getViewProjectionMatrix()* transform.GetTransformMatrixWithScale();
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureLocation, 0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUseProgram(0);
	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
	GLuint mvpLocation;
	GLuint texture;
	GLuint textureLocation;
};