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

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {
    private static final int SERVERPORT = 8820;
    private static final String SERVER_IP = "10.0.0.3";
    private Socket socket;

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
        signIn = (Button) findViewById(R.id.SignUp);
        logIn = (Button) findViewById(R.id.LogIn);

        //new Thread(new ClientThread()).start();

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
                String message = "001:" + email.getText()+ ":" + password.getText(); //Creating the message for the server
                //sendMessage(v, message);
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

                Intent intent = new Intent (getApplicationContext(), SignUp.class);
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

    //Functions for the connection with the server

    public void sendMessage(View v, String message) {
        try {
            //EditText editText = (EditText) findViewById(R.id.Message);
            //String str = editText.getText().toString();
            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())),true);
            out.println(message);
            //editText.setText("");
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    class ClientThread implements Runnable
    {
        @Override
        public void run()
        {
            //try to open new socket
            try {
                InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
                socket = new Socket(serverAddr, SERVERPORT);
            } catch (UnknownHostException e1) {
                e1.printStackTrace();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}