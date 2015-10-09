package openGLES;

public class Userdata {

	// Handle to a program object
	public int Program;

	// Attribute locations
	public int VertexLoc;
	public int NormalLoc;
	public int TextureLoc;
	
	// Uniform location
	public int ModelViewMatrixLoc;
	public int ModelViewInvTransMatrixLoc;
	public int ModelViewProjectionMatrixLoc;
	
	public int TextureUniformLoc;
	
	public int PointLightPosLoc[] = new int[3];	
	public int PointLightColLoc[] = new int[3];
	public int AmbientLightColLoc[] = new int[3];
		
	public int PointLightSpotDirLoc[] = new int[3];
	public int PointLightCutOffLoc[] = new int[3];
	public int PointLightExpLoc[] = new int[3];
	
	//
	
	//public int lightSourceInfoLoc;
	
	public int distanceAttenuationLoc;
	public int distanceAttenuationFlagLoc;
	
	public int AmbientMatLoc;
	public int DiffuseMatLoc;
	public int SpecularMatLoc;
	public int SpecularPowLoc;
	
	public int isOnTextureLoc;

}
