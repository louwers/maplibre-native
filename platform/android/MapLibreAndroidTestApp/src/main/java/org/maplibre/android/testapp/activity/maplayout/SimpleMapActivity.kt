package org.maplibre.android.testapp.activity.maplayout

import android.os.Bundle
import android.view.MenuItem
import android.widget.Button
import androidx.activity.OnBackPressedCallback
import androidx.appcompat.app.AppCompatActivity
import org.maplibre.android.camera.CameraUpdateFactory
import org.maplibre.android.geometry.LatLng
import org.maplibre.android.maps.*
import org.maplibre.android.style.layers.LineLayer
import org.maplibre.android.style.layers.Property
import org.maplibre.android.style.layers.PropertyFactory.lineCap
import org.maplibre.android.style.layers.PropertyFactory.lineColor
import org.maplibre.android.style.layers.PropertyFactory.lineDasharray
import org.maplibre.android.style.layers.PropertyFactory.lineJoin
import org.maplibre.android.style.layers.PropertyFactory.lineWidth
import org.maplibre.android.style.layers.PropertyFactory.visibility
import org.maplibre.android.style.sources.GeoJsonSource
import org.maplibre.android.testapp.R
import org.maplibre.android.testapp.utils.ApiKeyUtils
import org.maplibre.android.testapp.utils.NavUtils
import org.maplibre.geojson.LineString
import org.maplibre.geojson.Point

private const val SOURCE_ID = "source"
private const val LAYER_ID = "layer"
private const val CENTRE_LAT = 39.749
private const val CENTRE_LONG = -105.005
private const val CENTRE_ZOOM = 10.0
private const val TOTAL_POINTS = 10000
private const val INCREMENT = 0.0001

/**
 * Test activity showcasing a simple MapView without any MapLibreMap interaction.
 */
class SimpleMapActivity : AppCompatActivity() {
    private lateinit var mapView: MapView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        onBackPressedDispatcher.addCallback(this, object: OnBackPressedCallback(true) {
            override fun handleOnBackPressed() {
                // activity uses singleInstance for testing purposes
                // code below provides a default navigation when using the app
                NavUtils.navigateHome(this@SimpleMapActivity)
            }
        })
        setContentView(R.layout.activity_map_simple)
        mapView = findViewById(R.id.mapView)
        mapView.onCreate(savedInstanceState)
        mapView.getMapAsync {
            val key = ApiKeyUtils.getApiKey(applicationContext)
            if (key == null || key == "YOUR_API_KEY_GOES_HERE") {
                it.moveCamera(CameraUpdateFactory.newLatLngZoom(LatLng(
                    CENTRE_LAT,
                    CENTRE_LONG
                ), CENTRE_ZOOM
                ))

                configure(it)
                val button = mapView.findViewById<Button>(R.id.reconfigure_button)
                button.setOnClickListener { _ ->
                    configure(it)
                }

            } else {
                val styles = Style.getPredefinedStyles()
                if (styles.isNotEmpty()) {
                    val styleUrl = styles[0].url
                    it.setStyle(Style.Builder().fromUri(styleUrl))
                }
            }
        }
    }

    private fun configure(map: MapLibreMap) {
        map.setStyle(
            "https://basemaps.cartocdn.com/gl/voyager-gl-style/style.json"
        ) {
            style ->
                val source = style.getSource(SOURCE_ID) ?: GeoJsonSource(
                    SOURCE_ID
                ).apply {
                    setGeoJson(
                        LineString.fromLngLats(List(TOTAL_POINTS) {
                            Point.fromLngLat(CENTRE_LONG + it * INCREMENT, CENTRE_LAT + it * INCREMENT)
                        })
                    )

                    style.addSource(this)
                }

                style.getLayer(LAYER_ID) ?: LineLayer(LAYER_ID, source.id).apply {
                    setProperties(
                        lineCap(Property.LINE_CAP_ROUND),
                        lineJoin(Property.LINE_JOIN_ROUND),
                        visibility(Property.VISIBLE),
                        lineWidth(3f),
                        lineColor("#FF0000"),
                        lineDasharray(arrayOf(1f, 1.50f))
                    )
                    style.addLayer(this)
                }

                map.moveCamera(CameraUpdateFactory.newLatLngZoom(LatLng(
                    CENTRE_LAT,
                    CENTRE_LONG
                ), CENTRE_ZOOM
                ))
        }
    }

    override fun onStart() {
        super.onStart()
        mapView.onStart()
    }

    override fun onResume() {
        super.onResume()
        mapView.onResume()
    }

    override fun onPause() {
        super.onPause()
        mapView.onPause()
    }

    override fun onStop() {
        super.onStop()
        mapView.onStop()
    }

    override fun onLowMemory() {
        super.onLowMemory()
        mapView.onLowMemory()
    }

    override fun onDestroy() {
        super.onDestroy()
        mapView.onDestroy()
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        mapView.onSaveInstanceState(outState)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            android.R.id.home -> {
                // activity uses singleInstance for testing purposes
                // code below provides a default navigation when using the app
                onBackPressedDispatcher.onBackPressed()
                return true
            }
        }
        return super.onOptionsItemSelected(item)
    }
}
