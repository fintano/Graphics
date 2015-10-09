package openGLES;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import openGLES.Userdata;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import object.AxisX;
import object.AxisY;
import object.AxisZ;
import object.Object;
import object.ObjectLoader;
import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLException;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.GLWrapper;
import android.opengl.Matrix;
import android.os.SystemClock;
import android.util.FloatMath;
import android.util.Log;

import com.example.gles20ex1.R;

public class TestRender implements GLSurfaceView.Renderer {

	/* Constructor */
	public TestRender(Context context) {
		mContext = context;
		Matrix.setIdentityM(mMVStack, 0);
		Matrix.setIdentityM(mPStack, 0);
		mMVStackOffset += 16;
		mPStackOffset += 16;
	}

	private String readShader(Context context, int ShaderID) {
		StringBuffer shaderbuffer = new StringBuffer();

		// read the files
		try {
			InputStream inputStream = context.getResources().openRawResource(
					ShaderID);
			// setup Buffered reader
			BufferedReader in = new BufferedReader(new InputStreamReader(
					inputStream));

			String read = in.readLine();
			while (read != null) {
				shaderbuffer.append(read + "\n");
				read = in.readLine();
			}

			shaderbuffer.deleteCharAt(shaderbuffer.length() - 1);

		} catch (Exception e) {
			Log.d("ERROR-readingShader",
					"Could not read shader: " + e.getLocalizedMessage());
		}

		return shaderbuffer.toString();
	}

	private static int loadShader(int type, String shaderSrc) {
		int shader;
		int[] compiled = new int[1];

		// Create the shader object
		shader = GLES20.glCreateShader(type);

		if (shader == 0)
			return 0;

		// Load the shader source
		GLES20.glShaderSource(shader, shaderSrc);

		// Compile the shader
		GLES20.glCompileShader(shader);

		// Check the compile status
		GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compiled, 0);

