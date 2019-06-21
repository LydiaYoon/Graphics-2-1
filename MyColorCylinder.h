#pragma once
//������ �ҷ��� ���� ó���� �ҷ��� �ѹ��� ��ȿ��

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
	int NumPolygon; // �ٰ��� ���� ����
	int NumTriangle; // �ʿ��� �ﰢ���� ����
	int NumVertex; // �ʿ��� ���� ����
	float radius; // ������

	CylinderVertex * vertices; // ������ ���� ���� ����ü
	vec4 * vertex_pos;
	vec4 * vertex_colors;
	int index;

	GLuint vao;
	GLuint buf;
	GLuint prog;
	bool bInit; // �ʱ�ȭ�Ǿ����� Ȯ��
	float time;

	
	MyColorCylinder()	//������
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
		// Ȥ�� �ι��ҷ��� ���� ������ ����
		colorcylinder();

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
 
		glGenBuffers(1, &buf);
		glBindBuffer(GL_ARRAY_BUFFER, buf);

		// GL_STATIC_DRAW : �� �����ʹ� �ٲ��� �ʴ´�
		glBufferData(GL_ARRAY_BUFFER, sizeof(CylinderVertex)*NumVertex, vertices, GL_STATIC_DRAW);
		// ���۵����� �ϳ��� ����
		// ���� �ʿ��� ������ ����ü�� ���� �迭�� �ϳ���
		// �����Ҵ��� �ؼ� ũ�⸦ �˰������ CubeVertexũ���� Numvertex������ŭ ������;

		prog = InitShader("vshader.glsl", "fshader.glsl");
		glUseProgram(prog);

		GLuint vPosition = glGetAttribLocation(prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(CylinderVertex), BUFFER_OFFSET(0));
		// ó������ ���, ������ ��� ���� vec4��ŭ �����

		GLuint vColor = glGetAttribLocation(prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(CylinderVertex), BUFFER_OFFSET(sizeof(vec4)));

		//bInit = true; // init�� �� �ҷ��� �ʱ�ȭ�� �� �Ǹ� true
	
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
		vertices[index].pos = vec4(0,0,radius,1.0); // �߽���
		index++;
	}

	void colorcylinder()
	{
		index = 0; 
		// �Ǹ��� ���� �Ʒ���
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
		// �Ǹ��� ����
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
		NumPolygon = n; // �ٰ��� ���� ����
		NumTriangle = n*4; // �ʿ��� �ﰢ���� ����
		NumVertex = n*12; // �ʿ��� ���� ����

		if (vertices != NULL)
		{
			delete [] vertex_pos;
			delete [] vertex_colors;
			delete [] vertices;
		}// null�� �ƴϸ� �޸𸮸� �����
		vertex_pos = new vec4[NumVertex];
		vertex_colors = new vec4[NumVertex];
		vertices = new CylinderVertex[NumVertex];
		// �ʿ��� ���� ���� ��ŭ ���� �޸� �Ҵ�

		// �Ǹ��� ���κа� �Ʒ��κ��� vertex ����
		float dtheta =  PI * 2.0 / float(NumPolygon);
		for (int i=0; i<NumPolygon; i++)
		{
			vertex_pos[i] = vec4(cos(dtheta*i)*radius, sin(dtheta*i)*radius , radius, 1.0);
			vertex_pos[i+NumPolygon] = vec4(cos(dtheta*i)*radius, sin(dtheta*i)*radius , -radius, 1.0);
		}
		// �Ǹ��� ������ colors ����
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
		glBindVertexArray(vao); // �ѹ� �� ���ε�
		glUseProgram(prog);
		GLuint uTime = glGetUniformLocation(prog, "uTime");
		glUniform1f(uTime, time);
		glDrawArrays(GL_TRIANGLES, 0, NumVertex);
	}

};