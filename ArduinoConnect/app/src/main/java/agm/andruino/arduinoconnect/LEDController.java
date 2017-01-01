package agm.andruino.arduinoconnect;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Toast;
import android.widget.ToggleButton;
import java.io.IOException;

public class LEDController extends AppCompatActivity {

    //Componentes de la vista
    ToggleButton LEDBtn;
    Button SendColor;
    EditText REDNum, GREENNum, BLUENum;
    SeekBar REDbar, GREENbar, BLUEbar;

    //Conexión con el modulo bluetooth
    private BTController BTconect = BTController.getInstance();

    //Boolean para establecer si se esta obteniendo la información
    private boolean gettingInfo = false;

    //Función onCreate()
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_led_controller);

        //Conectar Elementos Gráficos
        LEDBtn = (ToggleButton) findViewById(R.id.LEDButton);

        SendColor = (Button) findViewById(R.id.SendColorButton);

        REDNum = (EditText) findViewById(R.id.REDNumber);
        REDbar = (SeekBar) findViewById(R.id.REDseek);

        GREENNum = (EditText) findViewById(R.id.GREENNumber);
        GREENbar = (SeekBar) findViewById(R.id.GREENseek);

        BLUENum = (EditText) findViewById(R.id.BLUENumber);
        BLUEbar = (SeekBar) findViewById(R.id.BLUEseek);


        //Define el comportamiento de los botones
        LEDBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isCheked) {
                if (isCheked && !gettingInfo) {
                    //The toggle is enabled
                    BTconect.write("#LP$");
                    Toast.makeText(getBaseContext(), R.string.led_on, Toast.LENGTH_SHORT).show();
                } else if (!gettingInfo) {
                    //The toggle is disabled
                    BTconect.write("#LP$");
                    Toast.makeText(getBaseContext(), R.string.led_off, Toast.LENGTH_SHORT).show();
                }
            }
        });
        SendColor.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View view) {

                String codigo = BTController.generarCodigo("LR", REDNum.getText().toString());
                BTconect.write(codigo);
                codigo = BTController.generarCodigo("LG", GREENNum.getText().toString());
                BTconect.write(codigo);
                codigo = BTController.generarCodigo("LB", BLUENum.getText().toString());
                BTconect.write(codigo);
            }

        });

        //Comportamiento de las barras
        REDbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                //Si la barra se mueve por el usuario, actualiza el valor en el input
                if (fromUser)
                    REDNum.setText(String.valueOf(progress));
            }
            public void onStartTrackingTouch(SeekBar seekBar){}
            public void onStopTrackingTouch(SeekBar seekBar){

                //Cuando deja de moverse la barra, manda el color al bluetooth
                String codigo = BTController.generarCodigo("LR", String.valueOf(seekBar.getProgress()));
                BTconect.write(codigo);
            }
        });
        GREENbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                //Si la barra se mueve por el usuario, actualiza el valor en el input
                if (fromUser)
                    GREENNum.setText(String.valueOf(progress));
            }
            public void onStartTrackingTouch(SeekBar seekBar){}
            public void onStopTrackingTouch(SeekBar seekBar){

                //Cuando deja de moverse la barra, manda el color al bluetooth
                String codigo = BTController.generarCodigo("LG", String.valueOf(seekBar.getProgress()));
                BTconect.write(codigo);
            }
        });
        BLUEbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                //Si la barra se mueve por el usuario, actualiza el valor en el input
                if (fromUser)
                    BLUENum.setText(String.valueOf(progress));
            }
            public void onStartTrackingTouch(SeekBar seekBar){}
            public void onStopTrackingTouch(SeekBar seekBar){

                //Cuando deja de moverse la barra, manda el color al bluetooth
                String codigo = BTController.generarCodigo("LB", String.valueOf(seekBar.getProgress()));
                BTconect.write(codigo);
            }
        });

        //Comportamiento de los inputs
        REDNum.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {

                int num = 0;
                //Si hay algun numero escrito lo almacena para procesarlo
                if (s.toString().length() > 0)
                    num = Integer.parseInt(s.toString());
                //Si se introduce un numero negativo se guarda el numero como 0
                if (num < 0) {
                    num = 0;
                    //Si se introduce un numero mayor de 255, el valor cambia automaticamente a 255
                } else if (num > 255) {
                    num = 255;
                    REDNum.setText(String.valueOf(num));
                }
                //Establece el valor en la barra
                REDbar.setProgress(num);
            }
        });
        GREENNum.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {

                int num = 0;
                //Si hay algun numero escrito lo almacena para procesarlo
                if (s.toString().length() > 0)
                    num = Integer.parseInt(s.toString());
                //Si se introduce un numero negativo se guarda el numero como 0
                if (num < 0) {
                    num = 0;
                    //Si se introduce un numero mayor de 255, el valor cambia automaticamente a 255
                } else if (num > 255) {
                    num = 255;
                    GREENNum.setText(String.valueOf(num));
                }
                //Establece el valor en la barra
                GREENbar.setProgress(num);
            }
        });
        BLUENum.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {

                int num = 0;
                //Si hay algun numero escrito lo almacena para procesarlo
                if (s.toString().length() > 0)
                    num = Integer.parseInt(s.toString());
                //Si se introduce un numero negativo se guarda el numero como 0
                if (num < 0) {
                    num = 0;
                    //Si se introduce un numero mayor de 255, el valor cambia automaticamente a 255
                } else if (num > 255) {
                    num = 255;
                    BLUENum.setText(String.valueOf(num));
                }
                //Establece el valor en la barra
                BLUEbar.setProgress(num);
            }
        });
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
        BTconect.write("#LD$");
        //Pasa a modo obtención de datos
        gettingInfo = true;

        //1º Lee el estado del LED
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
        BLUENum.setText(codigo);

        //Deja el modo de obtención de datos
        gettingInfo = false;
    }

}