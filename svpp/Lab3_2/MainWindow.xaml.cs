using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace GraphicsEditor
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            ColorPicker.SelectionChanged += ColorPicker_SelectionChanged;
            BrushSizeSlider.ValueChanged += BrushSizeSlider_ValueChanged;
            DrawMode.Checked += Mode_Checked;
            DeleteMode.Checked += Mode_Checked;
            Canvas.MouseMove += Canvas_MouseMove;
        }

        private void ColorPicker_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ColorPicker.SelectedItem is ComboBoxItem selectedItem)
            {
                switch (selectedItem.Content.ToString())
                {
                    case "Красный":
                        Canvas.DefaultDrawingAttributes.Color = Colors.Red;
                        break;
                    case "Зелёный":
                        Canvas.DefaultDrawingAttributes.Color = Colors.Green;
                        break;
                    case "Синий":
                        Canvas.DefaultDrawingAttributes.Color = Colors.Blue;
                        break;
                }
            }
        }

        private void BrushSizeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            Canvas.DefaultDrawingAttributes.Width = BrushSizeSlider.Value;
            Canvas.DefaultDrawingAttributes.Height = BrushSizeSlider.Value;
        }

        private void Mode_Checked(object sender, RoutedEventArgs e)
        {
            if (Canvas == null)
            {
                return;
            }

            if (DrawMode.IsChecked == true)
            {
                Canvas.EditingMode = InkCanvasEditingMode.Ink;
            }
            else if (DeleteMode.IsChecked == true)
            {
                Canvas.EditingMode = InkCanvasEditingMode.EraseByStroke;
            }
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed && DrawMode.IsChecked == true)
            {
                Canvas.CaptureMouse();
            }
            else
            {
                Canvas.ReleaseMouseCapture();
            }
        }
    }
}
