precision mediump float; 

uniform vec4 u_PointLightPos;
uniform vec4 u_AmbientLightCol; 
uniform vec4 u_PointLightCol; //DiffuseLightCol and SpecularLightCol

uniform vec4 u_PointLightSpotDir;
uniform float u_PointLightExp;
uniform float u_PointLightCutOff; 

uniform vec4 u_PointLightPos2;
uniform vec4 u_AmbientLightCol2; 
uniform vec4 u_PointLightCol2; //DiffuseLightCol and SpecularLightCol

uniform vec4 u_PointLightSpotDir2;
uniform float u_PointLightExp2;
uniform float u_PointLightCutOff2; 

uniform vec4 u_PointLightPos3;
uniform vec4 u_AmbientLightCol3; 
uniform vec4 u_PointLightCol3; //DiffuseLightCol and SpecularLightCol

uniform vec4 u_PointLightSpotDir3;
uniform float u_PointLightExp3;
uniform float u_PointLightCutOff3; 


uniform vec3 distanceAttenuationFactors;
uniform int distanceAttenuationFlag;

uniform vec4 u_AmbientMat, u_DiffuseMat, u_SpecularMat;
uniform float u_SpecularPow; // Must be positive

uniform bool u_isTextureOn; 
uniform sampler2D u_Texture; 

varying vec4 v_P;
varying vec3 v_N;
varying vec2 v_TexCoord; 

const float c_zero = 0.0;
const float c_one = 1.0;

void main(void)  { 

	vec4 total = vec4(c_zero, c_zero, c_zero, c_zero); 

	vec3 N = normalize(v_N);  
	vec3 L;
	vec3 V = normalize(-v_P.xyz);
	vec3 R;
	float NdotL;
	
	vec4 tmpCol = vec4(c_zero, c_zero, c_zero, c_zero); 
	vec3 att_dist;
	float att_factor;
	float spot_factor;

	att_factor = c_one;

	//°¨¼èÈ¿°ú
	
	if(u_PointLightPos.w != c_zero)
	{
		
		L = u_PointLightPos.xyz - v_P.xyz;
		
		if(distanceAttenuationFlag == 1)
		{
			att_dist.x = c_one;
			att_dist.y = dot(L,L);
			att_dist.z = att_dist.y * att_dist.y ;
			att_factor = c_one/dot(att_dist,distanceAttenuationFactors);
		}
		
		L = normalize(L);
		
		// spot	
		
		if(u_PointLightCutOff < 180.0 )
		{
			vec3 spot_dir = normalize(u_PointLightSpotDir.xyz);
			//vec3 spot_dir = normalize(vec3(0.0, 0.0, -1.0));
			spot_factor = dot(-L, spot_dir);
			if(spot_factor >= cos(radians(u_PointLightCutOff)))
			{
				spot_factor = pow(spot_factor,u_PointLightExp);
			}
			else
			{
				spot_factor = c_zero;
			}
			att_factor *= spot_factor;
		}
		
	}
	else
	{
		L = u_PointLightPos.xyz;
		L = normalize(L);
	}
	
		
	R = reflect(-L, N); // N must be a unit vector
	NdotL = max(dot(N, L), c_zero);
	
	if(att_factor > c_zero){	
	
		if (NdotL > c_zero){
			tmpCol = u_DiffuseMat * NdotL; 
			tmpCol += u_SpecularMat * pow(max(dot(R, V), c_zero), u_SpecularPow);
			tmpCol *= u_PointLightCol; 
		}
		
		tmpCol += u_AmbientLightCol*u_AmbientMat; 	
		tmpCol *= att_factor;
	}
	
	total += tmpCol;
	
	// second
	
	tmpCol = vec4(c_zero, c_zero, c_zero, c_zero); 
	att_factor = c_one;

	//°¨¼èÈ¿°ú
	
	if(u_PointLightPos2.w != c_zero)
	{
		
		L = u_PointLightPos2.xyz - v_P.xyz;
		
		if(distanceAttenuationFlag == 1)
		{
			att_dist.x = c_one;
			att_dist.y = dot(L,L);
			att_dist.z = att_dist.y * att_dist.y ;
			att_factor = c_one/dot(att_dist,distanceAttenuationFactors);
		}
		
		L = normalize(L);
		
		// spot	
		
		if(u_PointLightCutOff2 < 180.0 )
		{
			vec3 spot_dir = normalize(u_PointLightSpotDir2.xyz);
			//vec3 spot_dir = normalize(vec3(0.0, 0.0, -1.0));
			spot_factor = dot(-L, spot_dir);
			if(spot_factor >= cos(radians(u_PointLightCutOff2)))
			{
				spot_factor = pow(spot_factor,u_PointLightExp2);
			}
			else
			{
				spot_factor = c_zero;
			}
			att_factor *= spot_factor;
		}
		
	}
	else
	{
		L = u_PointLightPos2.xyz;
		L = normalize(L);
	}
	
		
	R = reflect(-L, N); // N must be a unit vector
	NdotL = max(dot(N, L), c_zero);
	
	if(att_factor > c_zero){	
	
		if (NdotL > c_zero){
			tmpCol = u_DiffuseMat * NdotL; 
			tmpCol += u_SpecularMat * pow(max(dot(R, V), c_zero), u_SpecularPow);
			tmpCol *= u_PointLightCol2; 
		}
		
		tmpCol += u_AmbientLightCol2*u_AmbientMat; 	
		tmpCol *= att_factor;
	}
	
	total += tmpCol;
	
	// third
	
	
	tmpCol = vec4(c_zero, c_zero, c_zero, c_zero); 
	att_factor = c_one;

	//°¨¼èÈ¿°ú
	
	if(u_PointLightPos3.w != c_zero)
	{
		
		L = u_PointLightPos3.xyz - v_P.xyz;
		
		if(distanceAttenuationFlag == 1)
		{
			att_dist.x = c_one;
			att_dist.y = dot(L,L);
			att_dist.z = att_dist.y * att_dist.y ;
			att_factor = c_one/dot(att_dist,distanceAttenuationFactors);
		}
		
		L = normalize(L);
		
		// spot	
		
		if(u_PointLightCutOff3 < 180.0 )
		{
			vec3 spot_dir = normalize(u_PointLightSpotDir3.xyz);
			//vec3 spot_dir = normalize(vec3(0.0, 0.0, -1.0));
			spot_factor = dot(-L, spot_dir);
			if(spot_factor >= cos(radians(u_PointLightCutOff3)))
			{
				spot_factor = pow(spot_factor,u_PointLightExp3);
			}
			else
			{
				spot_factor = c_zero;
			}
			att_factor *= spot_factor;
		}
		
	}
	else
	{
		L = u_PointLightPos3.xyz;
		L = normalize(L);
	}
	
		
	R = reflect(-L, N); // N must be a unit vector
	NdotL = max(dot(N, L), c_zero);
	
	if(att_factor > c_zero){	
	
		if (NdotL > c_zero){
			tmpCol = u_DiffuseMat * NdotL; 
			tmpCol += u_SpecularMat * pow(max(dot(R, V), c_zero), u_SpecularPow);
			tmpCol *= u_PointLightCol3; 
		}
		
		tmpCol += u_AmbientLightCol3*u_AmbientMat; 	
		tmpCol *= att_factor;
	}
	
	total += tmpCol;
	
	//Modulate method. (= GL_MODULATE)
		if (u_isTextureOn)  { 
			vec4 TextureCol = texture2D(u_Texture, v_TexCoord.xy); 
			gl_FragColor = TextureCol*total; 
		} 
		else 
			gl_FragColor = total; 
}
