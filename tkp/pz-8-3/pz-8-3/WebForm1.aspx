<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="spammers1.WebForm1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:Image ID="Image1" runat="server" Height="391px" Width="761px" 
            ImageUrl="~/SKY_019.JPG" />
    
    </div>
    <asp:Button ID="Button1" runat="server" 
        Text="Приложение 1" Width="220px" 
        BackColor="#00FFCC" Font-Size="X-Large" ForeColor="Red" Height="97px" 
        onclick="Button1_Click" />
        <asp:Button ID="Button2" runat="server" Height="95px" OnClick="Button2_Click" Text="Приложение 2" Width="240px" />
        <asp:Button ID="Button3" runat="server" Height="99px" OnClick="Button3_Click" Text="Приложение 3" Width="300px" />
    </form>
</body>
</html>
