package openGLES;

import com.example.gles20ex1.R;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.FrameLayout;
import android.widget.RadioButton;
import android.widget.Toast;

public class TestActivity extends Activity {

	public static int renderMode = 0;// 0: Phong, 1: Phong_halfway
	public static int textureMode = 0;// 0: on, 1: off

	private TestSurfaceView mGLSurfaceView = null;

	public static RadioButton mLeftButton;
	public static RadioButton mMiddleButton;
	public static RadioButton mRightButton;
	public static RadioButton tmpButton;
	
	public static CheckBox LBox;
	public static CheckBox MBox;
	public static CheckBox RBox;
	
	public Button mButton1;
	public Button mButton2;
	Toast toast;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		final FrameLayout frameLayout = (FrameLayout) findViewById(R.id.frameLayout1);
		if (mGLSurfaceView == null) {
			mGLSurfaceView = new TestSurfaceView(this);
			frameLayout.addView(mGLSurfaceView);
		}
		
		mLeftButton = (RadioButton) findViewById(R.id.radioButton1);
		mMiddleButton = (RadioButton) findViewById(R.id.radioButton2);
		mRightButton = (RadioButton) findViewById(R.id.radioButton3);
		tmpButton = (RadioButton) findViewById(R.id.radioButton4);
		
		LBox = (CheckBox) findViewById(R.id.checkBox1);
		MBox = (CheckBox) findViewById(R.id.checkBox2);
		RBox = (CheckBox) findViewById(R.id.checkBox3);
		
		mButton1 = (Button) findViewById(R.id.button1);
		mButton1.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				renderMode++;
				if (renderMode == 2) {
					renderMode = 0;
				}
				if (renderMode == 0) {
					if(toast == null) {
						toast = toast.makeText(TestActivity.this, "Phong", Toast.LENGTH_SHORT);
					}
					else toast.setText("Phong");
					toast.show();
					mGLSurfaceView.setRenderMode(renderMode);
				}
				else if (renderMode == 1) {
					if(toast == null) {
						toast = toast.makeText(TestActivity.this, "Phong_halfway", Toast.LENGTH_SHORT);
					}
					else toast.setText("Phong_halfway");
					toast.show();
					mGLSurfaceView.setRenderMode(renderMode);
				}
			}
		});
		
		mButton2 = (Button) findViewById(R.id.button2);
		mButton2.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				textureMode++;
				if (textureMode == 2){
					textureMode = 0;
				}
				if (textureMode == 0) {
					if(toast == null) {
						toast = toast.makeText(TestActivity.this,"off" , Toast.LENGTH_SHORT);
					}
					else toast.setText("off");
					toast.show();
					mGLSurfaceView.setTextureMode(textureMode);
				}
				else if (textureMode == 1) {
					if(toast == null) {
						toast = toast.makeText(TestActivity.this, "on", Toast.LENGTH_SHORT);
					}
					else toast.setText("on");
					toast.show();
					mGLSurfaceView.setTextureMode(textureMode);
				}

			}
		});
		
	}

	@Override
	protected void onResume() {
		super.onResume();
		mGLSurfaceView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		mGLSurfaceView.onPause();
	}

	
	class TestSurfaceView extends GLSurfaceView {

		// member variables
		private TestRender mRenderer = null;

		// 포인트점 두개 이용 : 포인트점0,포인트점1
		// 포인트0,1 각각의 이전포인트x,y 현재 포인트 x,y
		// delta : 이전포인트와 현재 포인트간의 차이
		public float previousX[] = new float[2], currentX[] = new float[2], deltaX;
		public float previousY[] = new float[2], currentY[] = new float[2], deltaY;

		public TestSurfaceView(Context context) {
			super(context);
			// Create an OpenGL ES 2.0 context.
			setEGLContextClientVersion(2);

			// Set the Renderer for drawing on the GLSurfaceView
			mRenderer = new TestRender(context);
			setRenderer(mRenderer);
		}

		public void setRenderMode(int mode) {
			mRenderer.renderMode = mode;
			requestRender();
		}
		
		public void setTextureMode(int mode) {
			mRenderer.textureMode = mode;
			requestRender();
		}

		@Override
		public boolean onTouchEvent(MotionEvent e) {
			final int SENSITIVITY = 5;// 이벤트를 발생시킬지 기준이 되는 값

			switch (e.getAction() & MotionEvent.ACTION_MASK) {
			case MotionEvent.ACTION_DOWN:
				for (int i = 0; i < e.getPointerCount(); i++) {
					currentX[i] = e.getX(i);
					currentY[i] = e.getY(i);
					previousX[i] = currentX[i];
					previousY[i] = currentY[i];
				}
				break;
			case MotionEvent.ACTION_MOVE: // touch move
				if(e.getPointerCount() > 2)
					break;
				for (int i = 0; i < e.getPointerCount(); i++) {
					previousX[i] = currentX[i];
					previousY[i] = currentY[i];

					currentX[i] = e.getX(i);
					currentY[i] = e.getY(i);
				}

				// delta calculation of each coord
				deltaX = currentX[0] - previousX[0];
				deltaY = currentY[0] - previousY[0];

				if (e.getPointerCount() == 1) {
					if (TestActivity.mLeftButton.isChecked() == true) {
						if (Math.abs(deltaY) > SENSITIVITY)
							mRenderer.mCamera.MoveUpward(deltaY);
						if (Math.abs(deltaX) > SENSITIVITY)
							mRenderer.mCamera.MoveSideward(-deltaX);
					}
					else if (TestActivity.mMiddleButton.isChecked() == true) {
						if (Math.abs(deltaY) > SENSITIVITY)
							mRenderer.mCamera.MoveForward(deltaY);

					}
					else if (TestActivity.mRightButton.isChecked() == true) {
						if (Math.abs(deltaX) > SENSITIVITY){
							/*mRenderer.ObjectRotate+= deltaX;*/
							mRenderer.getCamera().BaseYaw(deltaX);
						}
					}
					else if (TestActivity.tmpButton.isChecked() == true){
						if (Math.abs(deltaX) > SENSITIVITY){
							mRenderer.ObjectRotate+= deltaX;
						}
					}
					
					if(TestActivity.LBox.isChecked() == true){
						mRenderer.LBox = 1;
					}
					else
						mRenderer.LBox = 0;
					if(TestActivity.MBox.isChecked() == true){
						mRenderer.MBox = 1;
					}
					else
						mRenderer.MBox = 0;
					if(TestActivity.RBox.isChecked() == true){
						mRenderer.RBox = 1;
					}
					else{
						mRenderer.RBox = 0;
					}
				}
				else if (e.getPointerCount() == 2) {
					float pre_diff = (previousX[0] - previousX[1])*(previousX[0] - previousX[1])
							+ (previousY[0] - previousY[1])*(previousY[0] - previousY[1]);
					float cur_diff = (currentX[0] - currentX[1])*(currentX[0] - currentX[1])
							+ (currentY[0] - currentY[1])*(currentY[0] - currentY[1]);
					
					double pre = Math.sqrt(pre_diff);
					double cur = Math.sqrt(cur_diff);

					mRenderer.mCamera.Zoom(pre-cur);
				}

				requestRender();
				break;
			}

			return true;
		}
	}
	
}
