package agm.andruino.arduinoconnect;

import android.app.DialogFragment;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

public class ClockController extends AppCompatActivity {

    //Componentes de la vista
    ToggleButton DisplayBtn;
    Button HourSet, DateSet;
    TextView hour, date;

    //Conexión con el modulo bluetooth
    private BTController BTconect = BTController.getInstance();

    //Boolean para establecer si se esta obteniendo la información
    private boolean gettingInfo = false;

    //Función onCreate()
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_clock_controller);

        //Conectar Elementos Gráficos
        DisplayBtn = (ToggleButton) findViewById(R.id.DisplayButton);
        hour = (TextView) findViewById(R.id.Hour);
        date = (TextView) findViewById(R.id.Date);
        HourSet = (Button) findViewById(R.id.setHour);
        DateSet = (Button) findViewById(R.id.setDate);

        //Define el comportamiento de los botones
        DisplayBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isCheked) {
                if (isCheked && !gettingInfo) {
                    //The toggle is enabled
                    BTconect.write("#DP$");
                    Toast.makeText(getBaseContext(), R.string.display_on, Toast.LENGTH_SHORT).show();
                } else if (!gettingInfo) {
                    //The toggle is disabled
                    BTconect.write("#DP$");
                    Toast.makeText(getBaseContext(), R.string.display_off, Toast.LENGTH_SHORT).show();
                }
            }
        });
        HourSet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String codigo = hour.getText().toString();
                codigo = "#CH"+codigo.substring(0,2)+codigo.substring(3,5)+"$";

                BTconect.write(codigo);
            }
        });
        DateSet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String codigo = date.getText().toString();
                codigo = "#CD"+codigo.substring(0,2)+codigo.substring(3,5)+codigo.substring(6,8)+"$";

                BTconect.write(codigo);
            }
        });

        //Define el comportamiento de las etiquetas al pulsarlas
        hour.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DialogFragment timePicker = new TimePickerFragment();
                timePicker.show(getFragmentManager(),"TimePicker");
            }
        });
        date.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DialogFragment datePicker = new DatePickerFragment();
                datePicker.show(getFragmentManager(),"DatePicker");
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
        BTconect.write("#DD$");
        //Pasa a modo obtención de datos
        gettingInfo = true;

        //1º Lee el estado del LED
        String codigo = BTconect.read();
        if (Integer.parseInt(codigo) == 1)
            DisplayBtn.setChecked(true);
        else
            DisplayBtn.setChecked(false);

        //2º Manda mensaje para obtener los datos del reloj
        BTconect.write("#CG$");

        //3º Lee el string con todos los datos del reloj
        codigo = BTconect.read();

        hour.setText(codigo.substring(0,2)+":"+codigo.substring(2,4));
        date.setText(codigo.substring(6,8)+"/"+codigo.substring(10,12)+"/"+codigo.substring(12,14));

        //Deja el modo de obtención de datos
        gettingInfo = false;
    }

}