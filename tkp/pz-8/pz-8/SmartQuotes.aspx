<%@ Import Namespace="System.IO" %>

<html>
  <body>
    <asp:Label ID="Output" RunAt="server" />
  </body>
</html>

<script language="C#" runat="server">
  void Page_Load (Object sender, EventArgs e)
  {
      ArrayList quotes = (ArrayList) Cache["Quotes"];

      if (quotes != null) {
          Random rand = new Random ();
          int index = rand.Next (0, quotes.Count - 1);
          Output.Text = (string) quotes[index];
      }
      else {
          Output.Text = "Server busy";
      }
  }
</script>