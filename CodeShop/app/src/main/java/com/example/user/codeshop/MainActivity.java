package com.example.user.codeshop;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    //private static int SPLASE_TIME_OUT = 4000;

    EditText email;
    EditText password;
    TextView checking;
    Button signIn;
    Button logIn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        email = (EditText) findViewById(R.id.Email);
        password = (EditText) findViewById(R.id.Password);
        checking = (TextView) findViewById(R.id.Checking);
        signIn = (Button) findViewById(R.id.SignIn);
        logIn = (Button) findViewById(R.id.LogIn);

        logIn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                //Hiding keyboard
                try
                {
                    InputMethodManager imm = (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), 0);
                }
                catch (Exception e)
                {

                }

                //Checking match - calling the server...

                if (true) //There is a match between the username and the password
                {
                    //checking.setText("" + email.getText() + password.getText());
                    Intent intent = new Intent (getApplicationContext(), Hello.class);
                    intent.putExtra("username","username from the server");
                    startActivity(intent);
                    finish(); //The user will not be able to return to the login screen
                }
                else //Message to the user if there isn't a match between the username and the password
                {
                    checking.setText("Message to the user");

                    //2 options:
                    //The username you entered doesn't belong to an account. Please check your username and try again.
                    //Sorry, your password is incorrect. Please double-check your password.
                }
            }
        });

        signIn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                //Hiding keyboard
                try
                {
                InputMethodManager imm = (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);
                imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), 0);
                }
                catch (Exception e)
                {

                }

                Intent intent = new Intent (getApplicationContext(), SignIn.class);
                startActivity(intent);
            }
        });
    }

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        InputMethodManager imm = (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);
        assert imm != null;
        imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), 0);
        return true;
    }
}
