package agm.andruino.arduinoconnect;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.CompoundButton;
import android.widget.Toast;
import android.widget.ToggleButton;

public class SoundController extends AppCompatActivity {

    //Conexión con el modulo bluetooth
    private BTController BTconect = BTController.getInstance();

    //Boolean para establecer si se esta obteniendo la información
    private boolean gettingInfo = false;

    //Función onCreate()
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sound_controller);

    }

    //Función onResume()
    @Override
    public void onResume() {
        super.onResume();

        //Recibe la información del arduino
        obtenerDatos();
    }

    //Función para obtener los datos del BT
    public void obtenerDatos() {

        //Manda mensaje para obtener los datos
        //BTconect.write("#LD$");
        //Pasa a modo obtención de datos
        gettingInfo = true;

        /*/1º Lee el estado del LED
        String codigo = BTconect.read();
        if (Integer.parseInt(codigo) == 1)
            LEDBtn.setChecked(true);
        else
            LEDBtn.setChecked(false);

        //1º Lee el color R
        codigo = BTconect.read();
        REDNum.setText(codigo);

        //2º Lee el color G
        codigo = BTconect.read();
        GREENNum.setText(codigo);

        //3º Lee el color B
        codigo = BTconect.read();
        BLUENum.setText(codigo);*/

        //Deja el modo de obtención de datos
        gettingInfo = false;
    }

}