package com.example.user.codeshop;

/**
 * Created by User on 19/12/2017.
 */

public class Product {
    String name;
    int count;
    int purchasedCount;
    boolean box;

    Product(String _describe, int _count, int _purchasedCount, boolean _box) {
        name = _describe;
        count = _count;
        purchasedCount = _purchasedCount;
        box = _box;
    }
}