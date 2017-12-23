package com.example.user.codeshop;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class SignUp extends AppCompatActivity {

    EditText email;
    EditText username;
    EditText password;
    TextView checking;
    Button signUp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_up);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        toolbar.setTitle("Sign Up");
        setSupportActionBar(toolbar);
        Intent intent = getIntent();

        email = (EditText) findViewById(R.id.Email_signUp);
        username = (EditText) findViewById(R.id.Username_signUp);
        password = (EditText) findViewById(R.id.Password_signUp);
        checking = (TextView) findViewById(R.id.Checking_signUp);
        signUp = (Button) findViewById(R.id.SignUp_signUp);

        signUp.setOnClickListener(new View.OnClickListener() {
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

                //Send to the server:  email.getText(),  username.getText(),  password.getText()
                if (true) //Valid
                {
                    checking.setText("Success message");

                }
                else //Message to the user if there isn't a match between the username and the password
                {
                    checking.setText("Message to the user");
                }
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
