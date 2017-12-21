package com.example.user.codeshop;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class Hello extends AppCompatActivity {

    TextView helloUsername;
    ImageButton cart;
    ImageButton settings;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello);

        helloUsername = (TextView) findViewById(R.id.HelloUsername_Hello);
        cart = (ImageButton) findViewById(R.id.Cart_imageButton_Hello);
        settings = (ImageButton) findViewById(R.id.Settings_imageButton_Hello);

        Intent intent = getIntent();
        Bundle extras = intent.getExtras();
        String username = extras.getString("username");

        helloUsername.setText("Hello, " + username);


        cart.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                //Intent intent = new Intent (getApplicationContext(), Hello.class);
                //userId?
                //intent.putExtra("username","username from the server");
                //startActivity(intent);
                Intent intent = new Intent (getApplicationContext(), Cart.class);
                startActivity(intent);
                //Toast.makeText(Hello.this, "It works - cart", Toast.LENGTH_LONG).show();

            }
        });

        settings.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                Toast.makeText(Hello.this, "It works - settings", Toast.LENGTH_LONG).show();

            }
        });
    }
}