		if (compiled[0] == 0) {
			Log.e("Error", GLES20.glGetShaderInfoLog(shader));
			GLES20.glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {

		int[] VertexShaderId = new int[programCount];
		int[] FragmentShaderId = new int[programCount];

		VertexShaderId[0] = R.raw.phongvertexshader;
		FragmentShaderId[0] = R.raw.phongfragmentshader;
		VertexShaderId[1] = R.raw.halfwayphongvertexshader;
		FragmentShaderId[1] = R.raw.halfwayphongfragmentshader;
		VertexShaderId[2] = R.raw.axisvertexshader;
		FragmentShaderId[2] = R.raw.axisfragmentshader;

		String[] vShaderStr = new String[programCount];
		String[] fShaderStr = new String[programCount];
		

		// Load the shader and get a linked program object
		int[] linked = new int[1];
		int[] vertexShader = new int[programCount];
		int[] fragmentShader = new int[programCount];

		for (int i = 0; i < programCount; ++i) {
			vShaderStr[i] = readShader(mContext, VertexShaderId[i]);
			fShaderStr[i] = readShader(mContext, FragmentShaderId[i]);

			// Load the shader and get a linked program object
			vertexShader[i] = loadShader(GLES20.GL_VERTEX_SHADER, vShaderStr[i]);
			fragmentShader[i] = loadShader(GLES20.GL_FRAGMENT_SHADER,
					fShaderStr[i]);
			if ((vertexShader[i] == 0) || (fragmentShader[i] == 0))
				return;

			data[i] = new Userdata();
			data[i].Program = GLES20.glCreateProgram();
			if (data[i].Program == 0)
				return;	

			GLES20.glAttachShader(data[i].Program, vertexShader[i]);
			GLES20.glAttachShader(data[i].Program, fragmentShader[i]);
			GLES20.glLinkProgram(data[i].Program);

			// Link the program
			GLES20.glGetProgramiv(data[i].Program,
					GLES20.GL_LINK_STATUS, linked, 0);

			if (linked[0] == 0) {
				Log.e("ERROR", "Error linking program:");
				Log.e("ERROR",
						GLES20.glGetProgramInfoLog(data[i].Program));
				GLES20.glDeleteProgram(data[i].Program);
				return;
			}

			// Free up no longer needed shader resources
			GLES20.glDeleteShader(vertexShader[i]);
			GLES20.glDeleteShader(fragmentShader[i]);

			// Get attribute locations
			data[i].VertexLoc = GLES20.glGetAttribLocation(data[i].Program, "a_Vertex");
			data[i].NormalLoc = GLES20.glGetAttribLocation(data[i].Program, "a_Normal");
			data[i].TextureLoc = GLES20.glGetAttribLocation(
					data[i].Program, "a_TexCoord");

			// Get uniform locations
			data[i].ModelViewMatrixLoc = GLES20.glGetUniformLocation(data[i].Program,
					"u_ModelViewMatrix");
			data[i].ModelViewInvTransMatrixLoc = GLES20.glGetUniformLocation(data[i].Program,
					"u_ModelViewInvTransMatrix");
			data[i].ModelViewProjectionMatrixLoc = GLES20.glGetUniformLocation(data[i].Program,
					"u_ModelViewProjectionMatrix");
			
			data[i].TextureUniformLoc = GLES20.glGetUniformLocation(
					data[i].Program, "u_Texture");
			
			//
			//for(int j=0; j<numberOfLights ; j++){
				
			data[i].PointLightSpotDirLoc[0] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightSpotDir");
			data[i].PointLightExpLoc[0] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightExp");
			data[i].PointLightCutOffLoc[0] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightCutOff");
			
			data[i].PointLightPosLoc[0] = GLES20.glGetUniformLocation(data[i].Program,
					"u_PointLightPos");
			data[i].PointLightColLoc[0] = GLES20.glGetUniformLocation(data[i].Program,
					"u_PointLightCol");
			data[i].AmbientLightColLoc[0] = GLES20.glGetUniformLocation(data[i].Program,
					"u_AmbientLightCol");
			
			data[i].PointLightSpotDirLoc[1] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightSpotDir2");
			data[i].PointLightExpLoc[1] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightExp2");
			data[i].PointLightCutOffLoc[1] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightCutOff2");
			
			data[i].PointLightPosLoc[1] = GLES20.glGetUniformLocation(data[i].Program,
					"u_PointLightPos2");
			data[i].PointLightColLoc[1] = GLES20.glGetUniformLocation(data[i].Program,
					"u_PointLightCol2");
			data[i].AmbientLightColLoc[1] = GLES20.glGetUniformLocation(data[i].Program,
					"u_AmbientLightCol2");
			
			data[i].PointLightSpotDirLoc[2] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightSpotDir3");
			data[i].PointLightExpLoc[2] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightExp3");
			data[i].PointLightCutOffLoc[2] = GLES20.glGetUniformLocation(data[i].Program, "u_PointLightCutOff3");
			
			data[i].PointLightPosLoc[2] = GLES20.glGetUniformLocation(data[i].Program,
					"u_PointLightPos3");
			data[i].PointLightColLoc[2] = GLES20.glGetUniformLocation(data[i].Program,
					"u_PointLightCol3");
			data[i].AmbientLightColLoc[2] = GLES20.glGetUniformLocation(data[i].Program,
					"u_AmbientLightCol3");
			//}
			
			//data[i].lightSourceInfoLoc = GLES20.glGetUniformLocation(data[i].Program, "lights[0]");
			
			
			
			data[i].distanceAttenuationFlagLoc = GLES20.glGetUniformLocation(data[i].Program, "distanceAttenuationFlag");
			data[i].distanceAttenuationLoc = GLES20.glGetUniformLocation(data[i].Program, "distanceAttenuationFactors");
			
			data[i].AmbientMatLoc = GLES20
					.glGetUniformLocation(data[i].Program, "u_AmbientMat");
			data[i].DiffuseMatLoc = GLES20
					.glGetUniformLocation(data[i].Program, "u_DiffuseMat");
			data[i].SpecularMatLoc = GLES20.glGetUniformLocation(data[i].Program,
					"u_SpecularMat");
			data[i].SpecularPowLoc = GLES20.glGetUniformLocation(data[i].Program,
					"u_SpecularPow");
			
			data[i].isOnTextureLoc = GLES20.glGetUniformLocation(data[i].Program,
					"u_isTextureOn");
		}

		objldr = new ObjectLoader();
		//cow = new ObjectLoader();
		chair = new ObjectLoader();
		platter = new ObjectLoader();
		bookshelf = new ObjectLoader();
		ironMan = new ObjectLoader();
		floor = new ObjectLoader();
		table = new ObjectLoader();
		
		for(int i = 0 ; i< 16 ; i++){
			if(i<4)
				subChair[i] = new ObjectLoader();
			if(i<1)
				subSubChair[i] = new ObjectLoader();
			if(i<1)
				subSubSubChair[i] = new ObjectLoader();
		}
		try {
			table.load(mContext,R.raw.table, "table.jpg");
			floor.load(mContext, R.raw.book, "book.jpg");
			objldr.load(mContext, R.raw.tiger, "tiger_tex.jpg");
			//cow.load(mContext,R.raw.cow, "");
			platter.load(mContext, R.raw.platter, "platter.jpg");
			chair.load(mContext, R.raw.chair, "chair.jpg");
			bookshelf.load(mContext, com.example.gles20ex1.R.raw.booksh, "bookshelf.jpg");
			ironMan.load(mContext,com.example.gles20ex1.R.raw.ironman,"IronMan_D.jpg");
			
			for(int i = 0 ; i< 16 ; i++){
				if(i<4)
					subChair[i].load(mContext, R.raw.chair, "chair.jpg");
				if(i<1)
					subSubChair[i].load(mContext, R.raw.chair, "chair.jpg");
				if(i<1)
					subSubSubChair[i].load(mContext, R.raw.chair, "chair.jpg");
			}
			
		}
		catch (IOException e) {
			e.printStackTrace();
		}

		axisX = new AxisX();
		axisY = new AxisY();
		axisZ = new AxisZ();

		axisX.initShapes();
		axisY.initShapes();
		axisZ.initShapes();

		mCamera = new Camera();
		
	
		// depth test
		GLES20.glEnable(GLES20.GL_DEPTH_TEST);
		// cull backface
		GLES20.glEnable(GLES20.GL_CULL_FACE);
		GLES20.glCullFace(GLES20.GL_BACK);

	}

	public void onDrawFrame(GL10 glUnused) {
		GLES20.glClearColor(0.01f, 0.23f, 0.33f, 1.0f);

		// Clear the color buffer
		GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);

		// Set up projection matrix
		float fovy = mCamera.getFovy();
		Perspective(fovy, ratio, NEAR, FAR);
		
		
		// lightSource in EC
		
		if(LBox == 1){
		GLES20.glUniform4fv(data[renderMode].PointLightPosLoc[0], 1, cameraPointLightPos, 0);
		
		GLES20.glUniform4fv(data[renderMode].PointLightSpotDirLoc[0], 1, cameraPointLightSpotDir,0);
		
		GLES20.glUniform1f(data[renderMode].PointLightCutOffLoc[0], 10.0f);
		GLES20.glUniform1f(data[renderMode].PointLightExpLoc[0], 10.0f);
		
		GLES20.glUniform4fv(data[renderMode].PointLightColLoc[0], 1,cameraPointLightCol, 0);
		GLES20.glUniform4fv(data[renderMode].AmbientLightColLoc[0], 1,cameraPointambientLightCol, 0);
		
		GLES20.glUniform1f(data[renderMode].distanceAttenuationFlagLoc, 1);
		GLES20.glUniform3fv(data[renderMode].distanceAttenuationLoc, 1, attenuation, 0);
		}
		else{
			GLES20.glUniform1f(data[renderMode].PointLightCutOffLoc[0], 0.0f);
		}
		
		
		// Set up viewing matrix
		mVMatrix = mCamera.GetViewMatrix();
		Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack,
				mMVStackOffset - 16, mVMatrix, 0);
		
