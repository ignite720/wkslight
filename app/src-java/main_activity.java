package com.wkslight.example;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class main_activity extends Activity {
    public static native int app_init();

    static {
        /*
        System.loadLibrary("bar");
        System.loadLibrary("foo");

        System.loadLibrary("app_core");
        System.loadLibrary("app");
        */

        System.loadLibrary("app");
    }

    @Override
    protected void onCreate(Bundle arg0) {
        Log.d("TAG_JAVA", "0-1, <JAVA>: hello");
        int ret = app_init();

        super.onCreate(arg0);
    }
}