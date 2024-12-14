using System.Windows;
using System.Windows.Media;

namespace Lab3_1;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        Status.Text = "Привет";
    }

    private void YellowBackground_Click(object sender, RoutedEventArgs e)
    {
        Background = Brushes.Yellow;
    }

    private void BlueBackground_Click(object sender, RoutedEventArgs e)
    {
        Background = Brushes.Blue;
    }

    private void RedBackground_Click(object sender, RoutedEventArgs e)
    {
        Background = Brushes.Red;
    }

    private void AboutDeveloper_Click(object sender, RoutedEventArgs e)
    {
        MessageBox.Show("Капитан Станислав Сергеевич", "О разработчике");
    }

    private void Close_Click(object sender, RoutedEventArgs e)
    {
        Close();
    }

    private void YellowBackground_MouseEnter(object sender, RoutedEventArgs e)
    {
        Status.Text = "Выберем желтый цвет";
    }

    private void BlueBackground_MouseEnter(object sender, RoutedEventArgs e)
    {
        Status.Text = "Выберем синий цвет";
    }

    private void RedBackground_MouseEnter(object sender, RoutedEventArgs e)
    {
        Status.Text = "Выберем красный цвет";
    }
    
    private void AboutDeveloper_MouseEnter(object sender, RoutedEventArgs e)
    {
        Status.Text = "Кто же он?";
    }
    
    private void Close_MouseEnter(object sender, RoutedEventArgs e)
    {
        Status.Text = "Закрываемся";
    }

    private void ClearStatus_MouseOver(object sender, RoutedEventArgs e)
    {
        Status.Text = "Бездействуем";
    }
}