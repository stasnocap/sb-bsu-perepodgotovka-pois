using System.Windows;
using System.Windows.Input;
using System.Windows.Shapes;

namespace Lab4_1
{
    public partial class MainWindow : Window
    {
        private bool isDrawing = false;
        private Point startPoint;

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
                var viewModel = (DrawingViewModel)DataContext;
                Point currentPoint = e.GetPosition(DrawingCanvas);
                Line line = new Line
                {
                    Stroke = viewModel.BrushColor,
                    StrokeThickness = viewModel.BrushSize,
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

        private void ClearButton_Click(object sender, RoutedEventArgs e)
        {
            DrawingCanvas.Children.Clear();
        }
    }
}