		mMVStackOffset += 16; // Push Matrix

		// lightSource in WC
		if(MBox == 1){
		float[] lightPosition = new float[4];
		Matrix.multiplyMV(lightPosition, 0, mMVStack, mMVStackOffset - 16, pointLightPos, 0);
		GLES20.glUniform4fv(data[renderMode].PointLightPosLoc[1], 1, lightPosition, 0);
		
		GLES20.glUniform4fv(data[renderMode].PointLightSpotDirLoc[1], 1, pointLightSpotDir,0);
		GLES20.glUniform1f(data[renderMode].PointLightCutOffLoc[1], 20.0f);
		GLES20.glUniform1f(data[renderMode].PointLightExpLoc[1], 5.0f);
	
		GLES20.glUniform4fv(data[renderMode].PointLightColLoc[1], 1,pointLightCol, 0);
		GLES20.glUniform4fv(data[renderMode].AmbientLightColLoc[1], 1,ambientLightCol, 0);
		}
		else{
			GLES20.glUniform1f(data[renderMode].PointLightCutOffLoc[1], 0.0f);
		}
		drawHierarchicalObject();
		
		// other objects 
		Matrix.setIdentityM(mMMatrix, 0);
		Matrix.rotateM(mMMatrix, 0, 45, 0, 1, 0);
		Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
		mMVStackOffset += 16; // Push Matrix
		drawObject(data[renderMode], bookshelf.object, 0, 0, 0, 1.0f, Color3);
		mMVStackOffset -= 16;
		Matrix.setIdentityM(mMMatrix, 0);
		Matrix.rotateM(mMMatrix, 0, ObjectRotate, 0.0f, 1.0f, 0.0f);//
		Matrix.translateM(mMMatrix, 0, 3, 0, 3);
		Matrix.rotateM(mMMatrix, 0, 45, 0, 1, 0);
		Matrix.scaleM(mMMatrix, 0, 1.5f, 1, 1.5f);
		Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
		
