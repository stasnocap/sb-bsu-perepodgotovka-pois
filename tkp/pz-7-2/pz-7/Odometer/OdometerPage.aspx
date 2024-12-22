<%@ Register TagPrefix="win" Namespace="Wintellect" Assembly="pz_7" %>
<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="OdometerPage.aspx.cs" Inherits="Wintellect.OdometerPage" %>

<html>
  <body>
    <form runat="server">
      <win:Odometer ID="Odometer1" Count="125" Digits="5" BorderColor="yellow"
        Width="224" Height="64" RunAt="server" />
    </form>
  </body>
</html>
