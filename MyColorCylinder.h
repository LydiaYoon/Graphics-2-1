#pragma once
//여러번 불려도 제일 처음에 불려진 한번만 유효함

#include <vgl.h>
#include <vec.h>
#include <InitShader.h>

#define PI 3.14159265359f

struct CylinderVertex
{
	vec4 pos;
	vec4 color;
};

class MyColorCylinder
{
public:
	int NumPolygon; // 다각형 각의 갯수
	int NumTriangle; // 필요한 삼각형의 갯수
	int NumVertex; // 필요한 점의 갯수
	float radius; // 반지름

	CylinderVertex * vertices; // 실제로 값을 보낼 구조체
	vec4 * vertex_pos;
	vec4 * vertex_colors;
	int index;

	GLuint vao;
	GLuint buf;
	GLuint prog;
	bool bInit; // 초기화되었는지 확인
	float time;

	
	MyColorCylinder()	//생성자
	{
		NumPolygon = 10;
		NumTriangle = 40;
		NumVertex = 120;
		radius = 0.5;

		vertices = NULL;
		vertex_pos = NULL;
		vertex_colors = NULL;

		index = 0;
		bInit = false;
		time = 0.0;
	}

	void init()
	{
		//if (bInit == true) return;
		// 혹시 두번불렀을 때의 오류를 방지
		colorcylinder();

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
 
		glGenBuffers(1, &buf);
		glBindBuffer(GL_ARRAY_BUFFER, buf);

		// GL_STATIC_DRAW : 이 데이터는 바뀌지 않는다
		glBufferData(GL_ARRAY_BUFFER, sizeof(CylinderVertex)*NumVertex, vertices, GL_STATIC_DRAW);
		// 버퍼데이터 하나를 보냄
		// 점에 필요한 정보를 구조체로 만들어서 배열이 하나임
		// 동적할당을 해서 크기를 알고싶으면 CubeVertex크기의 Numvertex갯수만큼 보낸다;

		prog = InitShader("vshader.glsl", "fshader.glsl");
		glUseProgram(prog);

		GLuint vPosition = glGetAttribLocation(prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(CylinderVertex), BUFFER_OFFSET(0));
		// 처음부터 얻고, 다음에 얻는 값은 vec4만큼 띄워서

		GLuint vColor = glGetAttribLocation(prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(CylinderVertex), BUFFER_OFFSET(sizeof(vec4)));

		//bInit = true; // init이 잘 불려서 초기화가 잘 되면 true
	
	}

	void quad(int a, int b, int c, int d)
	{
		vertices[index].color = vertex_colors[a];
		vertices[index].pos = vertex_pos[a];
		index++;

		vertices[index].color = vertex_colors[a];
		vertices[index].pos = vertex_pos[b];
		index++;

		vertices[index].color = vertex_colors[a];
		vertices[index].pos = vertex_pos[c];
		index++;

		vertices[index].color = vertex_colors[a];
		vertices[index].pos = vertex_pos[a];
		index++;

		vertices[index].color = vertex_colors[a];
		vertices[index].pos = vertex_pos[c];
		index++;

		vertices[index].color = vertex_colors[a];
		vertices[index].pos = vertex_pos[d];
		index++;
	}

	void triangle(int a, int b, float radius)
	{	
		vertices[index].color = vec4(1,1,1,1.0);
		vertices[index].pos = vertex_pos[a];
		index++;

		vertices[index].color = vec4(1,1,1,1.0);
		vertices[index].pos = vertex_pos[b];
		index++;

		vertices[index].color = vec4(1,1,1,1.0);
		vertices[index].pos = vec4(0,0,radius,1.0); // 중심점
		index++;
	}

	void colorcylinder()
	{
		index = 0; 
		// 실린더 윗면 아랫면
		for (int i=0; i<NumPolygon; i++)
		{
			if (i != (NumPolygon-1))
			{
				triangle(i, i+1, radius);
				triangle(i+NumPolygon, i+1+NumPolygon, -radius);
			}
			else
			{
				triangle(i, 0, radius);
				triangle(NumPolygon*2-1, NumPolygon, -radius);
			}
		}
		// 실린더 옆면
		for (int i=0; i<NumPolygon; i++)
		{
			if (i != (NumPolygon-1))
				quad(i, i+1, i+NumPolygon+1, i+NumPolygon);
			else
				quad(i, 0, NumPolygon, NumPolygon*2-1);
		}
	}
	
	void GenerateNPolygon(int n)
	{
		NumPolygon = n; // 다각형 각의 갯수
		NumTriangle = n*4; // 필요한 삼각형의 갯수
		NumVertex = n*12; // 필요한 점의 갯수

		if (vertices != NULL)
		{
			delete [] vertex_pos;
			delete [] vertex_colors;
			delete [] vertices;
		}// null이 아니면 메모리를 지우고
		vertex_pos = new vec4[NumVertex];
		vertex_colors = new vec4[NumVertex];
		vertices = new CylinderVertex[NumVertex];
		// 필요한 점의 갯수 만큼 동적 메모리 할당

		// 실린더 윗부분과 아랫부분의 vertex 생성
		float dtheta =  PI * 2.0 / float(NumPolygon);
		for (int i=0; i<NumPolygon; i++)
		{
			vertex_pos[i] = vec4(cos(dtheta*i)*radius, sin(dtheta*i)*radius , radius, 1.0);
			vertex_pos[i+NumPolygon] = vec4(cos(dtheta*i)*radius, sin(dtheta*i)*radius , -radius, 1.0);
		}
		// 실린더 옆면의 colors 생성
		float sidecolor = 1.0 / (NumPolygon-1);
		for (int i=0; i<NumPolygon; i++)
		{
			vertex_colors[i] = vec4(1-(sidecolor*i), 0, sidecolor*i, 1.0);
			//vertex_colors[i+NumPolygon] = color4(1-(sidecolor*i), 0, sidecolor*i, 1.0);
		}
	}

	void setTime(float input)	{	time = input;	}

	void Draw()
	{
		glBindVertexArray(vao); // 한번 더 바인딩
		glUseProgram(prog);
		GLuint uTime = glGetUniformLocation(prog, "uTime");
		glUniform1f(uTime, time);
		glDrawArrays(GL_TRIANGLES, 0, NumVertex);
	}

};