		mMVStackOffset += 16; // Push Matrix
		
		// lightSource in MC (ironman)
		
		if(RBox == 1){
			
			float[] lightPosition_MC = new float[4];
			Matrix.multiplyMV(lightPosition_MC, 0, mMVStack, mMVStackOffset - 16, ironPointLightPos,0);
		
			GLES20.glUniform4fv(data[renderMode].PointLightPosLoc[2], 1, lightPosition_MC, 0);
			GLES20.glUniform4fv(data[renderMode].PointLightColLoc[2], 1, ironPointLightCol, 0);
			GLES20.glUniform4fv(data[renderMode].AmbientLightColLoc[2], 1, ironPointambientLightCol, 0);
			GLES20.glUniform4fv(data[renderMode].PointLightSpotDirLoc[2], 1, ironPointLightSpotDir,0);
			GLES20.glUniform1f(data[renderMode].PointLightCutOffLoc[2], 15.0f);
			GLES20.glUniform1f(data[renderMode].PointLightExpLoc[2], 5.0f);
		}
		else{
			GLES20.glUniform1f(data[renderMode].PointLightCutOffLoc[2], 0.0f);
		}
		drawObject(data[renderMode], ironMan.object , 0, 0, 0, 1.0f, Color1);
	
		mMVStackOffset -= 16;
		
