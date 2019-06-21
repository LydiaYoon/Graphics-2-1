// vshader.glsl
#version 140

uniform float uTime;

in vec4 vPosition;
in vec4 vColor;

out vec4 pos;
out vec4 color;

void main()
{
	mat4 m1 = mat4(1.0); // z축 회전
	m1[0][0] = cos(uTime);		m1[1][0] = -sin(uTime);
	m1[0][1] = sin(uTime);		m1[1][1] = cos(uTime);

	mat4 m2 = mat4(1.0); // y축 회전
	m2[0][0] = cos(uTime*2);	m2[2][0] = sin(uTime*2);
	m2[0][2] = -sin(uTime*2);	m2[2][2] = cos(uTime*2);

	mat4 m3 = mat4(1.0); // x축 회전
	m3[1][1] = cos(uTime*3);	m3[2][1] = -sin(uTime*3);
	m3[1][2] = sin(uTime*3);	m3[2][2] = cos(uTime*3);

	gl_Position = m3 * m2 * m1 * vPosition;
	pos = vPosition;
	color = vColor;
}




/*
	m1[0][0] = cos(uTime);		m1[1][0] = -sin(uTime);		m1[2][0] = 0;
	m1[0][1] = sin(uTime);		m1[1][1] = cos(uTime);		m1[2][1] = 0;
	m1[0][2] = 0;				m1[1][2] = 0;				m1[2][2] = 1;

	m2[0][0] = cos(uTime*2);	m2[1][0] = 0;				m2[2][0] = sin(uTime*2);
	m2[0][1] = 0;				m2[1][1] = 1;				m2[2][1] = 0;
	m2[0][2] = -sin(uTime*2);	m2[1][2] = 0;				m2[2][2] = cos(uTime*2);

	m3[0][0] = 1;				m3[1][0] = 0;				m3[2][0] = 0;
	m3[0][1] = 0;				m3[1][1] = cos(uTime*3);	m3[2][1] = -sin(uTime*3);
	m3[0][2] = 0;				m3[1][2] = sin(uTime*3);	m3[2][2] = cos(uTime*3);
*/