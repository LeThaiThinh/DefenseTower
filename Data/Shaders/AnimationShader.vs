attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;
varying 	vec2 	v_uv;
uniform 	mat4 	u_wvpMatrix;
uniform     float   u_numFrames;
uniform     float   u_numFramesInLine;
uniform     float   u_numLines;
uniform     float   u_currentFrame;
uniform     float   u_currentColumn;
uniform     float   u_currentLine;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_wvpMatrix * posL;
	v_uv = vec2(a_uv.x/u_numFramesInLine + u_currentColumn/u_numFramesInLine, a_uv.y/u_numLines + u_currentLine/u_numLines);
}
   