		Matrix.setIdentityM(mMMatrix, 0);
		Matrix.scaleM(mMMatrix, 0, 20, 1, 20);
		Matrix.translateM(mMMatrix, 0, -3.0f, -1.5f, 3.0f);
		Matrix.rotateM(mMMatrix, 0, 25, 0, 1, 0);
		Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
		mMVStackOffset += 16; // Push Matrix
		drawObject(data[renderMode], table.object, 0, 0, 0, 1.0f, ColorRed);
		mMVStackOffset -= 16;
		GLES20.glUseProgram(data[2].Program);
		
		// x축
		Matrix.setIdentityM(mMMatrix, 0);
		drawAxis(data[2],axisX, 0, 0, 0, 1.0f, ColorRed);

		// Y축
		Matrix.setIdentityM(mMMatrix, 0);
		drawAxis(data[2],axisY, 0, 0, 0, 1.0f, ColorGreen);

		// z축
		Matrix.setIdentityM(mMMatrix, 0);
		drawAxis(data[2],axisZ, 0, 0, 0, 1.0f, ColorBlue);

		GLES20.glUseProgram(data[renderMode].Program);
		
		mMVStackOffset -= 16; // Pop Matrix

		}

	public void drawHierarchicalObject(){
		
		for(int i=0; i< 4; i++){
			Matrix.setIdentityM(mMMatrix, 0);
			Matrix.rotateM(mMMatrix, 0, 90*i, 0, 1, 0);
			Matrix.translateM(mMMatrix, 0, -5, 1.5f, 3);
			Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
			mMVStackOffset += 16; // Push Matrix
			drawObject(data[renderMode],subChair[i].object , 0, 0, 0, 1.0f, Color1);
			
				Matrix.setIdentityM(mMMatrix, 0);
				Matrix.rotateM(mMMatrix, 0, -ObjectRotate, 0.0f, 1.0f, 0.0f);//
				Matrix.rotateM(mMMatrix, 0, 180, 0, 1, 0);
				Matrix.translateM(mMMatrix, 0, -5, 1.5f, 3);
				Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
				mMVStackOffset += 16; // Push Matrix
				drawObject(data[renderMode],subSubChair[0].object , 0, 0, 0, 1.0f, Color2);
				
					Matrix.setIdentityM(mMMatrix, 0);
					Matrix.rotateM(mMMatrix, 0, 180, 0, 1, 0);
					Matrix.translateM(mMMatrix, 0, -5, 1.5f, 3);
					Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
					mMVStackOffset += 16; // Push Matrix
					drawObject(data[renderMode],subSubSubChair[0].object , 0, 0, 0, 1.0f, Color3);
					mMVStackOffset -= 16;
				
				mMVStackOffset -= 16;
			
			mMVStackOffset -= 16;
		}
		Matrix.setIdentityM(mMMatrix, 0);
		Matrix.translateM(mMMatrix, 0, -5, 0, 3);
		Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
		mMVStackOffset += 16; // Push Matrix
		drawObject(data[renderMode], chair.object, 0, 0, 0, 1.0f, ColorRed);
		mMVStackOffset -= 16;
	}
	
	public void drawAxis(Userdata data, Object object, float x, float y, float z, float scale, float[] axisCol) {

		Matrix.scaleM(mMMatrix, 0, scale, scale, scale);
		Matrix.translateM(mMMatrix, 0, x, y, z);//		
		Matrix.multiplyMM(mMVStack, mMVStackOffset, mMVStack, mMVStackOffset - 16, mMMatrix, 0);
		mMVStackOffset += 16; // Push Matrix

		Matrix.setIdentityM(tempMatrix, 0);
		Matrix.setIdentityM(ModelViewMatrix, 0);
		Matrix.multiplyMM(ModelViewMatrix, 0, tempMatrix, 0, mMVStack, mMVStackOffset - 16);

		Matrix.setIdentityM(ModelViewInvTransMatrix, 0);
		Matrix.setIdentityM(tempMatrix, 0);
		Matrix.invertM(tempMatrix, 0, ModelViewMatrix, 0);
		Matrix.transposeM(ModelViewInvTransMatrix, 0, tempMatrix, 0);
		
		Matrix.multiplyMM(ModelViewProjectionMatrix, 0, mPStack, mPStackOffset - 16, mMVStack,
				mMVStackOffset - 16);
		
		GLES20.glUniformMatrix4fv(data.ModelViewProjectionMatrixLoc, 1, false, ModelViewProjectionMatrix, 0);
		GLES20.glUniform4fv(data.DiffuseMatLoc, 1, axisCol, 0);
		
		object.draw(data);

		mMVStackOffset -= 16;
	}
	
	// 오브젝트를 그리는 함수
	// Object object : 그릴대상이 되는 오브젝트
	// float x : 오브젝트의 x축이동
	// float y : 오브젝트의 y축이동
	// float z : 오브젝트의 z축이동
	// float scale : 오브젝트 몇배 크기 확대
	public void drawObject(Userdata data, Object object, float x, float y, float z, float scale, float[] diffuseMat) {


		Matrix.setIdentityM(tempMatrix, 0);
		Matrix.setIdentityM(ModelViewMatrix, 0);
		Matrix.multiplyMM(ModelViewMatrix, 0, tempMatrix, 0, mMVStack, mMVStackOffset - 16);

		Matrix.setIdentityM(ModelViewInvTransMatrix, 0);
		Matrix.setIdentityM(tempMatrix, 0);
		Matrix.invertM(tempMatrix, 0, ModelViewMatrix, 0);
		Matrix.transposeM(ModelViewInvTransMatrix, 0, tempMatrix, 0);
		
		Matrix.multiplyMM(ModelViewProjectionMatrix, 0, mPStack, mPStackOffset - 16, mMVStack,
				mMVStackOffset - 16);
		
		GLES20.glUniformMatrix4fv(data.ModelViewMatrixLoc, 1, false, ModelViewMatrix, 0);
		GLES20.glUniformMatrix4fv(data.ModelViewInvTransMatrixLoc, 1, false, ModelViewInvTransMatrix, 0);
		GLES20.glUniformMatrix4fv(data.ModelViewProjectionMatrixLoc, 1, false, ModelViewProjectionMatrix, 0);

		GLES20.glUniform4fv(data.AmbientMatLoc, 1, ambientMat, 0);
		GLES20.glUniform4fv(data.DiffuseMatLoc, 1, diffuseMat, 0);
		GLES20.glUniform4fv(data.SpecularMatLoc, 1, specularMat, 0);
		GLES20.glUniform1f(data.SpecularPowLoc, specularPow);
		
		if(textureMode == 1 && object.textureIds[0] != 0)
			GLES20.glUniform1i(data.isOnTextureLoc, 1);
		else
			GLES20.glUniform1i(data.isOnTextureLoc, 0);
		
		object.draw(data);

		//mMVStackOffset -= 16;
	}
	
	public void onSurfaceChanged(GL10 glUnused, int width, int height) {
		// Set the viewport
		GLES20.glViewport(0, 0, width, height);
		ratio = (float) width / (float) height;

		// Set up projection matrix
		float fovy = mCamera.getFovy();
		Perspective(fovy, ratio, NEAR, FAR);
	}

	// Perspective함수
	void Perspective(float fovy, float aspect, float nearZ, float farZ) {
		float frustumW, frustumH;
		frustumH = nearZ * FloatMath.sin(fovy / 2) / FloatMath.cos(fovy); // near * tan
		frustumW = frustumH * aspect;
		Matrix.setIdentityM(mPStack, 0);
		Matrix.frustumM(mPStack, mPStackOffset - 16, -frustumW, frustumW,
				-frustumH, frustumH, nearZ, farZ);
	}
	
	public Camera getCamera(){
		return mCamera;
	}

	
	// Context
	private Context mContext;

	private final static int programCount = 3;
	
	private float[] mMVStack = new float[256];
	private float[] mPStack = new float[256];
	private int mMVStackOffset = 0;
	private int mPStackOffset = 0;
	
	// MVP matrix
	private float[] ModelViewMatrix = new float[16];
	private float[] ModelViewInvTransMatrix = new float[16];
	private float[] ModelViewProjectionMatrix = new float[16];
	private float[] tempMatrix = new float[16];

	// Model Matrix
	private float[] mMMatrix = new float[16];

	// View Matrix
	private float[] mVMatrix = new float[16];

	private float ratio;
	private final static float NEAR = 0.1f;
	private final static float FAR = 100000.0f;

	// 카메라 클래스
	public static int renderMode = 0;// 0 퐁 1고라드
	public static int textureMode = 0;// 0 on 1 off

	// 카메라 클래스
	public Camera mCamera;

	// 사용하는 쉐이더의 program,attribute등을 갖고있는 클래스
	private Userdata[] data = new Userdata[programCount];

	// Object data
	private ObjectLoader objldr, platter, chair,table;
	private ObjectLoader subChair[] = new ObjectLoader[4];
	private ObjectLoader subSubChair[] = new ObjectLoader[1];
	private ObjectLoader subSubSubChair[] = new ObjectLoader[1];
	private ObjectLoader ironMan, bookshelf, floor;
	public float ObjectRotate;

	// 색상저장한 변수
	float[] ColorGray = {0.1f, 0.1f, 0.1f, 1.0f };
	float[] ColorRed = { 1.0f, 0.0f, 0.0f, 1.0f };
	float[] ColorGreen = { 0.0f, 1.0f, 0.0f, 1.0f };
	float[] ColorBlue = { 0.0f, 0.0f, 1.0f, 1.0f };
	float[] Color1 = { 0.5675f, 0.2355f, 0.7856f, 1.0f};
	float[] Color2 = { 0.8144f, 0.5223f, 0.2444f, 1.0f};
	float[] Color3 = { 0.1144f, 0.4563f, 0.5124f, 1.0f};
	// 축오브젝트
	private AxisX axisX;
	private AxisY axisY;
	private AxisZ axisZ;
	
	// ironman light
	
	private float[] ironPointLightPos = {3.0f, 3.0f, 3.0f, 1.0f };
	private float[] ironPointLightSpotDir = {1.0f, -2.0f, 0.0f, 0.0f};
	private float[] ironPointambientLightCol = {0.8f, 0.7f, 0.6f, 1.0f};
	private float[] ironPointLightCol = {0.8f, 0.85f, 0.8f, 1.0f};
	
	
	// Light info of camera
	private float[] cameraPointLightPos = { 0.0f, 1.0f, 0.0f, 1.0f};
	private float[] cameraPointLightSpotDir = {0.0f, -1.0f, -5.0f, 0.0f};
	private float[] cameraPointambientLightCol = {0.8f, 0.7f, 0.6f, 1.0f};
	private float[] cameraPointLightCol = {0.8f, 0.85f, 0.8f, 1.0f};
	
	private float[] attenuation = {0.01f, 0.001f, 0.00025f};
	
	// Light info
	private float[] pointLightPos = { 0.0f, 15.0f, 0.0f, 1.0f };
	private float[] pointLightSpotDir = {0.0f, -1.0f, 0.0f, 0.0f};
	private float[] ambientLightCol = {0.3f, 0.3f, 0.3f, 1.0f};
	private float[] pointLightCol = {0.99f, 0.85f, 0.8f, 1.0f}; // diffuse and specular light color
	
	// Material info
	private float[] ambientMat = { 0.5f, 0.5f, 0.5f, 1.0f };
	private float[] specularMat = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	private float specularPow = 10.0f; // Must be positive
	
	public  int LBox = 0;
	public  int MBox = 0;
	public  int RBox = 0;
}
