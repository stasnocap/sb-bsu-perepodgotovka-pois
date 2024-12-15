<?php
class Product {
    private $name;
    private $price;
    private $description;
    private $category;
    private $stock;

    // Constructor
    public function __construct($name, $price, $description, $category, $stock) {
        $this->name = $name;
        $this->price = $price;
        $this->description = $description;
        $this->category = $category;
        $this->stock = $stock;
    }

    // Getter and Setter for name
    public function getName() {
        return $this->name;
    }

    public function setName($name) {
        $this->name = $name;
    }

    // Getter and Setter for price
    public function getPrice() {
        return $this->price;
    }

    public function setPrice($price) {
        $this->price = $price;
    }

    // Getter and Setter for description
    public function getDescription() {
        return $this->description;
    }

    public function setDescription($description) {
        $this->description = $description;
    }

    // Getter and Setter for category
    public function getCategory() {
        return $this->category;
    }

    public function setCategory($category) {
        $this->category = $category;
    }

    // Getter and Setter for stock
    public function getStock() {
        return $this->stock;
    }

    public function setStock($stock) {
        $this->stock = $stock;
    }

    // Overriding __toString method
    public function __toString() {
        return "Product Name: " . $this->name . "\n" .
               "Price: " . $this->price . "\n" .
               "Description: " . $this->description . "\n" .
               "Category: " . $this->category . "\n" .
               "Stock: " . $this->stock . "\n";
    }
}

// Example usage:
$product = new Product("Laptop", 999.99, "High performance laptop", "Electronics", 10);
echo $product;
?>
