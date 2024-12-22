using System;
using System.Web;
using System.Web.UI;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Text;

namespace Wintellect
{
    public class Odometer : Control
    {
        int MyCount = 0;
        int MyDigits = 0;
        int MyWidth = 128;
        int MyHeight = 48;
        Color MyForeColor = Color.White;
        Color MyBackColor1 = Color.Black;
        Color MyBackColor2 = Color.LightGray;
        Color MyBorderColor = Color.Gray;

        public int Count
        {
            get { return MyCount; }
            set
            {
                if (value >= 0)
                    MyCount = value;
                else
                    throw new ArgumentOutOfRangeException ();
            }
        }

        public int Digits
        {
            get { return MyDigits; }
            set
            {
                if (value >= 0)
                    MyDigits = value;
                else
                    throw new ArgumentOutOfRangeException ();
            }
        }

        public int Width
        {
            get { return MyWidth; }
            set
            {
                if (value >= 0)
                    MyWidth = value;
                else
                    throw new ArgumentOutOfRangeException ();
            }
        }

        public int Height
        {
            get { return MyHeight; }
            set
            {
                if (value >= 0)
                    MyHeight = value;
                else
                    throw new ArgumentOutOfRangeException ();
            }
        }

        public Color ForeColor
        {
            get { return MyForeColor; }
            set { MyForeColor = value; }
        }

        public Color BackColor1
        {
            get { return MyBackColor1; }
            set { MyBackColor1 = value; }
        }

        public Color BackColor2
        {
            get { return MyBackColor2; }
            set { MyBackColor2 = value; }
        }

        public Color BorderColor
        {
            get { return MyBorderColor; }
            set { MyBorderColor = value; }
        }

        protected override void Render (HtmlTextWriter writer)
        {
            StringBuilder builder = new StringBuilder ();

            builder.Append ("OdometerImageGen.ashx?");
            builder.Append ("Count=");
            builder.Append (Count);
            builder.Append ("&Digits=");
            builder.Append (Digits);
            builder.Append ("&Width=");
            builder.Append (Width);
            builder.Append ("&Height=");
            builder.Append (Height);
            builder.Append ("&ForeColor=");
            builder.Append (ForeColor.ToArgb ().ToString ());
            builder.Append ("&BackColor1=");
            builder.Append (BackColor1.ToArgb ().ToString ());
            builder.Append ("&BackColor2=");
            builder.Append (BackColor2.ToArgb ().ToString ());
            builder.Append ("&BorderColor=");
            builder.Append (BorderColor.ToArgb ().ToString ());

            writer.WriteBeginTag ("img");
            writer.WriteAttribute ("src", builder.ToString ());
            if (ID != null)
                writer.WriteAttribute ("id", ClientID);
            writer.Write (HtmlTextWriter.TagRightChar);
        }
    }

    public class OdometerImageGen : IHttpHandler
    {
        public void ProcessRequest (HttpContext context)
        {
            // ��������� ������� ������ �� ������ �������
            int Count = Convert.ToInt32 (context.Request["Count"]);
            int Digits = Convert.ToInt32 (context.Request["Digits"]);
            int Width = Convert.ToInt32 (context.Request["Width"]);
            int Height = Convert.ToInt32 (context.Request["Height"]);

            Color ForeColor = Color.FromArgb
                (Convert.ToInt32 (context.Request["ForeColor"]));
            Color BackColor1 = Color.FromArgb
                (Convert.ToInt32 (context.Request["BackColor1"]));
            Color BackColor2 = Color.FromArgb
                (Convert.ToInt32 (context.Request["BackColor2"]));
            Color BorderColor = Color.FromArgb
                (Convert.ToInt32 (context.Request["BorderColor"]));

            // ��������� ����������� ��� �������� �������
            Bitmap bitmap = GenerateImage (Count, Digits,
                Width, Height, ForeColor, BackColor1, BackColor2,
                BorderColor);

            // ��������� ���� ����������� HTTP-������ s iaiage/Jpeg
            context.Response.ContentType = "image/jpeg";

            // ������ ����������� � HWP-�����
            bitmap.Save (context.Response.OutputStream,
                ImageFormat.Jpeg);

            // �������
            bitmap.Dispose ();
        }

        public bool IsReusable
        {
            get { return true; }
        }

        Bitmap GenerateImage (int Count, int Digits,
            int Width, int Height, Color ForeColor, Color BackColor1,
            Color BackColor2, Color BorderColor)
        {
            const int BorderWidth = 4;
            const int MinCellWidth = 16;
            const int MinCellHeight = 24;

            // ��������, ��� ���������� ��������
            // ���������� ��� ����������� Count
            int digits = Digits;
            int places = Places (Count);
            if (digits < places)
                digits = places;

            // ���������� ������ ����� ���������� ������
            // � ������ � ������ ����� �����������
            int CellWidth = System.Math.Max (Width / digits,
                MinCellWidth);
            Width = (CellWidth * digits) + BorderWidth;
            Height = System.Math.Max (Height, MinCellHeight);

            // �������� ����������� � ������
            Bitmap bitmap = new Bitmap (Width, Height,
                PixelFormat.Format32bppArgb);

            // �������� ������ � ������, ������� �����
            // �������������� ��� ��������� �����������
            Font font = new Font ("Arial", Height / 2);
            Brush brushForeColor = new SolidBrush (ForeColor);
            Brush brushBorderColor = new SolidBrush (BorderColor);

            // �������� ������� Graphics, ������� ����� ���� �����������
            // ��� ��������� ���������� �����������
            Graphics g = Graphics.FromImage (bitmap);

            // ���������� ������ ������ �������
            g.FillRectangle (brushBorderColor, 0, 0, Width, Height);

            // �������� ������� StringFormat ��� ����������� ������,
            // ��������������� �� ����������� � ���������
            StringFormat format = new StringFormat ();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;

            // ������������� ��������, ������������
            // ��� ��������� ��������� �������� ��������
            int div1 = (int) System.Math.Pow (10, digits);
            int div2 = div1 / 10;

            // ������������ ���� � ���� ��������
            for (int i=0; i<digits; i++) {
                Rectangle rect =
                    new Rectangle (i * CellWidth + BorderWidth,
                    BorderWidth, CellWidth - BorderWidth,
                    Height - (2 * BorderWidth));

                Rectangle top = rect;
                top.Height = (rect.Height / 2) + 1;
                Rectangle bottom = rect;
                bottom.Y += rect.Height / 2;
                bottom.Height = rect.Height / 2;

                Brush brushBackColor1 =
                    new LinearGradientBrush (top, BackColor1,
                    BackColor2, LinearGradientMode.Vertical);

                Brush brushBackColor2 =
                    new LinearGradientBrush (bottom, BackColor2,
                    BackColor1, LinearGradientMode.Vertical);

                g.FillRectangle (brushBackColor2, bottom);
                g.FillRectangle (brushBackColor1, top);

                string num = ((Count % div1) / div2).ToString ();
                g.DrawString (num, font, brushForeColor, rect, format);

                div1 /= 10;
                div2 /= 10;

                brushBackColor1.Dispose ();
                brushBackColor2.Dispose ();
            }

            // ������������ �������� � �������
            font.Dispose ();
            brushForeColor.Dispose ();
            brushBorderColor.Dispose ();
            g.Dispose ();

            return bitmap;
        }

        // ���������� ���������� �������� � ��������� �������� ��������
        int Places (int val)
        {
            int count = 1;
            while (val / 10 > 0) {
                val /= 10;
                count++;
            }
            return count;
        }
    }
}