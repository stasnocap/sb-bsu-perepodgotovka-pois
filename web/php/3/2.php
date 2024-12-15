<?php
// Root class
class Appliance {
    private $brand;
    private $model;
    private $power;

    public function __construct($brand, $model, $power) {
        $this->brand = $brand;
        $this->model = $model;
        $this->power = $power;
    }

    public function getBrand() {
        return $this->brand;
    }

    public function setBrand($brand) {
        $this->brand = $brand;
    }

    public function getModel() {
        return $this->model;
    }

    public function setModel($model) {
        $this->model = $model;
    }

    public function getPower() {
        return $this->power;
    }

    public function setPower($power) {
        $this->power = $power;
    }

    public function __toString() {
        return "Brand: " . $this->brand . "\n" .
               "Model: " . $this->model . "\n" .
               "Power: " . $this->power . "W\n";
    }
}

// Derived class for Refrigerator
class Refrigerator extends Appliance {
    private $capacity;

    public function __construct($brand, $model, $power, $capacity) {
        parent::__construct($brand, $model, $power);
        $this->capacity = $capacity;
    }

    public function getCapacity() {
        return $this->capacity;
    }

    public function setCapacity($capacity) {
        $this->capacity = $capacity;
    }

    public function __toString() {
        return parent::__toString() .
               "Capacity: " . $this->capacity . " liters\n";
    }
}

// Derived class for Television
class Television extends Appliance {
    private $screenSize;

    public function __construct($brand, $model, $power, $screenSize) {
        parent::__construct($brand, $model, $power);
        $this->screenSize = $screenSize;
    }

    public function getScreenSize() {
        return $this->screenSize;
    }

    public function setScreenSize($screenSize) {
        $this->screenSize = $screenSize;
    }

    public function __toString() {
        return parent::__toString() .
               "Screen Size: " . $this->screenSize . " inches\n";
    }
}

// Example usage:
$fridge = new Refrigerator("LG", "GR-M762HLHM", 150, 400);
echo $fridge;

echo "\n";

$tv = new Television("Samsung", "QLED Q90T", 200, 55);
echo $tv;
?>
