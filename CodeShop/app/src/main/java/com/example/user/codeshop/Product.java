package com.example.user.codeshop;

/**
 This class is for use in the ListView.
 */

public class Product {
    String name; //The name of the product
    int count; //The number of products of this kind that the user throw to the trash
    int purchasedCount; //The number of  products of this kind that the user bought
    boolean box; //For the checkbox

    //C'tor
     Product(String _describe, int _count, int _purchasedCount, boolean _box) {
        name = _describe;
        count = _count;
        purchasedCount = _purchasedCount;
        box = _box;
    }
}