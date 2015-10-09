package object;

import java.nio.FloatBuffer;

import openGLES.Userdata;
import android.opengl.GLES20;


//Object which uses glDrawArrays method.
public class Object {

	protected FloatBuffer mVerticesBuffer;
	public int[] textureIds = new int[1];
	public float[] vnt;
	public int mVertexCount = 0;

	// Userdata data : 어떤 쉐이더,어떤 포인터를 이용하여 그림을 그릴지 알아야하므로 넘겨받는다.
	public void draw(Userdata data) {
		// Add program to OpenGL environment
		GLES20.glUseProgram(data.Program);

		mVerticesBuffer.position(0);
		GLES20.glVertexAttribPointer(data.VertexLoc, 3, GLES20.GL_FLOAT, false, 32, mVerticesBuffer);
		GLES20.glEnableVertexAttribArray(data.VertexLoc);

		mVerticesBuffer.position(3);
		GLES20.glVertexAttribPointer(data.NormalLoc, 3, GLES20.GL_FLOAT, false, 32, mVerticesBuffer);
		GLES20.glEnableVertexAttribArray(data.NormalLoc);

		// if 정상적으로 텍스쳐를 불러와 텍스쳐 아이디를 갖고있다면, 텍스쳐를 바인딩한다.
		// else 텍스쳐를 이용하지 않도록 모든 연결고리를 끊는다.
		if (textureIds[0] != 0) {
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureIds[0]);
			GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
			GLES20.glUniform1i(data.TextureUniformLoc, 0);
			mVerticesBuffer.position(6);
			GLES20.glVertexAttribPointer(data.TextureLoc, 2, GLES20.GL_FLOAT, false, 32, mVerticesBuffer);
			GLES20.glEnableVertexAttribArray(data.TextureLoc);
		}
		else {
			GLES20.glDisableVertexAttribArray(data.TextureLoc);
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
		}
		
		GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, mVertexCount);
	}

}
