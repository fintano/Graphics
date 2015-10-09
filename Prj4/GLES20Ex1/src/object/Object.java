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

	// Userdata data : � ���̴�,� �����͸� �̿��Ͽ� �׸��� �׸��� �˾ƾ��ϹǷ� �Ѱܹ޴´�.
	public void draw(Userdata data) {
		// Add program to OpenGL environment
		GLES20.glUseProgram(data.Program);

		mVerticesBuffer.position(0);
		GLES20.glVertexAttribPointer(data.VertexLoc, 3, GLES20.GL_FLOAT, false, 32, mVerticesBuffer);
		GLES20.glEnableVertexAttribArray(data.VertexLoc);

		mVerticesBuffer.position(3);
		GLES20.glVertexAttribPointer(data.NormalLoc, 3, GLES20.GL_FLOAT, false, 32, mVerticesBuffer);
		GLES20.glEnableVertexAttribArray(data.NormalLoc);

		// if ���������� �ؽ��ĸ� �ҷ��� �ؽ��� ���̵� �����ִٸ�, �ؽ��ĸ� ���ε��Ѵ�.
		// else �ؽ��ĸ� �̿����� �ʵ��� ��� ������� ���´�.
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
