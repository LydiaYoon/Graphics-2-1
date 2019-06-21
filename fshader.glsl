// fshader.glsl
#version 140

in vec4 pos;
in vec4 color;
out vec4 fcolor;

void main()
{
	float rad = pos.x*pos.x + pos.y*pos.y;
	rad = sqrt(rad);

	if (abs(pos.z) == 0.5)
	{
		if (rad<0.25)
			fcolor = vec4(1,0,0,1.0); // »¡°£»ö
		else if (rad<0.4)
		{
			if (pos.z>0.0) // À­¸é
				fcolor = vec4(1,1,0,1.0); // ³ë¶õ»ö
			else if (pos.z<0.0) // ¾Æ·§¸é
				fcolor = vec4(1,1,1,1.0); // Èò»ö
		}
		else
			fcolor = vec4(0,1,0,1.0); // ³ì»ö
	}
	else if (rad>=0.4 && abs(pos.z)>0.47)
		fcolor = vec4(0,1,0,1.0); // ³ì»ö
	else fcolor = color;
}
