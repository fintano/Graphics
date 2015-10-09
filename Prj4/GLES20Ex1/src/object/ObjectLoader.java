package object;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.StringTokenizer;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.util.Log;

public class ObjectLoader {
	public Object object = null;

	private int texId=0;
	
	public Object getObject() {
		return object;
	}
	
	public void setTexId(int _texId) {
		texId = _texId;
	}
	
	public void load(Context context, int objectId, String texfile) throws IOException {
		int i, j;
		object = new Object();
		
		InputStream inputStream = context.getResources().openRawResource(objectId);// 리소스 파일을 읽어온다.

		// setup Bufferedreader
		BufferedReader in = new BufferedReader(new InputStreamReader(inputStream));
		
		String str = in.readLine();
		
		// tokenizer based on space
		StringTokenizer tokenizer = new StringTokenizer(str);
		int npoly = Integer.parseInt(tokenizer.nextToken());
		
		object.mVertexCount = npoly*3;
		object.vnt = new float[npoly*3*8];
		
		for (i = 0; i < npoly; ++i) {
			str = in.readLine();
			for(j = 0; j < 3; ++j){
				str = in.readLine();
				tokenizer = new StringTokenizer(str);
				object.vnt[(i*3+j)*8]     = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 1] = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 2] = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 3] = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 4] = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 5] = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 6] = Float.parseFloat(tokenizer.nextToken());
				object.vnt[(i*3+j)*8 + 7] = Float.parseFloat(tokenizer.nextToken());
			}
		}
		
		// 버텍스 버퍼를 만든다.
		object.mVerticesBuffer = ByteBuffer.allocateDirect(npoly*3*8*4).order(ByteOrder.nativeOrder()).asFloatBuffer();

		// 버텍스버퍼에 버텍스 배열을 저장해준다.
		object.mVerticesBuffer.clear();
		object.mVerticesBuffer.put(object.vnt);
		object.mVerticesBuffer.flip();
		
		object.mVerticesBuffer.position(0);

		if(texfile != "") { //has texture
			try {
				AssetManager as = context.getAssets();
				InputStream id = as.open(texfile);
				loadTexture(id);

			}
			catch (Exception e) {
				Log.e("ObjectLoader","texture file load error");
			}
		}
		if(texId != 0) {
			object.textureIds[0] = texId;
		}
			
	}

	// 텍스쳐를 바인딩하는 함수
	// InputStream is : 텍스쳐를 바인딩할 이미지
	public void loadTexture(InputStream is) {
		GLES20.glPixelStorei(GLES20.GL_UNPACK_ALIGNMENT, 1);
		GLES20.glGenTextures(1, object.textureIds, 0);
		GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, object.textureIds[0]);

		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);

		GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);

		Bitmap bitmap = BitmapFactory.decodeStream(is);
		GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
		bitmap.recycle();
	}
}