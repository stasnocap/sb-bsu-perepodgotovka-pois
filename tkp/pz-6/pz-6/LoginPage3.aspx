<%@ Register TagPrefix="user" TagName="LoginControl"
  src="LoginControl3.ascx" %>

<html>
  <body>
    <h1>User Control Demo 3</h1>
    <hr>
    <form runat="server">
      <user:LoginControl ID="MyLogin" BackColor="#ccccff"
        OnLogin="OnLoginUser" RunAt="server" />
    </form>
    <hr>
    <h3><asp:Label ID="Output" RunAt="server" /></h3>
  </body>
</html>

<script language="C#" runat="server">
  void OnLoginUser (Object sender, EventArgs e)
  {
      Output.Text = "Hello, " + MyLogin.UserName;
  }
</script>