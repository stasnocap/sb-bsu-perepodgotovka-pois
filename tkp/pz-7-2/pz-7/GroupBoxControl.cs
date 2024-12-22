using System.Web.UI;

namespace pz_7
{
    public class GroupBox : Control
    {
        string MyText = "";

        public string Text
        {
            get { return MyText; }
            set { MyText = value; }
        }

        protected override void Render (HtmlTextWriter writer)
        {
            // Output a <fieldset> tag
            writer.WriteBeginTag ("fieldset");
            if (ID != null)
                writer.WriteAttribute ("id", ClientID);
            writer.Write (HtmlTextWriter.TagRightChar);

            // Output a <legend> element
            if (Text.Length > 0) {
                writer.WriteBeginTag ("legend");
                writer.Write (Text);
                writer.WriteEndTag ("legend");
            }

            // Output the content between <fieldset> and </fieldset> tags
            base.Render (writer);

            // Output a </fieldset> tag
            writer.WriteEndTag ("fieldset");
        }
    }
}
