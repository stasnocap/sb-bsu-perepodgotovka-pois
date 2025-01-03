﻿using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Lab3_2
{
    public partial class MainWindow : Window
    {
        private bool isDrawing = false;
        private Point startPoint;
        private Brush brushColor = Brushes.Black;
        private double brushSize = 2;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Canvas_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            isDrawing = true;
            startPoint = e.GetPosition(DrawingCanvas);
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (isDrawing)
            {
                Point currentPoint = e.GetPosition(DrawingCanvas);
                Line line = new Line
                {
                    Stroke = brushColor,
                    StrokeThickness = brushSize,
                    X1 = startPoint.X,
                    Y1 = startPoint.Y,
                    X2 = currentPoint.X,
                    Y2 = currentPoint.Y
                };
                startPoint = currentPoint;
                DrawingCanvas.Children.Add(line);
            }
        }

        private void Canvas_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            isDrawing = false;
        }

        private void BrushColorComboBox_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            string selectedColor = (BrushColorComboBox.SelectedItem as System.Windows.Controls.ComboBoxItem).Content.ToString();
            brushColor = selectedColor switch
            {
                "Красный" => Brushes.Red,
                "Синий" => Brushes.Blue,
                "Зеленый" => Brushes.Green,
                _ => Brushes.Black
            };
        }

        private void ClearButton_Click(object sender, RoutedEventArgs e)
        {
            DrawingCanvas.Children.Clear();
        }

        private void BrushSizeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (e.NewValue != e.OldValue)
            {
                brushSize = e.NewValue;
            }
        }
    }
}
