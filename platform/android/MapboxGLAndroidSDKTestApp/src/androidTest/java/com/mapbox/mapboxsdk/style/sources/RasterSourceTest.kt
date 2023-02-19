package com.mapbox.mapboxsdk.style.sources

import android.view.View
import androidx.test.annotation.UiThreadTest
import androidx.test.espresso.Espresso
import androidx.test.espresso.UiController
import androidx.test.espresso.ViewAction
import androidx.test.espresso.matcher.ViewMatchers.withId
import androidx.test.internal.runner.junit4.AndroidJUnit4ClassRunner
import com.mapbox.mapboxsdk.testapp.R
import com.mapbox.mapboxsdk.testapp.activity.EspressoTest
import com.mapbox.mapboxsdk.testapp.style.RuntimeStyleTests.BaseViewAction
import org.junit.Test
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4ClassRunner::class)
@UiThreadTest
class RasterSourceTest {
    @Test
    fun rasterSource_constructor() {
        val tiles = arrayOf("https://example.com")
        val tileSet = TileSet("2.1.0", *tiles)

        // set bounds
        val bounds = floatArrayOf(-180.0f, -85.05113f, 180.0f, 85.05113f)
        tileSet.setBounds(*bounds) // or like tileSet.setBounds(-180.0f, -85.05113f, 180.0f, 85.05113f) doesn't matter

        // trying to create source
        RasterSource("source_id", tileSet) // <- Crash here
    }
}