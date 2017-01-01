package agm.andruino.arduinoconnect;

import java.io.IOException;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.LinearLayout;

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

                // Inicia la siguiente acitividad.
                Intent i = new Intent(Inicio.this, ClockController.class);
                startActivity(i);
            }
        });
        ledController.setOnClickListener(new LinearLayout.OnClickListener() {
            public void onClick(View view) {

                // Inicia la siguiente acitividad.
                Intent i = new Intent(Inicio.this, LEDController.class);
                startActivity(i);
            }
        });
        soundController.setOnClickListener(new LinearLayout.OnClickListener() {
            public void onClick(View view) {

                // Inicia la siguiente acitividad.
                Intent i = new Intent(Inicio.this, SoundController.class);
                startActivity(i);
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

    //Función onDestroy()
    @Override
    public void onDestroy() {

        try {
            BTController.getInstance().close();
        } catch (IOException e) { }

        super.onDestroy();
    }

}