package com.wkslight.example;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class main_activity extends Activity {
	public static native void app_init();

	static {
		/*
		System.loadLibrary("bar");
		System.loadLibrary("foobar");
		System.loadLibrary("foo");

		System.loadLibrary("app_core");
		System.loadLibrary("app");
		*/

		System.loadLibrary("app");
	}

	@Override
	protected void onCreate(Bundle arg0) {
		Log.d("TAG_JAVA", "1 => hello");
		app_init();

		super.onCreate(arg0);
	}
}