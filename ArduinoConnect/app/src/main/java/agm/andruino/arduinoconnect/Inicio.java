package agm.andruino.arduinoconnect;

import java.io.IOException;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.Toast;

public class Inicio extends AppCompatActivity {

    LinearLayout clockController, ledController, soundController;

    //Función onCreate()
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_inicio);

        //Asocia los elementos a la vista
        clockController = (LinearLayout) findViewById(R.id.ClockController);
        ledController = (LinearLayout) findViewById(R.id.LedController);
        soundController = (LinearLayout) findViewById(R.id.SoundController);

        //Define el comportamiento al pulsar en las opciones
        clockController.setOnClickListener(new LinearLayout.OnClickListener() {
            public void onClick(View view) {

                // Inicia la siguiente acitividad mandandole un EXTRA que contiene la dirección MAC.
                /*Intent i = new Intent(Inicio.this, LEDController.class);
                startActivity(i);*/
            }
        });
        ledController.setOnClickListener(new LinearLayout.OnClickListener() {
            public void onClick(View view) {

                // Inicia la siguiente acitividad mandandole un EXTRA que contiene la dirección MAC.
                Intent i = new Intent(Inicio.this, LEDController.class);
                startActivity(i);
            }
        });
        soundController.setOnClickListener(new LinearLayout.OnClickListener() {
            public void onClick(View view) {

                // Inicia la siguiente acitividad mandandole un EXTRA que contiene la dirección MAC.
                /*Intent i = new Intent(Inicio.this, LEDController.class);
                startActivity(i);*/
            }
        });
    }

    //Función onResume()
    @Override
    public void onResume() {
        super.onResume();

        BTController.checkBTState(this);
        BTController.getInstance().checkBTConnection(this);
    }
}