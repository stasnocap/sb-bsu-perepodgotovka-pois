using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Media;

namespace Lab4_1
{
    public class DrawingViewModel : INotifyPropertyChanged
    {
        private Brush _brushColor = Brushes.Black;
        public Brush BrushColor
        {
            get => _brushColor;
            set
            {
                if (_brushColor != value)
                {
                    _brushColor = value;
                    OnPropertyChanged();
                }
            }
        }

        private double _brushSize = 2;
        public double BrushSize
        {
            get => _brushSize;
            set
            {
                if (_brushSize != value)
                {
                    _brushSize = value;
                    OnPropertyChanged();
                }
            }
        }

        public ObservableCollection<Brush> BrushColors { get; } = new ObservableCollection<Brush>
        {
            Brushes.Black, Brushes.Red, Brushes.Blue, Brushes.Green
        };

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}