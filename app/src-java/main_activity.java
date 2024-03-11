package com.wkslight.example;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class main_activity extends Activity {
	public static native void app_init();

	static {
		//System.loadLibrary("foo");
		//System.loadLibrary("bar");

		//System.loadLibrary("app_core");
		System.loadLibrary("app");
	}

	@Override
	protected void onCreate(Bundle arg0) {
		Log.d("Hello world!", "hi from java");
		app_init();

		super.onCreate(arg0);
	}
}