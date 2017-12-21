package com.example.user.codeshop;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

/**
 * Created by User on 19/12/2017.
 */

public class ListAdapter extends BaseAdapter {
    Context ctx;
    LayoutInflater lInflater;
    ArrayList<Product> objects;
    Spinner spinner;
    Product p;

    ListAdapter(Context context, ArrayList<Product> products) {
        ctx = context;
        objects = products;
        lInflater = (LayoutInflater) ctx.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return objects.size();
    }

    @Override
    public Object getItem(int position) {
        return objects.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view = convertView;
        if (view == null) {
            view = lInflater.inflate(R.layout.product_in_list, parent, false);
        }

        p = getProduct(position);

        ((TextView) view.findViewById(R.id.ProductName)).setText(p.name);
        ((TextView) view.findViewById(R.id.Count)).setText(p.count + "");

        //Creating spinner for each product
        String[] numbers=new String[p.count];
        for (int i = 0; i <p.count; i++)
        {
            int integer = i+1;
            numbers[i] = "" + integer;
        }

        spinner=(Spinner) view.findViewById(R.id.Choice_count);
        ArrayAdapter<String> adapter=new ArrayAdapter<String>(ctx,android.R.layout.simple_spinner_item,numbers);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                String s = spinner.getItemAtPosition(position).toString();
/*************************************************/
                System.out.println("?????????????????????");
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        CheckBox cb = (CheckBox) view.findViewById(R.id.CheckBox);
        cb.setOnCheckedChangeListener(myCheckChangList);
        cb.setTag(position);
        cb.setChecked(p.box);
        return view;
    }

    Product getProduct(int position)
    {
        return ((Product) getItem(position));
    }

    ArrayList<Product> getBox()
    {
        ArrayList<Product> box = new ArrayList<Product>();
        for (Product p : objects)
        {
            if (p.box)
            {
                box.add(p);
            }
        }
        return box;
    }



    CompoundButton.OnCheckedChangeListener myCheckChangList = new CompoundButton.OnCheckedChangeListener()
    {
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            getProduct((Integer) buttonView.getTag()).box = isChecked;

        }
    };


}
