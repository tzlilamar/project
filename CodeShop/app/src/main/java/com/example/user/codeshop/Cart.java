package com.example.user.codeshop;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.ArrayList;import android.widget.CompoundButton.OnCheckedChangeListener;import android.widget.CompoundButton;
import android.widget.Toast;


public class Cart extends AppCompatActivity {

    ArrayList<Product> products = new ArrayList<Product>();
    ListAdapter boxAdapter;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cart);


        //Intent intent = getIntent();
        //Bundle extras = intent.getExtras();
        //String username = extras.getString("username");

        /*listView=(ListView)findViewById(R.id.ListView);

        ListAdapter listAdapter=new ListAdapter();

        listView.setAdapter(listAdapter);

        PurchasedButton = (Button)findViewById(R.id.Purchased_button);
*/
        fillData(); //Ask the server
        boxAdapter = new ListAdapter(this, products);

        ListView lvMain = (ListView) findViewById(R.id.ListView);
        lvMain.setAdapter(boxAdapter);
    }

    void fillData() {
        //For example
        for (int i = 1; i <= 10; i++)
        {
            products.add(new Product("Product " + i, 3, 0, false));
        }
        for (int i = 11; i <= 20; i++)
        {
            products.add(new Product("Product " + i, 2, 0, false));
        }

    }

    public void showResult(View v) {
        String result = "Selected products are: ";
        for (Product p : boxAdapter.getBox()) {
            if (p.box == true) //Selected
            {
                result += "\n" + p.name + " - " + p.purchasedCount;
            }
        }
        Toast.makeText(this, result+"\n", Toast.LENGTH_LONG).show();
    }
}
